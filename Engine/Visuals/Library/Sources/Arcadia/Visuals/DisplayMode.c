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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/DisplayMode.h"

static void
Arcadia_Visuals_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Visuals_DisplayMode_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.DisplayMode", Arcadia_Visuals_DisplayMode,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_DisplayMode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getHorizontalResolution
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  )
{ return self->getHorizontalResolution(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getVerticalResolution
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  )
{ return self->getVerticalResolution(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getColorDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  )
{ return self->getColorDepth(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getFrequency
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  )
{ return self->getFrequency(thread, self); }

void
Arcadia_Visuals_DisplayMode_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  )
{ self->apply(thread, self); }
