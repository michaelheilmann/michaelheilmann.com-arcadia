// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(R_INTERPRETER_PROCEDURE_H_INCLUDED)
#define R_INTERPRETER_PROCEDURE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "R/Interpreter/Code.h"

Arcadia_declareObjectType(u8"R.Interpreter.Procedure", R_Interpreter_Procedure, u8"Arcadia.Object");

struct R_Interpreter_Procedure {
  Arcadia_Object _parent;
  /// The unqualified name of this procedure.
  Arcadia_String* unqualifiedName;
  /// List of strings. The string at index i denotes the name of the i-th parameter variable.
  Arcadia_List* parameterNames;
  /// Arcadia_BooleanValue_True indicates that code is invalid and foreignProcedure points to a foreign procedure of this procedure.
  /// Arcadia_BooleanValue_False indicates that foreignProcedure is invalid and code points to the code of this procedure.
  Arcadia_BooleanValue isForeign;
  union {
    Arcadia_ForeignProcedureValue foreignProcedure;
    R_Interpreter_Code* code;
  };
};

R_Interpreter_Procedure*
R_Interpreter_Procedure_createForeign
  ( 
    Arcadia_Thread* thread,
    Arcadia_String* procedureName,
    Arcadia_ForeignProcedureValue foreignProcedure
  );

R_Interpreter_Procedure*
R_Interpreter_Procedure_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    R_Interpreter_Code* code
  );

R_Interpreter_Code*
R_Interpreter_Procedure_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Procedure* self
  );

#endif // R_INTERPRETER_PROCEDURE_H_INCLUDED
