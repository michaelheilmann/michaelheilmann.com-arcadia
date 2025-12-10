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

#include "Arcadia/MIL/Frontend/Symbol.h"

static void
Arcadia_MIL_Symbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Symbol* self
  );

static void
Arcadia_MIL_Symbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SymbolDispatch* self
  );

static void
Arcadia_MIL_Symbol_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Symbol* self
  );

static void
Arcadia_MIL_Symbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Symbol* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_Symbol_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MIL_Symbol_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Symbol_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Symbol", Arcadia_MIL_Symbol,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MIL_Symbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Symbol* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Symbol_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->kind = (Arcadia_MIL_SymbolKind)Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_MIL_Symbol_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SymbolDispatch* self
  )
{ }

static void
Arcadia_MIL_Symbol_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Symbol* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_Symbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Symbol* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
}

Arcadia_MIL_Symbol*
Arcadia_MIL_Symbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_SymbolKind kind,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural32Value(thread, kind);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Symbol);
}
