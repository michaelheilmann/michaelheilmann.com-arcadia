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

#if !defined(R_INTERPRETER_METHOD_INCLUDED)
#define R_INTERPRETER_METHOD_INCLUDED

#include "R/ForeignProcedure.h"
#include "R/Interpreter/Code.h"
#include "R/Object.h"
#include "R/Value.h"

Rex_declareObjectType("R.Interpreter.Method", R_Interpreter_Method, "R.Object");

struct R_Interpreter_Method {
  R_Object _parent;
  /// If the method is ready.
  R_BooleanValue ready;
  /// The zero-based index of this method if ready is true.
  /// Zero otherwise.
  R_SizeValue index;
  /// The name of this method.
  R_String* name;
  /// R_BooleanValue_True indicates that code is invalid and foreignProcedure points to a foreign procedure of this method.
  /// R_BooleanValue_False indicates that foreignProcedure is invalid and code points to the code of this method.
  R_BooleanValue isForeign;
  union {
    R_ForeignProcedureValue foreignProcedure;
    R_Interpreter_Code* code;
  };
};

R_Interpreter_Method*
R_Interpreter_Method_createForeign
  (
    R_String* name,
    R_ForeignProcedureValue foreignProcedure
  );

R_Interpreter_Method*
R_Interpreter_Method_create
  (
    R_String* name,
    R_Interpreter_Code* code
  );

R_Interpreter_Code*
R_Interpreter_Method_getCode
  (
    R_Interpreter_Method* self
  );

#endif // R_INTERPRETER_METHOD_INCLUDED
