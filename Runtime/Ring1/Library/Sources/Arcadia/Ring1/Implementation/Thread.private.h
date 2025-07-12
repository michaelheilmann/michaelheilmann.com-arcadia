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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_THREAD_PRIVATE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_THREAD_PRIVATE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Thread.h"

struct Arcadia_Thread {
  Arcadia_Status status;
  Arcadia_JumpTarget* jumpTarget;
  struct {
    Arcadia_Value* elements;
    Arcadia_SizeValue size;
    Arcadia_SizeValue capacity;
  } stack;
  // Weak reference to the process object which owns this thread object.
  // When the thread is constructed, this is NULL.
  // The constructing process assigns itself to this variable after the thread is constructed.
  Arcadia_Process* process;
};

/*@undefined thread does not point to an uninitialized Arcadia_Thread object*/
void
Arcadia_Thread_initializeValueStack
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an uninitialized Arcadia_Thread object*/
void
Arcadia_Thread_uninitializeValueStack
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an uninitialized Arcadia_Thread object*/
void
Arcadia_Thread_initialize
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an initialized Arcadia_Thread object*/
void
Arcadia_Thread_uninitialize
  (
    Arcadia_Thread* thread
  );

/*@undefined thread does not point to an initialized Arcadia_Thread object*/
void
Arcadia_Thread_increaseValueStackCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue additionalCapacity
  );

void
Arcadia_Thread_ensureValueStackFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue requiredFreeCapacity
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_THREAD_PRIVATE_H_INCLUDED
