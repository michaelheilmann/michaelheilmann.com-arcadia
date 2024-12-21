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

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct()
/// @endcode
static void
R_Mil_ModuleAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ModuleAst_visit
  (
    R_Mil_ModuleAst* self
  );

static const R_ObjectType_Operations _R_Mil_ModuleAst_objectTypeOperations = {
  .construct = &R_Mil_ModuleAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_ModuleAst_visit,
};

static const R_Type_Operations _R_Mil_ModuleAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ModuleAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.ModuleAst", R_Mil_ModuleAst, "R.Object", R_Object, &_R_Mil_ModuleAst_typeOperations);

static void
R_Mil_ModuleAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_ModuleAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ModuleAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->definitions = R_List_create();
  R_Object_setType(_self, _type);
}

static void
R_Mil_ModuleAst_visit
  (
    R_Mil_ModuleAst* self
  )
{
  R_Object_visit(self->definitions);
}

R_Mil_ModuleAst*
R_Mil_ModuleAst_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_Mil_ModuleAst* self = R_allocateObject(_R_Mil_ModuleAst_getType(), 0, &argumentValues[0]);
  return self;
}

void
R_Mil_ModuleAst_appendDefinition
  (
    R_Mil_ModuleAst* self,
    R_Mil_DefinitionAst* definition
  )
{ 
  R_List_appendObjectReferenceValue(self->definitions, (R_ObjectReferenceValue)definition);
}

R_SizeValue
R_Mil_ModuleAst_getNumberOfDefinitions
  (
    R_Mil_ModuleAst* self
  )
{ return R_List_getSize(self->definitions); }

