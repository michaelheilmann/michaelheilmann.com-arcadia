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

#include "Module/Visuals/Linux/DisplayMode.h"

#include "Module/Visuals/Include.h"
#include "Module/Visuals/Linux/DisplayDevice.h"

static void
Arcadia_Visuals_Linux_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Linux_DisplayMode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getHorizontalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getVerticalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getColorDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getFrequencyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_DisplayMode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Linux_DisplayMode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.DisplayMode", Arcadia_Visuals_Linux_DisplayMode, u8"Arcadia.Visuals.DisplayMode", Arcadia_Visuals_DisplayMode, &_typeOperations);

static void
Arcadia_Visuals_Linux_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_DisplayMode* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_DisplayMode_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (5 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->device = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Visuals_Linux_DisplayDevice_getType(thread));
  _self->horizontalResolution = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[1]);
  _self->verticalResolution = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[2]);
  _self->colorDepth = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[3]);
  _self->frequency = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[4]);

  ((Arcadia_Visuals_DisplayMode*)_self)->getHorizontalResolution = (Arcadia_Integer32Value(*)(Arcadia_Thread*,Arcadia_Visuals_DisplayMode*)) & Arcadia_Visuals_Linux_DisplayMode_getHorizontalResolutionImpl;
  ((Arcadia_Visuals_DisplayMode*)_self)->getVerticalResolution = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Linux_DisplayMode_getVerticalResolutionImpl;
  ((Arcadia_Visuals_DisplayMode*)_self)->getColorDepth = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Linux_DisplayMode_getColorDepthImpl;
  ((Arcadia_Visuals_DisplayMode*)_self)->getFrequency = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Linux_DisplayMode_getFrequencyImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Visuals_Linux_DisplayMode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{
  if (self->device) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->device);
  }
}

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getHorizontalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->horizontalResolution; }

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getVerticalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->verticalResolution; }

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getColorDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->colorDepth; }

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getFrequencyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->frequency; }

Arcadia_Visuals_Linux_DisplayMode*
Arcadia_Visuals_Linux_DisplayMode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* device,
    Arcadia_Integer32Value horizontalResolution,
    Arcadia_Integer32Value verticalResolution,
    Arcadia_Integer32Value colorDepth,
    Arcadia_Integer32Value frequency
  )
{
  Arcadia_Value argumentValues[] = {
    device ? Arcadia_Value_makeObjectReferenceValue(device) : Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    Arcadia_Value_makeInteger32Value(horizontalResolution),
    Arcadia_Value_makeInteger32Value(verticalResolution),
    Arcadia_Value_makeInteger32Value(colorDepth),
    Arcadia_Value_makeInteger32Value(frequency),
  };
  Arcadia_Visuals_Linux_DisplayMode* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_DisplayMode_getType(thread), 5, &argumentValues[0]);
  return self;
}
