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

#if !defined(ARCADIA_MILC_COMPILATIONTASK_H_INCLUDED)
#define ARCADIA_MILC_COMPILATIONTASK_H_INCLUDED

#include "Arcadia/MILC/Context.h"

/// @brief Represents a compilation task.
/// @warning The context object passed to the compilation task object is modified by each invocation of Arcadia.MILC.CompilationTask.execute.
Arcadia_declareObjectType(u8"Arcadia.MILC.CompilationTask", Arcadia_MILC_CompilationTask,
                          u8"Arcadia.Object");

struct Arcadia_MILC_CompilationTaskDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_CompilationTask {
  Arcadia_Object _parent;
  /// @brief The context.
  Arcadia_MILC_Context* context;
  /// @brief The log.
  Arcadia_Log* log;
};

Arcadia_MILC_CompilationTask*
Arcadia_MILC_CompilationTask_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

void
Arcadia_MILC_CompilationTask_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_CompilationTask* self,
    Arcadia_FilePath* workingDirectoryPath,
    Arcadia_List* moduleDirectoryPaths
  );

#endif // ARCADIA_MILC_COMPILATIONTASK_H_INCLUDED
