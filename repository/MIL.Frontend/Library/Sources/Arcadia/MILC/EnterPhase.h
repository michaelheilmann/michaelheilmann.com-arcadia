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

#if !defined(ARCADIA_MILC_ENTERPHASE_H_INCLUDED)
#define ARCADIA_MILC_ENTERPHASE_H_INCLUDED

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Symbols/ModuleSymbol.h"

/// @brief The enter phase.
/// @warning The context object passed to the compilation task object is modified by each invocation of Arcadia.MILC.EnterPhase.execute.
/// @remarks
/// step 1:
/// for each module node
/// - find all module definition nodes and enter the symbols
/// - in particular, ensure that there are no two module symbols under a module node
/// - associate the module symbol with the module node
/// step 2:
/// for each module node
/// - find all (class|enumeration|procedure) nodes and enter the symbols 
Arcadia_declareObjectType(u8"Arcadia.MILC.EnterPhase", Arcadia_MILC_EnterPhase,
                          u8"Arcadia.Object");

struct Arcadia_MILC_EnterPhaseDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_EnterPhase {
  Arcadia_Object _parent;
  /// @brief The context.
  Arcadia_MILC_Context* context;
  /// @brief The last module symbol discovered for the current module node.
  /// If this is not null and another module symbol for the current module node is discovered, then this is an error.
  Arcadia_MILC_ModuleSymbol* lastSymbol;
  /// @brief A deque to add non-module definition nodes to be processed after their corresponding module definition node.
  /// This spares us the hazzle of recursive descent of the syntax tree.
  Arcadia_Deque* deque;
};

Arcadia_MILC_EnterPhase*
Arcadia_MILC_EnterPhase_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

void
Arcadia_MILC_EnterPhase_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  );

#endif // ARCADIA_MILC_ENTERPHASE_H_INCLUDED
