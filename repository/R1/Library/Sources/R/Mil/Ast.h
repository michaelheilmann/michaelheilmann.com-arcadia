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

typedef struct R_Mil_DefinitionAst R_Mil_DefinitionAst;
typedef struct R_Mil_StatementAst R_Mil_StatementAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ModuleAst
/// @endcode
/// @code
/// module : definition*
/// @endcode
Rex_declareObjectType("R.Mil.ModuleAst", R_Mil_ModuleAst, "R.Object");

struct R_Mil_ModuleAst {
  R_Object _parent;
  R_List* definitions;
};

R_Mil_ModuleAst*
R_Mil_ModuleAst_create
  (
  );

void
R_Mil_ModuleAst_appendDefinition
  (
    R_Mil_ModuleAst* self,
    R_Mil_DefinitionAst* definition
  );

R_SizeValue
R_Mil_ModuleAst_getNumberOfDefinitions
  (
    R_Mil_ModuleAst* self
  );

R_Mil_DefinitionAst*
R_Mil_ModuleAst_getDefinitionAt
  (
    R_Mil_ModuleAst* self,
    R_SizeValue index
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.OperandAst", R_Mil_OperandAst, "R.Object");

struct R_Mil_OperandAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.BooleanLiteralOperandAst extends R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.BooleanConstantOperandAst", R_Mil_BooleanLiteralOperandAst, "R.Mil.OperandAst");

struct R_Mil_BooleanLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

R_Mil_BooleanLiteralOperandAst*
R_Mil_BooleanLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.IntegerLiteralOperandAst extends R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.IntegerLiteralOperandAst", R_Mil_IntegerLiteralOperandAst, "R.Mil.OperandAst");

struct R_Mil_IntegerLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

/// @undefined @a value is not an integer literal
R_Mil_IntegerLiteralOperandAst*
R_Mil_IntegerLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.RealLiteralOperandAst extends R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.RealLiteralOperandAst", R_Mil_RealLiteralOperandAst, "R.Mil.OperandAst");

struct R_Mil_RealLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

/// @undefined @a value is not a real literal
R_Mil_RealLiteralOperandAst*
R_Mil_RealLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.StringLiteralOperandAst extends R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.StringLiteralOperandAst", R_Mil_StringLiteralOperandAst, "R.Mil.OperandAst");

struct R_Mil_StringLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

R_Mil_StringLiteralOperandAst*
R_Mil_StringLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.VariableOperandAst extends R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.VariableOperandAst", R_Mil_VariableOperandAst, "R.Mil.OperandAst");

struct R_Mil_VariableOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

R_Mil_VariableOperandAst*
R_Mil_VariableOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.VoidLiteralOperandAst extends R.Mil.OperandAst
/// @endcode
Rex_declareObjectType("R.Mil.VoidLiteralOperandAst", R_Mil_VoidLiteralOperandAst, "R.Mil.OperandAst");

struct R_Mil_VoidLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

R_Mil_VoidLiteralOperandAst*
R_Mil_VoidLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ExpressionAst
/// @endcode
Rex_declareObjectType("R.Mil.ExpressionAst", R_Mil_ExpressionAst, "R.Object");

struct R_Mil_ExpressionAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.UnaryExpressionAst extends R.Mil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
/// @code
/// invoke variableOperand '(' (operand (',' operand)*)? ')'
/// @endcode
Rex_declareObjectType("R.Mil.InvokeExpressionAst", R_Mil_InvokeExpressionAst, "R.Mil.ExpressionAst");

struct R_Mil_InvokeExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_VariableOperandAst* callee;
  R_List* operands;
};

R_Mil_InvokeExpressionAst*
R_Mil_InvokeExpressionAst_create
  (
    R_Mil_VariableOperandAst* callee,
    R_List* operands
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum R_Mil_UnaryExpressionAstType R_Mil_UnaryExpressionAstType;

enum R_Mil_UnaryExpressionAstType {
  R_Mil_UnaryExpressionAstType_Negate = 1,
  R_Mil_UnaryExpressionAstType_Not = 2,
};

/// @code
/// class R.Mil.UnaryExpressionAst extends R.Mil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
/// @code
/// (negate|not) <operand1>
/// @endcode
Rex_declareObjectType("R.Mil.UnaryExpressionAst", R_Mil_UnaryExpressionAst, "R.Mil.ExpressionAst");

struct R_Mil_UnaryExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_UnaryExpressionAstType type;
  R_Mil_OperandAst* operand1;
};

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
/// class R.Mil.BinaryOperationExpressionAst extends R.Mil.ExpressionAst
/// @endcode
/// Represents a binary operations like
/// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Rex_declareObjectType("R.Mil.BinaryExpressionAst", R_Mil_BinaryExpressionAst, "R.Mil.ExpressionAst");

struct R_Mil_BinaryExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_BinaryExpressionAstType type;
  R_Mil_OperandAst* operand1;
  R_Mil_OperandAst* operand2;
};

R_Mil_BinaryExpressionAst*
R_Mil_BinaryExpressionAst_create
  (
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.LoadExpressionAst extends R.Mil.ExpressionAst
/// @endcode
/// Represents a load expression
/// @code
/// BooleanLiteral | NumberLiteral | StringLiteral | VariableName
/// @endcode
Rex_declareObjectType("R.Mil.LiteralExpressionAst", R_Mil_LoadExpressionAst, "R.Mil.ExpressionAst");

struct R_Mil_LoadExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_OperandAst* operand;
};

