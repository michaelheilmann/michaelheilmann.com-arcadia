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
typedef struct Cil_ProgramAst Cil_ProgramAst;

typedef struct Cil_OperandAst Cil_OperandAst;

typedef struct Cil_ExpressionAst Cil_ExpressionAst;
typedef struct Cil_UnaryOperationExpressionAst Cil_UnaryOperationExpressionAst;
typedef struct Cil_BinaryOperationExpressionAst Cil_BinaryOperationExpressionAst;

typedef struct Cil_StatementAst Cil_StatementAst;
typedef struct Cil_ExpressionStatementAst Cil_ExpressionStatementAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ProgramAst
/// @endcode
/// @code
/// program : statement*
/// @endcode
typedef struct Cil_ProgramAst Cil_ProgramAst;
void _Cil_ProgramAst_registerType();

struct Cil_ProgramAst {
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
typedef struct Cil_OperandAst Cil_OperandAst;
void _Cil_OperandAst_registerType();

struct Cil_OperandAst {
  uint8_t dummy;
};

void
Cil_OperandAst_construct
  (
    Cil_OperandAst* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.BooleanConstantOperandAst extends Cil.OperandAst
/// @endcode
typedef struct Cil_BooleanConstantOperandAst Cil_BooleanConstantOperandAst;
void _Cil_BooleanConstantOperandAst_registerType();

struct Cil_BooleanConstantOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_BooleanConstantOperandAst_construct
  (
    Cil_BooleanConstantOperandAst* self,
    R_String* value
  );

Cil_BooleanConstantOperandAst*
Cil_BooleanConstantOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.IntegerConstantOperandAst extends Cil.OperandAst
/// @endcode
typedef struct Cil_IntegerConstantOperandAst Cil_IntegerConstantOperandAst;
void _Cil_IntegerConstantOperandAst_registerType();

struct Cil_IntegerConstantOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_IntegerConstantOperandAst_construct
  (
    Cil_IntegerConstantOperandAst* self,
    R_String* value
  );

Cil_IntegerConstantOperandAst*
Cil_IntegerConstantOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.StringConstantOperandAst extends Cil.OperandAst
/// @endcode
typedef struct Cil_StringConstantOperandAst Cil_StringConstantOperandAst;
void _Cil_StringConstantOperandAst_registerType();

struct Cil_StringConstantOperandAst {
  Cil_OperandAst parent;
  R_String* value;
};

void
Cil_StringConstantOperandAst_construct
  (
    Cil_StringConstantOperandAst* self,
    R_String* value
  );

Cil_StringConstantOperandAst*
Cil_StringConstantOperandAst_create
  (
    R_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Cil.ExpressionAst
/// @endcode
typedef struct Cil_ExpressionAst Cil_ExpressionAst;
void _Cil_ExpressionAst_registerType();

struct Cil_ExpressionAst {
  uint8_t dummy;
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
typedef struct Cil_UnaryExpressionAst Cil_UnaryExpressionAst;
void _Cil_UnaryExpressionAst_registerType();

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
  Cil_BinaryExpressionAstType_Subtract = 2,
  Cil_BinaryExpressionAstType_Multiply = 3,
  Cil_BinaryExpressionAstType_Divide = 4,
};

/// @code
/// class Cil.BinaryOperationExpressionAst
/// @endcode
/// Represents a binary operations like
//// @code
/// (add|subtract|multiply|divide) <operand1> <operand2>
/// @endcode
typedef struct Cil_BinaryExpressionAst Cil_BinaryExpressionAst;
void _Cil_BinaryExpressionAst_registerType();

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
/// class Cil.StatementAst
/// @endcode
typedef struct Cil_StatementAst Cil_StatementAst;
void _Cil_StatementAst_registerType();

struct Cil_StatementAst {
  uint8_t dummy;
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
typedef struct Cil_ExpressionStatementAst Cil_ExpressionStatementAst;
void _Cil_ExpressionStatementAst_registerType();

struct Cil_ExpressionStatementAst {
  Cil_StatementAst parent;
  Cil_ExpressionAst* expression;
};

void
Cil_ExpressionStatementAst_construct
  (
    Cil_ExpressionStatementAst* self,
    Cil_ExpressionAst* expression
  );

/// @brief Create a CIL expression statement AST.
/// @return A pointer to this CIL expression statement ASt.
Cil_ExpressionStatementAst*
Cil_ExpressionStatementAst_create
  (
    Cil_ExpressionAst* expression
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // CIL_AST_H_INCLUDED
