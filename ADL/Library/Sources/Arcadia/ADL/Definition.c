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

#define ARCADIA_ADL_PRIVATE (1)
#include "Arcadia/ADL/Definition.h"

#include "Arcadia/ADL/Definitions.h"

static void
Arcadia_ADL_Definition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  );

static void
Arcadia_ADL_Definition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  );

static void
Arcadia_ADL_Definition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_DefinitionDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_Definition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_Definition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_ADL_Definition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  )
{
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
}

static void
Arcadia_ADL_Definition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_Definition_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->definitions = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_Definitions_getType(thread));
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_ADL_Definition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_DefinitionDispatch* self
  )
{
}

Arcadia_ADL_Definitions*
Arcadia_ADL_Definitions_getDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  )
{ return self->definitions; }

Arcadia_String*
Arcadia_ADL_Definition_getName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  )
{ return self->name; }

void
Arcadia_ADL_Definition_link
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  )
{ Arcadia_VirtualCall(Arcadia_ADL_Definition, link, self); }
