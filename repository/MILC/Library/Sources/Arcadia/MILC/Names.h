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

#if !defined(ARCADIA_MILC_NAMES_H_INCLUDED)
#define ARCADIA_MILC_NAMES_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Collections/Include.h"

static inline Arcadia_String*
Arcadia_MILC_Names_toTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* names
  )
{ 
  Arcadia_StringBuilder* stringBuilder = Arcadia_StringBuilder_create(thread);
  Arcadia_String* name = (Arcadia_String*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, (Arcadia_List*)names, 0, _Arcadia_String_getType(thread));
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, name);
  for (Arcadia_SizeValue i = 1, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)names); i < n; ++i) {
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, u8".");
    name = (Arcadia_String*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, (Arcadia_List*)names, i, _Arcadia_String_getType(thread));
    Arcadia_StringBuilder_insertBackString(thread, stringBuilder, name);
  }
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuilder));
}

#endif // ARCADIA_MILC_NAMES_H_INCLUDED
