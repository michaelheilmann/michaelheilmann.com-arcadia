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
#include "Arcadia/ADL/Definitions/Audials/AddWhiteNoiseOperationDefinition.h"

#include "Arcadia/ADL/Context.h"
#include "Arcadia/ADL/Reader.module.h"
#include "Arcadia/ADL/Reference.h"
#include "Arcadia/ADL/Definitions/Audials/Include.h"

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinition* self
  );

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinition* self
  );

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinition* self
  );

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinitionDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_AddWhiteNoiseOperationDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_AddWhiteNoiseOperationDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.AddWhiteNoiseOperationDefinition", Arcadia_ADL_AddWhiteNoiseOperationDefinition,
                         u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         &_typeOperations);

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinition* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinition* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinition* self
  )
{
  Arcadia_EnterConstructor(Arcadia_ADL_AddWhiteNoiseOperationDefinition);
  {
    Arcadia_Value definitions, name;
    definitions = Arcadia_ValueStack_getValue(thread, 2);
    name = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &definitions);
    Arcadia_ValueStack_pushValue(thread, &name);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_ADL_AddWhiteNoiseOperationDefinition);
}

static void
Arcadia_ADL_AddWhiteNoiseOperationDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_AddWhiteNoiseOperationDefinitionDispatch* self
  )
{
  ((Arcadia_ADL_DefinitionDispatch*)self)->link = (void (*)(Arcadia_Thread*, Arcadia_ADL_Definition*)) & Arcadia_ADL_AddWhiteNoiseOperationDefinition_linkImpl;
}

Arcadia_ADL_AddWhiteNoiseOperationDefinition*
Arcadia_ADL_AddWhiteNoiseOperationDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_AddWhiteNoiseOperationDefinition);
}
