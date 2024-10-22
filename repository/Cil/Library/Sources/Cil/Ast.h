// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-04

#if !defined(CIL_AST_H_INCLUDED)
#define CIL_AST_H_INCLUDED

#include "R.h"

typedef struct Cil_StatementAst Cil_StatementAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ProgramAst
/// @endcode
/// @code
/// program : statement*
/// @endcode
Rex_declareObjectType("Cil.ProgramAst", Cil_ProgramAst, "R.Object");

struct Cil_ProgramAst {
  R_Object _parent;
  R_List* statements;
};

void
Cil_ProgramAst_construct
  (
    Cil_ProgramAst* self
  );

Cil_ProgramAst*
Cil_ProgramAst_create
  (
  );

void
Cil_ProgramAst_append
  (
    Cil_ProgramAst* self,
    Cil_StatementAst* statement
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.OperandAst", Cil_OperandAst, "R.Object");

struct Cil_OperandAst {
  R_Object _parent;
};

void
Cil_OperandAst_construct
  (
    Cil_OperandAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.BooleanLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.BooleanConstantOperandAst", Cil_BooleanLiteralOperandAst, "Cil.OperandAst");

struct Cil_BooleanLiteralOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_BooleanLiteralOperandAst_construct
  (
    Cil_BooleanLiteralOperandAst* self,
    R_String* value
  );

Cil_BooleanLiteralOperandAst*
Cil_BooleanLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.NumberLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.NumberLiteralOperandAst", Cil_NumberLiteralOperandAst, "Cil.OperandAst");

struct Cil_NumberLiteralOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_NumberLiteralOperandAst_construct
  (
    Cil_NumberLiteralOperandAst* self,
    R_String* value
  );

Cil_NumberLiteralOperandAst*
Cil_NumberLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.StringLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.StringLiteralOperandAst", Cil_StringLiteralOperandAst, "Cil.OperandAst");

struct Cil_StringLiteralOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_StringLiteralOperandAst_construct
  (
    Cil_StringLiteralOperandAst* self,
    R_String* value
  );

Cil_StringLiteralOperandAst*
Cil_StringLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.VariableOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.VariableOperandAst", Cil_VariableOperandAst, "Cil.OperandAst");

struct Cil_VariableOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_VariableOperandAst_construct
  (
    Cil_VariableOperandAst* self,
    R_String* value
  );

Cil_VariableOperandAst*
Cil_VariableOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.VoidLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.VoidLiteralOperandAst", Cil_VoidLiteralOperandAst, "Cil.OperandAst");

struct Cil_VoidLiteralOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_VoidLiteralOperandAst_construct
  (
    Cil_VoidLiteralOperandAst* self,
    R_String* value
  );

Cil_VoidLiteralOperandAst*
Cil_VoidLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ExpressionAst
/// @endcode
Rex_declareObjectType("Cil.ExpressionAst", Cil_ExpressionAst, "R.Object");

struct Cil_ExpressionAst {
  R_Object _parent;
};

void
Cil_ExpressionAst_construct
  (
    Cil_ExpressionAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum Cil_UnaryExpressionAstType Cil_UnaryExpressionAstType;

enum Cil_UnaryExpressionAstType {
  Cil_UnaryExpressionAstType_Negate = 1,
  Cil_UnaryExpressionAstType_Not = 2,
};

/// @code
/// class Cil.UnaryExpressionAst extends Cil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
//// @code
/// (negate|not) <operand1>
/// @endcode
Rex_declareObjectType("Cil.UnaryExpressionAst", Cil_UnaryExpressionAst, "Cil.ExpressionAst");

struct Cil_UnaryExpressionAst {
  Cil_ExpressionAst parent;
  Cil_UnaryExpressionAstType type;
  Cil_OperandAst* operand1;
};

void
Cil_UnaryExpressionAst_construct
  (
    Cil_UnaryExpressionAst* self,
    Cil_UnaryExpressionAstType type,
    Cil_OperandAst* operand1
  );

Cil_UnaryExpressionAst*
Cil_UnaryExpressionAst_create
  (
    Cil_UnaryExpressionAstType type,
    Cil_OperandAst* operand1
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum Cil_BinaryExpressionAstType Cil_BinaryExpressionAstType;

enum Cil_BinaryExpressionAstType {
  Cil_BinaryExpressionAstType_Add = 1,
  Cil_BinaryExpressionAstType_And = 2,
  Cil_BinaryExpressionAstType_Concatenate = 3,
  Cil_BinaryExpressionAstType_Divide = 4,
  Cil_BinaryExpressionAstType_Multiply = 5,
  Cil_BinaryExpressionAstType_Or = 6,
  Cil_BinaryExpressionAstType_Subtract = 7,
};

/// @code
/// class Cil.BinaryOperationExpressionAst extends Cil.ExpressionAst
/// @endcode
/// Represents a binary operations like
//// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Rex_declareObjectType("Cil.BinaryExpressionAst", Cil_BinaryExpressionAst, "Cil.ExpressionAst");

struct Cil_BinaryExpressionAst {
  Cil_ExpressionAst parent;
  Cil_BinaryExpressionAstType type;
  Cil_OperandAst* operand1;
  Cil_OperandAst* operand2;
};

void
Cil_BinaryExpressionAst_construct
  (
    Cil_BinaryExpressionAst* self,
    Cil_BinaryExpressionAstType type,
    Cil_OperandAst* operand1,
    Cil_OperandAst* operand2
  );

Cil_BinaryExpressionAst*
Cil_BinaryExpressionAst_create
  (
    Cil_BinaryExpressionAstType type,
    Cil_OperandAst* operand1,
    Cil_OperandAst* operand2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.LoadExpressionAst extends Cil.ExpressionAst
/// @endcode
/// Represents a load expression
/// @code
/// BooleanLiteral | NumberLiteral | StringLiteral | VariableName
/// @endcode
Rex_declareObjectType("Cil.LiteralExpressionAst", Cil_LoadExpressionAst, "Cil.ExpressionAst");

struct Cil_LoadExpressionAst {
  Cil_ExpressionAst parent;
  Cil_OperandAst* operand;
};

void
Cil_LoadExpressionAst_construct
  (
    Cil_LoadExpressionAst* self,
    Cil_OperandAst* operand
  );

Cil_LoadExpressionAst*
Cil_LoadExpressionAst_create
  (
    Cil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.StatementAst
/// @endcode
Rex_declareObjectType("Cil.StatementAst", Cil_StatementAst, "R.Object");

struct Cil_StatementAst {
  R_Object _parent;
};

void
Cil_StatementAst_construct
  (
    Cil_StatementAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ExpressionStatementAst extends Cil.Statement
/// @endcode
/// Represents
Rex_declareObjectType("Cil.ExpressionStatementAst", Cil_ExpressionStatementAst, "Cil.StatementAst");

struct Cil_ExpressionStatementAst {
  Cil_StatementAst parent;
  R_String* targetVariableName;
  Cil_ExpressionAst* expression;
};

void
Cil_ExpressionStatementAst_construct
  (
    Cil_ExpressionStatementAst* self,
    R_String* targetVariableName,
    Cil_ExpressionAst* expression
  );

/// @brief Create a CIL expression statement AST.
/// @return A pointer to this CIL expression statement ASt.
Cil_ExpressionStatementAst*
Cil_ExpressionStatementAst_create
  (
    R_String* targetVariableName,
    Cil_ExpressionAst* expression
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.LabelStatementAst extends Cil.Statement
/// @endcode
/// Represents
/// @code
/// name ':'
/// @endcode
Rex_declareObjectType("Cil.LabelStatementAst", Cil_LabelStatementAst, "Cil.StatementAst");

struct Cil_LabelStatementAst {
  Cil_StatementAst parent;
  R_String* labelName;
};

void
Cil_LabelStatementAst_construct
  (
    Cil_LabelStatementAst* self,
    R_String* labelName
  );

/// @brief Create a CIL label statement AST.
/// @return A pointer to this CIL label statement AST.
Cil_LabelStatementAst*
Cil_LabelStatementAst_create
  (
    R_String* labelName
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ReturnStatementAst extends Cil.Statement
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Rex_declareObjectType("Cil.ReturnStatementAst", Cil_ReturnStatementAst, "Cil.StatementAst");

struct Cil_ReturnStatementAst {
  Cil_StatementAst parent;
  Cil_OperandAst* operand;
};

void
Cil_ReturnStatementAst_construct
  (
    Cil_ReturnStatementAst* self,
    Cil_OperandAst* operand
  );

/// @brief Create a CIL return statement AST.
/// @return A pointer to this CIL return statement AST.
Cil_ReturnStatementAst*
Cil_ReturnStatementAst_create
  (
    Cil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.DefinitionAst extends R.Object
/// @endcode
Rex_declareObjectType("Cil.DefinitionAst", Cil_DefinitionAst, "R.Object");

struct Cil_DefinitionAst {
  R_Object _parent;
};

void
Cil_DefinitionAst_construct
  (
    Cil_DefinitionAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ProcedureDefinitionAst extends Cil.DefinitionAst
/// @endcode
/// Represents
/// @code
/// procedureDefinition : 'procedure' ('native' string)? name procedureParameters procedureBody
/// procedureBody : '{' statements '}'
/// @endcode
Rex_declareObjectType("Cil.ProcedureDefinitionAst", Cil_ProcedureDefinitionAst, "R.Object");

struct Cil_ProcedureDefinitionAst {
  Cil_DefinitionAst _parent;
  R_String* nativeName;
  R_String* procedureName;
  R_List* procedureParameters;
  R_List* procedureBody;
};

void
Cil_ProcedureDefinitionAst_construct
  (
    Cil_ProcedureDefinitionAst* self,
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  );

/// @brief Create a CIL procedure definition AST.
/// @return A pointer to this CIL procedure definition AST.
Cil_ProcedureDefinitionAst*
Cil_ProcedureDefinitionAst_create
  (
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ClassDefinitionAst extends Cil.DefinitionAst
/// @endcode
/// Represents
/// @code
/// classDefinition : 'class' name ('extends' name)? classBody
/// classBody : '{' classMemberDefinition* '}'
/// @endcode
Rex_declareObjectType("Cil.ClassDefinitionAst", Cil_ClassDefinitionAst, "Cil.DefinitionAst");

struct Cil_ClassDefinitionAst {
  Cil_DefinitionAst _parent;
  R_String* className;
  R_String* extendedClassName;
  R_List* classBody;
};

void
Cil_ClassDefinitionAst_construct
  (
    Cil_ClassDefinitionAst* self,
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  );

/// @brief Create a CIL class definition AST.
/// @return A pointer to this CIL class definition AST.
Cil_ClassDefinitionAst*
Cil_ClassDefinitionAst_create
  (
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.ClassMemberDefinitionAst", Cil_ClassMemberDefinitionAst, "Cil.DefinitionAst");

struct Cil_ClassMemberDefinitionAst {
  Cil_DefinitionAst _parent;
};

void
Cil_ClassMemberDefinitionAst_construct
  (
    Cil_ClassMemberDefinitionAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.MethodDefinitionAst", Cil_MethodDefinitionAst, "Cil.ClassMemberDefinitionAst");

struct Cil_MethodDefinitionAst {
  Cil_ClassMemberDefinitionAst _parent;
  R_String* methodName;
  R_List* methodParameters;
  R_List* methodBody;
};

void
Cil_MethodDefinitionAst_construct
  ( 
    Cil_MethodDefinitionAst* self,
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

Cil_MethodDefinitionAst*
Cil_MethodDefinitionAst_create
  (
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.ConstructorDefinitionAst", Cil_ConstructorDefinitionAst, "Cil.ClassMemberDefinitionAst");

struct Cil_ConstructorDefinitionAst {
  Cil_ClassMemberDefinitionAst _parent;
  R_List* constructorParameters;
  R_List* constructorBody;
};

void
Cil_ConstructorDefinitionAst_construct
  (
    Cil_ConstructorDefinitionAst* self,
    R_List* constructorParameters,
    R_List* constructorBody
  );

Cil_ConstructorDefinitionAst*
Cil_ConstructorDefinitionAst_create
  (
    R_List* constructorParameters,
    R_List* constructorBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.VariableDefinitionAst", Cil_VariableDefinitionAst, "Cil.ClassMemberDefinitionAst");

struct Cil_VariableDefinitionAst {
  Cil_ClassMemberDefinitionAst _parent;
  R_String* variableName;
};

void
Cil_VariableDefinitionAst_construct
  (
    Cil_VariableDefinitionAst* self,
    R_String* name
  );

Cil_VariableDefinitionAst*
Cil_VariableDefinitionAst_create
  (
    R_String* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // CIL_AST_H_INCLUDED
