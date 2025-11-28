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

#if !defined(ARCADIA_DDL_READER_DEFAULTREADER_H_INCLUDED)
#define ARCADIA_DDL_READER_DEFAULTREADER_H_INCLUDED

#include "Arcadia/DDL/Nodes/Include.h"
#include "Arcadia/DDL/Reader/Parser.h"

/// @code
/// class Arcadia.DDL.DefaultReader
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.DDL.DefaultReader", Arcadia_DDL_DefaultReader,
                          u8"Arcadia.Object");

struct Arcadia_DDL_DefaultReader {
  Arcadia_Object parent;
  Arcadia_DDL_Parser* parser;
};

/// @brief Create a Data Definition Language default reader.
/// @param thread A pointer to this thread.
/// @return A pointer to the Data Definition Language default reader.
Arcadia_DDL_DefaultReader*
Arcadia_DDL_DefaultReader_create
  (
    Arcadia_Thread* thread
  );

/// @brief Run this DDL default reader.
/// @param thread A pointer to this thread.
/// @param self A pointer to this DDL default reader.
/// @return A pointer to the result DDL tree node.
Arcadia_DDL_Node*
Arcadia_DDL_DefaultReader_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_DefaultReader* self,
    Arcadia_UTF8Reader* input
  );

#endif // ARCADIA_DDL_READER_DEFAULTREADER_H_INCLUDED
