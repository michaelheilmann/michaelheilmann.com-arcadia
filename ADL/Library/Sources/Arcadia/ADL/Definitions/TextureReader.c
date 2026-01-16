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
#include "Arcadia/ADL/Definitions/TextureReader.h"

#include "Arcadia/DDLS/Include.h"
#include "Arcadia/ADL/Reader.module.h"
#include "Arcadia/ADL/Definitions/TextureDefinition.h"

static const char* SCHEMA =
  "{\n"
  "  kind : \"Schema\",\n"
  "  name : \"Texture\",\n"
  "  definition : {\n"
  "    kind : \"Map\",\n"
  "    entries : [\n"
  "      {\n"
  "        kind : \"MapEntry\",\n"
  "        name : \"type\",\n"
  "        type : {\n"
  "          kind : \"String\",\n"
  "        },\n"
  "      },\n"
  "      {\n"
  "        kind : \"MapEntry\",\n"
  "        name : \"name\",\n"
  "        type : {\n"
  "          kind : \"String\",\n"
  "        },\n"
  "      },\n"
  "      {\n"
  "        kind : \"MapEntry\",\n"
  "        name : \"pixelBuffer\",\n"
  "        type : {\n"
  "          kind : \"String\",\n"
  "        },\n"
  "      },\n"
  "    ],\n"
  "  },\n"
  "}\n"
  ;

static Arcadia_String*
Arcadia_ADL_TextureReader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self
  );

static Arcadia_ADL_TextureDefinition*
Arcadia_ADL_TextureReader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  );

static void
Arcadia_ADL_TextureReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self
  );

static void
Arcadia_ADL_TextureReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReaderDispatch* self
  );

static void
Arcadia_ADL_TextureReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_TextureReader_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_TextureReader_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.TextureReader", Arcadia_ADL_TextureReader,
                         u8"Arcadia.ADL.Reader", Arcadia_ADL_Reader,
                         &_typeOperations);

static Arcadia_String*
Arcadia_ADL_TextureReader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self
  )
{ return self->TYPENAME; }

static Arcadia_ADL_TextureDefinition*
Arcadia_ADL_TextureReader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  )
{
  Arcadia_DDLS_ValidationContext_run(thread, self->validationContext, self->SCHEMANAME, input);

  Arcadia_String* type = Arcadia_ADL_Reader_getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->TYPE);
  Arcadia_String* name = Arcadia_ADL_Reader_getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->NAME);
  Arcadia_String* pixelBufferName = Arcadia_ADL_Reader_getStringValue(thread, (Arcadia_DDL_MapNode*)input, self->PIXELBUFFER);

  // Assert the definition has the correct type.
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(self->TYPENAME);
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)type, &t)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_ADL_TextureDefinition* definition = Arcadia_ADL_TextureDefinition_create(thread, definitions, name, pixelBufferName);
  return definition;
}

static void
Arcadia_ADL_TextureReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_TextureReader_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_DDLS_DefaultReader* reader = (Arcadia_DDLS_DefaultReader*)Arcadia_DDLS_DefaultReader_create(thread);
    Arcadia_DDLS_Node* node = Arcadia_DDLS_DefaultReader_run(thread, reader, Arcadia_String_createFromCxxString(thread, SCHEMA));
    if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)node, _Arcadia_DDLS_SchemaNode_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_addSchema(thread, validationContext, (Arcadia_DDLS_SchemaNode*)node);
    self->validationContext = validationContext;
  }
  //
  self->TYPE = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"type");
  self->NAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"name");
  self->SCHEMANAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"Texture");
  self->TYPENAME = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"Texture");
  //
  self->PIXELBUFFER = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), u8"pixelBuffer");
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_ADL_TextureReader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReaderDispatch* self
  )
{
  ((Arcadia_ADL_ReaderDispatch*)self)->getTypeName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_ADL_Reader*)) & Arcadia_ADL_TextureReader_getTypeName;
  ((Arcadia_ADL_ReaderDispatch*)self)->read = (Arcadia_ADL_Definition * (*)(Arcadia_Thread*, Arcadia_ADL_Reader*, Arcadia_ADL_Context*, Arcadia_ADL_Definitions*, Arcadia_DDL_Node*)) & Arcadia_ADL_TextureReader_read;
}

static void
Arcadia_ADL_TextureReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_TextureReader* self
  )
{
  //
  if (self->validationContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->validationContext);
  }
  //
  if (self->TYPE) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->TYPE);
  }
  if (self->NAME) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->NAME);
  }
  if (self->SCHEMANAME) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->SCHEMANAME);
  }
  if (self->TYPENAME) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->TYPENAME);
  }
  //
  if (self->PIXELBUFFER) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->PIXELBUFFER);
  }
  //
}

Arcadia_ADL_TextureReader*
Arcadia_ADL_TextureReader_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_TextureReader);
}
