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

#include "Arcadia/DDLS/Reader/DefaultReader.h"

#include "Arcadia/DDLS/Extensions.h"
#include "Arcadia/DDLS/Semantical/SymbolReader.h"

#include "Arcadia/DDLS/Semantical/MapSymbol.h"
#include "Arcadia/DDLS/Semantical/MapEntrySymbol.h"
#include "Arcadia/DDLS/Semantical/ScalarSymbol.h"

static Arcadia_DDLS_ScalarType*
readScalarType
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_DDLS_ScalarSymbol* source
  );

static Arcadia_DDLS_MapType*
readMapType
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_DDLS_MapSymbol* source
  );

static Arcadia_DDLS_Type*
readType
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_DDLS_Symbol* source
  );

static Arcadia_DDLS_ScalarType*
readScalarType
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_DDLS_ScalarSymbol* source
  )
{
  if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)source->name, &self->BOOLEAN)) {
    Arcadia_DDLS_ScalarType* target = Arcadia_DDLS_ScalarType_create(thread);
    target->name = source->name;
    return target;
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)source->name, &self->NUMBER)) {
    Arcadia_DDLS_ScalarType* target = Arcadia_DDLS_ScalarType_create(thread);
    target->name = source->name;
    return target;
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)source->name, &self->STRING)) {
    Arcadia_DDLS_ScalarType* target = Arcadia_DDLS_ScalarType_create(thread);
    target->name = source->name;
    return target;
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)source->name, &self->VOID)) {
    Arcadia_DDLS_ScalarType* target = Arcadia_DDLS_ScalarType_create(thread);
    target->name = source->name;
    return target;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static Arcadia_DDLS_MapType*
readMapType
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_DDLS_MapSymbol* source
  )
{
  Arcadia_DDLS_MapType* target = Arcadia_DDLS_MapType_create(thread);
  Arcadia_List* sourceKeys = Arcadia_Map_getKeys(thread, source->entries);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourceKeys); i < n; ++i) {
    Arcadia_Value v = Arcadia_Map_get(thread, source->entries, Arcadia_List_getAt(thread, sourceKeys, i));
    if (!Arcadia_Value_isInstanceOf(thread, &v, _Arcadia_DDLS_MapEntrySymbol_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_DDLS_MapEntrySymbol* o = (Arcadia_DDLS_MapEntrySymbol*)Arcadia_Value_getObjectReferenceValue(&v);
    Arcadia_String* targetName = o->entryName;
    Arcadia_DDLS_Type* targetValue = readType(thread, self, o->entryType);
    Arcadia_Map_set(thread, target->entries, Arcadia_Value_makeObjectReferenceValue(targetName),
                                             Arcadia_Value_makeObjectReferenceValue(targetValue),
                                             NULL,
                                             NULL);
  }
  return target;
}

static Arcadia_DDLS_Type*
readType
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_DDLS_Symbol* source
  )
{
  switch (source->kind) {
    case Arcadia_DDLS_SymbolKind_MapType: {
      return (Arcadia_DDLS_Type*)readMapType(thread, self, (Arcadia_DDLS_MapSymbol*)source);
    } break;
    case Arcadia_DDLS_SymbolKind_ScalarType: {
      return (Arcadia_DDLS_Type*)readScalarType(thread, self, (Arcadia_DDLS_ScalarSymbol*)source);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  };
}

static void
Arcadia_DDLS_DefaultReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self
  );

static void
Arcadia_DDLS_DefaultReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self
  );

static Arcadia_DDLS_Type*
Arcadia_DDLS_DefaultReader_runImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_Utf8Reader* input
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_DefaultReader_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDLS_DefaultReader_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_DefaultReader_visitImpl,
};                                                                                  

static const Arcadia_Type_Operations _Arcadia_DDLS_DefaultReader_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_DefaultReader_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.DefaultReader", Arcadia_DDLS_DefaultReader,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_DDLS_DefaultReader_typeOperations);

static void
Arcadia_DDLS_DefaultReader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_DefaultReader_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->parser = Arcadia_DDL_Parser_create(thread);
  //
  self->run = &Arcadia_DDLS_DefaultReader_runImpl;
  //
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_Languages_StringTable* stringTable = Arcadia_DDL_Parser_getStringTable(thread, self->parser);
#define Define(Variable, Text) \
  Arcadia_StringBuffer_clear(thread, stringBuffer); \
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, Text); \
  self->Variable = Arcadia_Value_makeObjectReferenceValue(Arcadia_Languages_StringTable_getOrCreateString(thread, stringTable, stringBuffer));

  Define(BOOLEAN, u8"Boolean");
  Define(NUMBER, u8"Number");
  Define(STRING, u8"String");
  Define(VOID, u8"Void");

#undef Define
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_DDLS_DefaultReader_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self
  )
{
  if (self->parser) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parser);
  }
#define Define(Variable, Text) \
  Arcadia_Value_visit(thread, &self->Variable);

  Define(BOOLEAN, u8"Boolean");
  Define(NUMBER, u8"Number");
  Define(STRING, u8"String");
  Define(VOID, u8"Void");

#undef Define
}

static Arcadia_DDLS_Type*
Arcadia_DDLS_DefaultReader_runImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_Utf8Reader* input 
  )
{
  Arcadia_Languages_StringTable* stringTable = Arcadia_Languages_StringTable_create(thread);
  Arcadia_DDL_Parser_setInput(thread, self->parser, input);
  Arcadia_DDL_Node* node = Arcadia_DDL_Parser_run(thread, self->parser);
  Arcadia_DDLS_SymbolReader* symbolReader = Arcadia_DDLS_SymbolReader_create(thread, stringTable);
  Arcadia_DDLS_Symbol* typeSymbol = Arcadia_DDLS_SymbolReader_run(thread, symbolReader, node);
  return readType(thread, self, typeSymbol);
}

Arcadia_DDLS_DefaultReader*
Arcadia_DDLS_DefaultReader_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_DefaultReader);
}

Arcadia_DDLS_Type*
Arcadia_DDLS_DefaultReader_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_Utf8Reader* input
  )
{ return self->run(thread, self, input); }
