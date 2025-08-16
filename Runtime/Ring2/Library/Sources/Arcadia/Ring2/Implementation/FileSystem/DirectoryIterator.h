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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_DIRECTORYITERATOR_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_DIRECTORYITERATOR_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Implementation/Configure.h"
#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_FilePath Arcadia_FilePath;

Arcadia_declareObjectType(u8"Arcadia.DirectoryIterator", Arcadia_DirectoryIterator,
                          u8"Arcadia.Object");
                          
struct Arcadia_DirectoryIterator {
  Arcadia_Object _parent;
  Arcadia_BooleanValue (*hasValue)(Arcadia_Thread* thread, Arcadia_DirectoryIterator* self);
  Arcadia_FilePath* (*getValue)(Arcadia_Thread* thread, Arcadia_DirectoryIterator* self);
  void (*nextValue)(Arcadia_Thread* thread, Arcadia_DirectoryIterator* self);
};

Arcadia_BooleanValue
Arcadia_DirectoryIterator_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  );

Arcadia_FilePath*
Arcadia_DirectoryIterator_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  );

void
Arcadia_DirectoryIterator_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_DIRECTORYITERATOR_H_INCLUDED
