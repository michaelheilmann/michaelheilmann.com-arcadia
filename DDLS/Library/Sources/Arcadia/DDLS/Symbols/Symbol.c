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

#include "Arcadia/DDLS/Symbols/Symbol.h"

#include "Arcadia/DDLS/Symbols/Scope.h"

static void
Arcadia_DDLS_Symbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Symbol* self
  );

static void
Arcadia_DDLS_Symbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SymbolDispatch* self
  );

static void
Arcadia_DDLS_Symbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Symbol* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_Symbol_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_DDLS_Symbol_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_Symbol_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_DDLS_Symbol_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDLS_Symbol_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_Symbol_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.Symbol", Arcadia_DDLS_Symbol,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_DDLS_Symbol_typeOperations);

static void
Arcadia_DDLS_Symbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Symbol* self
  )
{
  Arcadia_EnterConstructor(Arcadia_DDLS_Symbol);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->kind = Arcadia_ValueStack_getInteger32Value(thread, 1);
  //
  Arcadia_LeaveConstructor(Arcadia_DDLS_Symbol);
}

static void
Arcadia_DDLS_Symbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SymbolDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_DDLS_Symbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Symbol* self
  )
{/*Intentionally empty.*/}
