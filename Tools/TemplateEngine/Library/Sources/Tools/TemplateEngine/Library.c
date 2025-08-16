// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include <stdlib.h>
#include <string.h>
#include "Tools/TemplateEngine/Library.h"
#include "Tools/TemplateEngine/Environment.h"

// Return x:Arcadia.Integer8 where x denotes the day of the week [1,7] in UTC time.
static void
getUtcDayOfWeek
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

// Return x:Arcadia.String where x denotes the name of the day of the month [1,31] in UTC time.
static void
getUtcDayOfMonth
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

// Return x:Arcadia.String where x denotes the name of the day of the week name in UTC time.
static void
getUtcDayOfWeekName
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

// Returns x:Arcadia.Integer8 where x denotes the month of the year [1,12] in UTC time.
static void
getUtcMonth
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

// Returns x:Arcadia.String where x denotes the name of the month of the year in UTC time.
static void
getUtcMonthName
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

// [..., 1:Arcadia.Integer8} -> [..., x:Arcadia.Integer32] where x denotes the year in UTC time.
static void
getUtcYear
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
getUtcDayOfWeek
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (0 != numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_PointInTime* pointInTime = Arcadia_PointInTime_create(thread, Arcadia_TimeStamp_getNow(thread));
  Arcadia_Integer8Value v = Arcadia_PointInTime_getDayOfWeek(thread, pointInTime, Arcadia_TimeSpecification_Utc);
  Arcadia_Value_setInteger8Value(targetValue, v + 1);
}


static void
getUtcDayOfMonth
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (0 != numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_PointInTime* pointInTime = Arcadia_PointInTime_create(thread, Arcadia_TimeStamp_getNow(thread));
  Arcadia_Integer8Value v = Arcadia_PointInTime_getDayOfMonth(thread, pointInTime, Arcadia_TimeSpecification_Utc);
  Arcadia_Value_setInteger8Value(targetValue, v + 1);
}

static void
getUtcDayOfWeekName
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (0 != numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value target, argumentValues;
  getUtcDayOfWeek(thread, &target, 0, &argumentValues);
  switch (Arcadia_Value_getInteger8Value(&target)) {
    case 1: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Monday", sizeof(u8"Monday") - 1))));
    } break;
    case 2: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Tuesday", sizeof(u8"Tuesday") - 1))));
    } break;
    case 3: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Wednesday", sizeof(u8"Wednesday") - 1))));
    } break;
    case 4: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Thursday", sizeof(u8"Thursday") - 1))));
    } break;
    case 5: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Friday", sizeof(u8"Friday") - 1))));
    } break;
    case 6: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Saturday", sizeof(u8"Saturday") - 1))));
    } break;
    case 7: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"Sunday", sizeof(u8"Sunday") - 1))));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
getUtcMonth
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (0 != numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_PointInTime* pointInTime = Arcadia_PointInTime_create(thread, Arcadia_TimeStamp_getNow(thread));
  Arcadia_Integer8Value v = Arcadia_PointInTime_getMonth(thread, pointInTime, Arcadia_TimeSpecification_Utc);
  Arcadia_Value_setInteger8Value(targetValue, v + 1);
}


static void
getUtcMonthName
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (0 != numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value target, argumentValues;
  getUtcMonth(thread, &target, 0, &argumentValues);
  switch (Arcadia_Value_getInteger8Value(&target)) {
    case 1: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"January", sizeof(u8"January") - 1))));
    } break;
    case 2: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"February", sizeof(u8"February") - 1))));
    } break;
    case 3: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"March", sizeof(u8"March") - 1))));
    } break;
    case 4: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"April", sizeof(u8"April") - 1))));
    } break;
    case 5: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"May", sizeof(u8"May") - 1))));
    } break;
    case 6: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"June", sizeof(u8"June") - 1))));
    } break;
    case 7: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"July", sizeof(u8"July") - 1))));
    } break;
    case 8: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"August", sizeof(u8"August") - 1))));
    } break;
    case 9: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"September", sizeof(u8"September") - 1))));
    } break;
    case 10: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"October", sizeof(u8"October") - 1))));
    } break;
    case 11: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"November", sizeof(u8"November") - 1))));
    } break;
    case 12: {
      Arcadia_Value_setObjectReferenceValue(targetValue, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"December", sizeof(u8"December") - 1))));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
getUtcYear
  (
    Arcadia_Thread* thread,
    Arcadia_Value* targetValue,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
  if (0 != numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_PointInTime* pointInTime = Arcadia_PointInTime_create(thread, Arcadia_TimeStamp_getNow(thread));
  Arcadia_Integer32Value v = Arcadia_PointInTime_getYear(thread, pointInTime, Arcadia_TimeSpecification_Utc);
  Arcadia_Value_setInteger32Value(targetValue, v + 1900);
}

void
Arcadia_TemplateEngine_registerTimeLibrary
  (
    Arcadia_Thread* thread,
    Environment *environment
  )
{
  Arcadia_Value k, v;

  k = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"dayOfWeek", sizeof(u8"dayOfWeek") - 1))));
  v = Arcadia_Value_makeForeignProcedureValue(&getUtcDayOfWeek);
  Environment_set(thread, environment, k, v);

  k = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"dayOfMonth", sizeof(u8"dayOfMonth") - 1))));
  v = Arcadia_Value_makeForeignProcedureValue(&getUtcDayOfMonth);
  Environment_set(thread, environment, k, v);

  k = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"dayOfWeekName", sizeof(u8"dayOfWeekName") - 1))));
  v = Arcadia_Value_makeForeignProcedureValue(&getUtcDayOfWeekName);
  Environment_set(thread, environment, k, v);

  k = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"month", sizeof(u8"month") - 1))));
  v = Arcadia_Value_makeForeignProcedureValue(&getUtcMonth);
  Environment_set(thread, environment, k, v);

  k = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"monthName", sizeof(u8"monthName") - 1))));
  v = Arcadia_Value_makeForeignProcedureValue(&getUtcMonthName);
  Environment_set(thread, environment, k, v);

  k = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"year", sizeof(u8"year") - 1))));
  v = Arcadia_Value_makeForeignProcedureValue(&getUtcYear);
  Environment_set(thread, environment, k, v);
}
