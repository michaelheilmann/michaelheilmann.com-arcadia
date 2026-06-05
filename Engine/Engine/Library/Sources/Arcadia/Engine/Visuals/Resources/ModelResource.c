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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Visuals/Resources/ModelResource.h"

#include <assert.h>

static void
Arcadia_Engine_Visuals_Implementation_ModelResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResource* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ModelResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResourceDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_ModelResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_ModelResource_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_ModelResource_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_ModelResource_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.ModelResource", Arcadia_Engine_Visuals_Implementation_ModelResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Engine_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_ModelResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResource* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Visuals_Implementation_ModelResource);
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
  //
  self->dirty = Arcadia_Engine_Visuals_Implementation_ModelResource_LocalToWorldMatrixDirty;
  //
  self->localToWorldMatrix = Arcadia_Math_Matrix4Real32_create(thread);
  Arcadia_Math_Matrix4Real32_setIdentity(thread, self->localToWorldMatrix);
  //
  Arcadia_LeaveConstructor(Arcadia_Engine_Visuals_Implementation_ModelResource);
}


static void
Arcadia_Engine_Visuals_Implementation_ModelResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResourceDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_ModelResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResource* self
  )
{
  if (self->localToWorldMatrix) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->localToWorldMatrix);
  }
}

void
Arcadia_Engine_Visuals_Implementation_ModelResource_setLocalToWorldMatrix
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_ModelResource* self,
    Arcadia_Math_Matrix4Real32* localToWorldMatrix
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Visuals_Implementation_ModelResource, setLocalToWorldMatrix, self, localToWorldMatrix); }
