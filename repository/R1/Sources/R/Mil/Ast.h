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

#if !defined(R_MIL_AST_H_INCLUDED)
#define R_MIL_AST_H_INCLUDED

#include "R.h"

typedef struct R_Mil_StatementAst R_Mil_StatementAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ProgramAst
/// @endcode
/// @code
/// program : statement*
/// @endcode
Rex_declareObjectType("Cil.ProgramAst", R_Mil_ProgramAst, "R.Object");

struct R_Mil_ProgramAst {
  R_Object _parent;
  R_List* statements;
};

void
R_Mil_ProgramAst_construct
  (
    R_Mil_ProgramAst* self
  );

R_Mil_ProgramAst*
R_Mil_ProgramAst_create
  (
  );

void
R_Mil_ProgramAst_append
  (
    R_Mil_ProgramAst* self,
    R_Mil_StatementAst* statement
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.OperandAst", R_Mil_OperandAst, "R.Object");

struct R_Mil_OperandAst {
  R_Object _parent;
};

void
R_Mil_OperandAst_construct
  (
    R_Mil_OperandAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.BooleanLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.BooleanConstantOperandAst", R_Mil_BooleanLiteralOperandAst, "Cil.OperandAst");

struct R_Mil_BooleanLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

void
R_Mil_BooleanLiteralOperandAst_construct
  (
    R_Mil_BooleanLiteralOperandAst* self,
    R_String* value
  );

R_Mil_BooleanLiteralOperandAst*
R_Mil_BooleanLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.NumberLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.NumberLiteralOperandAst", R_Mil_NumberLiteralOperandAst, "Cil.OperandAst");

struct R_Mil_NumberLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

void
R_Mil_NumberLiteralOperandAst_construct
  (
    R_Mil_NumberLiteralOperandAst* self,
    R_String* value
  );

R_Mil_NumberLiteralOperandAst*
R_Mil_NumberLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.StringLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.StringLiteralOperandAst", R_Mil_StringLiteralOperandAst, "Cil.OperandAst");

struct R_Mil_StringLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

void
R_Mil_StringLiteralOperandAst_construct
  (
    R_Mil_StringLiteralOperandAst* self,
    R_String* value
  );

R_Mil_StringLiteralOperandAst*
R_Mil_StringLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.VariableOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.VariableOperandAst", R_Mil_VariableOperandAst, "Cil.OperandAst");

struct R_Mil_VariableOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

void
R_Mil_VariableOperandAst_construct
  (
    R_Mil_VariableOperandAst* self,
    R_String* value
  );

R_Mil_VariableOperandAst*
R_Mil_VariableOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.VoidLiteralOperandAst extends Cil.OperandAst
/// @endcode
Rex_declareObjectType("Cil.VoidLiteralOperandAst", R_Mil_VoidLiteralOperandAst, "Cil.OperandAst");

struct R_Mil_VoidLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

void
R_Mil_VoidLiteralOperandAst_construct
  (
    R_Mil_VoidLiteralOperandAst* self,
    R_String* value
  );

R_Mil_VoidLiteralOperandAst*
R_Mil_VoidLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ExpressionAst
/// @endcode
Rex_declareObjectType("Cil.ExpressionAst", R_Mil_ExpressionAst, "R.Object");

struct R_Mil_ExpressionAst {
  R_Object _parent;
};

void
R_Mil_ExpressionAst_construct
  (
    R_Mil_ExpressionAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum R_Mil_UnaryExpressionAstType R_Mil_UnaryExpressionAstType;

enum R_Mil_UnaryExpressionAstType {
  R_Mil_UnaryExpressionAstType_Negate = 1,
  R_Mil_UnaryExpressionAstType_Not = 2,
};

/// @code
/// class Cil.UnaryExpressionAst extends Cil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
//// @code
/// (negate|not) <operand1>
/// @endcode
Rex_declareObjectType("Cil.UnaryExpressionAst", R_Mil_UnaryExpressionAst, "Cil.ExpressionAst");

struct R_Mil_UnaryExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_UnaryExpressionAstType type;
  R_Mil_OperandAst* operand1;
};

void
R_Mil_UnaryExpressionAst_construct
  (
    R_Mil_UnaryExpressionAst* self,
    R_Mil_UnaryExpressionAstType type,
    R_Mil_OperandAst* operand1
  );

R_Mil_UnaryExpressionAst*
R_Mil_UnaryExpressionAst_create
  (
    R_Mil_UnaryExpressionAstType type,
    R_Mil_OperandAst* operand1
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum R_Mil_BinaryExpressionAstType R_Mil_BinaryExpressionAstType;

enum R_Mil_BinaryExpressionAstType {
  R_Mil_BinaryExpressionAstType_Add = 1,
  R_Mil_BinaryExpressionAstType_And = 2,
  R_Mil_BinaryExpressionAstType_Concatenate = 3,
  R_Mil_BinaryExpressionAstType_Divide = 4,
  R_Mil_BinaryExpressionAstType_Multiply = 5,
  R_Mil_BinaryExpressionAstType_Or = 6,
  R_Mil_BinaryExpressionAstType_Subtract = 7,
};

/// @code
/// class Cil.BinaryOperationExpressionAst extends Cil.ExpressionAst
/// @endcode
/// Represents a binary operations like
//// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Rex_declareObjectType("Cil.BinaryExpressionAst", R_Mil_BinaryExpressionAst, "Cil.ExpressionAst");

struct R_Mil_BinaryExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_BinaryExpressionAstType type;
  R_Mil_OperandAst* operand1;
  R_Mil_OperandAst* operand2;
};

void
R_Mil_BinaryExpressionAst_construct
  (
    R_Mil_BinaryExpressionAst* self,
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  );

R_Mil_BinaryExpressionAst*
R_Mil_BinaryExpressionAst_create
  (
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.LoadExpressionAst extends Cil.ExpressionAst
/// @endcode
/// Represents a load expression
/// @code
/// BooleanLiteral | NumberLiteral | StringLiteral | VariableName
/// @endcode
Rex_declareObjectType("Cil.LiteralExpressionAst", R_Mil_LoadExpressionAst, "Cil.ExpressionAst");

struct R_Mil_LoadExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_OperandAst* operand;
};

void
R_Mil_LoadExpressionAst_construct
  (
    R_Mil_LoadExpressionAst* self,
    R_Mil_OperandAst* operand
  );

R_Mil_LoadExpressionAst*
R_Mil_LoadExpressionAst_create
  (
    R_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.StatementAst
/// @endcode
Rex_declareObjectType("Cil.StatementAst", R_Mil_StatementAst, "R.Object");

struct R_Mil_StatementAst {
  R_Object _parent;
};

void
R_Mil_StatementAst_construct
  (
    R_Mil_StatementAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ExpressionStatementAst extends Cil.Statement
/// @endcode
/// Represents
Rex_declareObjectType("Cil.ExpressionStatementAst", R_Mil_ExpressionStatementAst, "Cil.StatementAst");

struct R_Mil_ExpressionStatementAst {
  R_Mil_StatementAst parent;
  R_String* targetVariableName;
  R_Mil_ExpressionAst* expression;
};

void
R_Mil_ExpressionStatementAst_construct
  (
    R_Mil_ExpressionStatementAst* self,
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  );

/// @brief Create a CIL expression statement AST.
/// @return A pointer to this CIL expression statement ASt.
R_Mil_ExpressionStatementAst*
R_Mil_ExpressionStatementAst_create
  (
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.LabelStatementAst extends Cil.Statement
/// @endcode
/// Represents
/// @code
/// name ':'
/// @endcode
Rex_declareObjectType("Cil.LabelStatementAst", R_Mil_LabelStatementAst, "Cil.StatementAst");

struct R_Mil_LabelStatementAst {
  R_Mil_StatementAst parent;
  R_String* labelName;
};

void
R_Mil_LabelStatementAst_construct
  (
    R_Mil_LabelStatementAst* self,
    R_String* labelName
  );

/// @brief Create a CIL label statement AST.
/// @return A pointer to this CIL label statement AST.
R_Mil_LabelStatementAst*
R_Mil_LabelStatementAst_create
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
Rex_declareObjectType("Cil.ReturnStatementAst", R_Mil_ReturnStatementAst, "Cil.StatementAst");

struct R_Mil_ReturnStatementAst {
  R_Mil_StatementAst parent;
  R_Mil_OperandAst* operand;
};

void
R_Mil_ReturnStatementAst_construct
  (
    R_Mil_ReturnStatementAst* self,
    R_Mil_OperandAst* operand
  );

/// @brief Create a CIL return statement AST.
/// @return A pointer to this CIL return statement AST.
R_Mil_ReturnStatementAst*
R_Mil_ReturnStatementAst_create
  (
    R_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.DefinitionAst extends R.Object
/// @endcode
Rex_declareObjectType("Cil.DefinitionAst", R_Mil_DefinitionAst, "R.Object");

struct R_Mil_DefinitionAst {
  R_Object _parent;
};

void
R_Mil_DefinitionAst_construct
  (
    R_Mil_DefinitionAst* self
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
Rex_declareObjectType("Cil.ProcedureDefinitionAst", R_Mil_ProcedureDefinitionAst, "R.Object");

struct R_Mil_ProcedureDefinitionAst {
  R_Mil_DefinitionAst _parent;
  R_String* nativeName;
  R_String* procedureName;
  R_List* procedureParameters;
  R_List* procedureBody;
};

void
R_Mil_ProcedureDefinitionAst_construct
  (
    R_Mil_ProcedureDefinitionAst* self,
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  );

/// @brief Create a CIL procedure definition AST.
/// @return A pointer to this CIL procedure definition AST.
R_Mil_ProcedureDefinitionAst*
R_Mil_ProcedureDefinitionAst_create
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
Rex_declareObjectType("Cil.ClassDefinitionAst", R_Mil_ClassDefinitionAst, "Cil.DefinitionAst");

struct R_Mil_ClassDefinitionAst {
  R_Mil_DefinitionAst _parent;
  R_String* className;
  R_String* extendedClassName;
  R_List* classBody;
};

void
R_Mil_ClassDefinitionAst_construct
  (
    R_Mil_ClassDefinitionAst* self,
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  );

/// @brief Create a CIL class definition AST.
/// @return A pointer to this CIL class definition AST.
R_Mil_ClassDefinitionAst*
R_Mil_ClassDefinitionAst_create
  (
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, "Cil.DefinitionAst");

struct R_Mil_ClassMemberDefinitionAst {
  R_Mil_DefinitionAst _parent;
};

void
R_Mil_ClassMemberDefinitionAst_construct
  (
    R_Mil_ClassMemberDefinitionAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.MethodDefinitionAst", R_Mil_MethodDefinitionAst, "Cil.ClassMemberDefinitionAst");

struct R_Mil_MethodDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_String* methodName;
  R_List* methodParameters;
  R_List* methodBody;
};

void
R_Mil_MethodDefinitionAst_construct
  ( 
    R_Mil_MethodDefinitionAst* self,
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.ConstructorDefinitionAst", R_Mil_ConstructorDefinitionAst, "Cil.ClassMemberDefinitionAst");

struct R_Mil_ConstructorDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_List* constructorParameters;
  R_List* constructorBody;
};

void
R_Mil_ConstructorDefinitionAst_construct
  (
    R_Mil_ConstructorDefinitionAst* self,
    R_List* constructorParameters,
    R_List* constructorBody
  );

R_Mil_ConstructorDefinitionAst*
R_Mil_ConstructorDefinitionAst_create
  (
    R_List* constructorParameters,
    R_List* constructorBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Cil.VariableDefinitionAst", R_Mil_VariableDefinitionAst, "Cil.ClassMemberDefinitionAst");

struct R_Mil_VariableDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_String* variableName;
};

void
R_Mil_VariableDefinitionAst_construct
  (
    R_Mil_VariableDefinitionAst* self,
    R_String* name
  );

R_Mil_VariableDefinitionAst*
R_Mil_VariableDefinitionAst_create
  (
    R_String* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_AST_H_INCLUDED
