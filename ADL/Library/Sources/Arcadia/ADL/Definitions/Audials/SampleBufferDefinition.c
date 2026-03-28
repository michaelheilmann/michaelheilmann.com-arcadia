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
#include "Arcadia/ADL/Definitions/Audials/SampleBufferDefinition.h"

#include "Arcadia/ADL/Context.h"
#include "Arcadia/ADL/Reader.module.h"
#include "Arcadia/ADL/Reference.h"
#include "Arcadia/ADL/Definitions/Audials/Include.h"

static void
Arcadia_ADL_SampleBufferDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinition* self
  );

static void
Arcadia_ADL_SampleBufferDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinition* self
  );

static void
Arcadia_ADL_SampleBufferDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinition* self
  );

static void
Arcadia_ADL_SampleBufferDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinitionDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) &Arcadia_ADL_SampleBufferDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) &Arcadia_ADL_SampleBufferDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.SampleBufferDefinition", Arcadia_ADL_SampleBufferDefinition,
                         u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         &_typeOperations);

static void
Arcadia_ADL_SampleBufferDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinition* self
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->operations); i < n; ++i) {
    Arcadia_ADL_Reference* operation = (Arcadia_ADL_Reference*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, self->operations, i, _Arcadia_ADL_Reference_getType(thread));
    Arcadia_ADL_Reference_resolve(thread, operation);
    Arcadia_ADL_Definition_link(thread, operation->definition);
  }
}

static void
Arcadia_ADL_SampleBufferDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinition* self
  )
{
  if (self->operations) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->operations);
  }
}

static void
Arcadia_ADL_SampleBufferDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinition* self
  )
{
  Arcadia_EnterConstructor(Arcadia_ADL_SampleBufferDefinition);
  {
    Arcadia_Value definitions, name;
    definitions = Arcadia_ValueStack_getValue(thread, 3);
    name = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &definitions);
    Arcadia_ValueStack_pushValue(thread, &name);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->operations = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->duration = Arcadia_ValueStack_getNatural32Value(thread, 1);
  Arcadia_LeaveConstructor(Arcadia_ADL_SampleBufferDefinition);
}

static void
Arcadia_ADL_SampleBufferDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SampleBufferDefinitionDispatch* self
  )
{
  ((Arcadia_ADL_DefinitionDispatch*)self)->link = (void (*)(Arcadia_Thread*, Arcadia_ADL_Definition*)) & Arcadia_ADL_SampleBufferDefinition_linkImpl;
}

Arcadia_ADL_SampleBufferDefinition*
Arcadia_ADL_SampleBufferDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_Natural32Value duration
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural32Value(thread, duration);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_SampleBufferDefinition);
}
