#include "units.h"

// =============================
// Distance Conversions
// =============================
DIESEL_API feet_t meters_to_feet(meters_t m) { return (feet_t){ m.value * 3.280839895 }; }
DIESEL_API meters_t feet_to_meters(feet_t f) { return (meters_t){ f.value * 0.3048 }; }
DIESEL_API inches_t centimeters_to_inches(centimeters_t c) { return (inches_t){ c.value * 0.3937007874 }; }
DIESEL_API centimeters_t inches_to_centimeters(inches_t i) { return (centimeters_t){ i.value * 2.54 }; }
DIESEL_API kilometers_t miles_to_kilometers(miles_t mi) { return (kilometers_t){ mi.value * 1.609344 }; }
DIESEL_API miles_t kilometers_to_miles(kilometers_t km) { return (miles_t){ km.value * 0.6213711922 }; }

// =============================
// Mass Conversions
// =============================
DIESEL_API kilograms_t pounds_to_kilograms(pounds_t lb) { return (kilograms_t){ lb.value * 0.45359237 }; }
DIESEL_API pounds_t kilograms_to_pounds(kilograms_t kg) { return (pounds_t){ kg.value * 2.2046226218 }; }
DIESEL_API kilograms_t ounces_to_kilograms(ounces_t oz) { return (kilograms_t){ oz.value * 0.028349523125 }; }
DIESEL_API ounces_t kilograms_to_ounces(kilograms_t kg) { return (ounces_t){ kg.value * 35.27396195 }; }
DIESEL_API short_tons_t pounds_to_short_tons(pounds_t lb) { return (short_tons_t){ lb.value / 2000.0 }; }
DIESEL_API pounds_t short_tons_to_pounds(short_tons_t t) { return (pounds_t){ t.value * 2000.0 }; }
DIESEL_API long_tons_t pounds_to_long_tons(pounds_t lb) { return (long_tons_t){ lb.value / 2240.0 }; }
DIESEL_API pounds_t long_tons_to_pounds(long_tons_t t) { return (pounds_t){ t.value * 2240.0 }; }

// =============================
// Volume Conversions
// =============================
DIESEL_API liters_t gallons_to_liters(gallons_t g) { return (liters_t){ g.value * 3.785411784 }; }
DIESEL_API gallons_t liters_to_gallons(liters_t l) { return (gallons_t){ l.value * 0.2641720524 }; }
DIESEL_API liters_t pints_to_liters(pints_t p) { return (liters_t){ p.value * 0.473176473 }; }
DIESEL_API pints_t liters_to_pints(liters_t l) { return (pints_t){ l.value * 2.1133764189 }; }

// =============================
// Angle Conversions
// =============================
DIESEL_API radians_t degrees_to_radians(degrees_t d) { return (radians_t){ d.value * 0.017453292519943295 }; }
DIESEL_API degrees_t radians_to_degrees(radians_t r) { return (degrees_t){ r.value * 57.29577951308232 }; }
DIESEL_API degrees_t gradians_to_degrees(gradians_t g) { return (degrees_t){ g.value * 0.9 }; }
DIESEL_API gradians_t degrees_to_gradians(degrees_t d) { return (gradians_t){ d.value * 1.111111111111111 }; }
DIESEL_API turns_t degrees_to_turns(degrees_t d) { return (turns_t){ d.value / 360.0 }; }
DIESEL_API degrees_t turns_to_degrees(turns_t t) { return (degrees_t){ t.value * 360.0 }; }

