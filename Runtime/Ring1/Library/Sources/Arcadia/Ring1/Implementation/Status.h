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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_STATUS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_STATUS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include <stdint.h>



// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Success
#define Arcadia_Status_Success (0)



// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_AccessDenied
#define Arcadia_Status_AccessDenied (1)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_AllocationFailed
#define Arcadia_Status_AllocationFailed (2)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_ArgumentTypeInvalid
#define Arcadia_Status_ArgumentTypeInvalid (3)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_ArgumentValueInvalid
#define Arcadia_Status_ArgumentValueInvalid (4)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_ConversionFailed
#define Arcadia_Status_ConversionFailed (5)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_DivisionByZero
#define Arcadia_Status_DivisionByZero (6)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Empty
#define Arcadia_Status_Empty (7)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_EncodingInvalid
#define Arcadia_Status_EncodingInvalid (8)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_EnvironmentFailed
#define Arcadia_Status_EnvironmentFailed (9)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Exists
#define Arcadia_Status_Exists (10)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_OperationFailed
#define Arcadia_Status_OperationFailed (11)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Found
#define Arcadia_Status_Found (12)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Full
#define Arcadia_Status_Full (32)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Initialized
#define Arcadia_Status_Initialized (14)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_LexicalError
#define Arcadia_Status_LexicalError (15)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotEmpty
#define Arcadia_Status_NotEmpty (16)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotExists
#define Arcadia_Status_NotExists (17)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotFound
#define Arcadia_Status_NotFound (18)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotImplemented
#define Arcadia_Status_NotImplemented (19)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotInitialized
#define Arcadia_Status_NotInitialized (20)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NumberOfArgumentsInvalid
#define Arcadia_Status_NumberOfArgumentsInvalid (21)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_OperationInvalid
#define Arcadia_Status_OperationInvalid (22)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_SemanticalError
#define Arcadia_Status_SemanticalError (23)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_SyntacticalError
#define Arcadia_Status_SyntacticalError (24)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_TestFailed
#define Arcadia_Status_TestFailed (25)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_TypeExists
#define Arcadia_Status_TypeExists (26)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_TypeNotExists
#define Arcadia_Status_TypeNotExists (27)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Uninitialized
#define Arcadia_Status_Uninitialized (28)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because of a stack overflow.
/// This value is guaranteed to be a non-zero value.
/// @remarks A stack overflow situation occurs if the application attempts to add an element to a full stack.
#define Arcadia_Status_StackOverflow (29+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because of a stack underflow.
/// This value is guaranteed to be a non-zero value.
/// @remarks A stack underflow situation occurs if the application attempts to remove an element from an empty stack.
#define Arcadia_Status_StackUnderflow (30+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because of a stack corruption.
/// This valus is guaranteed to be a non-zero value.
/// @remarks A stack corruption 
#define Arcadia_Status_StackCorruption (31+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because a value was raised.
/// This value is guaranteed to be a non-zero value.
#define Arcadia_Status_ValueRaised (32+1000)

typedef uint32_t Arcadia_Status;

#endif // ARCADIA_RING1_IMPLEMENTATION_STATUS_H_INCLUDED
