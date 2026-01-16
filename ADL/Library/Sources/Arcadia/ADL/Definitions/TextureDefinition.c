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
#include "Arcadia/ADL/Definitions/TextureDefinition.h"

#include "Arcadia/ADL/Definitions/PixelBufferDefinition.h"

static void
Arcadia_ADL_TextureDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinition* self
  );

static void
Arcadia_ADL_TextureDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinition* self
  );

static void
Arcadia_ADL_TextureDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinition* self
  );

static void
Arcadia_ADL_TextureDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinitionDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_TextureDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_TextureDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.TextureDefinition", Arcadia_ADL_TextureDefinition,
                         u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         &_typeOperations);

static void
Arcadia_ADL_TextureDefinition_linkImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinition* self
  )
{
  Arcadia_ADL_Reference_resolve(thread, self->pixelBuffer);
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)self->pixelBuffer->definition, _Arcadia_ADL_PixelBufferDefinition_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ADL_Definition_link(thread, self->pixelBuffer->definition);
}

static void
Arcadia_ADL_TextureDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinition* self
  )
{
  if (self->pixelBuffer) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->pixelBuffer);
  }
}

static void
Arcadia_ADL_TextureDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_TextureDefinition_getType(thread);
  {
    Arcadia_Value definitions, name;
    definitions = Arcadia_ValueStack_getValue(thread, 3);
    name = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &definitions);
    Arcadia_ValueStack_pushValue(thread, &name);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->pixelBuffer = Arcadia_ADL_Reference_create(thread, ((Arcadia_ADL_Definition*)self)->definitions,
                                                   Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread)));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_ADL_TextureDefinition_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureDefinitionDispatch* self
  )
{
  ((Arcadia_ADL_DefinitionDispatch*)self)->link = (void (*)(Arcadia_Thread*, Arcadia_ADL_Definition*)) & Arcadia_ADL_TextureDefinition_linkImpl;
}

Arcadia_ADL_TextureDefinition*
Arcadia_ADL_TextureDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_String* pixelBufferName
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)pixelBufferName);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_TextureDefinition);
}
