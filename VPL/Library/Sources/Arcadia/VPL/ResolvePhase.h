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

#if !defined(ARCADIA_VPL_RESOLVEPHASE_H_INCLUDED)
#define ARCADIA_VPL_RESOLVEPHASE_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/Symbols/Include.h"

// Resolve types.
Arcadia_declareObjectType(u8"Arcadia.VPL.ResolvePhase", Arcadia_VPL_ResolvePhase,
                          Arcadia_Object);

struct Arcadia_VPL_ResolvePhaseDispatch {
  Arcadia_ObjectDispatch _parent;
};  
                         
struct Arcadia_VPL_ResolvePhase {
  Arcadia_Object _parent;
};
      
Arcadia_VPL_ResolvePhase*
Arcadia_VPL_ResolvePhase_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_VPL_ResolvePhase_run
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ResolvePhase* self,
    Arcadia_VPL_Symbols_Program* program
  );

#endif // ARCADIA_VPL_RESOLVEPHASE_H_INCLUDED
