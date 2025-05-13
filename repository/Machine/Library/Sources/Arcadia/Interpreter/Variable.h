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

#if !defined(R_INTERPRETER_VARIABLE_INCLUDED)
#define R_INTERPRETER_VARIABLE_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
typedef struct R_Interpreter_Class R_Interpreter_Class;

Arcadia_declareObjectType(u8"R.Interpreter.Variable", R_Interpreter_Variable, u8"Arcadia.Object");

struct R_Interpreter_Variable {
  Arcadia_Object _parent;
  /// If the variable is ready.
  Arcadia_BooleanValue ready;
  /// The zero-based index of this variable if ready is true.
  /// Zero otherwise.
  Arcadia_SizeValue index;
  /// The class defining this variable.
  R_Interpreter_Class *class;
  /// The name of this variable.
  Arcadia_String* name;
};

R_Interpreter_Variable*
R_Interpreter_Variable_create
  (
    Arcadia_Thread* thread,
    R_Interpreter_Class* class,
    Arcadia_String* name
  );

R_Interpreter_Class*
R_Interpreter_Variable_getClass
  (
    Arcadia_Thread* thread,
    R_Interpreter_Variable* self
  );

Arcadia_String*
R_Interpreter_Variable_getName
  (
    Arcadia_Thread* thread,
    R_Interpreter_Variable* self
  );

#endif // R_INTERPRETER_VARIABLE_INCLUDED
