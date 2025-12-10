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

#define ARCADIA_AUDIALS_PRIVATE (1)
#include "Arcadia/Audials/SceneNodeFactory.h"

static void
Arcadia_Audials_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self
  );

static void
Arcadia_Audials_SceneNodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactoryDispatch* self
  );

static void
Arcadia_Audials_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self
  );

static void
Arcadia_Audials_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Audials_SceneNodeFactory_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Audials_SceneNodeFactory_construct,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Audials_SceneNodeFactory_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_SceneNodeFactory_visit,
};

static const Arcadia_Type_Operations _Arcadia_Audials_SceneNodeFactory_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Audials_SceneNodeFactory_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcardia.Audials.SceneNodeFactory", Arcadia_Audials_SceneNodeFactory,
                         u8"Arcadia.Engine.SceneNodeFactory", Arcadia_Engine_SceneNodeFactory,
                         &_Arcadia_Audials_SceneNodeFactory_typeOperations);

static void
Arcadia_Audials_SceneNodeFactory_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_SceneNodeFactory_getType(thread);
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
Arcadia_Audials_SceneNodeFactory_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactoryDispatch* self
  )
{ }

static void
Arcadia_Audials_SceneNodeFactory_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_SceneNodeFactory_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self
  )
{/*Intentionally empty.*/}

Arcadia_Audials_Scene_SoundSourceNode*
Arcadia_Audials_SceneNodeFactory_createSoundSourceNode
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_SceneNodeFactory* self,
    Arcadia_Audials_BackendContext* backendContext
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Audials_SceneNodeFactory, createSoundSourceNode, self, backendContext); }
