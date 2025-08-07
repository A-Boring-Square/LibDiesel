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

/**
 * Represents a specific time of day in hours, minutes, seconds, and milliseconds.
 * Hours: 0-23
 * Minutes: 0-59
 * Seconds: 0-59
 * Milliseconds: 0-999 (optional, can be zero if unused)
 */
typedef struct {
    int hour;       // 0-23
    int minute;     // 0-59
    int second;     // 0-59
    int millisecond;// 0-999 (optional)
} Time;

/**
 * Represents a calendar date.
 * Year: e.g., 2025
 * Month: 1-12
 * Day: 1-31 (should be validated according to month and leap years)
 */
typedef struct {
    int year;   // e.g., 2025
    int month;  // 1-12
    int day;    // 1-31
} Date;

/**
 * Retrieves the current UTC time from an NTP server by querying its IP address.
 *
 * @param ntp_server_ip The IPv4 address of the NTP server as a string.
 * 
 * @return value_t
 *   On success: value_t with kind VALUE_UINT containing the UNIX timestamp (seconds since Jan 1, 1970 UTC).
 *   On failure: value_t with kind VALUE_ERROR describing the failure cause.
 *
 * @note This function uses UDP port 123 to communicate with the NTP server.
 *       Only IPv4 addresses are supported currently.
 */
DIESEL_API value_t get_time_from_time_server(string_t ntp_server_ip);

/**
 * Converts seconds into whole minutes by integer division.
 *
 * @param seconds Number of seconds.
 * @return Number of whole minutes.
 */
DIESEL_API int seconds_to_minutes(int seconds);

/**
 * Converts seconds into whole hours by integer division.
 *
 * @param seconds Number of seconds.
 * @return Number of whole hours.
 */
DIESEL_API int seconds_to_hours(int seconds);

/**
 * Converts minutes into seconds by multiplication.
 *
 * @param minutes Number of minutes.
 * @return Number of seconds.
 */
DIESEL_API int minutes_to_seconds(int minutes);

/**
 * Converts minutes into whole hours by integer division.
 *
 * @param minutes Number of minutes.
 * @return Number of whole hours.
 */
DIESEL_API int minutes_to_hours(int minutes);

/**
 * Converts hours into seconds by multiplication.
 *
 * @param hours Number of hours.
 * @return Number of seconds.
 */
DIESEL_API int hours_to_seconds(int hours);

/**
 * Converts hours into minutes by multiplication.
 *
 * @param hours Number of hours.
 * @return Number of minutes.
 */
DIESEL_API int hours_to_minutes(int hours);

/**
 * Converts hours into whole days by integer division.
 *
 * @param hours Number of hours.
 * @return Number of whole days.
 */
DIESEL_API int hours_to_days(int hours);

/**
 * Converts days into hours by multiplication.
 *
 * @param days Number of days.
 * @return Number of hours.
 */
DIESEL_API int days_to_hours(int days);

/**
 * Converts a UNIX timestamp (seconds since Jan 1, 1970 UTC) to a Time struct in UTC.
 *
 * @param timestamp UNIX timestamp in seconds.
 * @return Time struct representing the UTC time of day (hours, minutes, seconds).
 *
 * @note Milliseconds field is set to zero.
 */
DIESEL_API Time unix_time_to_utc(uint64_t timestamp);

/**
 * Applies a UTC offset (in hours) to a Time struct, adjusting the hour and normalizing it to 0-23.
 *
 * @param time Pointer to the Time struct to modify.
 * @param offset UTC offset in hours (can be negative).
 *
 * @note Does not affect minutes, seconds, or milliseconds.
 */
DIESEL_API void apply_utc_offset(Time* time, int offset);

#endif // LIB_DIESEL_TIME_H
