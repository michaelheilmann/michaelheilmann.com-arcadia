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

#if !defined(ARCADIA_MILC_MEMBERENTERPHASE_H_INCLUDED)
#define ARCADIA_MILC_MEMBERENTERPHASE_H_INCLUDED

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/AST/Include.h"
#include "Arcadia/MILC/Symbols/ModuleSymbol.h"

/// @brief The member enter phase.
/// @warning The context object passed to the compilation task object is modified by each invocation of Arcadia.MILC.EnterPhase.execute.
/// @remarks
/// - for class symbols enter the constructor, method, and fields symbols
/// - for enumeration symbols enter the enumeration element symbols
/// - for procedure symbols add their parameter variables
Arcadia_declareObjectType(u8"Arcadia.MILC.MemberEnterPhase", Arcadia_MILC_MemberEnterPhase,
                          u8"Arcadia.MILC.AST.Visitor");

struct Arcadia_MILC_MemberEnterPhaseDispatch {
  Arcadia_MILC_AST_VisitorDispatch _parent;
};

struct Arcadia_MILC_MemberEnterPhase {
  Arcadia_MILC_AST_Visitor _parent;
  /// @brief The context.
  Arcadia_MILC_Context* context;
};

Arcadia_MILC_MemberEnterPhase*
Arcadia_MILC_MemberEnterPhase_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

void
Arcadia_MILC_MemberEnterPhase_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase* self
  );

#endif // ARCADIA_MILC_MEMBERENTERPHASE_H_INCLUDED
