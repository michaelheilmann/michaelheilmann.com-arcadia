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

#if !defined(ARCADIA_MILC_ENVIRONMENT_H_INCLUDED)
#define ARCADIA_MILC_ENVIRONMENT_H_INCLUDED

#include "Arcadia/MILC/Symbols/Symbol.h"
#include "Arcadia/MILC/AST/CompilationUnitNode.h"

/// @brief An environment storing information on a symbol.
Arcadia_declareObjectType(u8"Arcadia.MILC.Environment", Arcadia_MILC_Environment,
                          u8"Arcadia.Object");

struct Arcadia_MILC_EnvironmentDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Environment {
  Arcadia_Object _parent;
  /// @brief The symbol this environment is associated with.
  Arcadia_MILC_Symbol* symbol;
  /// @brief The compilation unit the symbol is defined in.
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode;
};

Arcadia_MILC_Environment*
Arcadia_MILC_Environment_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode
  );

#endif // ARCADIA_MILC_ENVIRONMENT_H_INCLUDED
