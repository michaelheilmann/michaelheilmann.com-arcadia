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

#if !defined(ARCADIA_MIL_FRONTEND_SEMANTICALANALYSIS_ENTERPASS_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_SEMANTICALANALYSIS_ENTERPASS_H_INCLUDED

#include "Arcadia/Include.h"
#include "Arcadia/MIL/Frontend/Tests/SemanticalAnalysis/Pass.h"
#include "Arcadia/MIL/Frontend/Include.h"
typedef struct Arcadia_MIL_CallableContext Arcadia_MIL_CallableContext;

void
Arcadia_MIL_SemanticalAnalysis_EnterPass_onModule
  (
    Arcadia_Thread* thread,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_MIL_AST_ModuleNode* moduleAst
  );

/// The first pass (enter pass) of the compiler.
/// Guarantees:
/// - no class-class, prodecure-procedure, class-procedure name collision
/// - no label name collision
Arcadia_declareObjectType(u8"Arcadia.MIL.SemanticalAnalysis.EnterPass", Arcadia_MIL_SemanticalAnalysis_EnterPass,
                          u8"Arcadia.MIL.Pass");

struct Arcadia_MIL_SemanticalAnalysis_EnterPassDispatch {
  Arcadia_MIL_PassDispatch _parent;
};

struct Arcadia_MIL_SemanticalAnalysis_EnterPass {
  Arcadia_MIL_Pass _parent;
};

Arcadia_MIL_SemanticalAnalysis_EnterPass*
Arcadia_MIL_SemanticalAnalysis_EnterPass_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MIL_FRONTEND_SEMANTICALANALYSIS_ENTERPASS_H_INCLUDED
