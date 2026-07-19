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

#if !defined(ARCADIA_COLLECTIONS_ARRAYSTACK_H_INCLUDED)
#define ARCADIA_COLLECTIONS_ARRAYSTACK_H_INCLUDED

#if !defined(ARCADIA_COLLECTIONS_MODULE)
  #error("do not include directly, include `Arcadia/Collections/Include.h` instead")
#endif

#include "Arcadia/Collections/Stack.h"

Arcadia_declareObjectType(u8"Arcadia.ArrayStack", Arcadia_ArrayStack,
                          u8"Arcadia.Stack");

struct Arcadia_ArrayStackDispatch {
  Arcadia_StackDispatch _parent;
};

struct Arcadia_ArrayStack {
  Arcadia_Stack _parent;
  Arcadia_Value* elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

// https://michaelheilmann.com/Arcadia/Collections/#Arcadia_ArrayStack_create
Arcadia_ArrayStack*
Arcadia_ArrayStack_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_COLLECTIONS_ARRAYSTACK_H_INCLUDED
