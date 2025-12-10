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
#include "Arcadia/ADL/Reference.h"

#include "Arcadia/Languages/Include.h"
#include "Arcadia/ADL/Definitions.h"

static void
Arcadia_ADL_Reference_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  );

static void
Arcadia_ADL_Reference_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ReferenceDispatch* self
  );

static void
Arcadia_ADL_Reference_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_Reference_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_Reference_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.Reference", Arcadia_ADL_Reference,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_ADL_Reference_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  )
{
  if (self->definition) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definition);
  }
  if (self->definitionName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitionName);
  }
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
  }
}

static void
Arcadia_ADL_Reference_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_Reference_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->definition = NULL;
  self->definitionName = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  self->definitions = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_ADL_Definitions_getType(thread));
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_ADL_Reference_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ReferenceDispatch* self
  )
{ }

Arcadia_ADL_Reference*
Arcadia_ADL_Reference_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* definitionName
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (definitions) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (definitionName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitionName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_Reference);
}

Arcadia_ADL_Definitions*
Arcadia_ADL_References_getDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  )
{ return self->definitions; }

Arcadia_String*
Arcadia_ADL_Reference_getDefinitionName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  )
{ return self->definitionName; }

void
Arcadia_ADL_Reference_resolve
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  )
{
  if (!self->definition) {
    self->definition = Arcadia_ADL_Definitions_getDefinitionOrNull(thread, self->definitions, self->definitionName);
    if (!self->definition) {
      Arcadia_StringBuffer* message = Arcadia_StringBuffer_create(thread);
      Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"unable to resolve reference `");
      Arcadia_StringBuffer_insertBackString(thread, message, self->definitionName);
      Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"`");
      Arcadia_Languages_Diagnostics_emit(thread, message);

      Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
      Arcadia_Thread_jump(thread);
    }
  }
}
