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

#include "Arcadia.Tools.TemplateEngine.Library/Environment.h"

#include "Arcadia.Tools.TemplateEngine.Library/Ast.h"
#include "Arcadia/DDL/Include.h"

static void
Environment_visit
  (
    Arcadia_Thread* thread,
    Environment* self
  );

static void
Environment_constructImpl
  (
    Arcadia_Thread* thread,
    Environment* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Environment_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Environment_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.Environment", Environment,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Environment_visit
  (
    Arcadia_Thread* thread,
    Environment* self
  )
{
  if (self->enclosing) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enclosing);
  }
  if (self->variables) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variables);
  }
}

static void
Environment_constructImpl
  (
    Arcadia_Thread* thread,
    Environment* self
  )
{
  Arcadia_TypeValue _type = _Environment_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (1 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->enclosing = NULL;
  } else {
    self->enclosing = (Environment*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Environment_getType(thread));
  }
  self->variables = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

Environment*
Environment_create
  (
    Arcadia_Thread* thread,
    Environment* enclosing
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (enclosing) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_ObjectReferenceValue)enclosing);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Environment);
}

Environment*
Environment_loadString
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  )
{
  Arcadia_DDL_Node* node = NULL;
  Arcadia_DDL_Parser* syntacticalAnalysis = Arcadia_DDL_Parser_create(thread);
  Arcadia_DDL_Parser_setInput(thread, syntacticalAnalysis, (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, source));
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis = Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create(thread);
  node = Arcadia_DDL_Parser_run(thread, syntacticalAnalysis);
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run(thread, semanticalAnalysis, node);
  Environment* variables = Environment_create(thread, NULL);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DDL_MapNode_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDL_MapNode* mapNode = (Arcadia_DDL_MapNode*)node;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    node = Arcadia_List_getObjectReferenceValueAt(thread, mapNode->entries, i);
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DDL_MapEntryNode_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_DDL_MapEntryNode* mapEntryNode = (Arcadia_DDL_MapEntryNode*)node;
    Arcadia_String* keyString = mapEntryNode->key->value;
    node = mapEntryNode->value;
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DDL_StringNode_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_String* valueString = ((Arcadia_DDL_StringNode*)mapEntryNode->value)->value;
    Arcadia_Map_set(thread, variables->variables, Arcadia_Value_makeObjectReferenceValue(keyString), Arcadia_Value_makeObjectReferenceValue(valueString), NULL, NULL);
  }
  return variables;
}

Arcadia_Value
Environment_get
  (
    Arcadia_Thread* thread,
    Environment* self,
    Arcadia_Value key,
    Arcadia_BooleanValue recursive
  )
{
  Arcadia_Value value = Arcadia_Map_get(thread, self->variables, key);
  if (Arcadia_Value_isVoidValue(&value) && recursive) {
    Environment* current = self->enclosing;
    if (current) {
      do {
        value = Arcadia_Map_get(thread, current->variables, key);
        current = current->enclosing;
      } while (Arcadia_Value_isVoidValue(&value) && NULL != current);
    }
  }
  return value;
}

void
Environment_set
  (
    Arcadia_Thread* thread,
    Environment* self,
    Arcadia_Value key,
    Arcadia_Value value
  )
{
  Arcadia_Map_set(thread, self->variables, key, value, NULL, NULL);
}
