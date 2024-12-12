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

#if !defined(R_INTERPRETER_CONSTRUCTOR_INCLUDED)
#define R_INTERPRETER_CONSTRUCTOR_INCLUDED

#include "R/ForeignProcedure.h"
#include "R/Object.h"
#include "R/Value.h"
#include "R/Interpreter/Include.h"

Rex_declareObjectType("R.Interpreter.Constructor", R_Interpreter_Constructor, "R.Object");

struct R_Interpreter_Constructor {
  R_Object _parent;
  /// R_BooleanValue_True indicates that code is invalid and foreignProcedure points to a foreign procedure of this method.
  /// R_BooleanValue_False indicates that foreignProcedure is invalid and code points to the code of this method.
  R_BooleanValue isForeign;
  union {
    R_ForeignProcedureValue foreignProcedure;
    R_Interpreter_Code* code;
  };
};

R_Interpreter_Constructor*
R_Interpreter_Constructor_createForeign
  (
    R_ForeignProcedureValue foreignProcedure
  );

R_Interpreter_Constructor*
R_Interpreter_Constructor_create
  (
    R_Interpreter_Code* code
  );

R_Interpreter_Code*
R_Interpreter_Constructor_getCode
  (
    R_Interpreter_Constructor* self
  );

#endif // R_INTERPRETER_CONSTRUCTOR_INCLUDED
