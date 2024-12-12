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
typedef struct R_Interpreter_Variable R_Interpreter_Variable;

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

#endif // R_INTERPRETER_CLASS_H_INCLUDED
