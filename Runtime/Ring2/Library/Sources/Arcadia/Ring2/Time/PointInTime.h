// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

#if !defined(ARCADIA_RING2_TIME_POINTINTIME_H_INCLUDED)
#define ARCADIA_RING2_TIME_POINTINTIME_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Time/TimeSpecification.h"

Arcadia_declareObjectType(u8"Arcadia.PointInTime", Arcadia_PointInTime,
                          u8"Arcadia.Object");

struct Arcadia_PointInTimeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_PointInTime {
  Arcadia_Object _parent;
  /// Timestamp since the start of the epoch.
  Arcadia_Integer64Value timeStamp;
  // @brief Second of minute [0,60] (60 for leap second).
  Arcadia_Integer8Value second;
  // @brief Minute of hour [0,59].
  Arcadia_Integer8Value minute;
  // @brief Hour of day [0,23].
  Arcadia_Integer8Value hour;
  // @brief Day of month [1,31].
  Arcadia_Integer8Value day;
  // @brief Month of year [0,11].
  Arcadia_Integer8Value month;
  // @brief Year since 1900.
  Arcadia_Integer32Value year;
};


// A year is a leap year if divisible by 4.
// Except if divisible by 100 (e.g., 1900), unless
// It is also divisible by 400 (e.g., 2000).
static inline bool isLeapYear(int year) {
  if (year % 4 != 0) return false;
  if (year % 100 != 0) return true;
  return (year % 100 == 0);
}

// The zero-based month (0,11) and the year.
static inline int getDaysInMonth(int month, int year) {
  static const int nonLeapDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
  static const int leapDays[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
  return isLeapYear(year) ? leapDays[month] : nonLeapDays[month];
}

/// @brief Get the timestamp of now.
/// @param thread A pointer to this thread.
/// @return The timestamp of now.
Arcadia_Integer64Value
Arcadia_TimeStamp_getNow
  (
    Arcadia_Thread* thread
  );

/// @brief Create a point in time.
/// @param thread A pointer to this thread.
/// @param timeStamp The time stamp.
Arcadia_PointInTime*
Arcadia_PointInTime_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value timeStamp
  );

// @brief Get the day of the week [0,6].
// @param thread A pointer to this thread.
// @return The day of the month [0,6].
Arcadia_Integer8Value
Arcadia_PointInTime_getDayOfWeek
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  );

// @brief Get the day of the month [0,30].
// @param thread A pointer to this thread.
// @return The day of the month [0,30].
Arcadia_Integer8Value
Arcadia_PointInTime_getDayOfMonth
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  );

// @brief Get the month of the year [0,11].
// @param thread A pointer to this thread.
// @return The month of the year [0,11].
Arcadia_Integer8Value
Arcadia_PointInTime_getMonth
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  );

// @brief Get the year since the start of the epoch.
// @param thread A pointer to this thread.
// @return The year since the start of the epoch.
Arcadia_Integer32Value
Arcadia_PointInTime_getYear
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  );

#endif // ARCADIA_RING2_TIME_POINTINTIME_H_INCLUDED
