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
#include "Arcadia/Visuals/DisplayDevice.h"

static void
Arcadia_Visuals_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_DisplayDevice_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.DisplayDevice", Arcadia_Visuals_DisplayDevice,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_DisplayDevice* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_DisplayDevice_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->getCurrentDisplayMode = NULL;
  _self->getAvailableDisplayModes = NULL;
  _self->getId = NULL;
  _self->getName = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_Visuals_DisplayDevice_getBounds
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  )
{
  self->getBounds(thread, self, left, top, right, bottom);
}

Arcadia_Visuals_DisplayMode*
Arcadia_Visuals_DisplayDevice_getCurrentDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  )
{
  return self->getCurrentDisplayMode(thread, self);
}

Arcadia_List*
Arcadia_Visuals_DisplayDevice_getAvailableDisplayModes
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  )
{ 
  return self->getAvailableDisplayModes(thread, self);
}

Arcadia_String*
Arcadia_Visuals_DisplayDevice_getName
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  )
{ return self->getName(thread, self); }

Arcadia_String*
Arcadia_Visuals_DisplayDevice_getId
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  )
{ return self->getId(thread, self); }
