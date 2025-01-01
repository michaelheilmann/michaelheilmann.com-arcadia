// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"

static void
R_Interpreter_Class_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Interpreter_Class_visit
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Class_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Class_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"R.Interpreter.Class", R_Interpreter_Class, u8"R.Object", R_Object, &_typeOperations);

static void
R_Interpreter_Class_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Interpreter_Class* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Class_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->className = R_Argument_getObjectReferenceValue(process, &argumentValues[0], _R_String_getType(process));
  _self->extendedClassName = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[1], _R_String_getType(process));
  _self->classMembers = R_Map_create(process);

  _self->extendedClass = NULL;

  _self->complete = Arcadia_BooleanValue_False;
  

  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Interpreter_Class_visit
  (
    Arcadia_Process* process,
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
    Arcadia_Process* process,
    R_String* className,
    R_String* extendedClassName
  )
{
  R_Value argumentValues[] = { 
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = className },
    {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
  };
  if (extendedClassName) {
    R_Value_setObjectReferenceValue(&argumentValues[1], extendedClassName);
  }
  R_Interpreter_Class* self = R_allocateObject(process, _R_Interpreter_Class_getType(process), 2, &argumentValues[0]);
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
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Constructor* constructor
  )
{ 
  R_String* name = R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, u8"<constructor>", c_strlen(u8"<constructor>")));
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name };
  R_Value value = R_Map_get(process, self->classMembers, key);
  if (!R_Value_isVoidValue(&value)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_Exists);
    Arcadia_Process_jump(process);
  }
  R_Value_setObjectReferenceValue(&value, constructor);
  R_Map_set(process, self->classMembers, key, value);
}

void
R_Interpreter_Class_addMethod
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Method* method
  )
{
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = method->unqualifiedName };
  R_Value value = R_Map_get(process, self->classMembers, key);
  if (!R_Value_isVoidValue(&value)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_Exists);
    Arcadia_Process_jump(process);
  }
  R_Value_setObjectReferenceValue(&value, method);
  R_Map_set(process, self->classMembers, key, value);
}

void
R_Interpreter_Class_addVariable
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Variable* variable
  )
{
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = variable->name };
  R_Value value = R_Map_get(process, self->classMembers, key);
  if (!R_Value_isVoidValue(&value)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_Exists);
    Arcadia_Process_jump(process);
  }
  R_Value_setObjectReferenceValue(&value, variable);
  R_Map_set(process, self->classMembers, key, value);
}

static R_Interpreter_Class*
getClass
  (
    Arcadia_Process* process,
    R_Value v
  )
{
  if (!R_Value_isObjectReferenceValue(&v)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  R_ObjectReferenceValue o = R_Value_getObjectReferenceValue(&v);
  if (!Arcadia_Type_isSubType(R_Object_getType(o), _R_Interpreter_Class_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  return o;
}

static void
completeExtendedClass
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_ProcessState* processState
  )
{ 
  /* (1) if an extended class name is specified, resolve and complete the class. */
  if (self->extendedClassName) {
    self->extendedClass = getClass(process, R_Interpreter_ProcessState_getGlobal(process, processState, self->extendedClassName));
    R_Interpreter_Class_complete(process, self->extendedClass, processState);
  }
  /* (2) ensure extension sequence is acyclic, and complete extended class if an extended class exists. */
  if (self->extendedClassName) {
    self->extendedClass = getClass(process, R_Interpreter_ProcessState_getGlobal(process, processState, self->extendedClassName));
    R_Interpreter_Class_complete(process, self->extendedClass, processState);
    R_Map* temporary = R_Map_create(process);
    R_Interpreter_Class* current = self;
    do {
      R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = current->className };
      R_Value v = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = self };
      v = R_Map_get(process, temporary, v);
      if (R_Value_isObjectReferenceValue(&v)) {
        /* "Y may not inherit from itself" */
        Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
        Arcadia_Process_jump(process);
      }
      R_Map_set(process, temporary, v, k);
      current = current->extendedClass;
    } while (current);
  }
}

static void
completeVariables
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_ProcessState* processState
  )
{
  Arcadia_SizeValue numberOfVariables = 0;
  if (self->extendedClass) {
    numberOfVariables = self->extendedClass->numberOfVariables;
  }
  // Complete class instance variables.
  R_List* classMember = R_Map_getValues(process, self->classMembers);
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(classMember); i < n; ++i) {
    R_Value value = R_List_getAt(process, classMember, i);
    Arcadia_TypeValue valueType = R_Value_getType(process, &value);
    if (Arcadia_Type_isSubType(valueType, _R_Interpreter_Variable_getType(process))) {
      R_Interpreter_Variable* variable = R_Value_getObjectReferenceValue(&value);
      variable->index = numberOfVariables++;
      variable->ready = Arcadia_BooleanValue_True;
    } else {
      Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
      Arcadia_Process_jump(process);
    }
  }
  self->numberOfVariables = numberOfVariables;
}

void
R_Interpreter_Class_complete
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_ProcessState* processState
  )
{ 
  if (self->complete) {
    return;
  }
  /* (1) if an extended class name is specified, resolve and complete the class. */
  if (self->extendedClassName) {
    self->extendedClass = getClass(process, R_Interpreter_ProcessState_getGlobal(process, processState, self->extendedClassName));
    R_Interpreter_Class_complete(process, self->extendedClass, processState);
  }
  /* (2) ensure extension sequence is acyclic, and complete extended class if an extended class exists. */
  if (self->extendedClassName) {
    self->extendedClass = getClass(process, R_Interpreter_ProcessState_getGlobal(process, processState, self->extendedClassName));
    R_Interpreter_Class_complete(process, self->extendedClass, processState);
    R_Map* temporary = R_Map_create(process);
    R_Interpreter_Class* current = self;
    do {
      R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = current->className };
      R_Value v = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = self };
      v = R_Map_get(process, temporary, v);
      if (R_Value_isObjectReferenceValue(&v)) {
        /* "Y may not inherit from itself" */
        Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
        Arcadia_Process_jump(process);
      }
      R_Map_set(process, temporary, v, k);
      current = current->extendedClass;
    } while (current);
  }
  /* (3) complete the variables */
  completeVariables(process, self, processState);

  /* (4) complete the methods and the method dispatch */
  self->methodDispatch = R_Map_create(process);
  if (self->extendedClass) {
    self->methodDispatch = R_Map_clone(process, self->extendedClass->methodDispatch);
  } else {
    self->methodDispatch = R_Map_create(process);
  }
  R_List* members = R_Map_getValues(process, self->classMembers);
  for (Arcadia_SizeValue i = 0, n = R_List_getSize(members); i < n; ++i) {
    R_Value v = R_List_getAt(process, members, i);
    if (Arcadia_Type_isSubType(R_Value_getType(process, &v), _R_Interpreter_Method_getType(process))) {
      R_Interpreter_Method *m = R_Value_getObjectReferenceValue(&v);
      R_Value k2 = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = m->unqualifiedName };
      R_Value v2 = R_Map_get(process, self->methodDispatch, k2);
      if (!R_Value_isVoidValue(&v2)) {
        R_Interpreter_Method* m2 = R_Value_getObjectReferenceValue(&v2);
        m->index = m2->index;
        m->ready = Arcadia_BooleanValue_True;
      } else {
        m->index = R_Map_getSize(self->methodDispatch);
        m->ready = Arcadia_BooleanValue_True;
      }
    }
  }

  self->complete = Arcadia_BooleanValue_True;
}
