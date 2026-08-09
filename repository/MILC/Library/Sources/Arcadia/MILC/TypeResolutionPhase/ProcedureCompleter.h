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

#if !defined(ARCADIA_MILC_TYPERESOLUTIONPHASE_PROCEDURECOMPLETER_H_INCLUDED)
#define ARCADIA_MILC_TYPERESOLUTIONPHASE_PROCEDURECOMPLETER_H_INCLUDED

#include "Arcadia/MILC/Completer.h"

// create Arcadia.MILC.MethodSymbol
// create Arcadia.MILC.VariableSymbol
Arcadia_declareObjectType(u8"Arcadia.MILC.TypeResolutionPhase.ProcedureCompleter", Arcadia_MILC_TypeResolutionPhase_ProcedureCompleter,
                          Arcadia_MILC_Completer);

struct Arcadia_MILC_TypeResolutionPhase_ProcedureCompleterDispatch {
  Arcadia_MILC_CompleterDispatch _parent;
};

struct Arcadia_MILC_TypeResolutionPhase_ProcedureCompleter {
  Arcadia_MILC_Completer _parent;
};

Arcadia_MILC_TypeResolutionPhase_ProcedureCompleter*
Arcadia_MILC_TypeResolutionPhase_ProcedureCompleter_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MILC_TYPERESOLUTIONPHASE_PROCEDURECOMPLETER_H_INCLUDED
