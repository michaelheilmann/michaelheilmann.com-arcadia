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

void
_Cil_ProgramAst_registerType
  (
  )
{ R_registerObjectType("Cil.ProgramAst", sizeof("Cil.ProgramAst") - 1, sizeof(Cil_ProgramAst), NULL, NULL, &Cil_ProgramAst_visit, NULL); }

void
Cil_ProgramAst_construct
  (
    Cil_ProgramAst* self
  )
{
  self->statements = R_List_create();
  R_Object_setType(self, R_getObjectType("Cil.ProgramAst", sizeof("Cil.ProgramAst") - 1));
}

Cil_ProgramAst*
Cil_ProgramAst_create
  (
  )
{
  Cil_ProgramAst* self = R_allocateObject(R_getObjectType("Cil.ProgramAst", sizeof("Cil.ProgramAst") - 1));
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

void
_Cil_OperandAst_registerType
  (
  )
{
  R_registerObjectType("Cil.ConstantOperandAst", sizeof("Cil.ConstantOperandAst") - 1, sizeof(Cil_OperandAst), NULL, NULL, NULL, NULL);
}

void
Cil_OperandAst_construct
  (
    Cil_OperandAst* self
  )
{
  R_Object_setType(self, R_getObjectType("Cil.OperandAst", sizeof("Cil.OperandAst") - 1));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_BooleanConstantOperandAst_visit
  (
    Cil_BooleanConstantOperandAst* self
  )
{ R_Object_visit(self->value); }

void
_Cil_BooleanConstantOperandAst_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("Cil.ConstantOperandAst", sizeof("Cil.ConstantOperandAst") - 1);
  R_registerObjectType("Cil.BooleanConstantOperandAst", sizeof("Cil.BooleanConstantOperandAst") - 1, sizeof(Cil_BooleanConstantOperandAst), parentType, NULL, &Cil_BooleanConstantOperandAst_visit, NULL);
}

void
Cil_BooleanConstantOperandAst_construct
  (
    Cil_BooleanConstantOperandAst* self,
    R_String* value
  )
{
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, R_getObjectType("Cil.BooleanConstantOperandAst", sizeof("Cil.BooleanConstantOperandAst") - 1));
}

Cil_BooleanConstantOperandAst*
Cil_BooleanConstantOperandAst_create
  (
    R_String* value
  )
{
  Cil_BooleanConstantOperandAst* self = R_allocateObject(R_getObjectType("Cil.BooleanConstantOperandAst", sizeof("Cil.BooleanConstantOperandAst") - 1));
  Cil_BooleanConstantOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_IntegerConstantOperandAst_visit
  (
    Cil_IntegerConstantOperandAst* self
  )
{ R_Object_visit(self->value); }

void
_Cil_IntegerConstantOperandAst_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("Cil.ConstantOperandAst", sizeof("Cil.ConstantOperandAst") - 1);
  R_registerObjectType("Cil.IntegerConstantOperandAst", sizeof("Cil.IntegerConstantOperandAst") - 1, sizeof(Cil_IntegerConstantOperandAst), parentType, NULL, &Cil_IntegerConstantOperandAst_visit, NULL);
}

void
Cil_IntegerConstantOperandAst_construct
  (
    Cil_IntegerConstantOperandAst* self,
    R_String* value
  )
{
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, R_getObjectType("Cil.IntegerConstantOperandAst", sizeof("Cil.IntegerConstantOperandAst") - 1));
}

Cil_IntegerConstantOperandAst*
Cil_IntegerConstantOperandAst_create
  (
    R_String* value
  )
{
  Cil_IntegerConstantOperandAst* self = R_allocateObject(R_getObjectType("Cil.IntegerConstantOperandAst", sizeof("Cil.IntegerConstantOperandAst") - 1));
  Cil_IntegerConstantOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_StringConstantOperandAst_visit
  (
    Cil_StringConstantOperandAst* self
  )
{ R_Object_visit(self->value); }

void
_Cil_StringConstantOperandAst_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("Cil.ConstantOperandAst", sizeof("Cil.ConstantOperandAst") - 1);
  R_registerObjectType("Cil.StringConstantOperandAst", sizeof("Cil.StringConstantOperandAst") - 1, sizeof(Cil_StringConstantOperandAst), parentType, NULL, &Cil_StringConstantOperandAst_visit, NULL);
}

void
Cil_StringConstantOperandAst_construct
  (
    Cil_StringConstantOperandAst* self,
    R_String* value
  )
{
  Cil_OperandAst_construct((Cil_OperandAst*)self);
  self->value = value;
  R_Object_setType(self, R_getObjectType("Cil.StringConstantOperandAst", sizeof("Cil.StringConstantOperandAst") - 1));
}

