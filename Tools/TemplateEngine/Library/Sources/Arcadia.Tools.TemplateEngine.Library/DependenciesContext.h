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

#if !defined(ARCADIA_TEMPLATEENGINE_DEPENDENCIESCONTEXT_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_DEPENDENCIESCONTEXT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.DependenciesContext", DependenciesContext,
                          u8"Arcadia.Object");

struct DependenciesContextDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct DependenciesContext {
  Arcadia_Object _parent;
  // The path of the dependencies file.
  Arcadia_FilePath* dependenciesFilePath;
  // Map from absolute file name strings to a set list of absolute file name strings
  Arcadia_Map* dependencies;
};

DependenciesContext*
DependenciesContext_create
  (
    Arcadia_Thread* thread
  );

void
DependenciesContext_write
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  );

/* Invoke this if a source file was discovered. This may be invoked multiple times for the same file. */
void
DependencyContext_onFile
  (
    Arcadia_Thread* thread,
    DependenciesContext* self,
    Arcadia_FilePath* path
  );

/* Invoke this if a dependency froom a file "from" to a file "to" was discovered. This may be invoked multiple times for the same combination of files. */
void
DependencyContext_onDependency
  (
    Arcadia_Thread* thread,
    DependenciesContext* self,
    Arcadia_FilePath* from,
    Arcadia_FilePath* to
  );

#endif // ARCADIA_TEMPLATEENGINE_DEPENDENCIESCONTEXT_H_INCLUDED