// =============================
// Time Conversions
// =============================
DIESEL_API milliseconds_t seconds_to_milliseconds(seconds_t s) { return (milliseconds_t){ s.value * 1000.0 }; }
DIESEL_API seconds_t milliseconds_to_seconds(milliseconds_t ms) { return (seconds_t){ ms.value / 1000.0 }; }
DIESEL_API minutes_t seconds_to_minutes(seconds_t s) { return (minutes_t){ s.value / 60.0 }; }
DIESEL_API seconds_t minutes_to_seconds(minutes_t m) { return (seconds_t){ m.value * 60.0 }; }
DIESEL_API hours_t seconds_to_hours(seconds_t s) { return (hours_t){ s.value / 3600.0 }; }
DIESEL_API seconds_t hours_to_seconds(hours_t h) { return (seconds_t){ h.value * 3600.0 }; }
DIESEL_API days_t hours_to_days(hours_t h) { return (days_t){ h.value / 24.0 }; }
DIESEL_API hours_t days_to_hours(days_t d) { return (hours_t){ d.value * 24.0 }; }

// =============================
// Speed Conversions
// =============================
DIESEL_API kilometers_per_hour_t meters_per_second_to_kmh(meters_per_second_t mps) { return (kilometers_per_hour_t){ mps.value * 3.6 }; }
DIESEL_API meters_per_second_t kmh_to_meters_per_second(kilometers_per_hour_t kmh) { return (meters_per_second_t){ kmh.value / 3.6 }; }
DIESEL_API miles_per_hour_t meters_per_second_to_mph(meters_per_second_t mps) { return (miles_per_hour_t){ mps.value * 2.2369362921 }; }
DIESEL_API meters_per_second_t mph_to_meters_per_second(miles_per_hour_t mph) { return (meters_per_second_t){ mph.value * 0.44704 }; }
DIESEL_API knots_t meters_per_second_to_knots(meters_per_second_t mps) { return (knots_t){ mps.value * 1.9438444924 }; }
DIESEL_API meters_per_second_t knots_to_meters_per_second(knots_t k) { return (meters_per_second_t){ k.value * 0.5144444444 }; }

// =============================
// Temperature Conversions
// =============================
DIESEL_API fahrenheit_t celsius_to_fahrenheit(celsius_t c) { return (fahrenheit_t){ c.value * 9.0/5.0 + 32.0 }; }
DIESEL_API celsius_t fahrenheit_to_celsius(fahrenheit_t f) { return (celsius_t){ (f.value - 32.0) * 5.0/9.0 }; }
DIESEL_API kelvin_t celsius_to_kelvin(celsius_t c) { return (kelvin_t){ c.value + 273.15 }; }
DIESEL_API celsius_t kelvin_to_celsius(kelvin_t k) { return (celsius_t){ k.value - 273.15 }; }
DIESEL_API kelvin_t fahrenheit_to_kelvin(fahrenheit_t f) { return celsius_to_kelvin(fahrenheit_to_celsius(f)); }
DIESEL_API fahrenheit_t kelvin_to_fahrenheit(kelvin_t k) { return celsius_to_fahrenheit(kelvin_to_celsius(k)); }

// =============================
// Digital Storage Conversions
// =============================
DIESEL_API kilobytes_t bytes_to_kilobytes(bytes_t b) { return (kilobytes_t){ b.value / 1024.0 }; }
DIESEL_API bytes_t kilobytes_to_bytes(kilobytes_t kb) { return (bytes_t){ kb.value * 1024.0 }; }
DIESEL_API megabytes_t kilobytes_to_megabytes(kilobytes_t kb) { return (megabytes_t){ kb.value / 1024.0 }; }
DIESEL_API kilobytes_t megabytes_to_kilobytes(megabytes_t mb) { return (kilobytes_t){ mb.value * 1024.0 }; }
DIESEL_API gigabytes_t megabytes_to_gigabytes(megabytes_t mb) { return (gigabytes_t){ mb.value / 1024.0 }; }
DIESEL_API megabytes_t gigabytes_to_megabytes(gigabytes_t gb) { return (megabytes_t){ gb.value * 1024.0 }; }
DIESEL_API terabytes_t gigabytes_to_terabytes(gigabytes_t gb) { return (terabytes_t){ gb.value / 1024.0 }; }
DIESEL_API gigabytes_t terabytes_to_gigabytes(terabytes_t tb) { return (gigabytes_t){ tb.value * 1024.0 }; }