Cil_StringConstantOperandAst*
Cil_StringConstantOperandAst_create
  (
    R_String* value
  )
{
  Cil_StringConstantOperandAst* self = R_allocateObject(R_getObjectType("Cil.StringConstantOperandAst", sizeof("Cil.StringConstantOperandAst") - 1));
  Cil_StringConstantOperandAst_construct(self, value);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
_Cil_ExpressionAst_registerType
  (
  )
{
  R_registerObjectType("Cil.ExpressionAst", sizeof("Cil.ExpressionAst") - 1, sizeof(Cil_ExpressionAst), NULL, NULL, NULL, NULL);
}

void
Cil_ExpressionAst_construct
  (
    Cil_ExpressionAst* self
  )
{
  R_Object_setType(self, R_getObjectType("Cil.ExpressionAst", sizeof("Cil.ExpressionAst") - 1));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_UnaryExpressionAst_visit
  (
    Cil_UnaryExpressionAst* self
  )
{ R_Object_visit(self->operand1); }

void
_Cil_UnaryExpressionAst_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("Cil.ExpressionAst", sizeof("Cil.ExpressionAst") - 1);
  R_registerObjectType("Cil.UnaryExpressionAst", sizeof("Cil.UnaryExpressionAst") - 1, sizeof(Cil_UnaryExpressionAst), parentType, NULL, &Cil_UnaryExpressionAst_visit, NULL);
}

void
Cil_UnaryExpressionAst_construct
  (
    Cil_UnaryExpressionAst* self,
    Cil_UnaryExpressionAstType type,
    Cil_OperandAst* operand1
  )
{
  Cil_ExpressionAst_construct((Cil_ExpressionAst*)self);
  self->type = type;
  self->operand1 = operand1;
  R_Object_setType(self, R_getObjectType("Cil.UnaryExpressionAst", sizeof("Cil.UnaryExpressionAst") - 1));
}

Cil_UnaryExpressionAst*
Cil_UnaryExpressionAst_create
  (
    Cil_UnaryExpressionAstType type,
    Cil_OperandAst* operand1
  )
{
  Cil_UnaryExpressionAst* self = R_allocateObject(R_getObjectType("Cil.UnaryExpressionAst", sizeof("Cil.UnaryExpressionAst") - 1));
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

void
_Cil_BinaryExpressionAst_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("Cil.ExpressionAst", sizeof("Cil.ExpressionAst") - 1);
  R_registerObjectType("Cil.BinaryExpressionAst", sizeof("Cil.BinaryExpressionAst") - 1, sizeof(Cil_BinaryExpressionAst), parentType, NULL, &Cil_BinaryExpressionAst_visit, NULL);
}

void
Cil_BinaryExpressionAst_construct
  (
    Cil_BinaryExpressionAst* self,
    Cil_BinaryExpressionAstType type,
    Cil_OperandAst* operand1,
    Cil_OperandAst* operand2
  )
{
  Cil_ExpressionAst_construct((Cil_ExpressionAst*)self);
  self->type = type;
  self->operand1 = operand1;
  self->operand2 = operand2;
  R_Object_setType(self, R_getObjectType("Cil.BinaryExpressionAst", sizeof("Cil.BinaryExpressionAst") - 1));
}

Cil_BinaryExpressionAst*
Cil_BinaryExpressionAst_create
  (
    Cil_BinaryExpressionAstType type,
    Cil_OperandAst* operand1,
    Cil_OperandAst* operand2
  )
{
  Cil_BinaryExpressionAst* self = R_allocateObject(R_getObjectType("Cil.BinaryExpressionAst", sizeof("Cil.BinaryExpressionAst") - 1));
  Cil_BinaryExpressionAst_construct(self, type, operand1, operand2);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
_Cil_StatementAst_registerType
  (
  )
{
  R_registerObjectType("Cil.StatementAst", sizeof("Cil.StatementAst") - 1, sizeof(Cil_StatementAst), NULL, NULL, NULL, NULL);
}

void
Cil_StatementAst_construct
  (
    Cil_StatementAst* self
  )
{
  R_Object_setType(self, R_getObjectType("Cil.StatementAst", sizeof("Cil.StatementAst") - 1));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Cil_ExpressionStatementAst_visit
  (
    Cil_ExpressionStatementAst* self
  )
{
  R_Object_visit(self->expression);
}

void
_Cil_ExpressionStatementAst_registerType
  (
  )
{
  R_Type* parentType = R_getObjectType("Cil.StatementAst", sizeof("Cil.StatementAst") - 1);
  R_registerObjectType("Cil.ExpressionStatementAst", sizeof("Cil.ExpressionStatementAst") - 1, sizeof(Cil_ExpressionStatementAst), parentType, NULL, &Cil_ExpressionStatementAst_visit, NULL);
}

void
Cil_ExpressionStatementAst_construct
  (
    Cil_ExpressionStatementAst* self,
    Cil_ExpressionAst* expression
  )
{
  Cil_StatementAst_construct((Cil_StatementAst*)self);
  self->expression =  expression;
  R_Object_setType(self, R_getObjectType("Cil.ExpressionStatementAst", sizeof("Cil.ExpressionStatementAst") - 1));
}

Cil_ExpressionStatementAst*
Cil_ExpressionStatementAst_create
  (
    Cil_ExpressionAst* expression
  )
{
  Cil_ExpressionStatementAst* self = R_allocateObject(R_getObjectType("Cil.ExpressionStatementAst", sizeof("Cil.ExpressionStatementAst") - 1));
  Cil_ExpressionStatementAst_construct(self, expression);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

