#if !defined(ARCADIA_VISUALS_VPL_TREE_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_TREE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// The empty tree. Has neither children nor a value.
#define Arcadia_Visuals_VPL_TreeFlags_Empty (0)

// <expression> '+' <expression>
#define Arcadia_Visuals_VPL_TreeFlags_Add (1)

// <expression> '-' <expression>
#define Arcadia_Visuals_VPL_TreeFlags_Subtract (2)

// <expression> '*' <expression>
#define Arcadia_Visuals_VPL_TreeFlags_Multiply (3)

// <expression> '/' <expression>
#define Arcadia_Visuals_VPL_TreeFlags_Divide (4)

// <name>
#define Arcadia_Visuals_VPL_TreeFlags_Name (5)

// <expression> '=' <expression> ';'
#define Arcadia_Visuals_VPL_TreeFlags_Assignment (6)

// <type> <name> ';'
#define Arcadia_Visuals_VPL_TreeFlags_VariableDefinition (7)

// <expression> '.' <expression>
#define Arcadia_Visuals_VPL_TreeFlags_Access (8)

// <statement>*
#define Arcadia_Visuals_VPL_TreeFlags_StatementList (9)

// <integer>, <natural>, <real>
#define Arcadia_Visuals_VPL_TreeFlags_Number (10)

// <expression> '(' <arguments> ')'
#define Arcadia_Visuals_VPL_TreeFlags_Call (11)

// <type> <name>
#define Arcadia_Visuals_VPL_TreeFlags_ParameterVariableDefinition (12)

// <returnValueType> <name> '(' ´<parameters> ')' <body>
#define Arcadia_Visuals_VPL_TreeFlags_FunctionDefinition (12)

Arcadia_declareObjectType(u8"Arcadia.Visuals.VPL.Tree", Arcadia_Visuals_VPL_Tree,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_TreeDispatch {
  Arcadia_ObjectDispatch _parent;
};

// @todo
// This implementation is  quite inefficient in terms of memory/visitation cost and it is error-prone.
// Fix by using the typical sub-typing approach. However, it is good for now until VPL matures.
struct Arcadia_Visuals_VPL_Tree {
  Arcadia_Object _parent;
  Arcadia_Natural8Value flags;
  Arcadia_String* literal; // For Number
  Arcadia_String* name; // For Name
  Arcadia_List* statementList; // For StatementList
  struct {
    Arcadia_Visuals_VPL_Tree* returnValueType;
    Arcadia_Visuals_VPL_Tree* name;
    Arcadia_List* parameters;
    Arcadia_Visuals_VPL_Tree* body;
  } functionDefinition;
  struct {
    Arcadia_Visuals_VPL_Tree* type;
    Arcadia_Visuals_VPL_Tree* name;
  } parameterVariableDefinition;
  struct {
    Arcadia_Visuals_VPL_Tree* target;
    Arcadia_List* arguments;
  } call;
  struct {
    Arcadia_Visuals_VPL_Tree* lhs, * rhs;
  } access;
  struct {
    Arcadia_Visuals_VPL_Tree* lhs, * rhs;
  } add;
  struct {
    Arcadia_Visuals_VPL_Tree* lhs, * rhs;
  } subtract;
  struct {
    Arcadia_Visuals_VPL_Tree* lhs, *rhs;
  } multiply;
  struct {
    Arcadia_Visuals_VPL_Tree* lhs, * rhs;
  } divide;
  struct {
    Arcadia_Visuals_VPL_Tree *lhs, *rhs;
  } assignment;
  struct {
    Arcadia_Visuals_VPL_Tree* type, *name;
  } variableDefinition;
};

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeCall
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* target
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeNumber
  (
    Arcadia_Thread* thread,
    Arcadia_String* literal
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeAccess
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeAdd
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeSubtract
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeMultiply
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeDivide
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeName
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeStatementList
  (
    Arcadia_Thread* thread
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeAssignment
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* type,
    Arcadia_Visuals_VPL_Tree* name
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* type,
    Arcadia_Visuals_VPL_Tree* name
  );

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeFunctionDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* returnValueType,
    Arcadia_Visuals_VPL_Tree* name,
    Arcadia_List* parameters,
    Arcadia_Visuals_VPL_Tree* body
  );

#endif // ARCADIA_VISUALS_VPL_TREE_H_INCLUDED
