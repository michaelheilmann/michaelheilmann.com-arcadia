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

#if !defined(R_INTERPRETER_PROCESSSTATE_PRIVATE_H_INCLUDED)
#define R_INTERPRETER_PROCESSSTATE_PRIVATE_H_INCLUDED

#include "Arcadia/Interpreter/ProcessState.h"
#include "Arcadia/Ring2/Implementation/Map.h"

struct R_Interpreter_ProcessState {
  // Global classe and global procedures.
  Arcadia_Map* globals;
  
  R_Interpreter_Code_Constants* constants;
  R_Interpreter_ThreadState* mainThread;
  R_Interpreter_ThreadState* currentThread;
};

#endif // R_INTERPRETER_PROCESSSTATE_PRIVATE_H_INCLUDED
