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
#include "Arcadia/ADL/Definitions/CheckerboardFillOperationDefinition.h"

#include "Arcadia/ADL/Definitions/ColorDefinition.h"
#include "Arcadia/ADL/Definitions.h"
#include "Arcadia/ADL/Reference.h"

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* self
  );

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* self
  );

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* self
  );

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinitionDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.PixelBufferOperations.CheckerboardFillOperationDefinition", Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition,
                         u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         &_typeOperations);

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* self
  )
{
  Arcadia_ADL_Definition* definition;

  Arcadia_ADL_Reference_resolve(thread, self->firstCheckerColor);
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)self->firstCheckerColor->definition, _Arcadia_ADL_ColorDefinition_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ADL_Reference_resolve(thread, self->secondCheckerColor);
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)self->secondCheckerColor->definition, _Arcadia_ADL_ColorDefinition_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* self
  )
{
  if (self->firstCheckerColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->firstCheckerColor);
  }
  if (self->secondCheckerColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->secondCheckerColor);
  }
}

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_getType(thread);
  {
    Arcadia_Value definitions, name;
    definitions = Arcadia_ValueStack_getValue(thread, 6);
    name = Arcadia_ValueStack_getValue(thread, 5);
    Arcadia_ValueStack_pushValue(thread, &name);
    Arcadia_ValueStack_pushValue(thread, &definitions);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 6 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->checkerWidth = Arcadia_ValueStack_getInteger32Value(thread, 4);
  self->checkerHeight = Arcadia_ValueStack_getInteger32Value(thread, 3);

  self->firstCheckerColor = Arcadia_ADL_Reference_create(thread, ((Arcadia_ADL_Definition*)self)->definitions,
                                                        (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread)));
  self->secondCheckerColor = Arcadia_ADL_Reference_create(thread, ((Arcadia_ADL_Definition*)self)->definitions,
                                                         (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread)));

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 6 + 1);
}

static void
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinitionDispatch* self
  )
{
  ((Arcadia_ADL_DefinitionDispatch*)self)->link = (void (*)(Arcadia_Thread*, Arcadia_ADL_Definition*)) & Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_linkImpl;
}

Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* qualifiedName,
    Arcadia_Integer32Value checkerWidth,
    Arcadia_Integer32Value checkerHeight,
    Arcadia_String* firstColorName,
    Arcadia_String* secondColorName
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)qualifiedName);
  Arcadia_ValueStack_pushInteger32Value(thread, checkerWidth);
  Arcadia_ValueStack_pushInteger32Value(thread, checkerHeight);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)firstColorName);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)secondColorName);
  Arcadia_ValueStack_pushNatural8Value(thread, 6);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition);
}
