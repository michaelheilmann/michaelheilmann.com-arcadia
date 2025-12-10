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

#include "Arcadia/Visuals/Implementation/BackendContext.h"

static void
Arcadia_Visuals_Implementation_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

static void
Arcadia_Visuals_Implementation_BackendContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContextDispatch* self
  );

static void
Arcadia_Visuals_Implementation_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

static void
Arcadia_Visuals_Implementation_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_BackendContext_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_BackendContext_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_BackendContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.BackendContext", Arcadia_Visuals_Implementation_BackendContext,
                         u8"Arcadia.Visuals.BackendContext", Arcadia_Visuals_BackendContext,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_BackendContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Implementation_BackendContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContextDispatch* self
  )
{ }

static void
Arcadia_Visuals_Implementation_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{/*Intentionally empty.*/}

Arcadia_Visuals_Implementation_ConstantBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createConstantBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createConstantBufferResource, self); }

Arcadia_Visuals_Implementation_FragmentProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createFragmentProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createFragmentProgramResource, self); }

Arcadia_Visuals_Implementation_FrameBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createFrameBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createFrameBufferResource, self); }

Arcadia_Visuals_Implementation_RenderingContextResource*
Arcadia_Visuals_Implementation_BackendContext_createRenderingContextResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createRenderingContextResource, self); }

Arcadia_Visuals_Implementation_MeshResource*
Arcadia_Visuals_Implementation_BackendContext_createMeshResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_VertexBufferResource* vertexBuffer,
    Arcadia_Visuals_Implementation_ProgramResource* program
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createMeshResource, self, vertexBuffer, program); }

Arcadia_Visuals_Implementation_ProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_VertexProgramResource* vertexProgram,
    Arcadia_Visuals_Implementation_FragmentProgramResource* fragmentProgram
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createProgramResource, self, vertexProgram, fragmentProgram); }

Arcadia_Visuals_Implementation_TextureResource*
Arcadia_Visuals_Implementation_BackendContext_createTextureResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createTextureResource, self); }

Arcadia_Visuals_Implementation_VertexBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createVertexBufferResource, self); }

Arcadia_Visuals_Implementation_VertexProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createVertexProgramResource, self); }

Arcadia_Visuals_Implementation_ViewportResource*
Arcadia_Visuals_Implementation_BackendContext_createViewportResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Visuals_Implementation_BackendContext, createViewportResource, self); }
