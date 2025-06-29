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

#if !defined(ARCADIA_TOOLS_RYULOOKUPTABLEGENERATOR_COMMON_H_INCLUDED)
#define ARCADIA_TOOLS_RYULOOKUPTABLEGENERATOR_COMMON_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

void
Arcadia_printInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32
  );

void
Arcadia_printImmutableUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* string
  );

void
Arcadia_printImmutableUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableUtf8String* string
  );

void
Arcadia_printStringBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* stringBuffer
  );

void
Arcadia_printNewline  
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_TOOLS_RYULOOKUPTABLEGENERATOR_COMMON_H_INCLUDED
