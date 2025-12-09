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

#define ARCADIA_ADL_PRIVATE (1)
#include "Arcadia/ADL/Definitions.h"

#include "Arcadia/ADL/Definition.h"

static void
Arcadia_ADL_Definitions_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* self
  );

static void
Arcadia_ADL_Definitions_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_ADL_Definitions_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_Definitions_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.Definitions", Arcadia_ADL_Definitions,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_ADL_Definitions_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* self
  )
{
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
  }
}

static void
Arcadia_ADL_Definitions_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_Definitions_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->definitions = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

Arcadia_ADL_Definitions*
Arcadia_ADL_Definitions_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_Definitions);
}

Arcadia_ADL_Definition*
Arcadia_ADL_Definitions_getDefinitionOrNull
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* self,
    Arcadia_String* name
  )
{
  Arcadia_Value v = Arcadia_Map_get(thread, self->definitions, Arcadia_Value_makeObjectReferenceValue(name));
  if (Arcadia_Value_isVoidValue(&v)) {
    return NULL;
  }
  return (Arcadia_ADL_Definition*)Arcadia_Value_getObjectReferenceValueChecked(thread, v, _Arcadia_ADL_Definition_getType(thread));
}

void
Arcadia_ADL_Definitions_link
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* self
  )
{
  Arcadia_List* definitions = Arcadia_Map_getValues(thread, self->definitions);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)definitions); i < n; ++i) {
    Arcadia_ADL_Definition* definition =
      (Arcadia_ADL_Definition*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, definitions, i, _Arcadia_ADL_Definition_getType(thread));
    Arcadia_ADL_Definition_link(thread, definition);
  }
}