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
#include "Arcadia/MILC/Symbols/EnumerationSymbol.h"

static void
Arcadia_MILC_EnumerationSymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbol* self
  );

static void
Arcadia_MILC_EnumerationSymbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbolDispatch* self
  );

static void
Arcadia_MILC_EnumerationSymbol_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbol* self
  );

static void
Arcadia_MILC_EnumerationSymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbol* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_EnumerationSymbol_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_EnumerationSymbol_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_EnumerationSymbol_visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_EnumerationSymbol_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.EnumerationSymbol", Arcadia_MILC_EnumerationSymbol,
                         u8"Arcadia.MILC.Symbol", Arcadia_MILC_Symbol,
                         &_typeOperations);

static void
Arcadia_MILC_EnumerationSymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbol* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_EnumerationSymbol);
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  {
    Arcadia_Value temporary = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_MILC_SymbolKind_getType(thread), Arcadia_MILC_SymbolKind_Enumeration));
    Arcadia_ValueStack_pushValue(thread, &temporary);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->scope = NULL;
  //
  Arcadia_LeaveConstructor(Arcadia_MILC_EnumerationSymbol);
}

static void
Arcadia_MILC_EnumerationSymbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbolDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_EnumerationSymbol_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbol* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_EnumerationSymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnumerationSymbol* self
  )
{
  if (self->scope) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scope);
  }
}

Arcadia_MILC_EnumerationSymbol*
Arcadia_MILC_EnumerationSymbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_EnumerationSymbol);
}
