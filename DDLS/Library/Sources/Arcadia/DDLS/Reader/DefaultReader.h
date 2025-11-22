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

#if !defined(ARCADIA_DDLS_READER_DEFAULTREADER_H_INCLUDED)
#define ARCADIA_DDLS_READER_DEFAULTREADER_H_INCLUDED

#include "Arcadia/DDLS/Schema.h"
#include "Arcadia/DDL/Include.h"

Arcadia_declareObjectType(u8"Arcadia.DDLS.DefaultReader", Arcadia_DDLS_DefaultReader,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_DefaultReader {
  Arcadia_Object parent;
  Arcadia_Value BOOLEAN;
  Arcadia_Value NUMBER;
  Arcadia_Value STRING;
  Arcadia_Value VOID;

  Arcadia_DDL_Parser* parser;
  Arcadia_DDLS_Type* (*run)(Arcadia_Thread* thread, Arcadia_DDLS_DefaultReader*, Arcadia_Utf8Reader*);
};

Arcadia_DDLS_DefaultReader*
Arcadia_DDLS_DefaultReader_create
  (
    Arcadia_Thread* thread
  );

Arcadia_DDLS_Type*
Arcadia_DDLS_DefaultReader_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_DefaultReader* self,
    Arcadia_Utf8Reader* input
  );

#endif // ARCADIA_DDLS_READER_DEFAULTREADER_H_INCLUDED
