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

#define ARCADIA_AUDIALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/OpenAL/System.h"

#include "Arcadia/Audials/Implementation/Configure.h"
#include "Arcadia/Audials/Implementation/OpenAL/Backend.h"

static Arcadia_Audials_OpenAL_System* g_instance = NULL;

static void
Arcadia_Audials_OpenAL_System_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_System* self
  );

static void
Arcadia_Audials_OpenAL_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Audials_OpenAL_System_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_System* self
  );

static void
Arcadia_Audials_OpenAL_System_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_System* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Audials_OpenAL_System_constructImpl,
  .destruct = &Arcadia_Audials_OpenAL_System_destructImpl,
  .visit = &Arcadia_Audials_OpenAL_System_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.OpenAL.System", Arcadia_Audials_OpenAL_System,
                         u8"Arcadia.Audials.System", Arcadia_Audials_System,
                         &_typeOperations);

static void
Arcadia_Audials_OpenAL_System_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_System* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_OpenAL_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Audials_OpenAL_System* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Audials_OpenAL_System_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->alcDevice = NULL;
  _self->alcContext = NULL;
  _self->alBufferId = 0;
  _self->alSourceId = 0;

  ((Arcadia_Audials_System*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Audials_System*)) & Arcadia_Audials_OpenAL_System_updateImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Audials_OpenAL_System_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_System* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_OpenAL_System_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_System* self
  )
{/*Intentionally empty.*/}

static void
destroyCallback
  (
    void* argument1,
    void* argument2
  )
{
  g_instance = NULL;
}

Arcadia_Audials_OpenAL_System*
Arcadia_Audials_OpenAL_System_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_OpenAL_System);
}

Arcadia_Audials_OpenAL_System*
Arcadia_Audials_OpenAL_System_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Audials_OpenAL_System* instance = Arcadia_Audials_OpenAL_System_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
