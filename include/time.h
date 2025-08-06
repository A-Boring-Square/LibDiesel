#ifndef LIB_DIESEL_TIME_H
#define LIB_DIESEL_TIME_H

#include <time.h>
#include "types.h" // for value_t, error_t, etc.
#include "_export.h"

typedef struct {
    int hour;       // 0-23
    int minute;     // 0-59
    int second;     // 0-59
    int millisecond;// 0-999 (optional, can be 0 if unused)
} Time;

typedef struct {
    int year;   // e.g. 2025
    int month;  // 1-12
    int day;    // 1-31 (validate per month)
} Date;


// Attempts to get the current atomic time (UTC) from an NTP server.
// Returns:
// - value_t of kind VALUE_UINT with the timestamp on success
// - value_t of kind VALUE_ERROR on failure
EXPORT value_t get_time_from_time_server(const char *ntp_server_ip);

#endif // LIB_DIESEL_TIME_H
