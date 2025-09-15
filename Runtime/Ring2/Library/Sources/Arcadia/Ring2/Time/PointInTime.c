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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Time/PointInTime.h"

#include <time.h>
#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"

Arcadia_Integer64Value
Arcadia_TimeStamp_getNow
  (
    Arcadia_Thread* thread
  )
{
  time_t t;
  time(&t);
  return t;
}

static void
Arcadia_PointInTime_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_PointInTime_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.PointInTime", Arcadia_PointInTime,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_PointInTime_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_PointInTime* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_PointInTime_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->timeStamp = Arcadia_ValueStack_getInteger64Value(thread, 1);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

Arcadia_PointInTime*
Arcadia_PointInTime_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value timeStamp
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger64Value(thread, timeStamp);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_PointInTime);
}

Arcadia_Integer8Value
Arcadia_PointInTime_getDayOfWeek
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  )
{
  switch (timeSpecification) {
    case Arcadia_TimeSpecification_LocalTime: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (localtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!localtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_wday;
    } break;
    case Arcadia_TimeSpecification_Utc: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (gmtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!gmtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_wday;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

Arcadia_Integer8Value
Arcadia_PointInTime_getDayOfMonth
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  )
{
  switch (timeSpecification) {
    case Arcadia_TimeSpecification_LocalTime: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (localtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!localtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_mday - 1;
    } break;
    case Arcadia_TimeSpecification_Utc: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (gmtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!gmtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_mday - 1;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

Arcadia_Integer8Value
Arcadia_PointInTime_getMonth
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  )
{
  switch (timeSpecification) {
    case Arcadia_TimeSpecification_LocalTime: {
      time_t t1 = self->timeStamp;
      struct tm t2;
  #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (localtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
  #else
      if (!localtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
  #endif
      return t2.tm_mon;
    } break;
    case Arcadia_TimeSpecification_Utc: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (gmtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!gmtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_mon;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

Arcadia_Integer32Value
Arcadia_PointInTime_getYear
  (
    Arcadia_Thread* thread,
    Arcadia_PointInTime* self,
    Arcadia_TimeSpecification timeSpecification
  )
{
  switch (timeSpecification) {
    case Arcadia_TimeSpecification_LocalTime: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (localtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!localtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_year;
    } break;
    case Arcadia_TimeSpecification_Utc: {
      time_t t1 = self->timeStamp;
      struct tm t2;
    #if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
      if (gmtime_s(&t2, &t1)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #else
      if (!gmtime_r(&t1, &t2)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    #endif
      return t2.tm_year;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}
