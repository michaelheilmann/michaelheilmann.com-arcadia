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

#if !defined(ARCADIA_VISUALS_VPL_TREE_NODE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_NODE_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// The empty tree. Has neither children nor a value.
#define Arcadia_VPL_Tree_NodeFlags_Empty (0)

// See Arcadia.VPL.Tree.BinaryExprNode for more information.
#define Arcadia_VPL_Tree_NodeFlags_BinaryExpr (1024)

// <name>
#define Arcadia_VPL_Tree_NodeFlags_Name (5)

// <expression> '=' <expression> ';'
#define Arcadia_VPL_Tree_NodeFlags_Assignment (6)

// <type> <name> ';'
#define Arcadia_VPL_Tree_NodeFlags_VariableDefinition (7)

// <statement>*
#define Arcadia_VPL_Tree_NodeFlags_StatementList (9)

// <integer>, <natural>, <real>
#define Arcadia_VPL_Tree_NodeFlags_Number (10)

// <expression> '(' <arguments> ')'
#define Arcadia_VPL_Tree_NodeFlags_Call (11)

// <type> <name>
#define Arcadia_VPL_Tree_NodeFlags_ParameterVariableDefinition (12)

// <returnValueType> <name> '(' ´<parameters> ')' <body>
#define Arcadia_VPL_Tree_NodeFlags_FunctionDefinition (12)

// See Arcadia.VPL.Tree.ConstantRecordField for more information.
#define Arcadia_VPL_Tree_NodeFlags_ConstantRecordField (1026)

// See Arcadia.VPL.Tree.ConstantRecord for more information.
#define Arcadia_VPL_Tree_NodeFlags_ConstantRecord (1025)


Arcadia_declareObjectType(u8"Arcadia.VPL.Tree.Node", Arcadia_VPL_Tree_Node,
                          u8"Arcadia.Object");

struct Arcadia_VPL_Tree_NodeDispatch {
  Arcadia_ObjectDispatch _parent;
};

// @todo
// This implementation is  quite inefficient in terms of memory/visitation cost and it is error-prone.
// Fix by using the typical sub-typing approach. However, it is good for now until VPL matures.
struct Arcadia_VPL_Tree_Node {
  Arcadia_Object _parent;
  Arcadia_Integer32Value flags;
  Arcadia_String* literal; // For Number
  struct {
    Arcadia_String* name;
    Arcadia_String* mappedName;
  } name; // For name
  Arcadia_List* statementList; // For StatementList
  struct {
    Arcadia_VPL_Tree_Node* returnValueType;
    Arcadia_VPL_Tree_Node* name;
    Arcadia_List* parameters;
    Arcadia_VPL_Tree_Node* body;
  } functionDefinition;
  struct {
    Arcadia_VPL_Tree_Node* type;
    Arcadia_VPL_Tree_Node* name;
  } parameterVariableDefinition;
  struct {
    Arcadia_VPL_Tree_Node* target;
    Arcadia_List* arguments;
  } call;
  struct {
    Arcadia_VPL_Tree_Node* type, *name;
  } variableDefinition;
};

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeCall
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* target
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeNumber
  (
    Arcadia_Thread* thread,
    Arcadia_String* literal
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeAccess
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeAdd
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeSubtract
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeMultiply
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeDivide
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeName
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeStatementList
  (
    Arcadia_Thread* thread
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeAssignment
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* lhs,
    Arcadia_VPL_Tree_Node* rhs
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* type,
    Arcadia_VPL_Tree_Node* name
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* type,
    Arcadia_VPL_Tree_Node* name
  );

Arcadia_VPL_Tree_Node*
Arcadia_VPL_Tree_makeFunctionDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* returnValueType,
    Arcadia_VPL_Tree_Node* name,
    Arcadia_List* parameters,
    Arcadia_VPL_Tree_Node* body
  );

#endif // ARCADIA_VISUALS_VPL_TREE_NODE_H_INCLUDED
