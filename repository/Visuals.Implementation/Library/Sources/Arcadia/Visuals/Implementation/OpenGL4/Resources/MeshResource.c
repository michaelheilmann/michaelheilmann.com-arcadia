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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MaterialResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextNode
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setMeshAmbientColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Color4Real32* meshAmbientColor
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MeshResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.MeshResource", Arcadia_Visuals_Implementation_OpenGL4_MeshResource,
                         u8"Arcadia.Visuals.Implementation.MeshResource", Arcadia_Visuals_Implementation_MeshResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_MeshResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->constantBuffer = NULL;
  self->vertexBuffer = NULL;

  Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext =
    Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_OpenGL4_BackendContext_getType(thread));

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Object* o;

    o = (Arcadia_Object*)Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource(thread, (Arcadia_Visuals_Implementation_BackendContext*)backendContext);
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->constantBuffer = (Arcadia_Visuals_Implementation_OpenGL4_ConstantBufferResource*)o;
    
    o = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource_getType(thread));
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->vertexBuffer = (Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource*)o;

    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->vertexBuffer) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);
      self->vertexBuffer = NULL;
    }
    if (self->constantBuffer) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
      self->constantBuffer = NULL;
    }
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}


static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_MeshResourceDispatch*)self)->setMeshAmbientColor = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_MeshResource*, Arcadia_Math_Color4Real32*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setMeshAmbientColorImpl;

  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_RenderingContextResource*)) & Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  assert(NULL == self->constantBuffer);
  assert(NULL == self->vertexBuffer);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self
  )
{
  if (self->constantBuffer) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->constantBuffer);
    self->constantBuffer = NULL;
  }
  if (self->vertexBuffer) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);
    self->vertexBuffer = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextResource
  )
{
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->vertexBuffer);

  if (((Arcadia_Visuals_Implementation_MeshResource*)self)->dirty & (Arcadia_Visuals_Implementation_MeshResource_MeshAmbientColorDirty)) {
    Arcadia_Visuals_Implementation_ConstantBufferResource_clear(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->constantBuffer);
    // @todo We need to ability to do sub-range updates:
    // There is no need to rewrite every value if only one value is dirty.
    Arcadia_Visuals_Implementation_ConstantBufferResource_writeColor4Real32(thread, (Arcadia_Visuals_Implementation_ConstantBufferResource*)self->constantBuffer, ((Arcadia_Visuals_Implementation_MeshResource*)self)->meshAmbientColor);
    ((Arcadia_Visuals_Implementation_MeshResource*)self)->dirty &= ~Arcadia_Visuals_Implementation_MeshResource_MeshAmbientColorDirty;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_setMeshAmbientColorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MeshResource* self,
    Arcadia_Math_Color4Real32* meshAmbientColor
  )
{
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(meshAmbientColor);
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)((Arcadia_Visuals_Implementation_MeshResource*)self)->meshAmbientColor, &t)) {
    Arcadia_Math_Color4Real32_assign(thread, ((Arcadia_Visuals_Implementation_MeshResource*)self)->meshAmbientColor, meshAmbientColor);
    ((Arcadia_Visuals_Implementation_MeshResource*)self)->dirty |= Arcadia_Visuals_Implementation_MeshResource_MeshAmbientColorDirty;
  }
}

Arcadia_Visuals_Implementation_OpenGL4_MeshResource*
Arcadia_Visuals_Implementation_OpenGL4_MeshResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_OpenGL4_VertexBufferResource* vertexBuffer
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (vertexBuffer) Arcadia_ValueStack_pushObjectReferenceValue(thread, vertexBuffer); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_MeshResource);
}
