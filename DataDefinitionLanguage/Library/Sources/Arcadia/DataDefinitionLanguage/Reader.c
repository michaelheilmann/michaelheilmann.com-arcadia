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

#include "Arcadia/DataDefinitionLanguage/Reader.h"

#include "Arcadia/DataDefinitionLanguage/Include.h"

struct Arcadia_DataDefinitionLanguage_Reader {
  Arcadia_Object _parent;
  Arcadia_DataDefinitionLanguage_Parser* parser;
};

static void
Arcadia_DataDefinitionLanguage_Reader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_DataDefinitionLanguage_Reader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Reader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_DataDefinitionLanguage_Reader_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_DataDefinitionLanguage_Reader_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.DataDefinitionLanguage.Reader", Arcadia_DataDefinitionLanguage_Reader, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_DataDefinitionLanguage_Reader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_DataDefinitionLanguage_Reader* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_DataDefinitionLanguage_Reader_getType(thread);
  //
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  //
  _self->parser = Arcadia_DataDefinitionLanguage_Parser_create(thread);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_DataDefinitionLanguage_Reader_visit
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Reader* self
  )
{
  if (self->parser) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parser);
  }
}

Arcadia_DataDefinitionLanguage_Reader*
Arcadia_DataDefinitionLanguage_Reader_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_DataDefinitionLanguage_Reader* self = Arcadia_allocateObject(thread, _Arcadia_DataDefinitionLanguage_Reader_getType(thread), 0, &argumentValues[0]);
  return self;
}

Arcadia_DataDefinitionLanguage_Tree_Node*
Arcadia_DataDefinitionLanguage_Reader_read
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Reader* self,
    Arcadia_Utf8Reader* input
  )
{
  Arcadia_DataDefinitionLanguage_Parser_setInput(thread, self->parser, input);
  return Arcadia_DataDefinitionLanguage_Parser_run(thread, self->parser);
}
