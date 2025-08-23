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

#if !defined(ARCADIA_RING2_LOGGING_LOGCATEGORY_H_INCLUDED)
#define ARCADIA_RING2_LOGGING_LOGCATEGORY_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

Arcadia_declareEnumerationType("Arcadia.LogCategory", Arcadia_LogCategory);
  
enum Arcadia_LogCategory {
  /// The "information" log level.
  Arcadia_LogCategory_Information = 1 << 2,
  /// The "warning" log level.
  Arcadia_LogCategory_Warning = 1 << 3,
  /// the "error" log level.
  Arcadia_LogCategory_Error = 1 << 4,
};

#endif // ARCADIA_RING2_LOGGING_LOGCATEGORY_H_INCLUDED
