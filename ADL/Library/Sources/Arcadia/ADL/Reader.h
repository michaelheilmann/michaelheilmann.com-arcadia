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

#if !defined(ARCADIA_ADL_READER_H_INCLUDED)
#define ARCADIA_ADL_READER_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
#include "Arcadia/DDL/Include.h"
typedef struct Arcadia_ADL_Context Arcadia_ADL_Context;

/* The base of all readers. A reader reads ADL definitions of a type from a DDL node. */
Arcadia_declareObjectType(u8"Arcadia.ADL.Reader", Arcadia_ADL_Reader,
                          u8"Arcadia.Object");

struct Arcadia_ADL_ReaderDispatch {
  Arcadia_ObjectDispatch _parent;
  Arcadia_String* (*getTypeName)(Arcadia_Thread*, Arcadia_ADL_Reader*);
  Arcadia_ADL_Definition* (*read)(Arcadia_Thread*, Arcadia_ADL_Reader*, Arcadia_ADL_Context*, Arcadia_ADL_Definitions*, Arcadia_DDL_Node*);
};

struct Arcadia_ADL_Reader {
  Arcadia_Object _parent;
};

/* Get teh type name supported by this reader. */
Arcadia_String*
Arcadia_ADL_Reader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reader* self
  );

/* Read the ADL definition from a DDL node. */
Arcadia_ADL_Definition*
Arcadia_ADL_Reader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  );

#endif  // ARCADIA_ADL_READER_H_INCLUDED
