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

#if !defined(R_INTERPRETER_CLASS_H_INCLUDED)
#define R_INTERPRETER_CLASS_H_INCLUDED

#include "R/Object.h"
#include "R/Map.h"
#include "R/Value.h"
typedef struct R_Interpreter_Constructor R_Interpreter_Constructor;
typedef struct R_Interpreter_Method R_Interpreter_Method;
typedef struct R_Interpreter_ProcessState R_Interpreter_ProcessState;
typedef struct R_Interpreter_Variable R_Interpreter_Variable;

/// COMPLETION OF CLASSES
/// When a class is added to the interpreter process, then it is "incomplete".
/// Before an object of that class (or a any of its subclasses) can be instantiated, the class must be "complete".
/// To complete a class, the "R_Interpreter_Class_complete" function must be invoked.
/// The function performs the following actions:
/// - if the class X is already complete, return
/// - if for the class X there is no name of an extended class is specified, the class X is "complete"
/// - otherwise each of the following steps must succeed
///   - the extended class Y was found
///   - "R_Interpreter_Class_complete" is successful for Y
/// - an index is assigned to the variables described in "CLASS INSTANCE VARIABLES"
/// - an index is assigned to the methods as described in "CLASS INSTANCE METHODS"
/// 
/// CLASS INSTANCE VARIABLES
/// When the class A1 <: ... <: An is readied, then any propertiy the set of variables U_i variables(Ai)
/// is assigned an index 1, 2, 3, ..., m such that no two variables x_i and y_j with x_i != y_j have
/// the same index. When an instance o with type(o) = A1 is created, the representation of o in memory
/// holds a reference to an array of length m. Getting/Setting a variable is simply a matter of searching
/// the variable in the list of variables and accessing the index of that variable in the array.
/// 
/// CLASS INSTANCE METHODS
/// When the class A1 <: ... <: An is readied, then any propertiy the set of properties U_i members(Ai)
/// is assigned an index 1, 2, 3, ..., m such that no two methods p_i and p_j with p_i != p_j have
/// the same index. When an instance o with type(o) = A1 is created, the representation of o in memory
/// holds a reference to an array of length m. Invoking a method is simply a matter of searching
/// the method in the list of methods and accessing the index of that method in the array.
Rex_declareObjectType("R.Interpreter.Class", R_Interpreter_Class, "R.Object");

struct R_Interpreter_Class {
  R_Object _parent;

  /// The name of the class.
  R_String* className;
  /// The ename of the class extended by this class.
  R_String* extendedClassName;
  /// The set of class members.
  R_Map* classMembers;

  /// A pointer to the extended class.
  /// null if extendedClassName is null.
  /// Otherwise a pointer to the extended class if it was resolved successfully.
  R_Interpreter_Class* extendedClass;
  /// If this class is complete.
  R_BooleanValue complete;
};

R_Interpreter_Class*
R_Interpreter_Class_create
  (
    R_String* className,
    R_String* extendedClassName
  );

void
R_Interpreter_Class_addConstructor
  (
    R_Interpreter_Class* self,
    R_Interpreter_Constructor* constructor
  );

void
R_Interpreter_Class_addMethod
  (
    R_Interpreter_Class* self,
    R_Interpreter_Method* method
  );

void
R_Interpreter_Class_addVariable
  (
    R_Interpreter_Class* self,
    R_Interpreter_Variable* variable
  );

void
R_Interpreter_Class_complete
  (
    R_Interpreter_Class* self,
    R_Interpreter_ProcessState* processState
  );

#endif // R_INTERPRETER_CLASS_H_INCLUDED
