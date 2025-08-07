#ifndef LIB_DIESEL_TIME_H
#define LIB_DIESEL_TIME_H

#include <time.h>
#include "types.h" // for value_t, error_t, etc.
#include "_export.h"

#define UTC_PLUS_0  0
#define UTC_PLUS_1  1
#define UTC_PLUS_2  2
#define UTC_PLUS_3  3
#define UTC_PLUS_4  4
#define UTC_PLUS_5  5
#define UTC_PLUS_6  6
#define UTC_PLUS_7  7
#define UTC_PLUS_8  8
#define UTC_PLUS_9  9
#define UTC_PLUS_10 10
#define UTC_PLUS_11 11
#define UTC_PLUS_12 12
#define UTC_PLUS_13 13
#define UTC_PLUS_14 14


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
DIESEL_API value_t get_time_from_time_server(string_t ntp_server_ip);

DIESEL_API int seconds_to_minutes(int seconds);

DIESEL_API int seconds_to_hours(int seconds);

DIESEL_API int minutes_to_seconds(int minutes);

DIESEL_API int minutes_to_hours(int minutes);

DIESEL_API int hours_to_seconds(int hours);

DIESEL_API int hours_to_minutes(int hours);

DIESEL_API int hours_to_days(int hours);

DIESEL_API int days_to_hours(int days);

DIESEL_API Time unix_time_to_utc(uint64_t timestamp);

DIESEL_API apply_utc_offset(Time* time, int offset);

#endif // LIB_DIESEL_TIME_H
