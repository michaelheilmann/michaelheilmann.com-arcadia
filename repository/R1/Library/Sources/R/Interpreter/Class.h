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

#if !defined(R_INTERPRETER_CLASS_H_INCLUDED)
#define R_INTERPRETER_CLASS_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Implementation/Map.h"
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
/// A class X defines variables Vd(X) := { vd(X)[1], vd(x)[2], ..., vd(x)[n] }.
/// The set of variables defined by a class X and all of its ancestor classes is denoted by V(X) := Vd(X) + V(Y).
/// Each variable in V(X) is assigned an unique index from 0, 1, ..., |V(X)| - 1.
/// When class instance x such that type(x) = X is created, then an array of size |V(X)| is allocated in which the i-th element contains the value of the variable with index i.
/// If we want to load the value of a variable then we simply load the value from the array element of its index.
/// Likewise, if we want to store a value in a variable then we simply store the value in the array element of its index.
/// 
/// CLASS INSTANCE METHODS
/// When the class A1 <: ... <: An is readied, then any propertiy the set of properties U_i members(Ai)
/// is assigned an index 1, 2, 3, ..., m such that no two methods p_i and p_j with p_i != p_j have
/// the same index. When an instance o with type(o) = A1 is created, the representation of o in memory
/// holds a reference to an array of length m. Invoking a method is simply a matter of searching
/// the method in the list of methods and accessing the index of that method in the array.
/// 
/// PARAMETER VARIABLES
/// The parameter variables x1, x2, ..., xn of a procedure or method or constructor are stored in the registers 0, ..., n - 1.
Rex_declareObjectType(u8"R.Interpreter.Class", R_Interpreter_Class, u8"Arcadia.Object");

struct R_Interpreter_Class {
  Arcadia_Object _parent;

  /// The name of the class.
  Arcadia_String* className;
  /// The ename of the class extended by this class.
  Arcadia_String* extendedClassName;
  /// The set of class members.
  Arcadia_Map* classMembers;

  /// The number of variables (synthetic) getVarsDefined(cls) := |cls.varsDefined| + getVarsDefined(cls.extendedClass).
  Arcadia_SizeValue numberOfVariables;

  /// Used for link
  Arcadia_Map* methodDispatch;

  /// A pointer to the extended class.
  /// null if extendedClassName is null.
  /// Otherwise a pointer to the extended class if it was resolved successfully.
  R_Interpreter_Class* extendedClass;
  /// If this class is complete.
  Arcadia_BooleanValue complete;
};

R_Interpreter_Class*
R_Interpreter_Class_create
  (
    Arcadia_Process* process,
    Arcadia_String* className,
    Arcadia_String* extendedClassName
  );

void
R_Interpreter_Class_addConstructor
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Constructor* constructor
  );

void
R_Interpreter_Class_addMethod
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Method* method
  );

void
R_Interpreter_Class_addVariable
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_Variable* variable
  );

void
R_Interpreter_Class_complete
  (
    Arcadia_Process* process,
    R_Interpreter_Class* self,
    R_Interpreter_ProcessState* processState
  );

#endif // R_INTERPRETER_CLASS_H_INCLUDED
