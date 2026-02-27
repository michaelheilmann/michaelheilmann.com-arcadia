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

#if !defined(ARCADIA_ARMS_TYPENAME_H_INCLUDED)
#define ARCADIA_ARMS_TYPENAME_H_INCLUDED

#include "Arcadia/ARMS/Configure.h"
#include "Arcadia/ARMS/SizeType.h"
#include "Arcadia/ARMS/Natural8Type.h"
#include "Arcadia/ARMS/StatusType.h"

typedef struct Arcadia_ARMS_TypeName Arcadia_ARMS_TypeName;

/** TOOD: The set of types and the set of type names are monotonically non-decreasing until they are destroyed when the process ends. */
Arcadia_ARMS_Status
Arcadia_ARMS_TypeName_getOrCreate
  (
    Arcadia_ARMS_TypeName** result,
    const Arcadia_ARMS_Natural8* bytes,
    Arcadia_ARMS_Size numberOfBytes
  );

Arcadia_ARMS_Status
Arcadia_ARMS_TypeName_getData
  (
    Arcadia_ARMS_TypeName* typeName,
    const Arcadia_ARMS_Natural8** bytes,
    Arcadia_ARMS_Size* numberOfBytes
  );

/** TOOD: Add reference counting for type names. */
void
Arcadia_ARMS_TypeName_ref
  (
    Arcadia_ARMS_TypeName* typeName
  );

/** TOOD: Add reference counting for type names. */
void
Arcadia_ARMS_TypeName_unref
  (
    Arcadia_ARMS_TypeName* typeName
  );

#endif // ARCADIA_ARMS_TYPENAME_H_INCLUDED
