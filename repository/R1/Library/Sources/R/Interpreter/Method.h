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

#if !defined(R_INTERPRETER_METHOD_INCLUDED)
#define R_INTERPRETER_METHOD_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "R/Interpreter/Code.h"
#include "R/List.h"

Rex_declareObjectType(u8"R.Interpreter.Method", R_Interpreter_Method, u8"Arcadia.Object");

struct R_Interpreter_Method {
  Arcadia_Object _parent;
  /// If the method is ready.
  Arcadia_BooleanValue ready;
  /// The unqualified name of this method.
  Arcadia_String* unqualifiedName;
  /// List of strings. The string at index i denotes the name of the i-th parameter variable.
  R_List* parameterNames;
  /// Arcadia_BooleanValue_True indicates that code is invalid and foreignProcedure points to a foreign procedure of this method.
  /// Arcadia_BooleanValue_False indicates that foreignProcedure is invalid and code points to the code of this method.
  Arcadia_BooleanValue isForeign;
  union {
    Arcadia_ForeignProcedureValue foreignProcedure;
    R_Interpreter_Code* code;
  };
  /// The zero-based index of this method if ready is true.
  /// Zero otherwise.
  Arcadia_SizeValue index;
};

R_Interpreter_Method*
R_Interpreter_Method_createForeign
  (
    Arcadia_Process* process,
    Arcadia_String* unqualifiedName,
    Arcadia_ForeignProcedureValue foreignProcedure
  );

R_Interpreter_Method*
R_Interpreter_Method_create
  (
    Arcadia_Process* process,
    Arcadia_String* unqualifiedName,
    R_Interpreter_Code* code
  );

R_Interpreter_Code*
R_Interpreter_Method_getCode
  (
    R_Interpreter_Method* self
  );

#endif // R_INTERPRETER_METHOD_INCLUDED
