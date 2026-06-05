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

#define ARCADIA_MILC_PRIVATE (1)
#include "Arcadia/MILC/Enter/EnumerationCompleter.h"

static void
Arcadia_MILC_EnumerationCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self
  );

static void
Arcadia_MILC_EnumerationCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleterDispatch* self
  );

static void
Arcadia_MILC_EnumerationCompleter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self
  );

static void
Arcadia_MILC_EnumerationCompleter_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self
  );

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self,
    Arcadia_MILC_Symbol* symbol
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_EnumerationCompleter_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_EnumerationCompleter_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_EnumerationCompleter_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_EnumerationCompleter_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.EnumerationCompleter", Arcadia_MILC_EnumerationCompleter,
                         u8"Arcadia.MILC.Completer", Arcadia_MILC_Completer,
                         &_typeOperations);

static void
Arcadia_MILC_EnumerationCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_EnumerationCompleter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_EnumerationCompleter);
}

static void
Arcadia_MILC_EnumerationCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleterDispatch* self
  )
{
  ((Arcadia_MILC_CompleterDispatch*)self)->complete = (void (*)(Arcadia_Thread*, Arcadia_MILC_Completer*, Arcadia_MILC_Symbol*)) &completeImpl;
}

static void
Arcadia_MILC_EnumerationCompleter_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_EnumerationCompleter_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self
  )
{/*Intentionally empty.*/}

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationCompleter* self,
    Arcadia_MILC_Symbol* symbol
  )
{ }

Arcadia_MILC_EnumerationCompleter*
Arcadia_MILC_EnumerationCompleter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_EnumerationCompleter);
}
