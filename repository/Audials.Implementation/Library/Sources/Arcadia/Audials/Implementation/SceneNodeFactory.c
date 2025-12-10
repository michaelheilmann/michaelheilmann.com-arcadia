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
#include "Arcadia/Audials/Implementation/SceneNodeFactory.h"

#include "Arcadia/Audials/Implementation/BackendContext.h"
#include "Arcadia/Audials/Implementation/Scene/SoundSourceNode.h"

static void
Arcadia_Audials_Implementation_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self
  );

static void
Arcadia_Audials_Implementation_SceneNodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactoryDispatch* self
  );

static void
Arcadia_Audials_Implementation_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self
  );

static void
Arcadia_Audials_Implementation_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self
  );

static Arcadia_Audials_Implementation_Scene_SoundSourceNode*
Arcadia_Audials_Implementation_SceneNodeFactory_createSoundSourceNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self,
    Arcadia_Audials_Implementation_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Audials_Implementation_SceneNodeFactory_construct,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Audials_Implementation_SceneNodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_Implementation_SceneNodeFactory_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcardia.Audials.Implementation.SceneNodeFactory", Arcadia_Audials_Implementation_SceneNodeFactory,
                         u8"Arcadia.Audials.SceneNodeFactory", Arcadia_Audials_SceneNodeFactory,
                         &_typeOperations);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Audials_Implementation_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_Implementation_SceneNodeFactory_getType(thread);
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
Arcadia_Audials_Implementation_SceneNodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactoryDispatch* self
  )
{
  ((Arcadia_Audials_SceneNodeFactoryDispatch*)self)->createSoundSourceNode = (Arcadia_Audials_Scene_SoundSourceNode * (*)(Arcadia_Thread*, Arcadia_Audials_SceneNodeFactory*, Arcadia_Audials_BackendContext*)) & Arcadia_Audials_Implementation_SceneNodeFactory_createSoundSourceNodeImpl;
}

static void
Arcadia_Audials_Implementation_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_Implementation_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

static Arcadia_Audials_Implementation_Scene_SoundSourceNode*
Arcadia_Audials_Implementation_SceneNodeFactory_createSoundSourceNodeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_SceneNodeFactory* self,
    Arcadia_Audials_Implementation_BackendContext* backendContext
  )
{ return Arcadia_Audials_Implementation_Scene_SoundSourceNode_create(thread, backendContext); }

Arcadia_Audials_Implementation_SceneNodeFactory*
Arcadia_Audials_Implementation_SceneNodeFactory_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_Implementation_SceneNodeFactory);
}
