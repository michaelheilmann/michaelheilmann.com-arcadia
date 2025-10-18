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

#if !defined(ARCADIA_RING1_CONCURRENCY_CONDITION_H_INCLUDED)
#define ARCADIA_RING1_CONCURRENCY_CONDITION_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Configure.h"
#include <stddef.h>

/// @brief The type of return values of Arcadia_Concurrency_Condition functions.
typedef enum Arcadia_Concurrency_Condition_Result Arcadia_Concurrency_Condition_Result;

/// @brief A "condition" object to be embedded into structs or to be allocated on the stack or the heap.
typedef struct Arcadia_Concurrency_Condition Arcadia_Concurrency_Condition;

enum Arcadia_Concurrency_Condition_Result {
  Arcadia_Concurrency_Condition_Result_Success,
  Arcadia_Concurrency_Condition_Result_ArgumentInvalid,
  Arcadia_Concurrency_Condition_Result_AllocationFailed,
  Arcadia_Concurrency_Condition_Result_EnvironmentFailed,
  Arcadia_Concurrency_Condition_Result_Initialized,
};

struct Arcadia_Concurrency_Condition {
  void* pimpl;
}; // struct Arcadia_Concurrency_Condition

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_initialize
  (
    Arcadia_Concurrency_Condition* condition
  );

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_uninitialize
  (
    Arcadia_Concurrency_Condition* condition
  );

Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_wait
  (
    Arcadia_Concurrency_Condition* condition
  );
  
Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_signalOne
  (
    Arcadia_Concurrency_Condition* condition
  );
  
Arcadia_Concurrency_Condition_Result
Arcadia_Concurrency_Condition_signalAll
  (
    Arcadia_Concurrency_Condition* condition
  );

#endif // ARCADIA_RING1_CONCURRENCY_CONDITION_H_INCLUDED
