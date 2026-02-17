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

#define ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/NodeFactory.h"

#include "Arcadia/Audials/Implementation/BackendContext.h"
#include "Arcadia/Audials/Implementation/Nodes/SoundSourceNode.h"

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self
  );

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactoryDispatch* self
  );

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self
  );

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self
  );

static Arcadia_Engine_Audials_Implementation_SoundSourceNode*
Arcadia_Engine_Audials_Implementation_NodeFactory_createSoundSourceNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self,
    Arcadia_Engine_Audials_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Audials_Implementation_NodeFactory_construct,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Audials_Implementation_NodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Audials_Implementation_NodeFactory_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.Implementation.NodeFactory", Arcadia_Engine_Audials_Implementation_NodeFactory,
                         u8"Arcadia.Engine.Audials.NodeFactory", Arcadia_Engine_Audials_NodeFactory,
                         &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Audials_Implementation_NodeFactory_getType(thread);
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

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactoryDispatch* self
  )
{
  ((Arcadia_Engine_Audials_NodeFactoryDispatch*)self)->createSoundSourceNode = (Arcadia_Engine_Audials_SoundSourceNode * (*)(Arcadia_Thread*, Arcadia_Engine_Audials_NodeFactory*, Arcadia_Engine_Audials_BackendContext*)) & Arcadia_Engine_Audials_Implementation_NodeFactory_createSoundSourceNodeImpl;
}

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Audials_Implementation_NodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self
  )
{/*Intentionally empty.*/}

static Arcadia_Engine_Audials_Implementation_SoundSourceNode*
Arcadia_Engine_Audials_Implementation_NodeFactory_createSoundSourceNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Audials_Implementation_NodeFactory* self,
    Arcadia_Engine_Audials_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Engine_Audials_Implementation_SoundSourceNode_create(thread, backendContext); }

Arcadia_Engine_Audials_Implementation_NodeFactory*
Arcadia_Engine_Audials_Implementation_NodeFactory_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Audials_Implementation_NodeFactory);
}
