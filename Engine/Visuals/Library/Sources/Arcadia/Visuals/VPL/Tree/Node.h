#if !defined(ARCADIA_VISUALS_VPL_TREE_NODE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_NODE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// The empty tree. Has neither children nor a value.
#define Arcadia_Visuals_VPL_Tree_NodeFlags_Empty (0)

// "add", "subtract", "multiply", "divide", and "access" operations
#define Arcadia_Visuals_VPL_Tree_NodeFlags_BinaryExpr (1024)

// <name>
#define Arcadia_Visuals_VPL_Tree_NodeFlags_Name (5)

// <expression> '=' <expression> ';'
#define Arcadia_Visuals_VPL_Tree_NodeFlags_Assignment (6)

// <type> <name> ';'
#define Arcadia_Visuals_VPL_Tree_NodeFlags_VariableDefinition (7)

// <statement>*
#define Arcadia_Visuals_VPL_Tree_NodeFlags_StatementList (9)

// <integer>, <natural>, <real>
#define Arcadia_Visuals_VPL_Tree_NodeFlags_Number (10)

// <expression> '(' <arguments> ')'
#define Arcadia_Visuals_VPL_Tree_NodeFlags_Call (11)

// <type> <name>
#define Arcadia_Visuals_VPL_Tree_NodeFlags_ParameterVariableDefinition (12)

// <returnValueType> <name> '(' ´<parameters> ')' <body>
#define Arcadia_Visuals_VPL_Tree_NodeFlags_FunctionDefinition (12)

Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Tree.Node", Arcadia_Visuals_VPL_Tree_Node,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_Tree_NodeDispatch {
  Arcadia_ObjectDispatch _parent;
};

// @todo
// This implementation is  quite inefficient in terms of memory/visitation cost and it is error-prone.
// Fix by using the typical sub-typing approach. However, it is good for now until VPL matures.
struct Arcadia_Visuals_VPL_Tree_Node {
  Arcadia_Object _parent;
  Arcadia_Integer32Value flags;
  Arcadia_String* literal; // For Number
  Arcadia_String* name; // For Name
  Arcadia_List* statementList; // For StatementList
  struct {
    Arcadia_Visuals_VPL_Tree_Node* returnValueType;
    Arcadia_Visuals_VPL_Tree_Node* name;
    Arcadia_List* parameters;
    Arcadia_Visuals_VPL_Tree_Node* body;
  } functionDefinition;
  struct {
    Arcadia_Visuals_VPL_Tree_Node* type;
    Arcadia_Visuals_VPL_Tree_Node* name;
  } parameterVariableDefinition;
  struct {
    Arcadia_Visuals_VPL_Tree_Node* target;
    Arcadia_List* arguments;
  } call;
  struct {
    Arcadia_Visuals_VPL_Tree_Node*lhs, *rhs;
  } assignment;
  struct {
    Arcadia_Visuals_VPL_Tree_Node* type, *name;
  } variableDefinition;
};

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeCall
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* target
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeNumber
  (
    Arcadia_Thread* thread,
    Arcadia_String* literal
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeAccess
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeAdd
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeSubtract
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeMultiply
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeDivide
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeName
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeStatementList
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeAssignment
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* lhs,
    Arcadia_Visuals_VPL_Tree_Node* rhs
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* type,
    Arcadia_Visuals_VPL_Tree_Node* name
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* type,
    Arcadia_Visuals_VPL_Tree_Node* name
  );

Arcadia_Visuals_VPL_Tree_Node*
Arcadia_Visuals_VPL_Tree_makeFunctionDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree_Node* returnValueType,
    Arcadia_Visuals_VPL_Tree_Node* name,
    Arcadia_List* parameters,
    Arcadia_Visuals_VPL_Tree_Node* body
  );

#endif // ARCADIA_VISUALS_VPL_TREE_NODE_H_INCLUDED
