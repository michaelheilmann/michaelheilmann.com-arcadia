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

#if !defined(ARCADIA_DDL_READER_SCANNER_H_INCLUDED)
#define ARCADIA_DDL_READER_SCANNER_H_INCLUDED

#include "Arcadia/DDL/Reader/WordType.h"
#include "Arcadia/Languages/Include.h"

/// @brief A scanner for DDL.
/// @code
/// class Arcadia.DDL.Scanner
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DDL.Scanner", Arcadia_DDL_Scanner,
                          u8"Arcadia.Languages.Scanner");

/// @brief Create a DDL scanner.
/// @param thread A pointer to this thread.
/// @return A pointer to the DDL scanner.
Arcadia_DDL_Scanner*
Arcadia_DDL_Scanner_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_DDL_READER_SCANNER_H_INCLUDED
