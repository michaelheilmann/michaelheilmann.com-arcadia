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

#if !defined(R_INTERPRETER_VARIABLE_INCLUDED)
#define R_INTERPRETER_VARIABLE_INCLUDED

#include "R/ForeignProcedure.h"
#include "R/Object.h"
#include "R/Value.h"
typedef struct R_Interpreter_Class R_Interpreter_Class;

Rex_declareObjectType("R.Interpreter.Variable", R_Interpreter_Variable, "R.Object");

struct R_Interpreter_Variable {
  R_Object _parent;
  /// If the variable is ready.
  R_BooleanValue ready;
  /// The zero-based index of this variable if ready is true.
  /// Zero otherwise.
  R_SizeValue index;
  /// The class defining this variable.
  R_Interpreter_Class *class;
  /// The name of this variable.
  R_String* name;
};

R_Interpreter_Variable*
R_Interpreter_Variable_create
  (
    R_Interpreter_Class* class,
    R_String* name
  );

R_Interpreter_Class*
R_Interpreter_Variable_getClass
  (
    R_Interpreter_Variable* self
  );

R_String*
R_Interpreter_Variable_getName
  (
    R_Interpreter_Variable* self
  );

#endif // R_INTERPRETER_VARIABLE_INCLUDED
