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

#include "Arcadia.Ring1.Tests.ObjectTypeTests/MyInterfaceA.h"

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MyObjectA_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MyObjectA_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MyObjectA_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MyObjectA_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineInterfaceType(u8"Arcadia.MyObjectA", Arcadia_MyObjectA,
                            u8"Arcadia.Interface", Arcadia_Object,
                            &_typeOperations);

static void
Arcadia_MyObjectA_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MyObjectA* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MyObjectA);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MyObjectA);
}

static void
Arcadia_MyObjectA_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MyObjectA* self
  )
{ }

static void
Arcadia_MyObjectA_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MyObjectADispatch* self
  )
{ }

static void
Arcadia_MyObjectA_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MyObjectA* self
  )
{ }

Arcadia_MyObjectA*
Arcadia_MyObjectA_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MyObjectA);
}
