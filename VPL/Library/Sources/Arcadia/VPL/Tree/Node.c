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
#include "Arcadia/VPL/Tree/Node.h"

#include "Arcadia/VPL/Tree/BinaryExprNode.h"

static void
Arcadia_VPL_Tree_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* self
  );

static void
Arcadia_VPL_Tree_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeDispatch* self
  );

static void
Arcadia_VPL_Tree_Node_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Tree_Node_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Tree_Node_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.VPL.Tree.Node", Arcadia_VPL_Tree_Node,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_Tree_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Tree_Node);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->flags = Arcadia_ValueStack_getInteger32Value(thread, 1);
  self->functionDefinition.name = NULL;
  self->functionDefinition.returnValueType = NULL;
  self->functionDefinition.parameters = NULL;
  self->functionDefinition.body = NULL;
  self->parameterVariableDefinition.name = NULL;
  self->parameterVariableDefinition.type = NULL;
  self->literal = NULL;
  self->statementList = NULL;
  self->name.name = NULL;
  self->name.mappedName = NULL;
  self->call.arguments = NULL;
  self->call.target = NULL;
  self->variableDefinition.type = NULL; self->variableDefinition.name = NULL;
  Arcadia_LeaveConstructor(Arcadia_VPL_Tree_Node);
}

static void
Arcadia_VPL_Tree_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_NodeDispatch* self
  )
{ }

static void
Arcadia_VPL_Tree_Node_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* self
  )
{
  if (self->functionDefinition.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.name);
  }
  if (self->functionDefinition.returnValueType) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.returnValueType);
  }
  if (self->functionDefinition.parameters) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.parameters);
  }
  if (self->functionDefinition.body) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.body);
  }


  if (self->parameterVariableDefinition.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parameterVariableDefinition.name);
  }
  if (self->parameterVariableDefinition.type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parameterVariableDefinition.type);
  }

  if (self->call.arguments) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->call.arguments);
  }
  if (self->call.target) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->call.target);
  }

  if (self->literal) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->literal);
  }

  if (self->statementList) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->statementList);
  }

  if (self->name.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name.name);
  }
  if (self->name.mappedName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name.mappedName);
  }

  if (self->variableDefinition.type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableDefinition.type);
  }
  if (self->variableDefinition.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableDefinition.name);
  }
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_Node_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, Arcadia_VPL_Tree_NodeFlags_Empty);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Tree_Node);
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeCall
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* target
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->call.target = target;
  self->call.arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->flags = Arcadia_VPL_Tree_NodeFlags_Call;
  return self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeNumber
  (
    Arcadia_Thread* thread,
    Arcadia_String* literal
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->literal = literal;
  self->flags = Arcadia_VPL_Tree_NodeFlags_Number;
  return self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeAccess
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  )
{
  Arcadia_VPL_Tree_BinaryExprNode* self = Arcadia_VPL_Tree_BinaryExprNode_create(thread, Arcadia_VPL_Tree_BinaryExprNodeFlags_Access, lhs, rhs);
  return (Arcadia_VPL_Tree_Node*)self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeAdd
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  )
{
  Arcadia_VPL_Tree_BinaryExprNode* self = Arcadia_VPL_Tree_BinaryExprNode_create(thread, Arcadia_VPL_Tree_BinaryExprNodeFlags_Add, lhs, rhs);
  return (Arcadia_VPL_Tree_Node*)self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeSubtract
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  )
{
  Arcadia_VPL_Tree_BinaryExprNode* self = Arcadia_VPL_Tree_BinaryExprNode_create(thread, Arcadia_VPL_Tree_BinaryExprNodeFlags_Subtract, lhs, rhs);
  return (Arcadia_VPL_Tree_Node*)self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeMultiply
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  )
{
  Arcadia_VPL_Tree_BinaryExprNode* self = Arcadia_VPL_Tree_BinaryExprNode_create(thread, Arcadia_VPL_Tree_BinaryExprNodeFlags_Multiply, lhs, rhs);
  return (Arcadia_VPL_Tree_Node*)self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeDivide
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  )
{
  Arcadia_VPL_Tree_BinaryExprNode* self = Arcadia_VPL_Tree_BinaryExprNode_create(thread, Arcadia_VPL_Tree_BinaryExprNodeFlags_Divide, lhs, rhs);
  return (Arcadia_VPL_Tree_Node*)self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeName
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->name.name = name;
  self->flags = Arcadia_VPL_Tree_NodeFlags_Name;
  return self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeStatementList
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->statementList = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->flags = Arcadia_VPL_Tree_NodeFlags_StatementList;
  return self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeAssignment
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  )
{
  Arcadia_VPL_Tree_BinaryExprNode* self = Arcadia_VPL_Tree_BinaryExprNode_create(thread, Arcadia_VPL_Tree_BinaryExprNodeFlags_Assignment, lhs, rhs);
  return (Arcadia_VPL_Tree_Node*)self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* type,
    Arcadia_VPL_Tree_Node* name
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->variableDefinition.type = type;
  self->variableDefinition.name = name;
  self->flags = Arcadia_VPL_Tree_NodeFlags_VariableDefinition;
  return self;
}

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* type,
    Arcadia_VPL_Tree_Node* name
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->parameterVariableDefinition.type = type;
  self->parameterVariableDefinition.name = name;
  self->flags = Arcadia_VPL_Tree_NodeFlags_ParameterVariableDefinition;
  return self;
}


Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeFunctionDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* returnValueType,
    Arcadia_VPL_Tree_Node* name,
    Arcadia_List* parameters,
    Arcadia_VPL_Tree_Node* body
  )
{
  Arcadia_VPL_Tree_Node* self = Arcadia_VPL_Tree_Node_create(thread);
  self->functionDefinition.name = name;
  self->functionDefinition.returnValueType = returnValueType;
  self->functionDefinition.parameters = parameters;
  self->functionDefinition.body = body;
  self->flags = Arcadia_VPL_Tree_NodeFlags_FunctionDefinition;
  return self;
}
