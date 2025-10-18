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
#include "Arcadia/Visuals/BackendContext.h"

static void
Arcadia_Visuals_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  );

static void
Arcadia_Visuals_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) &Arcadia_Visuals_BackendContext_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_BackendContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.BackendContext", Arcadia_Visuals_BackendContext,
                         u8"Arcadia.Engine.BackendContext", Arcadia_Engine_BackendContext,
                         &_typeOperations);

static void
Arcadia_Visuals_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_BackendContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->windows = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->createIcon = NULL;
  self->createWindow = NULL;
  self->getDisplayDevices = NULL;
  self->update = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  )
{
  if (self->windows) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->windows);
  }
}

Arcadia_Visuals_Icon*
Arcadia_Visuals_BackendContext_createIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self,
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  )
{ return self->createIcon(thread, self, pixelBuffer); }

Arcadia_Visuals_Window*
Arcadia_Visuals_BackendContext_createWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  )
{ return self->createWindow(thread, self); }

Arcadia_List*
Arcadia_Visuals_BackendContext_getDisplayDevices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  )
{ return self->getDisplayDevices(thread, self); }

void
Arcadia_Visuals_BackendContext_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  )
{ self->update(thread, self); }
