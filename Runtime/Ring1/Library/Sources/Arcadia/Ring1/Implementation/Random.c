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

#define ARCADIA_RING1_MODULE (1)
#include "Arcadia/Ring1/Implementation/Random.h"

#include "Arcadia/Ring1/Include.h"

static void
Arcadia_Random_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Random* self
  );

static void
Arcadia_Random_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_RandomDispatch* self
  );

static void
Arcadia_Random_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Random* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Random_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Random_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Random_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Random", Arcadia_Random,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Random_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Random* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Random);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_Random);
}

static void
Arcadia_Random_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_RandomDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Random_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Random* self
  )
{/*Intentionally empty.*/}

Arcadia_Random*
Arcadia_Random_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Random);
}
