#ifndef LIB_DIESEL_UNITS_H
#define LIB_DIESEL_UNITS_H

#include "_export.h"

// =============================
// Strong typedefs
// =============================

/**
 * @brief Represents a distance in millimeters.
 */
typedef struct { double value; } millimeters_t;

/**
 * @brief Represents a distance in centimeters.
 */
typedef struct { double value; } centimeters_t;

/**
 * @brief Represents a distance in meters.
 */
typedef struct { double value; } meters_t;

/**
 * @brief Represents a distance in kilometers.
 */
typedef struct { double value; } kilometers_t;

/**
 * @brief Represents a distance in inches (imperial).
 */
typedef struct { double value; } inches_t;

/**
 * @brief Represents a distance in feet (imperial).
 */
typedef struct { double value; } feet_t;

/**
 * @brief Represents a distance in yards (imperial).
 */
typedef struct { double value; } yards_t;

/**
 * @brief Represents a distance in miles (imperial).
 */
typedef struct { double value; } miles_t;

/**
 * @brief Represents a mass in milligrams.
 */
typedef struct { double value; } milligrams_t;

/**
 * @brief Represents a mass in grams.
 */
typedef struct { double value; } grams_t;

/**
 * @brief Represents a mass in kilograms.
 */
typedef struct { double value; } kilograms_t;

/**
 * @brief Represents a mass in tonnes (1000 kg).
 */
typedef struct { double value; } tonnes_t;

/**
 * @brief Represents a mass in ounces (imperial).
 */
typedef struct { double value; } ounces_t;

/**
 * @brief Represents a mass in pounds (imperial).
 */
typedef struct { double value; } pounds_t;

/**
 * @brief Represents a mass in stones (imperial).
 */
typedef struct { double value; } stones_t;

/**
 * @brief Represents a mass in short tons (US ton, 2000 lb).
 */
typedef struct { double value; } short_tons_t;

/**
 * @brief Represents a mass in long tons (UK ton, 2240 lb).
 */
typedef struct { double value; } long_tons_t;

/**
 * @brief Represents a volume in milliliters.
 */
typedef struct { double value; } milliliters_t;

/**
 * @brief Represents a volume in liters.
 */
typedef struct { double value; } liters_t;

/**
 * @brief Represents a volume in fluid ounces (imperial).
 */
typedef struct { double value; } fluid_ounces_t;

/**
 * @brief Represents a volume in cups (imperial).
 */
typedef struct { double value; } cups_t;

/**
 * @brief Represents a volume in pints (imperial).
 */
typedef struct { double value; } pints_t;

/**
 * @brief Represents a volume in quarts (imperial).
 */
typedef struct { double value; } quarts_t;

/**
 * @brief Represents a volume in gallons (imperial).
 */
typedef struct { double value; } gallons_t;

/**
 * @brief Represents an angle in radians.
 */
typedef struct { double value; } radians_t;

/**
 * @brief Represents an angle in degrees.
 */
typedef struct { double value; } degrees_t;

/**
 * @brief Represents an angle in gradians.
 */
typedef struct { double value; } gradians_t;

/**
 * @brief Represents an angle in turns (1 turn = 360 degrees).
 */
typedef struct { double value; } turns_t;


/**
 * @brief Represents a speed in meters per second.
 */
typedef struct { double value; } meters_per_second_t;

/**
 * @brief Represents a speed in kilometers per hour.
 */
typedef struct { double value; } kilometers_per_hour_t;

/**
 * @brief Represents a speed in miles per hour.
 */
typedef struct { double value; } miles_per_hour_t;

/**
 * @brief Represents a speed in knots (nautical miles per hour).
 */
typedef struct { double value; } knots_t;

/**
 * @brief Represents a temperature in Celsius.
 */
typedef struct { double value; } celsius_t;

/**
 * @brief Represents a temperature in Fahrenheit.
 */
typedef struct { double value; } fahrenheit_t;

/**
 * @brief Represents a temperature in Kelvin.
 */
typedef struct { double value; } kelvin_t;

/**
 * @brief Represents a digital storage size in bytes.
 */
typedef struct { double value; } bytes_t;

/**
 * @brief Represents a digital storage size in kilobytes.
 */
typedef struct { double value; } kilobytes_t;

/**
 * @brief Represents a digital storage size in megabytes.
 */
typedef struct { double value; } megabytes_t;

/**
 * @brief Represents a digital storage size in gigabytes.
 */
typedef struct { double value; } gigabytes_t;

/**
 * @brief Represents a digital storage size in terabytes.
 */
typedef struct { double value; } terabytes_t;

// =============================
// Conversion Function Declarations
// =============================

/**
 * @brief Convert meters to feet.
 * @param m Distance in meters.
 * @return Distance in feet.
 */
