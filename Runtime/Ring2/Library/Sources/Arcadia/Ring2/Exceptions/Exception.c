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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Exceptions/Exception.h"

static void
_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Exception* self
  );

static void
Arcadia_Exception_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ExceptionDispatch* self
  );

static void
_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Exception* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Exception", Arcadia_Exception,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Exception* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Exception_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Exception_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ExceptionDispatch* self
  )
{ }

static void
_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Exception* self
  )
{/*Intentionally empty.*/}
