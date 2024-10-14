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
/// class Cil.UnaryExpressionAst
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
  Cil_BinaryExpressionAstType_Concatenate = 2,
  Cil_BinaryExpressionAstType_Divide = 3,
  Cil_BinaryExpressionAstType_Multiply = 4,
  Cil_BinaryExpressionAstType_Subtract = 5,
};

/// @code
/// class Cil.BinaryOperationExpressionAst
/// @endcode
/// Represents a binary operations like
//// @code
/// (add|subtract|multiply|divide) <operand1> <operand2>
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
/// class Cil.LoadExpressionAst
/// @endcode
/// Represents a load expression
/// @code
/// 'load' BooleanLiteral | 'load' NumberLiteral | 'load' StringLiteral | 'load' VariableName
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
/// class Cil.ExpressionStatementAst
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
/// class Cil.LabelStatementAst
/// @endcode
/// Represents
Rex_declareObjectType("Cil.LabelStatementAst", Cil_LabelStatementAst, "Cil.LabelStatementAst");

struct Cil_LabelStatementAst {
  Cil_StatementAst parent;
  R_String* labelName;
};

void
Cil_LabelStatementAst_construct
  (
    Cil_LabelStatementAst* self,
    R_String* targetVariableName
  );

/// @brief Create a CIL label statement AST.
/// @return A pointer to this CIL label statement ASt.
Cil_LabelStatementAst*
Cil_LabelStatementAst_create
  (
    R_String* labelName
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // CIL_AST_H_INCLUDED
