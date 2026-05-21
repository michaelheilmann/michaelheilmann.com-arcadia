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

#if !defined(ARCADIA_MILC_SCANNER_H_INCLUDED)
#define ARCADIA_MILC_SCANNER_H_INCLUDED

#include "Arcadia/MILC/WordType.h"
#include "Arcadia/Languages/Include.h"
typedef struct Arcadia_MILC_Context Arcadia_MILC_Context;

/// @brief A scanner for the MIL compiler.
/// @code
/// class Arcadia.MILC.Scanner extends Arcadia.Languages.Scanner {
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MILC.Scanner", Arcadia_MILC_Scanner,
                          u8"Arcadia.Languages.Scanner");

/// @brief Create a MIL scanner.
/// @param thread A pointer to this thread.
/// @param context The context.
/// @return A pointer to this MIL scanner.
Arcadia_MILC_Scanner*
Arcadia_MILC_Scanner_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

#endif // ARCADIA_MILC_SCANNER_H_INCLUDED
