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

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_ArgumentTypeInvalid
#define Arcadia_Status_ArgumentTypeInvalid (2)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_ArgumentValueInvalid
#define Arcadia_Status_ArgumentValueInvalid (3)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_ConversionFailed
#define Arcadia_Status_ConversionFailed (4)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_DivisionByZero
#define Arcadia_Status_DivisionByZero (5)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_EncodingInvalid
#define Arcadia_Status_EncodingInvalid (6)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_EnvironmentFailed
#define Arcadia_Status_EnvironmentFailed (7)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Exists
#define Arcadia_Status_Exists (8)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_FileSystemOperationFailed
#define Arcadia_Status_FileSystemOperationFailed (9)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Found
#define Arcadia_Status_Found (10)

/// @brief Symbolic constant for a Arcadia_Status value indicating a failure because something is full.
/// This value is guaranteed to be a non-zero value.
#define Arcadia_Status_Full (10+1000)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Initialized
#define Arcadia_Status_Initialized (11)

/// @brief Symbolic constant for a Arcadia_Status value indicating a failure because something is empty.
/// This value is guaranteed to be a non-zero value.
#define Arcadia_Status_Empty (11+1000)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_LexicalError
#define Arcadia_Status_LexicalError (12)

/// @brief Symbolic constant for a Arcadia_Status value indicating a failure because something is not empty.
/// This value is guaranteed to be a non-zero value.
#define Arcadia_Status_NotEmpty (12+1000)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotExists
#define Arcadia_Status_NotExists (13)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotFound
#define Arcadia_Status_NotFound (14)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotInitialized
#define Arcadia_Status_NotInitialized (15)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NotImplemented
#define Arcadia_Status_NotImplemented (16)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_NumberOfArgumentsInvalid
#define Arcadia_Status_NumberOfArgumentsInvalid (17)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_OperationInvalid
#define Arcadia_Status_OperationInvalid (18)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_SemanticalError
#define Arcadia_Status_SemanticalError (19)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_SyntacticalError
#define Arcadia_Status_SyntacticalError (20)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_TestFailed
#define Arcadia_Status_TestFailed (21)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_TypeExists
#define Arcadia_Status_TypeExists (22)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_TypeNotExists
#define Arcadia_Status_TypeNotExists (23)

// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_Uninitialized
#define Arcadia_Status_Uninitialized (24)

#define Arcadia_Status_FileNotFound (25)



// https://michaelheilmann.com/Arcadia/Ring1/#Arcadia_Status_AllocationFailed
#define Arcadia_Status_AllocationFailed (24+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because of a stack overflow.
/// This value is guaranteed to be a non-zero value.
/// @remarks A stack overflow situation occurs if the application attempts to add an element to a full stack.
#define Arcadia_Status_StackOverflow (25+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because of a stack underflow.
/// This value is guaranteed to be a non-zero value.
/// @remarks A stack underflow situation occurs if the application attempts to remove an element from an empty stack.
#define Arcadia_Status_StackUnderflow (26+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because of a stack corruption.
/// This valus is guaranteed to be a non-zero value.
/// @remarks A stack corruption 
#define Arcadia_Status_StackCorruption (27+1000)

/// @brief Symbolic constant for an Arcadia_Status value indicating a failure because a value was raised.
/// This value is guaranteed to be a non-zero value.
#define Arcadia_Status_ValueRaised (28+1000)

typedef uint32_t Arcadia_Status;

#endif // ARCADIA_RING1_IMPLEMENTATION_STATUS_H_INCLUDED
