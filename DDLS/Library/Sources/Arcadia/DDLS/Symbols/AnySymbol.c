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

#include "Arcadia/DDLS/Symbols/AnySymbol.h"

static void
Arcadia_DDLS_AnySymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_AnySymbol* self
  );

static void
Arcadia_DDLS_AnySymbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_AnySymbolDispatch* self
  );

static void
Arcadia_DDLS_AnySymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_AnySymbol* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_AnySymbol_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_DDLS_AnySymbol_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_AnySymbol_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDLS_AnySymbol_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_AnySymbol_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.AnySymbol", Arcadia_DDLS_AnySymbol,
                         u8"Arcadia.DDLS.Symbol", Arcadia_DDLS_Symbol,
                         &_Arcadia_DDLS_AnySymbol_typeOperations);

static void
Arcadia_DDLS_AnySymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_AnySymbol* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_AnySymbol_getType(thread);
  //
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDLS_SymbolKind_Any);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
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
Arcadia_DDLS_AnySymbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_AnySymbolDispatch* self
  )
{ }

static void
Arcadia_DDLS_AnySymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_AnySymbol* self
  )
{/*Intentionally empty.*/}

Arcadia_DDLS_AnySymbol*
Arcadia_DDLS_AnySymbol_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_AnySymbol);
}
