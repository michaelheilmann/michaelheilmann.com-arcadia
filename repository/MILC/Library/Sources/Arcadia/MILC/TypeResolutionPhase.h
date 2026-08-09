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

#if !defined(ARCADIA_MILC_TYPERESOLUTIONPHASE_H_INCLUDED)
#define ARCADIA_MILC_TYPERESOLUTIONPHASE_H_INCLUDED

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/AST/Include.h"
#include "Arcadia/MILC/Symbols/ModuleSymbol.h"
#include "Arcadia/MILC/Completer.h"
typedef struct Arcadia_MILC_VariableSymbol Arcadia_MILC_VariableSymbol;

/// @brief The type resolution phase.
/// @warning The context object passed to the compilation task object is modified by each invocation of Arcadia.MILC.TypeResolutionPhase.run.
/// @remarks
/// - for enumeration constant symbols determine the type of their initializer.
///   LANGUAGE DEFINITION: The initializer of an enumeration constant, if present, must be an integer literal.
///   An integer literal is a non-empty sequence of decimal digits. Its type is the first of
///   Arcadia.Natural8, Arcadia.Natural16, Arcadia.Natural32, and Arcadia.Natural64 which is able to represent its value.
Arcadia_declareObjectType(u8"Arcadia.MILC.TypeResolutionPhase", Arcadia_MILC_TypeResolutionPhase,
                          u8"Arcadia.Object");

struct Arcadia_MILC_TypeResolutionPhaseDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_TypeResolutionPhase {
  Arcadia_Object _parent;
  /// @brief The context.
  Arcadia_MILC_Context* context;
  //
  Arcadia_MILC_Completer* classCompleter;
  Arcadia_MILC_Completer* constructorCompleter;
  Arcadia_MILC_Completer* enumerationCompleter;
  Arcadia_MILC_Completer* methodCompleter;
  Arcadia_MILC_Completer* procedureCompleter;
};

Arcadia_MILC_TypeResolutionPhase*
Arcadia_MILC_TypeResolutionPhase_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

Arcadia_MILC_TypeResolutionPhase*
Arcadia_MILC_TypeResolutionPhase_getInstance
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

void
Arcadia_MILC_TypeResolutionPhase_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase* self
  );

void
Arcadia_MILC_TypeResolutionPhase_resolveParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase* self,
    Arcadia_MILC_VariableSymbol* variableSymbol
  );

void
Arcadia_MILC_TypeResolutionPhase_resolveReturnValue
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase* self
  );

#endif // ARCADIA_MILC_TYPERESOLUTIONPHASE_H_INCLUDED