R_Mil_DefinitionAst*
R_Mil_ModuleAst_getDefinitionAt
  (
    R_Mil_ModuleAst* self,
    R_SizeValue index
  )
{
  R_Value definitionAstValue = R_List_getAt(self->definitions, index);
  R_Mil_DefinitionAst* definitionAst = R_Value_getObjectReferenceValue(&definitionAstValue);
  return definitionAst;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_OperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const R_ObjectType_Operations _R_Mil_OperandAst_objectTypeOperations = {
  .construct = &R_Mil_OperandAst_constructImpl,
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

static void
R_Mil_OperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_OperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_OperandAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  R_Object_setType(_self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_BooleanLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_BooleanLiteralOperandAst_visit
  (
    R_Mil_BooleanLiteralOperandAst* self
  );

static const R_ObjectType_Operations _R_Mil_BooleanLiteralOperandAst_objectTypeOperations = {
  .construct = &R_Mil_BooleanLiteralOperandAst_constructImpl,
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

static void
R_Mil_BooleanLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_BooleanLiteralOperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_BooleanLiteralOperandAst_getType();

  {
    R_Value argumentValues[] = { { .tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Mil_OperandAst_constructImpl(self, 0, &argumentValues[0]);
  }

  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object* objectValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!R_Type_isSubType(R_Object_getType(objectValue), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_String* stringValue = (R_String*)objectValue;
  _self->value = stringValue;
  R_Object_setType(_self, _type);
}

static void
R_Mil_BooleanLiteralOperandAst_visit
  (
    R_Mil_BooleanLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

R_Mil_BooleanLiteralOperandAst*
R_Mil_BooleanLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)value } };
  R_Mil_BooleanLiteralOperandAst* self = R_allocateObject(_R_Mil_BooleanLiteralOperandAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_IntegerLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_IntegerLiteralOperandAst_visit
  (
    R_Mil_IntegerLiteralOperandAst* self
  );

static const R_ObjectType_Operations _R_Mil_IntegerLiteralOperandAst_objectTypeOperations = {
  .construct = &R_Mil_IntegerLiteralOperandAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_IntegerLiteralOperandAst_visit,
};

static const R_Type_Operations _R_Mil_IntegerLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_IntegerLiteralOperandAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.IntegerLiteralOperandAst", R_Mil_IntegerLiteralOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_IntegerLiteralOperandAst_typeOperations);

static void
R_Mil_IntegerLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_IntegerLiteralOperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_IntegerLiteralOperandAst_getType();

  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Mil_OperandAst_constructImpl(self, 0, &argumentValues[0]);
  }
  
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object* objectValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!R_Type_isSubType(R_Object_getType(objectValue), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_String* stringValue = (R_String*)objectValue;
  _self->value = stringValue;
  R_Object_setType(_self, _type);  
}

static void
R_Mil_IntegerLiteralOperandAst_visit
  (
    R_Mil_IntegerLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

R_Mil_IntegerLiteralOperandAst*
R_Mil_IntegerLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)value } };
  R_Mil_IntegerLiteralOperandAst* self = R_allocateObject(_R_Mil_IntegerLiteralOperandAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_RealLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_RealLiteralOperandAst_visit
  (
    R_Mil_RealLiteralOperandAst* self
  );

static const R_ObjectType_Operations _R_Mil_RealLiteralOperandAst_objectTypeOperations = {
  .construct = &R_Mil_RealLiteralOperandAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_RealLiteralOperandAst_visit,
};

static const R_Type_Operations _R_Mil_RealLiteralOperandAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_RealLiteralOperandAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.RealLiteralOperandAst", R_Mil_RealLiteralOperandAst, "R.Mil.OperandAst", R_Mil_OperandAst, &_R_Mil_RealLiteralOperandAst_typeOperations);

static void
R_Mil_RealLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_RealLiteralOperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_IntegerLiteralOperandAst_getType();

  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Mil_OperandAst_constructImpl(self, 0, &argumentValues[0]);
  }

  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object* objectValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!R_Type_isSubType(R_Object_getType(objectValue), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_String* stringValue = (R_String*)objectValue;
  _self->value = stringValue;
  R_Object_setType(_self, _type);
}

static void
R_Mil_RealLiteralOperandAst_visit
  (
    R_Mil_RealLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

R_Mil_RealLiteralOperandAst*
R_Mil_RealLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)value } };
  R_Mil_RealLiteralOperandAst* self = R_allocateObject(_R_Mil_RealLiteralOperandAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_StringLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_StringLiteralOperandAst_visit
  (
    R_Mil_StringLiteralOperandAst* self
  );

static const R_ObjectType_Operations _R_Mil_StringLiteralOperandAst_objectTypeOperations = {
  .construct = &R_Mil_StringLiteralOperandAst_constructImpl,
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

static void
R_Mil_StringLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_StringLiteralOperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_StringLiteralOperandAst_getType();

  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Mil_OperandAst_constructImpl(self, 0, &argumentValues[0]);
  }
  
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object* objectValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!R_Type_isSubType(R_Object_getType(objectValue), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_String* stringValue = (R_String*)objectValue;
  _self->value = stringValue;
  R_Object_setType(_self, _type);  
}

static void
R_Mil_StringLiteralOperandAst_visit
  (
    R_Mil_StringLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

R_Mil_StringLiteralOperandAst*
R_Mil_StringLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)value } };
  R_Mil_StringLiteralOperandAst* self = R_allocateObject(_R_Mil_StringLiteralOperandAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(value : R.String)
/// @endcode
static void
R_Mil_VariableOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_VariableOperandAst_visit
  (
    R_Mil_VariableOperandAst* self
  );

static const R_ObjectType_Operations _R_Mil_VariableOperandAst_objectTypeOperations = {
  .construct = &R_Mil_VariableOperandAst_constructImpl,
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
R_Mil_VariableOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_VariableOperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_VariableOperandAst_getType();

  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Mil_OperandAst_constructImpl(self, 0, &argumentValues[0]);
  }
  
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->value = (R_String*)R_Value_getObjectReferenceValue(&argumentValues[0]);;

  R_Object_setType(_self, _type);
}

static void
R_Mil_VariableOperandAst_visit
  (
    R_Mil_VariableOperandAst* self
  )
{ R_Object_visit(self->value); }

