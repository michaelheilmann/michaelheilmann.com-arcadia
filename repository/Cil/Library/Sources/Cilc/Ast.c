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

#include "Cilc/Ast.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_ProgramAst_visit
  (
    Cil_ProgramAst* self
  )
{ R_Object_visit(self->statements); }

Rex_defineObjectType("Cil.ProgramAst", Cil_ProgramAst, "R.Object", R_Object, &Cil_ProgramAst_visit, NULL);

void
Cil_ProgramAst_construct
  (
    Cil_ProgramAst* self
  )
{
  R_Type* _type = _Cil_ProgramAst_getType();
  R_Object_construct((R_Object*)self);
  self->statements = R_List_create();
  R_Object_setType(self, _type);
}

Cil_ProgramAst*
Cil_ProgramAst_create
  (
  )
{
  Cil_ProgramAst* self = R_allocateObject(_Cil_ProgramAst_getType());
  Cil_ProgramAst_construct(self);
  return self;
}

void
Cil_ProgramAst_append
  (
    Cil_ProgramAst* self,
    Cil_StatementAst* statement
  )
{ 
  R_List_appendObjectReferenceValue(self->statements, (R_ObjectReferenceValue)statement);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_defineObjectType("Cil.OperandAst", Cil_OperandAst, "R.Object", R_Object, NULL, NULL);

void
Cil_OperandAst_construct
  (
    Cil_OperandAst* self
  )
{
  R_Type* _type = _Cil_OperandAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_BooleanLiteralOperandAst_visit
  (
    Cil_BooleanLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

Rex_defineObjectType("Cil.BooleanLiteralOperandAst", Cil_BooleanLiteralOperandAst, "Cil.OperandAst", Cil_OperandAst, &Cil_BooleanLiteralOperandAst_visit, NULL);

void
Cil_BooleanLiteralOperandAst_construct
  (
    Cil_BooleanLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _Cil_BooleanLiteralOperandAst_getType();
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

Cil_BooleanLiteralOperandAst*
Cil_BooleanLiteralOperandAst_create
  (
    R_String* value
  )
{
  Cil_BooleanLiteralOperandAst* self = R_allocateObject(_Cil_BooleanLiteralOperandAst_getType());
  Cil_BooleanLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_NumberLiteralOperandAst_visit
  (
    Cil_NumberLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

Rex_defineObjectType("Cil.NumberLiteralOperandAst", Cil_NumberLiteralOperandAst, "Cil.OperandAst", Cil_OperandAst, &Cil_NumberLiteralOperandAst_visit, NULL);

void
Cil_NumberLiteralOperandAst_construct
  (
    Cil_NumberLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _Cil_NumberLiteralOperandAst_getType();
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

Cil_NumberLiteralOperandAst*
Cil_NumberLiteralOperandAst_create
  (
    R_String* value
  )
{
  Cil_NumberLiteralOperandAst* self = R_allocateObject(_Cil_NumberLiteralOperandAst_getType());
  Cil_NumberLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_StringLiteralOperandAst_visit
  (
    Cil_StringLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

Rex_defineObjectType("Cil.StringLiteralOperandAst", Cil_StringLiteralOperandAst, "Cil.OperandAst", Cil_OperandAst, &Cil_StringLiteralOperandAst_visit, NULL);

void
Cil_StringLiteralOperandAst_construct
  (
    Cil_StringLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _Cil_StringLiteralOperandAst_getType();
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

Cil_StringLiteralOperandAst*
Cil_StringLiteralOperandAst_create
  (
    R_String* value
  )
{
  Cil_StringLiteralOperandAst* self = R_allocateObject(_Cil_StringLiteralOperandAst_getType());
  Cil_StringLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_VariableOperandAst_visit
  (
    Cil_VariableOperandAst* self
  )
{ R_Object_visit(self->value); }

Rex_defineObjectType("Cil.VariableOperandAst", Cil_VariableOperandAst, "Cil.OperandAst", Cil_OperandAst, &Cil_VariableOperandAst_visit, NULL);

void
Cil_VariableOperandAst_construct
  (
    Cil_VariableOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _Cil_VariableOperandAst_getType();
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

Cil_VariableOperandAst*
Cil_VariableOperandAst_create
    (
      R_String* value
    )
{
  Cil_VariableOperandAst* self = R_allocateObject(_Cil_VariableOperandAst_getType());
  Cil_VariableOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_VoidLiteralOperandAst_visit
  (
    Cil_StringLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

Rex_defineObjectType("Cil.VoidLiteralOperandAst", Cil_VoidLiteralOperandAst, "Cil.OperandAst", Cil_OperandAst, &Cil_VoidLiteralOperandAst_visit, NULL);

void
Cil_VoidLiteralOperandAst_construct
  (
    Cil_VoidLiteralOperandAst* self,
    R_String* value
  )
{
  R_Type* _type = _Cil_VoidLiteralOperandAst_getType();
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, _type);
}

Cil_VoidLiteralOperandAst*
Cil_VoidLiteralOperandAst_create
  (
    R_String* value
  )
{
  Cil_VoidLiteralOperandAst* self = R_allocateObject(_Cil_VoidLiteralOperandAst_getType());
  Cil_VoidLiteralOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_defineObjectType("Cil.ExpressionAst", Cil_ExpressionAst, "R.Object", R_Object, NULL, NULL);

void
Cil_ExpressionAst_construct
  (
    Cil_ExpressionAst* self
  )
{
  R_Type* _type = _Cil_ExpressionAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_UnaryExpressionAst_visit
  (
    Cil_UnaryExpressionAst* self
  )
{ R_Object_visit(self->operand1); }

Rex_defineObjectType("Cil.UnaryExpressionAst", Cil_UnaryExpressionAst, "Cil.ExpressionAst", Cil_ExpressionAst, &Cil_UnaryExpressionAst_visit, NULL);

void
Cil_UnaryExpressionAst_construct
  (
    Cil_UnaryExpressionAst* self,
    Cil_UnaryExpressionAstType type,
    Cil_OperandAst* operand1
  )
{
  R_Type* _type = _Cil_UnaryExpressionAst_getType();
  Cil_ExpressionAst_construct((Cil_ExpressionAst*)self);
  self->type = type;
  self->operand1 = operand1;
  R_Object_setType(self, _type);
}

Cil_UnaryExpressionAst*
Cil_UnaryExpressionAst_create
  (
    Cil_UnaryExpressionAstType type,
    Cil_OperandAst* operand1
  )
{
  Cil_UnaryExpressionAst* self = R_allocateObject(_Cil_UnaryExpressionAst_getType());
  Cil_UnaryExpressionAst_construct(self, type, operand1);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_BinaryExpressionAst_visit
  (
    Cil_BinaryExpressionAst* self
  )
{
  R_Object_visit(self->operand1);
  R_Object_visit(self->operand2);
}

Rex_defineObjectType("Cil.BinaryExpressionAst", Cil_BinaryExpressionAst, "Cil.ExpressionAst", Cil_ExpressionAst, &Cil_BinaryExpressionAst_visit, NULL);

void
Cil_BinaryExpressionAst_construct
  (
    Cil_BinaryExpressionAst* self,
    Cil_BinaryExpressionAstType type,
    Cil_OperandAst* operand1,
    Cil_OperandAst* operand2
  )
{
  R_Type* _type = _Cil_BinaryExpressionAst_getType();
  Cil_ExpressionAst_construct((Cil_ExpressionAst*)self);
  self->type = type;
  self->operand1 = operand1;
  self->operand2 = operand2;
  R_Object_setType(self, _type);
}

Cil_BinaryExpressionAst*
Cil_BinaryExpressionAst_create
  (
    Cil_BinaryExpressionAstType type,
    Cil_OperandAst* operand1,
    Cil_OperandAst* operand2
  )
{
  Cil_BinaryExpressionAst* self = R_allocateObject(_Cil_BinaryExpressionAst_getType());
  Cil_BinaryExpressionAst_construct(self, type, operand1, operand2);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_LoadExpressionAst_visit
  (
    Cil_LoadExpressionAst* self
  )
{
  R_Object_visit(self->operand);
}

Rex_defineObjectType("Cil.LoadExpressionAst", Cil_LoadExpressionAst, "Cil.ExpressionAst", Cil_ExpressionAst, &Cil_LoadExpressionAst_visit, NULL);

void
Cil_LoadExpressionAst_construct
  (
    Cil_LoadExpressionAst* self,
    Cil_OperandAst* operand
  )
{
  R_Type* _type = _Cil_LoadExpressionAst_getType();
  Cil_ExpressionAst_construct((Cil_ExpressionAst*)self);
  self->operand = operand;
  R_Object_setType(self, _type);
}

Cil_LoadExpressionAst*
Cil_LoadExpressionAst_create
  (
    Cil_OperandAst* operand
  )
{ 
  Cil_LoadExpressionAst* self = R_allocateObject(_Cil_LoadExpressionAst_getType());
  Cil_LoadExpressionAst_construct(self, operand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_defineObjectType("Cil.StatementAst", Cil_StatementAst, "R.Object", R_Object, NULL, NULL);

void
Cil_StatementAst_construct
  (
    Cil_StatementAst* self
  )
{
  R_Type* _type = _Cil_StatementAst_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType(self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_ExpressionStatementAst_visit
  (
    Cil_ExpressionStatementAst* self
  )
{
  R_Object_visit(self->targetVariableName);
  R_Object_visit(self->expression);
}

Rex_defineObjectType("Cil.ExpressionStatementAst", Cil_ExpressionStatementAst, "Cil.StatementAst", Cil_StatementAst, &Cil_ExpressionStatementAst_visit, NULL);

void
Cil_ExpressionStatementAst_construct
  (
    Cil_ExpressionStatementAst* self,
    R_String* targetVariableName,
    Cil_ExpressionAst* expression
  )
{
  R_Type* _type = _Cil_ExpressionStatementAst_getType();
  Cil_StatementAst_construct((Cil_StatementAst*)self);
  self->targetVariableName = targetVariableName;
  self->expression =  expression;
  R_Object_setType(self, _type);
}

Cil_ExpressionStatementAst*
Cil_ExpressionStatementAst_create
  (
    R_String* targetVariableName,
    Cil_ExpressionAst* expression
  )
{
  Cil_ExpressionStatementAst* self = R_allocateObject(_Cil_ExpressionStatementAst_getType());
  Cil_ExpressionStatementAst_construct(self, targetVariableName, expression);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_LabelStatementAst_visit
  (
    Cil_LabelStatementAst* self
  )
{
  R_Object_visit(self->labelName);
}

Rex_defineObjectType("Cil.LabelStatementAst", Cil_LabelStatementAst, "Cil.StatementAst", Cil_StatementAst, &Cil_LabelStatementAst_visit, NULL);

void
Cil_LabelStatementAst_construct
  (
    Cil_LabelStatementAst* self,
    R_String* labelName
  )
{
  R_Type* _type = _Cil_LabelStatementAst_getType();
  Cil_StatementAst_construct((Cil_StatementAst*)self);
  self->labelName = labelName;
  R_Object_setType(self, _type);
}

Cil_LabelStatementAst*
Cil_LabelStatementAst_create
  (
    R_String* labelName
  )
{
  Cil_LabelStatementAst* self = R_allocateObject(_Cil_LabelStatementAst_getType());
  Cil_LabelStatementAst_construct(self, labelName);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
