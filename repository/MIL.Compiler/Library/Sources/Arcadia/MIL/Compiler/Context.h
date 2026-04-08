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

#if !defined(ARCADIA_MIL_COMPILER_CONTEXT_H_INCLUDED)
#define ARCADIA_MIL_COMPILER_CONTEXT_H_INCLUDED

#include "Arcadia/MIL/Frontend/Include.h"

Arcadia_declareObjectType(u8"Arcadia.MIL.Compiler.Context", Arcadia_MIL_Compiler_Context,
                          u8"Arcadia.Object");

struct Arcadia_MIL_Compiler_ContextDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MIL_Compiler_Context {
  Arcadia_Object _parent;
  /// @brief List of modules (list of Arcadia.MIL.AST.ModuleNode objects).
  Arcadia_List* moduleNodes;
  /// @brief Path of the working directory.
  Arcadia_FilePath* workingDirectoryPath;
  /// @brief The log.
  Arcadia_Log* log;
  /// @brief The parser.
  Arcadia_MIL_Parser* parser;
};

Arcadia_MIL_Compiler_Context*
Arcadia_MIL_Compiler_Context_create
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log
  );

void
Arcadia_MIL_Compiler_Context_run
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self,
    Arcadia_FilePath* workingDirectoryPath,
    Arcadia_List* moduleDirectoryPaths
  );

#endif // ARCADIA_MIL_COMPILER_CONTEXT_H_INCLUDED
