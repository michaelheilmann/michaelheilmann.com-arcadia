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

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/MaterialResource.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/TextureResource.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h"

#include <assert.h>

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.MaterialResource", Arcadia_Visuals_Implementation_OpenGL4_MaterialResource,
                         u8"Arcadia.Visuals.Implementation.MaterialResource", Arcadia_Visuals_Implementation_MaterialResource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (4 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 4);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->ambientColorTexture = NULL;
  self->program = NULL;

  self->ambientColorSource = Arcadia_ValueStack_getInteger32Value(thread, 3);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Object* o;

    o = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_Visuals_Implementation_OpenGL4_TextureResource_getType(thread));
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->ambientColorTexture = (Arcadia_Visuals_Implementation_OpenGL4_TextureResource*)o;

    o = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_OpenGL4_ProgramResource_getType(thread));
    Arcadia_Visuals_Implementation_Resource_ref(thread, (Arcadia_Visuals_Implementation_Resource*)o);
    self->program = (Arcadia_Visuals_Implementation_OpenGL4_ProgramResource*)o; 

   Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (self->program) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);
      self->program = NULL;
    }
    if (self->ambientColorTexture) {
      Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->ambientColorTexture);
      self->ambientColorTexture = NULL;
    }
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}


static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResourceDispatch* self
  )
{
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->load = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_loadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unload = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_unloadImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->unlink = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*)) & Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_unlinkImpl;
  ((Arcadia_Visuals_Implementation_ResourceDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Visuals_Implementation_Resource*, Arcadia_Visuals_Implementation_EnterPassResource*)) & Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_renderImpl;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  )
{
  assert(NULL == self->ambientColorTexture);
  assert(NULL == self->program);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_loadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  )
{
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->ambientColorTexture);
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_unloadImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_unlinkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self
  )
{
  if (self->ambientColorTexture) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->ambientColorTexture);
    self->ambientColorTexture = NULL;
  }
  if (self->program) {
    Arcadia_Visuals_Implementation_Resource_unref(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);
    self->program = NULL;
  }
  ((Arcadia_Visuals_Implementation_Resource*)self)->context = NULL;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_MaterialResource* self,
    Arcadia_Visuals_Implementation_EnterPassResource* renderingContextNode
  )
{
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->ambientColorTexture);
  Arcadia_Visuals_Implementation_Resource_load(thread, (Arcadia_Visuals_Implementation_Resource*)self->program);
}

Arcadia_Visuals_Implementation_OpenGL4_MaterialResource*
Arcadia_Visuals_Implementation_OpenGL4_MaterialResource_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_BackendContext* backendContext,
    Arcadia_Visuals_Implementation_MaterialResource_AmbientColorSource ambientColorSource,
    Arcadia_Visuals_Implementation_OpenGL4_TextureResource* ambientColorTexture,
    Arcadia_Visuals_Implementation_OpenGL4_ProgramResource* program
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushInteger32Value(thread, ambientColorSource);
  if (ambientColorTexture) Arcadia_ValueStack_pushObjectReferenceValue(thread, ambientColorTexture); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (program) Arcadia_ValueStack_pushObjectReferenceValue(thread, program); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_MaterialResource);
}
