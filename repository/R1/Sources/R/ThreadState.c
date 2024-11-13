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

// Last modified: 2024-11-04

#include "R/ThreadState.private.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/UnmanagedMemory.h"
#include "R/Value.h"

#define R_Configuration_DefaultNumberOfArgumentRegisters 32
#define R_Configuration_DefaultNumberOfRegisters 256
#define R_Configuration_DefaultRegisterStackCapacity 256

void
_RegisterStack_initialize
  (
    _RegisterStack* self
  )
{ 
  self->capacity = R_Configuration_DefaultRegisterStackCapacity;
  self->elements = NULL;
  if (!R_allocateUnmanaged_nojump(&self->elements, sizeof(R_Value) * self->capacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    R_Value_setVoidValue(self->elements + i, R_VoidValue_Void);
  }
  self->size = 0;
}

void
_RegisterStack_uninitialize
  (
    _RegisterStack* self
  )
{ 
  self->size = 0;
  R_deallocateUnmanaged_nojump(self->elements);
  self->elements = NULL;
  self->capacity = 0;
}

R_ThreadState*
R_ThreadState_create
  (
  )
{
  R_ThreadState* threadState = NULL;
  if (!R_allocateUnmanaged_nojump(&threadState, sizeof(R_ThreadState))) {
    R_jump();
  }

  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    _RegisterStack_initialize(&threadState->registerStack);
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(threadState);
    R_jump();
  }

  threadState->unusedRegisterFrames = NULL;
  threadState->registerFrameStack = NULL;

  threadState->registers = NULL;
  threadState->numberOfRegisters = R_Configuration_DefaultNumberOfRegisters;
  if (!R_reallocateUnmanaged_nojump(&threadState->registers, sizeof(R_Value) * threadState->numberOfRegisters)) {
    _RegisterStack_uninitialize(&threadState->registerStack);
    R_deallocateUnmanaged_nojump(threadState);
    threadState = NULL;
    R_jump();
  }
  for (R_SizeValue i = 0, n = threadState->numberOfRegisters; i < n; ++i) {
    R_Value_setVoidValue(threadState->registers + i, R_VoidValue_Void);
  }
  return threadState;
}

void
R_ThreadState_destroy
  (
    R_ThreadState* threadState
  )
{
  while (threadState->unusedRegisterFrames) {
    _RegisterFrame* registerFrame = threadState->unusedRegisterFrames;
    threadState->unusedRegisterFrames = threadState->unusedRegisterFrames->previous;
    R_deallocateUnmanaged_nojump(registerFrame);
  }
  _RegisterStack_uninitialize(&threadState->registerStack);
  R_deallocateUnmanaged_nojump(threadState);
  threadState = NULL;
}

void
R_ThreadState_visit
  (
    R_ThreadState* threadState
  )
{
  for (R_SizeValue i = 0, n = threadState->numberOfRegisters; i < n; ++i) {
    R_Value_visit(threadState->registers + i);
  }
}

R_SizeValue
R_ThreadState_getNumberOfRegisters
  (
    R_ThreadState* threadState
  )
{ return threadState->numberOfRegisters; }

R_Value*
R_ThreadState_getRegisters
  (
    R_ThreadState* threadState
  )
{ return threadState->registers; }

R_Value*
R_ThreadState_getRegisterAt
  (
    R_ThreadState* threadState,
    R_SizeValue registerIndex
  )
{ return &(threadState->registers[registerIndex]); }

static void
_RegisterStack_ensureFreeCapacity
  (
    _RegisterStack* registerStack,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue availableFreeCapacity = registerStack->capacity - registerStack->size;
  if (availableFreeCapacity > requiredFreeCapacity) {
    return;
  }
  R_SizeValue additionalCapacity = availableFreeCapacity - requiredFreeCapacity;
  static const R_SizeValue maximalCapacity = R_SizeValue_Maximum / sizeof(R_Value);
  if (maximalCapacity - additionalCapacity < registerStack->capacity) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  R_SizeValue newCapacity = additionalCapacity + registerStack->capacity;
  if (R_reallocateUnmanaged_nojump(&registerStack->elements, sizeof(R_Value) * newCapacity)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  registerStack->capacity = newCapacity;
}  

#include <string.h>

void
R_ThreadState_pushRegisterFrame
  (
    R_ThreadState* threadState,
    R_SizeValue start,
    R_SizeValue length
  )
{ 
  if (start + length > R_Configuration_DefaultNumberOfRegisters) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  _RegisterStack_ensureFreeCapacity(&threadState->registerStack, length);
  _RegisterFrame* registerFrame = NULL;
  if (threadState->unusedRegisterFrames) {
    registerFrame = threadState->unusedRegisterFrames;
    threadState->unusedRegisterFrames = threadState->unusedRegisterFrames->previous;
  } else {
    if (!R_allocateUnmanaged_nojump(&registerFrame, sizeof(_RegisterFrame))) {
      R_jump();
    }
  }
  registerFrame->start = start;
  registerFrame->length = length;
  memcpy(threadState->registerStack.elements + threadState->registerStack.size, threadState->registers + start, registerFrame->length * sizeof(R_Value));
  registerFrame->previous = threadState->registerFrameStack;
  threadState->registerFrameStack = registerFrame;
}

void
R_ThreadState_popRegisterFrame
  (
    R_ThreadState* threadState
  )
{ 
  if (!threadState->registerFrameStack) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  _RegisterFrame* registerFrame = threadState->registerFrameStack;
  threadState->registerFrameStack = threadState->registerFrameStack->previous;
  memcpy(threadState->registers + registerFrame->start, threadState->registerStack.elements + registerFrame->start, registerFrame->length * sizeof(R_Value));
  registerFrame->previous = threadState->unusedRegisterFrames;
  threadState->unusedRegisterFrames = registerFrame;
}
