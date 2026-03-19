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

#define ARCADIA_VPL_PRIVATE (1)
#include "Arcadia/VPL/Tree/ProcedureDefnNode.h"
#include "Arcadia/VPL/Tree/NameExprNode.h"

#include "Arcadia/Languages/Include.h"

static Arcadia_String*
S
  (
    Arcadia_Thread* thread,
    const char* string
  )
{ return Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), string); }

static void
Arcadia_VPL_Tree_ProcedureDefnNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  );

static void
Arcadia_VPL_Tree_ProcedureDefnNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNodeDispatch* self
  );

static void
Arcadia_VPL_Tree_ProcedureDefnNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Tree_ProcedureDefnNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Tree_ProcedureDefnNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.VPL.Tree.ProcedureDefnNode", Arcadia_VPL_Tree_ProcedureDefnNode,
                         u8"Arcadia.VPL.Tree.Node", Arcadia_VPL_Tree_Node,
                         &_typeOperations);

static void
Arcadia_VPL_Tree_ProcedureDefnNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Tree_ProcedureDefnNode);
  {
    Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_VPL_Tree_NodeFlags_ProcedureDefn);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (5 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->modifiers = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 5, _Arcadia_List_getType(thread));
  self->returnValueType = (Arcadia_VPL_Tree_NameExprNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_VPL_Tree_NameExprNode_getType(thread));
  self->name = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  self->parameters = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_List_getType(thread));
  self->body = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_VPL_Tree_ProcedureDefnNode);
}

static void
Arcadia_VPL_Tree_ProcedureDefnNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNodeDispatch* self
  )
{ }

static void
Arcadia_VPL_Tree_ProcedureDefnNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  )
{
  if (self->modifiers) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->modifiers);
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->returnValueType) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->returnValueType);
  }
  if (self->parameters) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parameters);
  }
  if (self->body) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->body);
  }
}

Arcadia_VPL_Tree_ProcedureDefnNode*
Arcadia_VPL_Tree_ProcedureDefnNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_List* modifiers,
    Arcadia_VPL_Tree_NameExprNode* returnValueType,
    Arcadia_String* name,
    Arcadia_List* parameters,
    Arcadia_List* body
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)modifiers);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)returnValueType);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)parameters);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)body);
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Tree_ProcedureDefnNode);
}

Arcadia_BooleanValue
Arcadia_VPL_Tree_ProcedureDefnNode_isVertex
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  )
{ return Arcadia_List_contains(thread, self->modifiers, Arcadia_Value_makeObjectReferenceValue(S(thread, u8"vertex"))); }

Arcadia_BooleanValue
Arcadia_VPL_Tree_ProcedureDefnNode_isFragment
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  )
{ return Arcadia_List_contains(thread, self->modifiers, Arcadia_Value_makeObjectReferenceValue(S(thread, u8"fragment"))); }

Arcadia_BooleanValue
Arcadia_VPL_Tree_ProcedureDefnNode_isPixel
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_ProcedureDefnNode* self
  )
{ return Arcadia_List_contains(thread, self->modifiers, Arcadia_Value_makeObjectReferenceValue(S(thread, u8"pixel"))); }
