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

#include "Arcadia/Visuals/Implementation/BackendContext.h"

static void
Arcadia_Visuals_Implementation_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
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
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_BackendContext_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_BackendContext_destructImpl,
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

  self->createFragmentProgramResource = NULL;
  self->createProgramResource = NULL;
  self->createVertexBufferResource = NULL;
  self->createVertexProgramResource = NULL;
  self->createViewportResource = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

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

Arcadia_Visuals_Implementation_FragmentProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createFragmentProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ return self->createFragmentProgramResource(thread, self); }

Arcadia_Visuals_Implementation_ProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self,
    Arcadia_Visuals_Implementation_VertexProgramResource* vertexProgram,
    Arcadia_Visuals_Implementation_FragmentProgramResource* fragmentProgram
  )
{ return self->createProgramResource(thread, self, vertexProgram, fragmentProgram); }

Arcadia_Visuals_Implementation_VertexBufferResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexBufferResource
(
  Arcadia_Thread* thread,
  Arcadia_Visuals_Implementation_BackendContext* self
)
{ return self->createVertexBufferResource(thread, self); }

Arcadia_Visuals_Implementation_VertexProgramResource*
Arcadia_Visuals_Implementation_BackendContext_createVertexProgramResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ return self->createVertexProgramResource(thread, self); }

Arcadia_Visuals_Implementation_ViewportResource*
Arcadia_Visuals_Implementation_BackendContext_createViewportResource
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_BackendContext* self
  )
{ return self->createViewportResource(thread, self); }