R_Mil_VariableOperandAst*
R_Mil_VariableOperandAst_create
    (
      R_String* value
    )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)value } };
  R_Mil_VariableOperandAst* self = R_allocateObject(_R_Mil_VariableOperandAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_VoidLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_VoidLiteralOperandAst_visit
  (
    R_Mil_StringLiteralOperandAst* self
  );

static const R_ObjectType_Operations _R_Mil_VoidLiteralOperandAst_objectTypeOperations = {
  .construct = &R_Mil_VoidLiteralOperandAst_constructImpl,
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

static void
R_Mil_VoidLiteralOperandAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_VoidLiteralOperandAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_VoidLiteralOperandAst_getType();

  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
    R_Mil_OperandAst_constructImpl(self, 0, &argumentValues[0]);
  }

  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object* objectValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!R_Type_isSubType(R_Object_getType(objectValue), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_String* stringValue = (R_String*)objectValue;
  _self->value = stringValue;
  R_Object_setType(_self, _type);
}

static void
R_Mil_VoidLiteralOperandAst_visit
  (
    R_Mil_StringLiteralOperandAst* self
  )
{ R_Object_visit(self->value); }

R_Mil_VoidLiteralOperandAst*
R_Mil_VoidLiteralOperandAst_create
  (
    R_String* value
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)value } };
  R_Mil_VoidLiteralOperandAst* self = R_allocateObject(_R_Mil_VoidLiteralOperandAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct()
/// @endcode
static void
R_Mil_ExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const R_ObjectType_Operations _R_Mil_ExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_ExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _R_Mil_ExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ExpressionAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.ExpressionAst", R_Mil_ExpressionAst, "R.Object", R_Object, &_R_Mil_ExpressionAst_typeOperations);

void
R_Mil_ExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_ExpressionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ExpressionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  R_Object_setType(_self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(callee:R.Mil.VariableOperandAst,operands:R.List)
/// @endcode
static void
R_Mil_InvokeExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_InvokeExpressionAst_visit
  (
    R_Mil_InvokeExpressionAst* self
  );

static const R_ObjectType_Operations _R_Mil_InvokeExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_InvokeExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_InvokeExpressionAst_visit,
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
R_Mil_InvokeExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_InvokeExpressionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_InvokeExpressionAst_getType();
  {
    R_Value argumentValues[] = { { .tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }

  if (2 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }

  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_Mil_VariableOperandAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[1]), _R_List_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }

  _self->callee = R_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->operands = R_Value_getObjectReferenceValue(&argumentValues[1]);

  R_Object_setType(_self, _type);
}

static void
R_Mil_InvokeExpressionAst_visit
  (
    R_Mil_InvokeExpressionAst* self
  )
{
  R_Object_visit(self->callee);
  R_Object_visit(self->operands);
}

R_Mil_InvokeExpressionAst*
R_Mil_InvokeExpressionAst_create
  (
    R_Mil_VariableOperandAst* callee,
    R_List* operands
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)callee },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operands }, };
  R_Mil_InvokeExpressionAst* self = R_allocateObject(_R_Mil_InvokeExpressionAst_getType(), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(type : R.Natural32Value<R.Mil.UnaryExpressionAstType>, operand1 : R.Mil.OperandAst)
/// @endcode
static void
R_Mil_UnaryExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_UnaryExpressionAst_visit
  (
    R_Mil_UnaryExpressionAst* self
  );

static const R_ObjectType_Operations _R_Mil_UnaryExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_UnaryExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_UnaryExpressionAst_visit,
};

static const R_Type_Operations _R_Mil_UnaryExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_UnaryExpressionAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.UnaryExpressionAst", R_Mil_UnaryExpressionAst, "R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_UnaryExpressionAst_typeOperations);

static void
R_Mil_UnaryExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_UnaryExpressionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_UnaryExpressionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }

  if (2 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }

  if (!R_Value_isInteger32Value(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[1]), _R_Mil_OperandAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();  
  }

  _self->type = R_Value_getInteger32Value(&argumentValues[0]);
  _self->operand1 = R_Value_getObjectReferenceValue(&argumentValues[1]);

  R_Object_setType(_self, _type);
}

static void
R_Mil_UnaryExpressionAst_visit
  (
    R_Mil_UnaryExpressionAst* self
  )
{ R_Object_visit(self->operand1); }

