// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(R_INTERPRETER_CODE_H_INCLUDED)
#define R_INTERPRETER_CODE_H_INCLUDED

#include "Arcadia/Interpreter/Instruction.h"

/// @brief Code executed by the interpreter.
/// @remarks Code executed by the interpreter is a sequence of Natural8 values.
Arcadia_declareObjectType(u8"R.Interpreter.Code", R_Interpreter_Code, u8"Arcadia.Object");

struct R_Interpreter_CodeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct R_Interpreter_Code {
  Arcadia_Object _parent;
  /** @brief A pointer to an array of R_Machine_Code::cp Natural8 values. The first R_Machine_Code::sz values contain code. */
  Arcadia_Natural8Value* p;
  Arcadia_SizeValue sz, cp;
};

R_Interpreter_Code*
R_Interpreter_Code_create
  (
    Arcadia_Thread* thread
  );

void
R_Interpreter_Code_append
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

void
R_Interpreter_Code_appendIndexNatural8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    R_Machine_Code_IndexKind indexKind,
    Arcadia_Natural8Value indexValue
  );

void
R_Interpreter_Code_appendIndexNatural16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    R_Machine_Code_IndexKind indexKind,
    Arcadia_Natural16Value indexValue
  );

// index must be smaller than 52.4287.
void
R_Interpreter_Code_appendIndexNatural32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    R_Machine_Code_IndexKind indexKind,
    Arcadia_Natural16Value indexValue
  );

/// @brief Append a Natural8 value as a count.
/// @param self A pointer to this machine code.
/// @param countValue A Natural8 value as a count.
void
R_Interpreter_Code_appendCountNatural8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    Arcadia_Natural8Value countValue
  );

/// @brief Append a Natural16 value as a count.
/// @param self A pointer to this machine code.
/// @param countValue A Natural16 value as a count.
void
R_Interpreter_Code_appendCountNatural16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    Arcadia_Natural16Value countValue
  );

/// @brief Append a Natural32 value as a count.
/// @param self A pointer to this machine code.
/// @param countValue A Natural32 value as a count.
void
R_Interpreter_Code_appendCountNatural32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    Arcadia_Natural32Value countValue
  );

void
R_Interpreter_Code_decodeCount
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    Arcadia_Natural32Value* current,
    Arcadia_Natural32Value* countValue
  );

void
R_Interpreter_Code_decodeIndex
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* self,
    Arcadia_Natural32Value* current,
    R_Machine_Code_IndexKind* indexKind,
    Arcadia_Natural32Value* indexValue
  );

#endif // R_INTERPRETER_CODE_H_INCLUDED
