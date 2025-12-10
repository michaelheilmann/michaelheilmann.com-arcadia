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

#if !defined(ARCADIA_ADL_DEFINITIONS_COLORREADER_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_COLORREADER_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Reader.h"
#include "Arcadia/DDLS/Include.h"

Arcadia_declareObjectType(u8"Arcadia.ADL.ColorReader", Arcadia_ADL_ColorReader,
                          u8"Arcadia.ADL.Reader");

struct Arcadia_ADL_ColorReaderDispatch {
  Arcadia_ADL_ReaderDispatch _parent;
};

struct Arcadia_ADL_ColorReader {
  Arcadia_ADL_Reader _parent;

  // The string `type` cached here.
  Arcadia_String* TYPE;
  // The string `name` cached here.
  Arcadia_String* NAME;
  // The string `Color` cached here.
  Arcadia_String* SCHEMANAME;
  // The string `Color` cached here.
  Arcadia_String* TYPENAME;

  // The string `red` cached here.
  Arcadia_String* RED;
  // The string `green` cached here.
  Arcadia_String* GREEN;
  // The string `blue` cached here.
  Arcadia_String* BLUE;

  // The validation context. Cached here.
  Arcadia_DDLS_ValidationContext* validationContext;

};

Arcadia_ADL_ColorReader*
Arcadia_ADL_ColorReader_create
  (
    Arcadia_Thread* thread
  );

#endif  // ARCADIA_ADL_DEFINITIONS_COLORREADER_H_INCLUDED