R_Mil_LoadExpressionAst*
R_Mil_LoadExpressionAst_create
  (
    R_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.StatementAst
/// @endcode
Rex_declareObjectType("R.Mil.StatementAst", R_Mil_StatementAst, "R.Object");

struct R_Mil_StatementAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ExpressionStatementAst extends R.Mil.Statement
/// @endcode
/// Represents
Rex_declareObjectType("R.Mil.ExpressionStatementAst", R_Mil_ExpressionStatementAst, "R.Mil.StatementAst");

struct R_Mil_ExpressionStatementAst {
  R_Mil_StatementAst parent;
  R_String* targetVariableName;
  R_Mil_ExpressionAst* expression;
};

/// @brief Create a Mil expression statement AST.
/// @return A pointer to this Mil expression statement ASt.
R_Mil_ExpressionStatementAst*
R_Mil_ExpressionStatementAst_create
  (
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  );

/// @brief Get the name of the target variable.
/// @param self This expression statement AST.
/// @return The name of the target variable.
R_String*
R_Mil_ExpressionStatementAst_getTargetVariableName
  (
    R_Mil_ExpressionStatementAst* self
  );

/// @brief Get the expression AST of the expression statement AST.
/// @param self This expression statement AST.
/// @return The expression AST.
R_Mil_ExpressionAst*
R_Mil_ExpressionStatementAst_getExpression
  (
    R_Mil_ExpressionStatementAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.LabelStatementAst extends R.Mil.Statement
/// @endcode
/// Represents
/// @code
/// name ':'
/// @endcode
Rex_declareObjectType("R.Mil.LabelStatementAst", R_Mil_LabelStatementAst, "R.Mil.StatementAst");

struct R_Mil_LabelStatementAst {
  R_Mil_StatementAst parent;
  R_String* labelName;
};

/// @brief Create a MIL label statement AST.
/// @return A pointer to this MIL label statement AST.
R_Mil_LabelStatementAst*
R_Mil_LabelStatementAst_create
  (
    R_String* labelName
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ReturnStatementAst extends R.Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Rex_declareObjectType("R.Mil.ReturnStatementAst", R_Mil_ReturnStatementAst, "R.Mil.StatementAst");

struct R_Mil_ReturnStatementAst {
  R_Mil_StatementAst parent;
  R_Mil_OperandAst* operand;
};

/// @brief Create a Mil return statement AST.
/// @return A pointer to this Mil return statement AST.
R_Mil_ReturnStatementAst*
R_Mil_ReturnStatementAst_create
  (
    R_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.DefinitionAst extends R.Object
/// @endcode
Rex_declareObjectType("R.Mil.DefinitionAst", R_Mil_DefinitionAst, "R.Object");

struct R_Mil_DefinitionAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ProcedureDefinitionAst extends R.Mil.DefinitionAst
/// @endcode
/// Represents
/// @code
/// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters
///                     | 'procedure' 'entry'? name procedureParameters procedureBody
/// procedureBody : '{' statements '}'
/// @endcode
Rex_declareObjectType("R.Mil.ProcedureDefinitionAst", R_Mil_ProcedureDefinitionAst, "R.Object");

struct R_Mil_ProcedureDefinitionAst {
  R_Mil_DefinitionAst _parent;
  R_BooleanValue entry;
  R_String* nativeName;
  R_String* procedureName;
  R_List* procedureParameters;
  R_List* procedureBody;
};

/// @brief Create a MIL procedure definition AST.
/// @return A pointer to this MIL procedure definition AST.
R_Mil_ProcedureDefinitionAst*
R_Mil_ProcedureDefinitionAst_create
  (
    R_BooleanValue entry,
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ClassDefinitionAst extends R.Mil.DefinitionAst {
///   construct(className:String, extendedClassName:String, classBody:List)
/// }
/// @endcode
/// Represents
/// @code
/// classDefinition : 'class' name ('extends' name)? classBody
/// classBody : '{' classMemberDefinition* '}'
/// @endcode
Rex_declareObjectType("R.Mil.ClassDefinitionAst", R_Mil_ClassDefinitionAst, "R.Mil.DefinitionAst");

struct R_Mil_ClassDefinitionAst {
  R_Mil_DefinitionAst _parent;
  R_String* className;
  R_String* extendedClassName;
  R_List* classBody;
};

/// @brief Create a MIL class definition AST.
/// @return A pointer to this MIL class definition AST.
R_Mil_ClassDefinitionAst*
R_Mil_ClassDefinitionAst_create
  (
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, "R.Mil.DefinitionAst");

struct R_Mil_ClassMemberDefinitionAst {
  R_Mil_DefinitionAst _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("R.Mil.MethodDefinitionAst", R_Mil_MethodDefinitionAst, "R.Mil.ClassMemberDefinitionAst");

struct R_Mil_MethodDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_String* nativeName;
  R_String* methodName;
  R_List* methodParameters;
  R_List* methodBody;
};

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    R_String* nativeName,
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("R.Mil.ConstructorDefinitionAst", R_Mil_ConstructorDefinitionAst, "R.Mil.ClassMemberDefinitionAst");

struct R_Mil_ConstructorDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_String* nativeName;
  R_List* constructorParameters;
  R_List* constructorBody;
};

R_Mil_ConstructorDefinitionAst*
R_Mil_ConstructorDefinitionAst_create
  (
    R_String* nativeName,
    R_List* constructorParameters,
    R_List* constructorBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("R.Mil.VariableDefinitionAst", R_Mil_VariableDefinitionAst, "R.Mil.ClassMemberDefinitionAst");

struct R_Mil_VariableDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_String* variableName;
};

R_Mil_VariableDefinitionAst*
R_Mil_VariableDefinitionAst_create
  (
    R_String* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_AST_H_INCLUDED
