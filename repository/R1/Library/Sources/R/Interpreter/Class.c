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

#include "R/Include.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"

static void
R_Interpreter_Class_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Interpreter_Class_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Class* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
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

Rex_defineObjectType(u8"R.Interpreter.Class", R_Interpreter_Class, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Interpreter_Class_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Interpreter_Class* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Class_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->className = R_Argument_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  _self->extendedClassName = R_Argument_getObjectReferenceValueOrNull(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  _self->classMembers = Arcadia_Map_create(thread);

  _self->extendedClass = NULL;

  _self->complete = Arcadia_BooleanValue_False;

  Arcadia_Object_setType(thread, _self, _type);
}

static void
R_Interpreter_Class_visit
  (
    Arcadia_Thread* thread,
    R_Interpreter_Class* self
  )
{
  Arcadia_Object_visit(thread, self->className);
  Arcadia_Object_visit(thread, self->extendedClassName);
  Arcadia_Object_visit(thread, self->classMembers);
  Arcadia_Object_visit(thread, self->extendedClass);
}

R_Interpreter_Class*
R_Interpreter_Class_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* className,
    Arcadia_String* extendedClassName
  )
{
  Arcadia_Value argumentValues[] = { 
    {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = className },
    {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
  };
  if (extendedClassName) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[1], extendedClassName);
  }
  R_Interpreter_Class* self = Arcadia_allocateObject(thread, _R_Interpreter_Class_getType(thread), 2, &argumentValues[0]);
  return self;
}

Arcadia_String*
R_Interpreter_Class_getClassName
  (
    R_Interpreter_Class* self
  )
{ return self->className; }

Arcadia_String*
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
  Arcadia_String* name = Arcadia_String_create_pn(Arcadia_Process_getThread(process), Arcadia_ImmutableByteArray_create(Arcadia_Process_getThread(process), u8"<constructor>", sizeof(u8"<constructor>") - 1));
  Arcadia_Value key = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name };
  Arcadia_Value value = Arcadia_Map_get(Arcadia_Process_getThread(process), self->classMembers, key);
  if (!Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_Exists);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value_setObjectReferenceValue(&value, constructor);
  Arcadia_Map_set(Arcadia_Process_getThread(process), self->classMembers, key, value);
}

void
R_Interpreter_Class_addMethod
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Method* method
  )
{
  Arcadia_Value key = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = method->unqualifiedName };
  Arcadia_Value value = Arcadia_Map_get(Arcadia_Process_getThread(process), self->classMembers, key);
  if (!Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_Exists);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value_setObjectReferenceValue(&value, method);
  Arcadia_Map_set(Arcadia_Process_getThread(process), self->classMembers, key, value);
}

void
R_Interpreter_Class_addVariable
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Variable* variable
  )
{
  Arcadia_Value key = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = variable->name };
  Arcadia_Value value = Arcadia_Map_get(Arcadia_Process_getThread(process), self->classMembers, key);
  if (!Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_Exists);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  Arcadia_Value_setObjectReferenceValue(&value, variable);
  Arcadia_Map_set(Arcadia_Process_getThread(process), self->classMembers, key, value);
}

static R_Interpreter_Class*
getClass
  (
    Arcadia_Process* process,
    Arcadia_Value v
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  if (!Arcadia_Value_isObjectReferenceValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ObjectReferenceValue o = Arcadia_Value_getObjectReferenceValue(&v);
  if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(o), _R_Interpreter_Class_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
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
    Arcadia_Map* temporary = Arcadia_Map_create(Arcadia_Process_getThread(process));
    R_Interpreter_Class* current = self;
    do {
      Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = current->className };
      Arcadia_Value v = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = self };
      v = Arcadia_Map_get(Arcadia_Process_getThread(process), temporary, v);
      if (Arcadia_Value_isObjectReferenceValue(&v)) {
        /* "Y may not inherit from itself" */
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      Arcadia_Map_set(Arcadia_Process_getThread(process), temporary, v, k);
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
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_SizeValue numberOfVariables = 0;
  if (self->extendedClass) {
    numberOfVariables = self->extendedClass->numberOfVariables;
  }
  // Complete class instance variables.
  Arcadia_List* classMember = Arcadia_Map_getValues(thread, self->classMembers);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, classMember); i < n; ++i) {
    Arcadia_Value value = Arcadia_List_getAt(thread, classMember, i);
    Arcadia_TypeValue valueType = Arcadia_Value_getType(thread, &value);
    if (Arcadia_Type_isSubType(thread, valueType, _R_Interpreter_Variable_getType(thread))) {
      R_Interpreter_Variable* variable = Arcadia_Value_getObjectReferenceValue(&value);
      variable->index = numberOfVariables++;
      variable->ready = Arcadia_BooleanValue_True;
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
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
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
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
    Arcadia_Map* temporary = Arcadia_Map_create(thread);
    R_Interpreter_Class* current = self;
    do {
      Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = current->className };
      Arcadia_Value v = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = self };
      v = Arcadia_Map_get(thread, temporary, v);
      if (Arcadia_Value_isObjectReferenceValue(&v)) {
        /* "Y may not inherit from itself" */
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Map_set(thread, temporary, v, k);
      current = current->extendedClass;
    } while (current);
  }
  /* (3) complete the variables */
  completeVariables(process, self, processState);

  /* (4) complete the methods and the method dispatch */
  self->methodDispatch = Arcadia_Map_create(thread);
  if (self->extendedClass) {
    self->methodDispatch = Arcadia_Map_clone(thread, self->extendedClass->methodDispatch);
  } else {
    self->methodDispatch = Arcadia_Map_create(thread);
  }
  Arcadia_List* members = Arcadia_Map_getValues(thread, self->classMembers);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, members); i < n; ++i) {
    Arcadia_Value v = Arcadia_List_getAt(thread, members, i);
    if (Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, &v), _R_Interpreter_Method_getType(thread))) {
      R_Interpreter_Method *m = Arcadia_Value_getObjectReferenceValue(&v);
      Arcadia_Value k2 = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = m->unqualifiedName };
      Arcadia_Value v2 = Arcadia_Map_get(thread, self->methodDispatch, k2);
      if (!Arcadia_Value_isVoidValue(&v2)) {
        R_Interpreter_Method* m2 = Arcadia_Value_getObjectReferenceValue(&v2);
        m->index = m2->index;
        m->ready = Arcadia_BooleanValue_True;
      } else {
        m->index = Arcadia_Map_getSize(thread, self->methodDispatch);
        m->ready = Arcadia_BooleanValue_True;
      }
    }
  }

  self->complete = Arcadia_BooleanValue_True;
}