R_Mil_UnaryExpressionAst*
R_Mil_UnaryExpressionAst_create
  (
    R_Mil_UnaryExpressionAstType type,
    R_Mil_OperandAst* operand1
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Integer32, .integer32Value = type },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operand1 }, };
  R_Mil_UnaryExpressionAst* self = R_allocateObject(_R_Mil_UnaryExpressionAst_getType(), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(type : R.Mil.BinaryExpressionAstType, operand1 : R.Mil.OperandAst, operand2 : R.Mil.OperandAst)
/// @endcode
static void
R_Mil_BinaryExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_BinaryExpressionAst_visit
  (
    R_Mil_BinaryExpressionAst* self
  );

static const R_ObjectType_Operations _R_Mil_BinaryExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_BinaryExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_BinaryExpressionAst_visit,
};

static const R_Type_Operations _R_Mil_BinaryExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_BinaryExpressionAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.BinaryExpressionAst", R_Mil_BinaryExpressionAst, "R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_BinaryExpressionAst_typeOperations);

static void
R_Mil_BinaryExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_BinaryExpressionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_BinaryExpressionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }

  if (3 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }

  if (!R_Value_isInteger32Value(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }

  if (!R_Value_isObjectReferenceValue(&argumentValues[1])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[1]), _R_Mil_OperandAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }

  if (!R_Value_isObjectReferenceValue(&argumentValues[2])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[2]), _R_Mil_OperandAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }

  _self->type = R_Value_getInteger32Value(&argumentValues[0]);
  _self->operand1 = R_Value_getObjectReferenceValue(&argumentValues[1]);
  _self->operand2 = R_Value_getObjectReferenceValue(&argumentValues[2]);

  R_Object_setType(_self, _type);  
}

static void
R_Mil_BinaryExpressionAst_visit
  (
    R_Mil_BinaryExpressionAst* self
  )
{
  R_Object_visit(self->operand1);
  R_Object_visit(self->operand2);
}

R_Mil_BinaryExpressionAst*
R_Mil_BinaryExpressionAst_create
  (
    R_Mil_BinaryExpressionAstType type,
    R_Mil_OperandAst* operand1,
    R_Mil_OperandAst* operand2
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Integer32, .integer32Value = type },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operand1 },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operand2 }, };
  R_Mil_BinaryExpressionAst* self = R_allocateObject(_R_Mil_BinaryExpressionAst_getType(), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(expression : R.Mil.OperandAst)
/// @endcode
static void
R_Mil_LoadExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_LoadExpressionAst_visit
  (
    R_Mil_LoadExpressionAst* self
  );

static const R_ObjectType_Operations _R_Mil_LoadExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_LoadExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_LoadExpressionAst_visit,
};

static const R_Type_Operations _R_Mil_LoadExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_LoadExpressionAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.LoadExpressionAst", R_Mil_LoadExpressionAst, "R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_LoadExpressionAst_typeOperations);

static void
R_Mil_LoadExpressionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_LoadExpressionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_LoadExpressionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }

  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }

  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_Mil_OperandAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }

  _self->operand = R_Value_getObjectReferenceValue(&argumentValues[0]);

  R_Object_setType(_self, _type);
}

static void
R_Mil_LoadExpressionAst_visit
  (
    R_Mil_LoadExpressionAst* self
  )
{
  R_Object_visit(self->operand);
}

