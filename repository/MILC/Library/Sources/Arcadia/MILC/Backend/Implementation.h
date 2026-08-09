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

#if !defined(ARCADIA_MILC_BACKEND_IMPLEMENTATION_H_INCLUDED)
#define ARCADIA_MILC_BACKEND_IMPLEMENTATION_H_INCLUDED

#include "Arcadia/MILC/Context.h"

/// @brief The Cxx backend.
/// @warning The context object passed to the compilation task object is modified by each invocation of Arcadia.MILC.Backend.Implemetation.execute.
/// @remarks The Cxx backend operates over the root scope. Unlike other phases, it does not iterate over ASTs.
Arcadia_declareObjectType(u8"Arcadia.MILC.Backend.Implementation", Arcadia_MILC_Backend_Implementation,
                          u8"Arcadia.Object");

struct Arcadia_MILC_Backend_ImplementationDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Backend_Implementation {
  Arcadia_Object _parent;
};

Arcadia_MILC_Backend_Implementation*
Arcadia_MILC_Backend_Implementation_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_MILC_Backend_Implementation_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Context* context

  );

#endif // ARCADIA_MILC_BACKEND_IMPLEMENTATION_H_INCLUDED
