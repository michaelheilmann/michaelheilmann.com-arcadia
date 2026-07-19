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

#include "Arcadia.Ring2.Tests.ListTests/removeAt.h"

void Arcadia_Collections_Tests_ListTests_removeAt(Arcadia_Thread* thread) {
  { 
    Arcadia_List* l = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    Arcadia_List_insertBackInteger32Value(thread, l, 1);
    Arcadia_List_insertBackInteger32Value(thread, l, 2);
    Arcadia_List_insertBackInteger32Value(thread, l, 3);
    Arcadia_List_removeBack(thread, l, 1);
    Arcadia_Tests_assertTrue(thread, Arcadia_Collection_getSize(thread, (Arcadia_Collection*)l) == 2);
    Arcadia_Tests_assertTrue(thread, Arcadia_List_getInteger32ValueAt(thread, l, 0) == 1);
    Arcadia_Tests_assertTrue(thread, Arcadia_List_getInteger32ValueAt(thread, l, 1) == 2);

  }
}