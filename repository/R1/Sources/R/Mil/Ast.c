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

#include "R/Mil/Ast.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ProgramAst_visit
  (
    R_Mil_ProgramAst* self
  )
{ R_Object_visit(self->statements); }

static const R_ObjectType_Operations _R_Mil_ProgramAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ProgramAst_visit,
};

static const R_Type_Operations _R_Mil_ProgramAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ProgramAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ProgramAst", R_Mil_ProgramAst, "R.Object", R_Object, &_R_Mil_ProgramAst_typeOperations);

void
R_Mil_ProgramAst_construct
  (
    R_Mil_ProgramAst* self
  )
{
  R_Type* _type = _R_Mil_ProgramAst_getType();
  R_Object_construct((R_Object*)self);
  self->statements = R_List_create();
  R_Object_setType(self, _type);
}

R_Mil_ProgramAst*
R_Mil_ProgramAst_create
  (
  )
{
  R_Mil_ProgramAst* self = R_allocateObject(_R_Mil_ProgramAst_getType());
  R_Mil_ProgramAst_construct(self);
  return self;
}

void
R_Mil_ProgramAst_append
  (
    R_Mil_ProgramAst* self,
    R_Mil_StatementAst* statement
  )
{ 
  R_List_appendObjectReferenceValue(self->statements, (R_ObjectReferenceValue)statement);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _R_Mil_OperandAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _R_Mil_OperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_OperandAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.OperandAst", R_Mil_OperandAst, "R.Object", R_Object, &_R_Mil_OperandAst_typeOperations);

void
R_Mil_OperandAst_construct
  (
    R_Mil_OperandAst* self
  )
{
  R_Type* _type = _R_Mil_OperandAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_BooleanLiteralOperandAst_visit
  (
    R_Mil_BooleanLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

static const R_ObjectType_Operations _R_Mil_BooleanLiteralOperandAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_BooleanLiteralOperandAst_visit,
};

static const R_Type_Operations _R_Mil_BooleanLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_BooleanLiteralOperandAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.BooleanLiteralOperandAst", R_Mil_BooleanLiteralOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_BooleanLiteralOperandAst_typeOperations);

void
R_Mil_BooleanLiteralOperandAst_construct
  (
    R_Mil_BooleanLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _R_Mil_BooleanLiteralOperandAst_getType();
  R_Mil_OperandAst_construct((R_Mil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

R_Mil_BooleanLiteralOperandAst*
R_Mil_BooleanLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Mil_BooleanLiteralOperandAst* self = R_allocateObject(_R_Mil_BooleanLiteralOperandAst_getType());
  R_Mil_BooleanLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_NumberLiteralOperandAst_visit
  (
    R_Mil_NumberLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

static const R_ObjectType_Operations _R_Mil_NumberLiteralOperandAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_NumberLiteralOperandAst_visit,
};

static const R_Type_Operations _R_Mil_NumberLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_NumberLiteralOperandAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.NumberLiteralOperandAst", R_Mil_NumberLiteralOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_NumberLiteralOperandAst_typeOperations);

void
R_Mil_NumberLiteralOperandAst_construct
  (
    R_Mil_NumberLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _R_Mil_NumberLiteralOperandAst_getType();
  R_Mil_OperandAst_construct((R_Mil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

R_Mil_NumberLiteralOperandAst*
R_Mil_NumberLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Mil_NumberLiteralOperandAst* self = R_allocateObject(_R_Mil_NumberLiteralOperandAst_getType());
  R_Mil_NumberLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_StringLiteralOperandAst_visit
  (
    R_Mil_StringLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

static const R_ObjectType_Operations _R_Mil_StringLiteralOperandAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_StringLiteralOperandAst_visit,
};

static const R_Type_Operations _R_Mil_StringLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_StringLiteralOperandAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.StringLiteralOperandAst", R_Mil_StringLiteralOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_StringLiteralOperandAst_typeOperations);

void
R_Mil_StringLiteralOperandAst_construct
  (
    R_Mil_StringLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _R_Mil_StringLiteralOperandAst_getType();
  R_Mil_OperandAst_construct((R_Mil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

R_Mil_StringLiteralOperandAst*
R_Mil_StringLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Mil_StringLiteralOperandAst* self = R_allocateObject(_R_Mil_StringLiteralOperandAst_getType());
  R_Mil_StringLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_VariableOperandAst_visit
  (
    R_Mil_VariableOperandAst* self
  )
{ R_Object_visit(self->value); }

static const R_ObjectType_Operations _R_Mil_VariableOperandAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_VariableOperandAst_visit,
};

static const R_Type_Operations _R_Mil_VariableOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_VariableOperandAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.VariableOperandAst", R_Mil_VariableOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_VariableOperandAst_typeOperations);

void
R_Mil_VariableOperandAst_construct
  (
    R_Mil_VariableOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _R_Mil_VariableOperandAst_getType();
  R_Mil_OperandAst_construct((R_Mil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

R_Mil_VariableOperandAst*
R_Mil_VariableOperandAst_create
    (
      R_String* value
    )
{
  R_Mil_VariableOperandAst* self = R_allocateObject(_R_Mil_VariableOperandAst_getType());
  R_Mil_VariableOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_VoidLiteralOperandAst_visit
  (
    R_Mil_StringLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

static const R_ObjectType_Operations _R_Mil_VoidLiteralOperandAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_VoidLiteralOperandAst_visit,
};

static const R_Type_Operations _R_Mil_VoidLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_VoidLiteralOperandAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.VoidLiteralOperandAst", R_Mil_VoidLiteralOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_VoidLiteralOperandAst_typeOperations);

void
R_Mil_VoidLiteralOperandAst_construct
  (
    R_Mil_VoidLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _R_Mil_VoidLiteralOperandAst_getType();
  R_Mil_OperandAst_construct((R_Mil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

R_Mil_VoidLiteralOperandAst*
R_Mil_VoidLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Mil_VoidLiteralOperandAst* self = R_allocateObject(_R_Mil_VoidLiteralOperandAst_getType());
  R_Mil_VoidLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _R_Mil_ExpressionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _R_Mil_ExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ExpressionAst_objectTypeOperations,
  .add = NULL,
  . and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ExpressionAst", R_Mil_ExpressionAst, "R.Object", R_Object, &_R_Mil_ExpressionAst_typeOperations);

void
R_Mil_ExpressionAst_construct
  (
    R_Mil_ExpressionAst* self
  )
{
  R_Type* _type = _R_Mil_ExpressionAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_InvokeExpressionAstt_visit
  (
    R_Mil_InvokeExpressionAst* self
  )
{
  R_Object_visit(self->callee);
  R_Object_visit(self->operands);
}

static const R_ObjectType_Operations _R_Mil_InvokeExpressionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_InvokeExpressionAstt_visit,
};

static const R_Type_Operations _R_Mil_InvokeExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_InvokeExpressionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.InvokeExpressionAst", R_Mil_InvokeExpressionAst, "R.Object", R_Object, &_R_Mil_InvokeExpressionAst_typeOperations);

void
R_Mil_InvokeExpressionAst_construct
  (
    R_Mil_InvokeExpressionAst* self,
    R_Mil_VariableOperandAst* callee,
    R_List* operands
  )
{
  R_Type* _type = _R_Mil_InvokeExpressionAst_getType();
  R_Mil_ExpressionAst_construct((R_Mil_ExpressionAst*)self);
  self->callee = callee;
  self->operands = operands;
  R_Object_setType(self, _type);
}

R_Mil_InvokeExpressionAst*
R_Mil_InvokeExpressionAst_create
  (
    R_Mil_VariableOperandAst* callee,
    R_List* operands
  )
{
  R_Mil_InvokeExpressionAst* self = R_allocateObject(_R_Mil_InvokeExpressionAst_getType());
  R_Mil_InvokeExpressionAst_construct(self, callee, operands);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_UnaryExpressionAst_visit
  (
    R_Mil_UnaryExpressionAst* self
  )
{ R_Object_visit(self->operand1); }

static const R_ObjectType_Operations _R_Mil_UnaryExpressionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_UnaryExpressionAst_visit,
};

static const R_Type_Operations _R_Mil_UnaryExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_UnaryExpressionAst_objectTypeOperations,
  .add = NULL,
  . and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.UnaryExpressionAst", R_Mil_UnaryExpressionAst, "R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_UnaryExpressionAst_typeOperations);

void
R_Mil_UnaryExpressionAst_construct
  (
    R_Mil_UnaryExpressionAst* self,
    R_Mil_UnaryExpressionAstType type,
    R_Mil_OperandAst* operand1
  )
{
  R_Type* _type = _R_Mil_UnaryExpressionAst_getType();
  R_Mil_ExpressionAst_construct((R_Mil_ExpressionAst*)self);
  self->type = type;
  self->operand1 = operand1;
  R_Object_setType(self, _type);
}

R_Mil_UnaryExpressionAst*
R_Mil_UnaryExpressionAst_create
  (
    R_Mil_UnaryExpressionAstType type,
    R_Mil_OperandAst* operand1
  )
{
  R_Mil_UnaryExpressionAst* self = R_allocateObject(_R_Mil_UnaryExpressionAst_getType());
  R_Mil_UnaryExpressionAst_construct(self, type, operand1);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_BinaryExpressionAst_visit
  (
    R_Mil_BinaryExpressionAst* self
  )
{
  R_Object_visit(self->operand1);
  R_Object_visit(self->operand2);
}

static const R_ObjectType_Operations _R_Mil_BinaryExpressionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_BinaryExpressionAst_visit,
};

static const R_Type_Operations _R_Mil_BinaryExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_BinaryExpressionAst_objectTypeOperations,
  .add = NULL,
  . and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.BinaryExpressionAst", R_Mil_BinaryExpressionAst, "R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_BinaryExpressionAst_typeOperations);

void
R_Mil_BinaryExpressionAst_construct
  (
    R_Mil_BinaryExpressionAst* self,
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  )
{
  R_Type* _type = _R_Mil_BinaryExpressionAst_getType();
  R_Mil_ExpressionAst_construct((R_Mil_ExpressionAst*)self);
  self->type = type;
  self->operand1 = operand1;
  self->operand2 = operand2;
  R_Object_setType(self, _type);
}

R_Mil_BinaryExpressionAst*
R_Mil_BinaryExpressionAst_create
  (
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  )
{
  R_Mil_BinaryExpressionAst* self = R_allocateObject(_R_Mil_BinaryExpressionAst_getType());
  R_Mil_BinaryExpressionAst_construct(self, type, operand1, operand2);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_LoadExpressionAst_visit
  (
    R_Mil_LoadExpressionAst* self
  )
{
  R_Object_visit(self->operand);
}

static const R_ObjectType_Operations _R_Mil_LoadExpressionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_LoadExpressionAst_visit,
};

static const R_Type_Operations _R_Mil_LoadExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_LoadExpressionAst_objectTypeOperations,
  .add = NULL,
  . and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.LoadExpressionAst", R_Mil_LoadExpressionAst, "R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_LoadExpressionAst_typeOperations);

void
R_Mil_LoadExpressionAst_construct
  (
    R_Mil_LoadExpressionAst* self,
    R_Mil_OperandAst* operand
  )
{
  R_Type* _type = _R_Mil_LoadExpressionAst_getType();
  R_Mil_ExpressionAst_construct((R_Mil_ExpressionAst*)self);
  self->operand = operand;
  R_Object_setType(self, _type);
}

R_Mil_LoadExpressionAst*
R_Mil_LoadExpressionAst_create
  (
    R_Mil_OperandAst* operand
  )
{ 
  R_Mil_LoadExpressionAst* self = R_allocateObject(_R_Mil_LoadExpressionAst_getType());
  R_Mil_LoadExpressionAst_construct(self, operand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _R_Mil_StatementAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _R_Mil_StatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_StatementAst_objectTypeOperations,
  .add = NULL,
  . and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.StatementAst", R_Mil_StatementAst, "R.Object", R_Object, &_R_Mil_StatementAst_typeOperations);

void
R_Mil_StatementAst_construct
  (
    R_Mil_StatementAst* self
  )
{
  R_Type* _type = _R_Mil_StatementAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ExpressionStatementAst_visit
  (
    R_Mil_ExpressionStatementAst* self
  )
{
  R_Object_visit(self->targetVariableName);
  R_Object_visit(self->expression);
}

static const R_ObjectType_Operations _R_Mil_ExpressionStatementAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ExpressionStatementAst_visit,
};

static const R_Type_Operations _R_Mil_ExpressionStatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ExpressionStatementAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ExpressionStatementAst", R_Mil_ExpressionStatementAst, "R.Mil.StatementAst", R_Mil_StatementAst, &_R_Mil_ExpressionStatementAst_typeOperations);

void
R_Mil_ExpressionStatementAst_construct
  (
    R_Mil_ExpressionStatementAst* self,
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  )
{
  R_Type* _type = _R_Mil_ExpressionStatementAst_getType();
  R_Mil_StatementAst_construct((R_Mil_StatementAst*)self);
  self->targetVariableName = targetVariableName;
  self->expression =  expression;
  R_Object_setType(self, _type);
}

R_Mil_ExpressionStatementAst*
R_Mil_ExpressionStatementAst_create
  (
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  )
{
  R_Mil_ExpressionStatementAst* self = R_allocateObject(_R_Mil_ExpressionStatementAst_getType());
  R_Mil_ExpressionStatementAst_construct(self, targetVariableName, expression);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_LabelStatementAst_visit
  (
    R_Mil_LabelStatementAst* self
  )
{
  R_Object_visit(self->labelName);
}

static const R_ObjectType_Operations _R_Mil_LabelStatementAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_LabelStatementAst_visit,
};

static const R_Type_Operations _R_Mil_LabelStatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_LabelStatementAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.LabelStatementAst", R_Mil_LabelStatementAst, "R.Mil.StatementAst", R_Mil_StatementAst, &_R_Mil_LabelStatementAst_typeOperations);

void
R_Mil_LabelStatementAst_construct
  (
    R_Mil_LabelStatementAst* self,
    R_String* labelName
  )
{
  R_Type* _type = _R_Mil_LabelStatementAst_getType();
  R_Mil_StatementAst_construct((R_Mil_StatementAst*)self);
  self->labelName = labelName;
  R_Object_setType(self, _type);
}

R_Mil_LabelStatementAst*
R_Mil_LabelStatementAst_create
  (
    R_String* labelName
  )
{
  R_Mil_LabelStatementAst* self = R_allocateObject(_R_Mil_LabelStatementAst_getType());
  R_Mil_LabelStatementAst_construct(self, labelName);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ReturnStatementAst_visit
  (
    R_Mil_ReturnStatementAst* self
  )
{
  R_Object_visit(self->operand);
}

static const R_ObjectType_Operations _R_Mil_ReturnStatementAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ReturnStatementAst_visit,
};

static const R_Type_Operations _R_Mil_ReturnStatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ReturnStatementAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ReturnStatementAst", R_Mil_ReturnStatementAst, "R.Mil.StatementAst", R_Mil_StatementAst, &_R_Mil_ReturnStatementAst_typeOperations);

void
R_Mil_ReturnStatementAst_construct
  (
    R_Mil_ReturnStatementAst* self,
    R_Mil_OperandAst* operand
  )
{
  R_Type* _type = _R_Mil_ReturnStatementAst_getType();
  R_Mil_StatementAst_construct((R_Mil_StatementAst*)self);
  self->operand = operand;
  R_Object_setType(self, _type);
}

R_Mil_ReturnStatementAst*
R_Mil_ReturnStatementAst_create
  (
    R_Mil_OperandAst* operand
  )
{
  R_Mil_ReturnStatementAst* self = R_allocateObject(_R_Mil_ReturnStatementAst_getType());
  R_Mil_ReturnStatementAst_construct(self, operand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _R_Mil_DefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _R_Mil_DefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_DefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.DefinitionAst", R_Mil_DefinitionAst, "R.Object", R_Object, &_R_Mil_DefinitionAst_typeOperations);

void
R_Mil_DefinitionAst_construct
  (
    R_Mil_DefinitionAst* self
  )
{
  R_Type* _type = _R_Mil_DefinitionAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ProcedureDefinitionAst_visit
  (
    R_Mil_ProcedureDefinitionAst* self
  )
{
  if (self->nativeName) {
    R_Object_visit(self->nativeName);
  }
  R_Object_visit(self->procedureName);
  R_Object_visit(self->procedureParameters);
  if (self->procedureBody) {
    R_Object_visit(self->procedureBody);
  }
}

static const R_ObjectType_Operations _R_Mil_ProcedureDefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ProcedureDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_ProcedureDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ProcedureDefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ProcedureDefinitionAst", R_Mil_ProcedureDefinitionAst, "R.Mil.DefinitionAst", R_Mil_DefinitionAst, &_R_Mil_ProcedureDefinitionAst_typeOperations);

void
R_Mil_ProcedureDefinitionAst_construct
  (
    R_Mil_ProcedureDefinitionAst* self,
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  )
{
  R_Type* _type = _R_Mil_ProcedureDefinitionAst_getType();
  R_Mil_DefinitionAst_construct((R_Mil_DefinitionAst*)self);
  self->nativeName = nativeName;
  self->procedureName = procedureName;
  self->procedureParameters = procedureParameters;
  self->procedureBody = procedureBody;
  R_Object_setType(self, _type);
}

R_Mil_ProcedureDefinitionAst*
R_Mil_ProcedureDefinitionAst_create
  (
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  )
{
  R_Mil_ProcedureDefinitionAst* self = R_allocateObject(_R_Mil_ProcedureDefinitionAst_getType());
  R_Mil_ProcedureDefinitionAst_construct(self, nativeName, procedureName, procedureParameters, procedureBody);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ClassDefinitionAst_visit
  (
    R_Mil_ClassDefinitionAst* self
  )
{
  R_Object_visit(self->className);
  if (self->extendedClassName) {
    R_Object_visit(self->extendedClassName);
  }
  if (self->classBody) {
    R_Object_visit(self->classBody);
  }
}

static const R_ObjectType_Operations _R_Mil_ClassDefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ClassDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_ClassDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ClassDefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ClassDefinitionAst", R_Mil_ClassDefinitionAst, "R.Mil.DefinitionAst", R_Mil_DefinitionAst, &_R_Mil_ClassDefinitionAst_typeOperations);

void
R_Mil_ClassDefinitionAst_construct
  (
    R_Mil_ClassDefinitionAst* self,
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  )
{
  R_Type* _type = _R_Mil_ClassDefinitionAst_getType();
  R_Mil_DefinitionAst_construct((R_Mil_DefinitionAst*)self);
  self->className = className;
  self->extendedClassName = extendedClassName;
  self->classBody = classBody;
  R_Object_setType(self, _type);
}

R_Mil_ClassDefinitionAst*
R_Mil_ClassDefinitionAst_create
  (
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  )
{
  R_Mil_ClassDefinitionAst* self = R_allocateObject(_R_Mil_ClassDefinitionAst_getType());
  R_Mil_ClassDefinitionAst_construct(self, className, extendedClassName, classBody);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ClassMemberDefinitionAst_visit
  (
    R_Mil_ClassMemberDefinitionAst* self
  )
{/*Intentionally empty.*/}

static const R_ObjectType_Operations _R_Mil_ClassMemberDefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ClassMemberDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_ClassMemberDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ClassMemberDefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, "R.Mil.DefinitionAst", R_Mil_DefinitionAst, &_R_Mil_ClassMemberDefinitionAst_typeOperations);

void
R_Mil_ClassMemberDefinitionAst_construct
  (
    R_Mil_ClassMemberDefinitionAst* self
  )
{
  R_Type* _type = _R_Mil_ClassMemberDefinitionAst_getType();
  R_Mil_DefinitionAst_construct((R_Mil_DefinitionAst*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_MethodDefinitionAst_visit
  (
    R_Mil_MethodDefinitionAst* self
  )
{
  R_Object_visit(self->methodName);
  R_Object_visit(self->methodParameters);
  R_Object_visit(self->methodBody);
}

static const R_ObjectType_Operations _R_Mil_MethodDefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_MethodDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_MethodDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_MethodDefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.MethodDefinitionAst", R_Mil_MethodDefinitionAst, "R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, &_R_Mil_MethodDefinitionAst_typeOperations);

void
R_Mil_MethodDefinitionAst_construct
  (
    R_Mil_MethodDefinitionAst* self,
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  )
{
  R_Type* _type = _R_Mil_MethodDefinitionAst_getType();
  R_Mil_ClassMemberDefinitionAst_construct((R_Mil_ClassMemberDefinitionAst*)self);
  self->methodName = methodName;
  self->methodParameters = methodParameters;
  self->methodBody = methodBody;
  R_Object_setType(self, _type);
}

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  )
{
  R_Mil_MethodDefinitionAst* self = R_allocateObject(_R_Mil_MethodDefinitionAst_getType());
  R_Mil_MethodDefinitionAst_construct(self, methodName, methodParameters, methodBody);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ConstructorDefinitionAst_visit
  (
    R_Mil_ConstructorDefinitionAst* self
  )
{
  R_Object_visit(self->constructorParameters);
  R_Object_visit(self->constructorBody);
}

static const R_ObjectType_Operations _R_Mil_ConstructorDefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_ConstructorDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_ConstructorDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ConstructorDefinitionAst_objectTypeOperations,
  .add = NULL,
  . and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.ConstructorDefinitionAst", R_Mil_ConstructorDefinitionAst, "R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, &_R_Mil_ConstructorDefinitionAst_typeOperations);

void
R_Mil_ConstructorDefinitionAst_construct
  (
    R_Mil_ConstructorDefinitionAst* self,
    R_List* constructorParameters,
    R_List* constructorBody
  )
{
  R_Type* _type = _R_Mil_ConstructorDefinitionAst_getType();
  R_Mil_ClassMemberDefinitionAst_construct((R_Mil_ClassMemberDefinitionAst*)self);
  self->constructorParameters = constructorParameters;
  self->constructorBody = constructorBody;
  R_Object_setType(self, _type);
}

R_Mil_ConstructorDefinitionAst*
R_Mil_ConstructorDefinitionAst_create
  (
    R_List* constructorParameters,
    R_List* constructorBody
  )
{
  R_Mil_ConstructorDefinitionAst* self = R_allocateObject(_R_Mil_ConstructorDefinitionAst_getType());
  R_Mil_ConstructorDefinitionAst_construct(self, constructorParameters, constructorBody);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_VariableDefinitionAst_visit
  (
    R_Mil_VariableDefinitionAst* self
  )
{
  R_Object_visit(self->variableName);
}

static const R_ObjectType_Operations _R_Mil_VariableDefinitionAst_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = &R_Mil_VariableDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_VariableDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_VariableDefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.VariableDefinitionAst", R_Mil_VariableDefinitionAst, "R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, &_R_Mil_VariableDefinitionAst_typeOperations);

void
R_Mil_VariableDefinitionAst_construct
  (
    R_Mil_VariableDefinitionAst* self,
    R_String* variableName
  )
{
  R_Type* _type = _R_Mil_VariableDefinitionAst_getType();
  R_Mil_ClassMemberDefinitionAst_construct((R_Mil_ClassMemberDefinitionAst*)self);
  self->variableName = variableName;
  R_Object_setType(self, _type);
}

R_Mil_VariableDefinitionAst*
R_Mil_VariableDefinitionAst_create
  (
    R_String* variableName
  )
{
  R_Mil_VariableDefinitionAst* self = R_allocateObject(_R_Mil_VariableDefinitionAst_getType());
  R_Mil_VariableDefinitionAst_construct(self, variableName);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