R_Mil_LoadExpressionAst*
R_Mil_LoadExpressionAst_create
  (
    R_Mil_OperandAst* operand
  )
{ 
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operand } };
  R_Mil_LoadExpressionAst* self = R_allocateObject(_R_Mil_LoadExpressionAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_StatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const R_ObjectType_Operations _R_Mil_StatementAst_objectTypeOperations = {
  .construct = &R_Mil_StatementAst_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _R_Mil_StatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_StatementAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.StatementAst", R_Mil_StatementAst, "R.Object", R_Object, &_R_Mil_StatementAst_typeOperations);

static void
R_Mil_StatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_StatementAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_StatementAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  R_Object_setType(_self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(targetVariableName : R.String, expression : Mil.ExpressionAst)
/// @endcode
static void
R_Mil_ExpressionStatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ExpressionStatementAst_visit
  (
    R_Mil_ExpressionStatementAst* self
  );

static const R_ObjectType_Operations _R_Mil_ExpressionStatementAst_objectTypeOperations = {
  .construct = &R_Mil_ExpressionStatementAst_constructImpl,
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

static void
R_Mil_ExpressionStatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_ExpressionStatementAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ExpressionStatementAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Mil_StatementAst_constructImpl(self, 0, &argumentValues[0]);
  }
 
  if (2 != numberOfArgumentValues) {
     R_setStatus(R_Status_NumberOfArgumentsInvalid);
     R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Object_getType(R_Value_getObjectReferenceValue(&argumentValues[0])), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[1])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Object_getType(R_Value_getObjectReferenceValue(&argumentValues[1])), _R_Mil_ExpressionAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  
  _self->targetVariableName = (R_String*)R_Value_isObjectReferenceValue(&argumentValues[0]);
  _self->expression =  (R_Mil_ExpressionAst*)R_Value_isObjectReferenceValue(&argumentValues[1]);
  R_Object_setType(_self, _type);
}

static void
R_Mil_ExpressionStatementAst_visit
  (
    R_Mil_ExpressionStatementAst* self
  )
{
  R_Object_visit(self->targetVariableName);
  R_Object_visit(self->expression);
}

R_Mil_ExpressionStatementAst*
R_Mil_ExpressionStatementAst_create
  (
    R_String* targetVariableName,
    R_Mil_ExpressionAst* expression
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)targetVariableName },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)expression } };
  R_Mil_ExpressionStatementAst* self = R_allocateObject(_R_Mil_ExpressionStatementAst_getType(), 2, &argumentValues[0]);
  return self;
}

R_String*
R_Mil_ExpressionStatementAst_getTargetVariableName
  (
    R_Mil_ExpressionStatementAst* self
  )
{ return self->targetVariableName; }

