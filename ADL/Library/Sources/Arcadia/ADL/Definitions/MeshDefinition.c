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
#include "Arcadia/ADL/Definitions/MeshDefinition.h"

#include "Arcadia/ADL/Definitions/ColorDefinition.h"
#include "Arcadia/ADL/Definitions/MaterialDefinition.h"

static void
Arcadia_ADL_MeshDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

static void
Arcadia_ADL_MeshDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

static void
Arcadia_ADL_MeshDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  );

static void
Arcadia_ADL_MeshDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinitionDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_MeshDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_MeshDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.MeshDefinition", Arcadia_ADL_MeshDefinition,
                         u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         &_typeOperations);

static void
Arcadia_ADL_MeshDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{
  Arcadia_ADL_Reference_resolve(thread, self->ambientColor);
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)self->ambientColor->definition, _Arcadia_ADL_ColorDefinition_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_ADL_MeshDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{
  if (self->vertexPositions) {
    Arcadia_InternalImmutableByteArray_visit(thread, self->vertexPositions);
  }
  if (self->vertexAmbientColors) {
    Arcadia_InternalImmutableByteArray_visit(thread, self->vertexAmbientColors);
  }
  if (self->ambientColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->ambientColor);
  }
}

static void
Arcadia_ADL_MeshDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_MeshDefinition_getType(thread);
  {
    Arcadia_Value definitions, name;
    definitions = Arcadia_ValueStack_getValue(thread, 7);
    name = Arcadia_ValueStack_getValue(thread, 6);
    Arcadia_ValueStack_pushValue(thread, &definitions);
    Arcadia_ValueStack_pushValue(thread, &name);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (Arcadia_ValueStack_getSize(thread) < 1 || 7 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->numberOfVertices = Arcadia_ValueStack_getSizeValue(thread, 5);
  self->vertexPositions = Arcadia_ValueStack_getInternalImmutableByteArrayValue(thread, 4);
  self->vertexAmbientColors = Arcadia_ValueStack_getInternalImmutableByteArrayValue(thread, 3);
  self->vertexAmbientTextureCoordinates = Arcadia_ValueStack_getInternalImmutableByteArrayValue(thread, 2);
  self->ambientColor = Arcadia_ADL_Reference_create(thread, ((Arcadia_ADL_Definition*)self)->definitions,
                                                            (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread)));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_ADL_MeshDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinitionDispatch* self
  )
{
  ((Arcadia_ADL_DefinitionDispatch*)self)->link = (void (*)(Arcadia_Thread*, Arcadia_ADL_Definition*)) & Arcadia_ADL_MeshDefinition_linkImpl;
}

Arcadia_ADL_MeshDefinition*
Arcadia_ADL_MeshDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_SizeValue numberOfVertices,
    Arcadia_InternalImmutableByteArray* vertexPositions,
    Arcadia_InternalImmutableByteArray* vertexAmbientColors,
    Arcadia_InternalImmutableByteArray* vertexAmbientTextureCoordinates,
    Arcadia_String* ambientColorName
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushSizeValue(thread, numberOfVertices);
  Arcadia_ValueStack_pushInternalImmutableByteArrayValue(thread, vertexPositions);
  Arcadia_ValueStack_pushInternalImmutableByteArrayValue(thread, vertexAmbientColors);
  Arcadia_ValueStack_pushInternalImmutableByteArrayValue(thread, vertexAmbientTextureCoordinates);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)ambientColorName);
  Arcadia_ValueStack_pushNatural8Value(thread, 7);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_MeshDefinition);
}

Arcadia_SizeValue
Arcadia_ADL_MeshDefinition_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{ return self->numberOfVertices; }

Arcadia_InternalImmutableByteArray*
Arcadia_ADL_MeshDefinition_getVertexPositions
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{ return self->vertexPositions; }

Arcadia_InternalImmutableByteArray*
Arcadia_ADL_MeshDefinition_getVertexAmbientColors
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{ return self->vertexAmbientColors; }

Arcadia_InternalImmutableByteArray*
Arcadia_ADL_MeshDefinition_getVertexAmbientTextureCoordinates
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_MeshDefinition* self
  )
{ return self->vertexAmbientTextureCoordinates; }