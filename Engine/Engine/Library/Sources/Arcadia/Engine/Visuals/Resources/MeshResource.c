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
#include "Arcadia/Engine/Visuals/Resources/MeshResource.h"

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResourceDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self
  );

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshResource_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_MeshResource_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.MeshResource", Arcadia_Engine_Visuals_Implementation_MeshResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Engine_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Visuals_Implementation_MeshResource);
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
  self->dirty = Arcadia_Engine_Visuals_Implementation_MeshResource_MeshAmbientColorDirty
              | Arcadia_Engine_Visuals_Implementation_MeshResource_VerticesDirty
              ;
  //
  self->meshAmbientColor = Arcadia_Math_Color4Real32_create4(thread, 1.f, 1.f, 1.f, 1.f);
  //
  Arcadia_LeaveConstructor(Arcadia_Engine_Visuals_Implementation_MeshResource);
}

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResourceDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_MeshResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self
  )
{
  if (self->meshAmbientColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->meshAmbientColor);
  }
}

void
Arcadia_Engine_Visuals_Implementation_MeshResource_setMeshAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_MeshResource* self,
    Arcadia_Math_Color4Real32* meshAmbientColor
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Visuals_Implementation_MeshResource, setMeshAmbientColor, self, meshAmbientColor); }
