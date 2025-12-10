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

#if !defined(ARCADIA_RING2_LOGGING_LOG_H_INCLUDED)
#define ARCADIA_RING2_LOGGING_LOG_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_FileHandle Arcadia_FileHandle;
typedef struct Arcadia_String Arcadia_String;

Arcadia_declareObjectType(u8"Arcadia.Log", Arcadia_Log,
                          u8"Arcadia.Object");

struct Arcadia_LogDispatch {
  Arcadia_ObjectDispatch _parent;
  void (*info)(Arcadia_Thread*, Arcadia_Log*, Arcadia_String*);
  void (*error)(Arcadia_Thread*, Arcadia_Log*, Arcadia_String*);
};

struct Arcadia_Log {
  Arcadia_Object _parent;
  Arcadia_FileHandle* fileHandle;
};

void
Arcadia_Log_info
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self,
    Arcadia_String* message
  );

void
Arcadia_Log_error
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self,
    Arcadia_String* message
  );

#endif // ARCADIA_RING2_LOGGING_LOG_H_INCLUDED
