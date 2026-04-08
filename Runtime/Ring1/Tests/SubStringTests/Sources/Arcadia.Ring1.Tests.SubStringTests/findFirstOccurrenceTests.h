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

#if !defined(ARCADIA_RING1_TESTS_SUBSTRINGTESTS_FINDFIRSTOCCURRENCETESTS_H_INCLUDED)
#define ARCADIA_RING1_TESTS_SUBSTRINGTESTS_FINDFIRSTOCCURRENCETESTS_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

// Search 'a' in a string. The string does not contain any occurence of 'a'. No occurrence shall be found.
void
findFirstOccurrenceTests1
  (
    Arcadia_Thread* thread
  );

// Search 'a' in a a string. The string contains a single occurrence of 'a'. That single occurrence shall be found.
void
findFirstOccurrenceTests2
  (
    Arcadia_Thread* thread
  );

// Search 'a' in a string. The string contains multiply occurrences of 'a'. The first occurrence shall be found.
void
findFirstOccurrenceTests3
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_RING1_TESTS_SUBSTRINGTESTS_FINDFIRSTOCCURRENCETESTS_H_INCLUDED
