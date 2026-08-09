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

#if !defined(ARCADIA_MILC_CONTEXT_H_INCLUDED)
#define ARCADIA_MILC_CONTEXT_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/FileSystem/Include.h"
typedef struct Arcadia_MILC_Scanner Arcadia_MILC_Scanner;
typedef struct Arcadia_MILC_Parser Arcadia_MILC_Parser;
typedef struct Arcadia_MILC_EnterPhase Arcadia_MILC_EnterPhase;
typedef struct Arcadia_MILC_MemberEnterPhase Arcadia_MILC_MemberEnterPhase;
typedef struct Arcadia_MILC_Completer Arcadia_MILC_Completer;
typedef struct Arcadia_MILC_Environment Arcadia_MILC_Environment;
typedef struct  Arcadia_MILC_Backend_Implementation Arcadia_MILC_Backend_Implementation;

Arcadia_declareObjectType(u8"Arcadia.MILC.Context", Arcadia_MILC_Context,
                          Arcadia_Object);

struct Arcadia_MILC_ContextDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Context {
  Arcadia_Object _parent;
  Arcadia_Languages_StringTable* stringTable;
  Arcadia_Log* log;
  Arcadia_Languages_Diagnostics* diagnostics;
  /// @brief The working directory.
  Arcadia_FilePath* workingDirectoryPath;
  /// @brief The list of module nodes (objects of Arcadia.MILC.AST.ModuleNode or derived type).
  Arcadia_List* moduleNodes;
  /// @brief The root scope.
  Arcadia_Languages_Scope* scope;
  /// @brief A map from symbols to their environments.
  Arcadia_Map* environments;
  Arcadia_Map* instances;
};

Arcadia_MILC_Context*
Arcadia_MILC_Context_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MILC_CONTEXT_H_INCLUDED
