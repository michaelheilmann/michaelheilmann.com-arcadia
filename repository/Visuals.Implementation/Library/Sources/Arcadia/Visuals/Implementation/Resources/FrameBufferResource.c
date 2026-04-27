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

#include "Arcadia/Visuals/Implementation/Resources/FrameBufferResource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_FrameBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_FrameBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_FrameBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  );

static void
Arcadia_Visuals_Implementation_FrameBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_FrameBufferResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_FrameBufferResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_FrameBufferResource_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Visuals_Implementation_FrameBufferResource_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.FrameBufferResource", Arcadia_Visuals_Implementation_FrameBufferResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_FrameBufferResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Visuals_Implementation_FrameBufferResource);
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_LeaveConstructor(Arcadia_Visuals_Implementation_FrameBufferResource);
}

static void
Arcadia_Visuals_Implementation_FrameBufferResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResourceDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_FrameBufferResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_FrameBufferResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Visuals_Implementation_FrameBufferResource_activate
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_FrameBufferResource, activate, self); }

void
Arcadia_Visuals_Implementation_FrameBufferResource_deactivate
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_FrameBufferResource, activate, self); }

void
Arcadia_Visuals_Implementation_FrameBufferResource_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_FrameBufferResource, setSize, self, width, height); }

void
Arcadia_Visuals_Implementation_FrameBufferResource_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FrameBufferResource* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ Arcadia_VirtualCall(Arcadia_Visuals_Implementation_FrameBufferResource, getSize, self, width, height); }
