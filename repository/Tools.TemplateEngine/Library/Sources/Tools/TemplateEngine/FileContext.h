// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-09

#if !defined(TOOLS_TEMPLATEENGINE_FILECONTEXT_H_INCLUDED)
#define TOOLS_TEMPLATEENGINE_FILECONTEXT_H_INCLUDED

#include "R/Include.h"
#include "Tools/TemplateEngine/Context.h"

Rex_declareObjectType(u8"Tools.TemplateEngine.FileContext", FileContext, u8"Arcadia.Object");

struct FileContext {
  Arcadia_Object _parent;
  /// The underlaying context.
  Context* context;
  /// The path to the source file.
  Arcadia_FilePath* sourceFilePath;
  /// UTF8 reader for the source file.
  Arcadia_Utf8Reader* source;
  /// Map from strings to strings.
  Arcadia_Map* environment;
};

FileContext*
FileContext_create
  (
    Arcadia_Process* process,
    Context* context,
    Arcadia_FilePath* sourceFilePath
  );

void
FileContext_execute
  (
    Arcadia_Process* process,
    FileContext* context
  );

#endif // TOOLS_TEMPLATEENGINE_FILECONTEXT_H_INCLUDED
