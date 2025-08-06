#include "time.h"
#include "_export.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <unistd.h>
    #include <string.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

#define NTP_TIMESTAMP_DELTA 2208988800U

EXPORT value_t get_time_from_time_server(const char *ntp_server_ip) {
#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        return (value_t){
            .kind = VALUE_ERROR,
            .e = { "WSAStartup failed", "EWSA", "get_time_from_time_server" }
        };
    }
#endif

    int sockfd;
    struct sockaddr_in server_addr;
    uint8_t buffer[48] = {0};

    buffer[0] = 0x1B; // LI = 0, VN = 3, Mode = 3

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
#ifdef _WIN32
        WSACleanup();
#endif
        return (value_t){
            .kind = VALUE_ERROR,
            .e = { "Failed to create socket", "ESOCKET", "get_time_from_time_server" }
        };
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(123);
    if (inet_pton(AF_INET, ntp_server_ip, &server_addr.sin_addr) <= 0) {
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
        return (value_t){
            .kind = VALUE_ERROR,
            .e = { "Invalid IP address", "EADDR", "get_time_from_time_server" }
        };
    }

    if (sendto(sockfd, buffer, sizeof(buffer), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
        return (value_t){
            .kind = VALUE_ERROR,
            .e = { "Failed to send NTP request", "ESEND", "get_time_from_time_server" }
        };
    }

    struct sockaddr_in src_addr;
#ifdef _WIN32
    int addr_len = sizeof(src_addr);
#else
    socklen_t addr_len = sizeof(src_addr);
#endif

    if (recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&src_addr, &addr_len) < 0) {
#ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
#else
        close(sockfd);
#endif
        return (value_t){
            .kind = VALUE_ERROR,
            .e = { "Failed to receive NTP response", "ERECV", "get_time_from_time_server" }
        };
    }

#ifdef _WIN32
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif

    // Extract seconds since 1900
    uint32_t seconds_since_1900 = (buffer[40] << 24) | (buffer[41] << 16) |
                                  (buffer[42] << 8)  | (buffer[43]);

    uint32_t unix_time = seconds_since_1900 - NTP_TIMESTAMP_DELTA;

    return (value_t){
        .kind = VALUE_UINT,
        .u = unix_time
    };
}
