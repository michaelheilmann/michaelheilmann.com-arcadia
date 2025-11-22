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

#include "Arcadia/DDLS/Semantical/MapEntrySymbol.h"

static void
Arcadia_DDLS_MapEntrySymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_MapEntrySymbol* self
  );

static void
Arcadia_DDLS_MapEntrySymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_MapEntrySymbol* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_MapEntrySymbol_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDLS_MapEntrySymbol_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_MapEntrySymbol_visitImpl,
};                                                                                  

static const Arcadia_Type_Operations _Arcadia_DDLS_MapEntrySymbol_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_MapEntrySymbol_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.MapEntrySymbol", Arcadia_DDLS_MapEntrySymbol,
                         u8"Arcadia.DDLS.Symbol", Arcadia_DDLS_Symbol,
                         &_Arcadia_DDLS_MapEntrySymbol_typeOperations);

static void
Arcadia_DDLS_MapEntrySymbol_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_MapEntrySymbol* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_MapEntrySymbol_getType(thread);
  //
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_DDLS_SymbolKind_MapEntryType);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->entryName = NULL;
  self->entryType = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_DDLS_MapEntrySymbol_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_MapEntrySymbol* self
  )
{
  if (self->entryName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->entryName);
  }
  if (self->entryType) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->entryType);
  }
}

Arcadia_DDLS_MapEntrySymbol*
Arcadia_DDLS_MapEntrySymbol_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_MapEntrySymbol);
}