R_Mil_ExpressionAst*
R_Mil_ExpressionStatementAst_getExpression
  (
    R_Mil_ExpressionStatementAst* self
  )
{ return self->expression; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(labelName:R.String)
/// @endcode
static void
R_Mil_LabelStatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_LabelStatementAst_visit
  (
    R_Mil_LabelStatementAst* self
  );

static const R_ObjectType_Operations _R_Mil_LabelStatementAst_objectTypeOperations = {
  .construct = &R_Mil_LabelStatementAst_constructImpl,
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

static void
R_Mil_LabelStatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_LabelStatementAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_LabelStatementAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Mil_StatementAst_constructImpl(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->labelName = R_Value_getObjectReferenceValue(&argumentValues[0]);
  R_Object_setType(_self, _type);
}

static void
R_Mil_LabelStatementAst_visit
  (
    R_Mil_LabelStatementAst* self
  )
{ R_Object_visit(self->labelName); }

R_Mil_LabelStatementAst*
R_Mil_LabelStatementAst_create
  (
    R_String* labelName
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)labelName }, };
  R_Mil_LabelStatementAst* self = R_allocateObject(_R_Mil_LabelStatementAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(operand:R.Mil.OperandAst)
/// @endcode
static void
R_Mil_ReturnStatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ReturnStatementAst_visit
  (
    R_Mil_ReturnStatementAst* self
  );

static const R_ObjectType_Operations _R_Mil_ReturnStatementAst_objectTypeOperations = {
  .construct = &R_Mil_ReturnStatementAst_constructImpl,
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

Rex_defineObjectType("R.Mil.ReturnStatementAst", R_Mil_ReturnStatementAst, "Mil.StatementAst", R_Mil_StatementAst, &_R_Mil_ReturnStatementAst_typeOperations);

static void
R_Mil_ReturnStatementAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues 
  )
{
  R_Mil_ReturnStatementAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ReturnStatementAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Mil_StatementAst_constructImpl(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_Mil_OperandAst_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->operand = R_Value_getObjectReferenceValue(&argumentValues[0]);
  R_Object_setType(_self, _type);
}

static void
R_Mil_ReturnStatementAst_visit
  (
    R_Mil_ReturnStatementAst* self
  )
{ R_Object_visit(self->operand); }

R_Mil_ReturnStatementAst*
R_Mil_ReturnStatementAst_create
  (
    R_Mil_OperandAst* operand
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)operand }, };
  R_Mil_ReturnStatementAst* self = R_allocateObject(_R_Mil_ReturnStatementAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_DefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const R_ObjectType_Operations _R_Mil_DefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_DefinitionAst_constructImpl,
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

static void
R_Mil_DefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_DefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_DefinitionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  R_Object_setType(_self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(nativeName:R.String, procedureName:R.String,procedureParameters:R.List,procedureBody:List)
/// @endcode
static void
R_Mil_ProcedureDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ProcedureDefinitionAst_visit
  (
    R_Mil_ProcedureDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_ProcedureDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_ProcedureDefinitionAst_constructImpl,
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

static void
R_Mil_ProcedureDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_ProcedureDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ProcedureDefinitionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Mil_DefinitionAst_constructImpl(self, 0, &argumentValues[0]);
  }

  if (5 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->entry = R_Value_getBooleanValue(&argumentValues[0]);
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(&argumentValues[1], _R_String_getType());
  _self->procedureName = R_Argument_getObjectReferenceValue(&argumentValues[2], _R_String_getType());
  _self->procedureParameters = R_Argument_getObjectReferenceValue(&argumentValues[3], _R_List_getType());
  _self->procedureBody = R_Argument_getObjectReferenceValueOrNull(&argumentValues[4], _R_List_getType());
  R_Object_setType(_self, _type);
}

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

R_Mil_ProcedureDefinitionAst*
R_Mil_ProcedureDefinitionAst_create
  (
    R_BooleanValue entry,
    R_String* nativeName,
    R_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Boolean, .booleanValue = entry },
                               {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = procedureName },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = procedureParameters },
                               {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
  if (nativeName) {
    R_Value_setObjectReferenceValue(&argumentValues[1], nativeName);
  }
  if (procedureBody) {
    R_Value_setObjectReferenceValue(&argumentValues[4], procedureBody);
  }
  R_Mil_ProcedureDefinitionAst* self = R_allocateObject(_R_Mil_ProcedureDefinitionAst_getType(), 5, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(className:R.String, extendedClassName:R.String, classBody:R.List)
/// @endcode
static void
R_Mil_ClassDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ClassDefinitionAst_visit
  (
    R_Mil_ClassDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_ClassDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_ClassDefinitionAst_constructImpl,
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

static void
R_Mil_ClassDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{ 
  R_Mil_ClassDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ClassDefinitionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Mil_DefinitionAst_constructImpl(self, 0, &argumentValues[0]);
  }
  if (3 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->className = R_Argument_getObjectReferenceValue(&argumentValues[0], _R_String_getType());
  _self->extendedClassName = R_Argument_getObjectReferenceValueOrNull(&argumentValues[1], _R_String_getType());
  _self->classBody = R_Argument_getObjectReferenceValue(&argumentValues[2], _R_List_getType());
  R_Object_setType(_self, _type);
}

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

R_Mil_ClassDefinitionAst*
R_Mil_ClassDefinitionAst_create
  (
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = className },
    {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = classBody },
  };
  if (extendedClassName) {
    R_Value_setObjectReferenceValue(&argumentValues[1], extendedClassName);
  }
  R_Mil_ClassDefinitionAst* self = R_allocateObject(_R_Mil_ClassDefinitionAst_getType(), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_ClassMemberDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ClassMemberDefinitionAst_visit
  (
    R_Mil_ClassMemberDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_ClassMemberDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_ClassMemberDefinitionAst_constructImpl,
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

static void
R_Mil_ClassMemberDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_ClassMemberDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ClassMemberDefinitionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Mil_DefinitionAst_constructImpl(self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  R_Object_setType(_self, _type);
}

static void
R_Mil_ClassMemberDefinitionAst_visit
  (
    R_Mil_ClassMemberDefinitionAst* self
  )
{/*Intentionally empty.*/}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(methodName:R.String, methodParameters:R.List, methodBody:R.List)
/// @endcode
static void
R_Mil_MethodDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_MethodDefinitionAst_visit
  (
    R_Mil_MethodDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_MethodDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_MethodDefinitionAst_constructImpl,
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

static void
R_Mil_MethodDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_MethodDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_MethodDefinitionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }
  if (4 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(&argumentValues[0], _R_String_getType());
  _self->methodName = (R_String*)R_Argument_getObjectReferenceValue(&argumentValues[1], _R_String_getType());
  _self->methodParameters = (R_List*)R_Argument_getObjectReferenceValue(&argumentValues[2], _R_List_getType());
  _self->methodBody = (R_List*)R_Argument_getObjectReferenceValueOrNull(&argumentValues[3], _R_List_getType());
  R_Object_setType(_self, _type);
}

static void
R_Mil_MethodDefinitionAst_visit
  (
    R_Mil_MethodDefinitionAst* self
  )
{
  R_Object_visit(self->nativeName);
  R_Object_visit(self->methodName);
  R_Object_visit(self->methodParameters);
  R_Object_visit(self->methodBody);
}

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    R_String* nativeName,
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = methodName },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = methodParameters },
                               {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void }, };
  if (nativeName) {
    R_Value_setObjectReferenceValue(&argumentValues[0], nativeName);
  }
  if (methodBody) {
    R_Value_setObjectReferenceValue(&argumentValues[3], methodBody);
  }
  R_Mil_MethodDefinitionAst* self = R_allocateObject(_R_Mil_MethodDefinitionAst_getType(), 4, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// constructor(constructorParameters:R.List, constructorBody:R.List)
/// @endcode
static void
R_Mil_ConstructorDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_ConstructorDefinitionAst_visit
  (
    R_Mil_ConstructorDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_ConstructorDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_ConstructorDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_ConstructorDefinitionAst_visit,
};

static const R_Type_Operations _R_Mil_ConstructorDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ConstructorDefinitionAst_objectTypeOperations,
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

Rex_defineObjectType("R.Mil.ConstructorDefinitionAst", R_Mil_ConstructorDefinitionAst, "R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, &_R_Mil_ConstructorDefinitionAst_typeOperations);

static void
R_Mil_ConstructorDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_ConstructorDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_ConstructorDefinitionAst_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }
  if (3 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(&argumentValues[0], _R_String_getType());
  _self->constructorParameters = (R_List*)R_Argument_getObjectReferenceValue(&argumentValues[1], _R_List_getType());
  _self->constructorBody = (R_List*)R_Argument_getObjectReferenceValueOrNull(&argumentValues[2], _R_List_getType());
  R_Object_setType(_self, _type);
}

static void
R_Mil_ConstructorDefinitionAst_visit
  (
    R_Mil_ConstructorDefinitionAst* self
  )
{
  R_Object_visit(self->nativeName);
  R_Object_visit(self->constructorParameters);
  R_Object_visit(self->constructorBody);
}

R_Mil_ConstructorDefinitionAst*
R_Mil_ConstructorDefinitionAst_create
  (
    R_String* nativeName,
    R_List* constructorParameters,
    R_List* constructorBody
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)constructorParameters },
    {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
  };
  if (nativeName) {
    R_Value_setObjectReferenceValue(&argumentValues[0], nativeName);
  }
  if (constructorBody) {
    R_Value_setObjectReferenceValue(&argumentValues[2], constructorBody);
  }
  R_Mil_ConstructorDefinitionAst* self = R_allocateObject(_R_Mil_ConstructorDefinitionAst_getType(), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(variableName:R.String)
/// @endcode
static void
R_Mil_VariableDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_VariableDefinitionAst_visit
  (
    R_Mil_VariableDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_VariableDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_VariableDefinitionAst_constructImpl,
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

static void
R_Mil_VariableDefinitionAst_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_VariableDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_VariableDefinitionAst_getType();
  {
    R_Value argumentValues[] = { { .tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _R_String_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  _self->variableName = R_Value_getObjectReferenceValue(&argumentValues[0]);
  R_Object_setType(_self, _type);
}

static void
R_Mil_VariableDefinitionAst_visit
  (
    R_Mil_VariableDefinitionAst* self
  )
{ R_Object_visit(self->variableName); }

R_Mil_VariableDefinitionAst*
R_Mil_VariableDefinitionAst_create
  (
    R_String* variableName
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)variableName },
  };
  R_Mil_VariableDefinitionAst* self = R_allocateObject(_R_Mil_VariableDefinitionAst_getType(), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
