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
Rex_declareObjectType("Mil.ModuleAst", R_Mil_ModuleAst, "R.Object");

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
/// class Mil.OperandAst
/// @endcode
Rex_declareObjectType("Mil.OperandAst", R_Mil_OperandAst, "R.Object");

struct R_Mil_OperandAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Mil.BooleanLiteralOperandAst extends Mil.OperandAst
/// @endcode
Rex_declareObjectType("Mil.BooleanConstantOperandAst", R_Mil_BooleanLiteralOperandAst, "Mil.OperandAst");

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
/// class Mil.NumberLiteralOperandAst extends Mil.OperandAst
/// @endcode
Rex_declareObjectType("Mil.NumberLiteralOperandAst", R_Mil_NumberLiteralOperandAst, "Mil.OperandAst");

struct R_Mil_NumberLiteralOperandAst {
  R_Mil_OperandAst parent;
  R_String* value;
};

R_Mil_NumberLiteralOperandAst*
R_Mil_NumberLiteralOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Mil.StringLiteralOperandAst extends Mil.OperandAst
/// @endcode
Rex_declareObjectType("Mil.StringLiteralOperandAst", R_Mil_StringLiteralOperandAst, "Mil.OperandAst");

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
/// class Mil.VariableOperandAst extends Mil.OperandAst
/// @endcode
Rex_declareObjectType("Mil.VariableOperandAst", R_Mil_VariableOperandAst, "Mil.OperandAst");

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
/// class Mil.VoidLiteralOperandAst extends Mil.OperandAst
/// @endcode
Rex_declareObjectType("Mil.VoidLiteralOperandAst", R_Mil_VoidLiteralOperandAst, "Mil.OperandAst");

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
/// class Mil.ExpressionAst
/// @endcode
Rex_declareObjectType("Mil.ExpressionAst", R_Mil_ExpressionAst, "R.Object");

struct R_Mil_ExpressionAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Mil.UnaryExpressionAst extends Mil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
//// @code
/// invoke variableOperand '(' (operand (',' operand)*)? ')'
/// @endcode
Rex_declareObjectType("Mil.InvokeExpressionAst", R_Mil_InvokeExpressionAst, "Mil.ExpressionAst");

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
/// class Mil.UnaryExpressionAst extends Mil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
//// @code
/// (negate|not) <operand1>
/// @endcode
Rex_declareObjectType("Mil.UnaryExpressionAst", R_Mil_UnaryExpressionAst, "Mil.ExpressionAst");

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
/// class Mil.BinaryOperationExpressionAst extends Mil.ExpressionAst
/// @endcode
/// Represents a binary operations like
//// @code
/// (add|and|divide|subtract|multiply|or) <operand1> <operand2>
/// @endcode
Rex_declareObjectType("Mil.BinaryExpressionAst", R_Mil_BinaryExpressionAst, "Mil.ExpressionAst");

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
/// class Mil.LoadExpressionAst extends Mil.ExpressionAst
/// @endcode
/// Represents a load expression
/// @code
/// BooleanLiteral | NumberLiteral | StringLiteral | VariableName
/// @endcode
Rex_declareObjectType("Mil.LiteralExpressionAst", R_Mil_LoadExpressionAst, "Mil.ExpressionAst");

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
/// class Mil.StatementAst
/// @endcode
Rex_declareObjectType("Mil.StatementAst", R_Mil_StatementAst, "R.Object");

struct R_Mil_StatementAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Mil.ExpressionStatementAst extends Mil.Statement
/// @endcode
/// Represents
Rex_declareObjectType("Mil.ExpressionStatementAst", R_Mil_ExpressionStatementAst, "Mil.StatementAst");

struct R_Mil_ExpressionStatementAst {
  R_Mil_StatementAst parent;
  R_String* targetVariableName;
  R_Mil_ExpressionAst* expression;
};

/// @brief Create a CIL expression statement AST.
/// @return A pointer to this CIL expression statement ASt.
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
/// class Mil.LabelStatementAst extends Mil.Statement
/// @endcode
/// Represents
/// @code
/// name ':'
/// @endcode
Rex_declareObjectType("Mil.LabelStatementAst", R_Mil_LabelStatementAst, "Mil.StatementAst");

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
/// class Mil.ReturnStatementAst extends Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'return' (BooleanLiteral | NumberLiteral | StringLiteral | VariableName)
/// @endcode
Rex_declareObjectType("Mil.ReturnStatementAst", R_Mil_ReturnStatementAst, "Mil.StatementAst");

struct R_Mil_ReturnStatementAst {
  R_Mil_StatementAst parent;
  R_Mil_OperandAst* operand;
};

/// @brief Create a CIL return statement AST.
/// @return A pointer to this CIL return statement AST.
R_Mil_ReturnStatementAst*
R_Mil_ReturnStatementAst_create
  (
    R_Mil_OperandAst* operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Mil.DefinitionAst extends R.Object
/// @endcode
Rex_declareObjectType("Mil.DefinitionAst", R_Mil_DefinitionAst, "R.Object");

struct R_Mil_DefinitionAst {
  R_Object _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Mil.ProcedureDefinitionAst extends Mil.DefinitionAst
/// @endcode
/// Represents
/// @code
/// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters procedureBody
/// procedureBody : '{' statements '}'
/// @endcode
Rex_declareObjectType("Mil.ProcedureDefinitionAst", R_Mil_ProcedureDefinitionAst, "R.Object");

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
/// class Mil.ClassDefinitionAst extends Mil.DefinitionAst {
///   construct(className:String, extendedClassName:String, classBody:List)
/// }
/// @endcode
/// Represents
/// @code
/// classDefinition : 'class' name ('extends' name)? classBody
/// classBody : '{' classMemberDefinition* '}'
/// @endcode
Rex_declareObjectType("Mil.ClassDefinitionAst", R_Mil_ClassDefinitionAst, "Mil.DefinitionAst");

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

Rex_declareObjectType("Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, "Mil.DefinitionAst");

struct R_Mil_ClassMemberDefinitionAst {
  R_Mil_DefinitionAst _parent;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Mil.MethodDefinitionAst", R_Mil_MethodDefinitionAst, "Mil.ClassMemberDefinitionAst");

struct R_Mil_MethodDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_String* methodName;
  R_List* methodParameters;
  R_List* methodBody;
};

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Mil.ConstructorDefinitionAst", R_Mil_ConstructorDefinitionAst, "Mil.ClassMemberDefinitionAst");

struct R_Mil_ConstructorDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  R_List* constructorParameters;
  R_List* constructorBody;
};

R_Mil_ConstructorDefinitionAst*
R_Mil_ConstructorDefinitionAst_create
  (
    R_List* constructorParameters,
    R_List* constructorBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Mil.VariableDefinitionAst", R_Mil_VariableDefinitionAst, "Mil.ClassMemberDefinitionAst");

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
