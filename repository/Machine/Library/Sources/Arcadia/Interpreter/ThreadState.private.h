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

#if !defined(R_INTERPRETER_THREADSTATE_PRIVATE_H_INCLUDED)
#define R_INTERPRETER_THREADSTATE_PRIVATE_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Interpreter/Include.h"

#define R_ThreadState_withRegisterStack (0)

typedef struct Arcadia_Value Arcadia_Value;

#if defined(R_ThreadState_withRegisterStack) && 1 == R_ThreadState_withRegisterStack

typedef struct _RegisterStack _RegisterStack;

struct _RegisterStack {
  Arcadia_Value* elements;
  Arcadia_SizeValue size, capacity;
};

void
_RegisterStack_initialize
  (
    _RegisterStack* self
  );

void
_RegisterStack_uninitialize
  (
    _RegisterStack* self
  );

typedef struct _RegisterFrame _RegisterFrame;

struct _RegisterFrame {
  _RegisterFrame* previous;
  // The stack index (0 -> top of the stack, n - 1 -> bottom of the stack, n is the size of the stack) where registers backed up on the register stack by this register frame start at.
  Arcadia_SizeValue start;
  // The number of registers backed up on the registers by this register frame.
  // start + length not be greater than the size of the stack.
  Arcadia_SizeValue length;
};

#endif

struct R_Interpreter_ThreadState {
  struct {
    R_CallState* elements;
    Arcadia_SizeValue size;
    Arcadia_SizeValue capacity;
  } calls;

#if defined(R_Interpreter_ThreadState_withRegisterStack) && 1 == R_Interpreter_ThreadState_withRegisterStack

  _RegisterStack  registerStack;

  // List of unused register frame objects for being re-used.
  _RegisterFrame* unusedRegisterFrames;

  // Stack fo register frames.
  _RegisterFrame* registerFrameStack;

#endif

  Arcadia_Value* registers;
  Arcadia_SizeValue numberOfRegisters;

};

#endif // R_INTERPRETER_THREADSTATE_PRIVATE_H_INCLUDED
