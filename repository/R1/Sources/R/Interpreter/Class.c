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

// Last modified: 2024-12-12

#include "R/Interpreter/Class.h"

#include "R/ArgumentsValidation.h"
#include "R/Interpreter/Include.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/String.h"
#include "R/cstdlib.h"

static void
R_Interpreter_Class_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Interpreter_Class_visit
  (
    R_Interpreter_Class* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Class_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Class_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
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

Rex_defineObjectType("R.Interpreter.Class", R_Interpreter_Class, "R.Object", R_Object, &_typeOperations);

static void
R_Interpreter_Class_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_Class* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Interpreter_Class_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->className = R_Argument_getObjectReferenceValue(&argumentValues[0], _R_String_getType());
  _self->extendedClassName = R_Argument_getObjectReferenceValueOrNull(&argumentValues[1], _R_String_getType());
  _self->classMembers = R_Map_create();

  _self->extendedClass = NULL;

  _self->complete = R_BooleanValue_False;
  

  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Interpreter_Class_visit
  (
    R_Interpreter_Class* self
  )
{
  R_Object_visit(self->className);
  R_Object_visit(self->extendedClassName);
  R_Object_visit(self->classMembers);

  R_Object_visit(self->extendedClass);
}

R_Interpreter_Class*
R_Interpreter_Class_create
  (
    R_String* className,
    R_String* extendedClassName
  )
{
  R_Value argumentValues[] = { 
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = className },
    {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
  };
  if (extendedClassName) {
    R_Value_setObjectReferenceValue(&argumentValues[1], extendedClassName);
  }
  R_Interpreter_Class* self = R_allocateObject(_R_Interpreter_Class_getType(), 2, &argumentValues[0]);
  return self;
}

R_String*
R_Interpreter_Class_getClassName
  (
    R_Interpreter_Class* self
  )
{ return self->className; }

R_String*
R_Interpreter_Class_getExtendedClassName
  (
    R_Interpreter_Class* self
  )
{ return self->extendedClassName; }

void
R_Interpreter_Class_addConstructor
  (
    R_Interpreter_Class* self,
    R_Interpreter_Constructor* constructor
  )
{ 
  R_String* name = R_String_create_pn(R_ImmutableByteArray_create("<constructor>", c_strlen("<constructor>")));
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name };
  R_Value value = R_Map_get(self->classMembers, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  R_Value_setObjectReferenceValue(&value, constructor);
  R_Map_set(self->classMembers, key, value);
}

void
R_Interpreter_Class_addMethod
  (
    R_Interpreter_Class* self,
    R_Interpreter_Method* method
  )
{
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = method->name };
  R_Value value = R_Map_get(self->classMembers, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  R_Value_setObjectReferenceValue(&value, method);
  R_Map_set(self->classMembers, key, value);
}

void
R_Interpreter_Class_addVariable
  (
    R_Interpreter_Class* self,
    R_Interpreter_Variable* variable
  )
{
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = variable->name };
  R_Value value = R_Map_get(self->classMembers, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  R_Value_setObjectReferenceValue(&value, variable);
  R_Map_set(self->classMembers, key, value);
}

static R_Interpreter_Class*
getClass
  (
    R_Value v
  )
{
  if (!R_Value_isObjectReferenceValue(&v)) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_ObjectReferenceValue o = R_Value_getObjectReferenceValue(&v);
  if (!R_Type_isSubType(R_Object_getType(o), _R_Interpreter_Class_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  return o;
}

void
R_Interpreter_Class_complete
  (
    R_Interpreter_Class* self,
    R_Interpreter_ProcessState* processState
  )
{ 
  if (self->complete) {
    return;
  }
  if (self->extendedClassName) {
    R_Map* temporary = R_Map_create();
    self->extendedClass = getClass(R_Interpreter_ProcessState_getGlobal(processState, self->extendedClassName));
    R_Interpreter_Class_complete(self->extendedClass, processState);
    R_Interpreter_Class* current = self;
    do {
      R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = current->className };
      R_Value v = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = self };
      v = R_Map_get(temporary, v);
      if (R_Value_isObjectReferenceValue(&v)) {
        R_setStatus(R_Status_SemanticalError);
        R_jump();
      }
      R_Map_set(temporary, v, k);
      current = current->extendedClass;
    } while (current);
    self->complete = R_BooleanValue_True;
  }
  R_SizeValue methodIndex = 0;
  R_SizeValue variableIndex = 0;
  if (self->extendedClass) {
    R_List* classMember = R_Map_getValues(self->extendedClass->classMembers);
    for (R_SizeValue i = 0, n = R_List_getSize(classMember); i < n; ++i) {
      R_Value value = R_List_getAt(classMember, i);
      R_Type* valueType = R_Value_getType(&value);
      if (R_Type_isSubType(valueType, _R_Interpreter_Method_getType())) {
        R_Interpreter_Method* method = R_Value_getObjectReferenceValue(&value);
        if (methodIndex < method->index) {
          methodIndex = method->index;
        }
      } else if (R_Type_isSubType(valueType, _R_Interpreter_Variable_getType())) {
        R_Interpreter_Variable* variable = R_Value_getObjectReferenceValue(&value);
        if (variableIndex < variable->index) {
          variableIndex = variable->index;
        }
      } else {
        R_setStatus(R_Status_SemanticalError);
        R_jump();
      }
    }
  }
  methodIndex += 1;
  variableIndex += 1;
  // Complete instance class methods and the instance class variables.
  R_List* classMember = R_Map_getValues(self->classMembers);
  for (R_SizeValue i = 0, n = R_List_getSize(classMember); i < n; ++i) {
    R_Value value = R_List_getAt(classMember, i);
    R_Type* valueType = R_Value_getType(&value);
    if (R_Type_isSubType(valueType, _R_Interpreter_Method_getType())) {
      R_Interpreter_Method* method = R_Value_getObjectReferenceValue(&value);
      method->index = methodIndex++;
      method->ready = R_BooleanValue_True;
    } else if (R_Type_isSubType(valueType, _R_Interpreter_Variable_getType())) {
      R_Interpreter_Variable* variable = R_Value_getObjectReferenceValue(&value);
      variable->index = variableIndex++;
      variable->ready = R_BooleanValue_True;
    } else {
      R_setStatus(R_Status_SemanticalError);
      R_jump();
    }
  }
  
}