DIESEL_API feet_t meters_to_feet(meters_t m);

/**
 * @brief Convert feet to meters.
 * @param f Distance in feet.
 * @return Distance in meters.
 */
DIESEL_API meters_t feet_to_meters(feet_t f);

/**
 * @brief Convert centimeters to inches.
 * @param c Distance in centimeters.
 * @return Distance in inches.
 */
DIESEL_API inches_t centimeters_to_inches(centimeters_t c);

/**
 * @brief Convert inches to centimeters.
 * @param i Distance in inches.
 * @return Distance in centimeters.
 */
DIESEL_API centimeters_t inches_to_centimeters(inches_t i);

/**
 * @brief Convert miles to kilometers.
 * @param mi Distance in miles.
 * @return Distance in kilometers.
 */
DIESEL_API kilometers_t miles_to_kilometers(miles_t mi);

/**
 * @brief Convert kilometers to miles.
 * @param km Distance in kilometers.
 * @return Distance in miles.
 */
DIESEL_API miles_t kilometers_to_miles(kilometers_t km);

/**
 * @brief Convert pounds to kilograms.
 * @param lb Mass in pounds.
 * @return Mass in kilograms.
 */
DIESEL_API kilograms_t pounds_to_kilograms(pounds_t lb);

/**
 * @brief Convert kilograms to pounds.
 * @param kg Mass in kilograms.
 * @return Mass in pounds.
 */
DIESEL_API pounds_t kilograms_to_pounds(kilograms_t kg);

/**
 * @brief Convert ounces to kilograms.
 * @param oz Mass in ounces.
 * @return Mass in kilograms.
 */
DIESEL_API kilograms_t ounces_to_kilograms(ounces_t oz);

/**
 * @brief Convert kilograms to ounces.
 * @param kg Mass in kilograms.
 * @return Mass in ounces.
 */
DIESEL_API ounces_t kilograms_to_ounces(kilograms_t kg);

/**
 * @brief Convert pounds to short tons (US ton).
 * @param lb Mass in pounds.
 * @return Mass in short tons.
 */
DIESEL_API short_tons_t pounds_to_short_tons(pounds_t lb);

/**
 * @brief Convert short tons to pounds.
 * @param t Mass in short tons.
 * @return Mass in pounds.
 */
DIESEL_API pounds_t short_tons_to_pounds(short_tons_t t);

/**
 * @brief Convert pounds to long tons (UK ton).
 * @param lb Mass in pounds.
 * @return Mass in long tons.
 */
DIESEL_API long_tons_t pounds_to_long_tons(pounds_t lb);

/**
 * @brief Convert long tons to pounds.
 * @param t Mass in long tons.
 * @return Mass in pounds.
 */
DIESEL_API pounds_t long_tons_to_pounds(long_tons_t t);

/**
 * @brief Convert gallons to liters.
 * @param g Volume in gallons.
 * @return Volume in liters.
 */
DIESEL_API liters_t gallons_to_liters(gallons_t g);

/**
 * @brief Convert liters to gallons.
 * @param l Volume in liters.
 * @return Volume in gallons.
 */
DIESEL_API gallons_t liters_to_gallons(liters_t l);

/**
 * @brief Convert pints to liters.
 * @param p Volume in pints.
 * @return Volume in liters.
 */
DIESEL_API liters_t pints_to_liters(pints_t p);

/**
 * @brief Convert liters to pints.
 * @param l Volume in liters.
 * @return Volume in pints.
 */
DIESEL_API pints_t liters_to_pints(liters_t l);

/**
 * @brief Convert degrees to radians.
 * @param d Angle in degrees.
 * @return Angle in radians.
 */
DIESEL_API radians_t degrees_to_radians(degrees_t d);

/**
 * @brief Convert radians to degrees.
 * @param r Angle in radians.
 * @return Angle in degrees.
 */
DIESEL_API degrees_t radians_to_degrees(radians_t r);

/**
 * @brief Convert gradians to degrees.
 * @param g Angle in gradians.
 * @return Angle in degrees.
 */
DIESEL_API degrees_t gradians_to_degrees(gradians_t g);

/**
 * @brief Convert degrees to gradians.
 * @param d Angle in degrees.
 * @return Angle in gradians.
 */
DIESEL_API gradians_t degrees_to_gradians(degrees_t d);

/**
 * @brief Convert degrees to turns.
 * @param d Angle in degrees.
 * @return Angle in turns.
 */
DIESEL_API turns_t degrees_to_turns(degrees_t d);

/**
 * @brief Convert turns to degrees.
 * @param t Angle in turns.
 * @return Angle in degrees.
 */
DIESEL_API degrees_t turns_to_degrees(turns_t t);


