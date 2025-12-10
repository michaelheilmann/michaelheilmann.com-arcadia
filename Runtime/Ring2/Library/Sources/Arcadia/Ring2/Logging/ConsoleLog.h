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

#if !defined(ARCADIA_RING2_LOGGING_CONSOLELOG_H_INCLUDED)
#define ARCADIA_RING2_LOGGING_CONSOLELOG_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Logging/Log.h"
typedef struct Arcadia_FileHandle Arcadia_FileHandle;
typedef struct Arcadia_String Arcadia_String;

Arcadia_declareObjectType(u8"Arcadia.ConsoleLog", Arcadia_ConsoleLog,
                          u8"Arcadia.Log");

struct Arcadia_ConsoleLogDispatch {
  Arcadia_LogDispatch _parent;
};

struct Arcadia_ConsoleLog {
  Arcadia_Log _parent;
  Arcadia_BooleanValue colorEnabled;
  Arcadia_FileHandle* fileHandle;
};

Arcadia_ConsoleLog*
Arcadia_ConsoleLog_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_ConsoleLog_setColorEnabled
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self,
    Arcadia_BooleanValue colorEnabled
  );

Arcadia_BooleanValue
Arcadia_ConsoleLog_getColorEnabled
  (
    Arcadia_Thread* thread,
    Arcadia_ConsoleLog* self
  );

#endif // ARCADIA_RING2_LOGGING_CONSOLELOG_H_INCLUDED
