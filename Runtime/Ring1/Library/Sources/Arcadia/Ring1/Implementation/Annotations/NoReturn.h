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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_ANNOTATIONS_NORETURN_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_ANNOTATIONS_NORETURN_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Configure.h"

/// @since 1.0
/// @brief
/// Function annotation indicating a function does not return normally.
#if Arcadia_Configuration_CompilerC_Msvc == Arcadia_Configuration_CompilerC
  #define Arcadia_NoReturn() __declspec(noreturn)
#elif Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
  #define Arcadia_NoReturn() __attribute__((noreturn))
#else
  #define Arcadia_NoReturn()
#endif

#endif // ARCADIA_RING1_IMPLEMENTATION_ANNOTATIONS_NORETURN_H_INCLUDED