/**
 * @brief Convert meters per second to kilometers per hour.
 * @param mps Speed in meters per second.
 * @return Speed in kilometers per hour.
 */
DIESEL_API kilometers_per_hour_t meters_per_second_to_kmh(meters_per_second_t mps);

/**
 * @brief Convert kilometers per hour to meters per second.
 * @param kmh Speed in kilometers per hour.
 * @return Speed in meters per second.
 */
DIESEL_API meters_per_second_t kmh_to_meters_per_second(kilometers_per_hour_t kmh);

/**
 * @brief Convert meters per second to miles per hour.
 * @param mps Speed in meters per second.
 * @return Speed in miles per hour.
 */
DIESEL_API miles_per_hour_t meters_per_second_to_mph(meters_per_second_t mps);

/**
 * @brief Convert miles per hour to meters per second.
 * @param mph Speed in miles per hour.
 * @return Speed in meters per second.
 */
DIESEL_API meters_per_second_t mph_to_meters_per_second(miles_per_hour_t mph);

/**
 * @brief Convert meters per second to knots.
 * @param mps Speed in meters per second.
 * @return Speed in knots.
 */
DIESEL_API knots_t meters_per_second_to_knots(meters_per_second_t mps);

/**
 * @brief Convert knots to meters per second.
 * @param k Speed in knots.
 * @return Speed in meters per second.
 */
DIESEL_API meters_per_second_t knots_to_meters_per_second(knots_t k);

/**
 * @brief Convert Celsius to Fahrenheit.
 * @param c Temperature in Celsius.
 * @return Temperature in Fahrenheit.
 */
DIESEL_API fahrenheit_t celsius_to_fahrenheit(celsius_t c);

/**
 * @brief Convert Fahrenheit to Celsius.
 * @param f Temperature in Fahrenheit.
 * @return Temperature in Celsius.
 */
DIESEL_API celsius_t fahrenheit_to_celsius(fahrenheit_t f);

/**
 * @brief Convert Celsius to Kelvin.
 * @param c Temperature in Celsius.
 * @return Temperature in Kelvin.
 */
DIESEL_API kelvin_t celsius_to_kelvin(celsius_t c);

/**
 * @brief Convert Kelvin to Celsius.
 * @param k Temperature in Kelvin.
 * @return Temperature in Celsius.
 */
DIESEL_API celsius_t kelvin_to_celsius(kelvin_t k);

/**
 * @brief Convert Fahrenheit to Kelvin.
 * @param f Temperature in Fahrenheit.
 * @return Temperature in Kelvin.
 */
DIESEL_API kelvin_t fahrenheit_to_kelvin(fahrenheit_t f);

/**
 * @brief Convert Kelvin to Fahrenheit.
 * @param k Temperature in Kelvin.
 * @return Temperature in Fahrenheit.
 */
DIESEL_API fahrenheit_t kelvin_to_fahrenheit(kelvin_t k);

/**
 * @brief Convert bytes to kilobytes.
 * @param b Size in bytes.
 * @return Size in kilobytes.
 */
DIESEL_API kilobytes_t bytes_to_kilobytes(bytes_t b);

/**
 * @brief Convert kilobytes to bytes.
 * @param kb Size in kilobytes.
 * @return Size in bytes.
 */
DIESEL_API bytes_t kilobytes_to_bytes(kilobytes_t kb);

/**
 * @brief Convert kilobytes to megabytes.
 * @param kb Size in kilobytes.
 * @return Size in megabytes.
 */
DIESEL_API megabytes_t kilobytes_to_megabytes(kilobytes_t kb);

/**
 * @brief Convert megabytes to kilobytes.
 * @param mb Size in megabytes.
 * @return Size in kilobytes.
 */
DIESEL_API kilobytes_t megabytes_to_kilobytes(megabytes_t mb);

/**
 * @brief Convert megabytes to gigabytes.
 * @param mb Size in megabytes.
 * @return Size in gigabytes.
 */
DIESEL_API gigabytes_t megabytes_to_gigabytes(megabytes_t mb);

/**
 * @brief Convert gigabytes to megabytes.
 * @param gb Size in gigabytes.
 * @return Size in megabytes.
 */
DIESEL_API megabytes_t gigabytes_to_megabytes(gigabytes_t gb);

/**
 * @brief Convert gigabytes to terabytes.
 * @param gb Size in gigabytes.
 * @return Size in terabytes.
 */
DIESEL_API terabytes_t gigabytes_to_terabytes(gigabytes_t gb);

/**
 * @brief Convert terabytes to gigabytes.
 * @param tb Size in terabytes.
 * @return Size in gigabytes.
 */
DIESEL_API gigabytes_t terabytes_to_gigabytes(terabytes_t tb);



#endif // LIB_DIESEL_UNITS_H