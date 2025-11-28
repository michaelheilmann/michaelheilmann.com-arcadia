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

#include "Arcadia/DDLS/Semantical/SchemaSymbol.h"

#include "Arcadia/DDLS/Semantical/Scope.h"

static void
Arcadia_DDLS_SchemaSymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SchemaSymbol* self
  );

static void
Arcadia_DDLS_SchemaSymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SchemaSymbol* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_SchemaSymbol_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDLS_SchemaSymbol_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_SchemaSymbol_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDLS_SchemaSymbol_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_SchemaSymbol_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.SchemaSymbol", Arcadia_DDLS_SchemaSymbol,
                         u8"Arcadia.DDLS.Symbol", Arcadia_DDLS_Symbol,
                         &_Arcadia_DDLS_SchemaSymbol_typeOperations);

static void
Arcadia_DDLS_SchemaSymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SchemaSymbol* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_SchemaSymbol_getType(thread);
  //
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDLS_SymbolKind_Schema);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  self->definition = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_DDLS_SchemaSymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_SchemaSymbol* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->definition) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definition);
  }
}

Arcadia_DDLS_SchemaSymbol*
Arcadia_DDLS_SchemaSymbol_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_SchemaSymbol);
}
