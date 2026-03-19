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

#if !defined(ARCADIA_VPL_SEMANTICALANALYSIS_H_INCLUDED)
#define ARCADIA_VPL_SEMANTICALANALYSIS_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/Symbols/Include.h"

Arcadia_declareObjectType(u8"Arcadia.VPL.SemanticalAnalysis", Arcadia_VPL_SemanticalAnalysis,
                          Arcadia_Object);

struct Arcadia_VPL_SemanticalAnalysisDispatch {
  Arcadia_ObjectDispatch _parent;
};  
                         
struct Arcadia_VPL_SemanticalAnalysis {
  Arcadia_Object _parent;
  // Constant records and procedures are added to a work list.
  // They are taken out of the queue for processing.
  Arcadia_Deque* worklist;
};
      
Arcadia_VPL_SemanticalAnalysis*
Arcadia_VPL_SemanticalAnalysis_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_VPL_SemanticalAnalysis_run
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Symbols_Program* program
  );

// - create scope of the program
// - populate that scope with default symbols (e.g., the built-in types)
// - for each constant record defn:
//   - create constant record symbol
//   - create scope of constant record symbol
//   - add constant record symbol to scope of program
//   - for each variable defn of the constant record symbol / constant record defn:
//    - create variable symbol
//    - add variable symbol to scope of constant record symbol
void
Arcadia_VPL_SemanticalAnalysis_step1
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Symbols_Program* program
  );

/// Used in "enter" phase.
/// Create the procedure symbol for a procedure definition node.
Arcadia_VPL_Symbols_Procedure*
EnterPhase_enterProcedure
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* programSymbol,
    Arcadia_VPL_Tree_ProcedureDefnNode* node
  );

#endif // ARCADIA_VPL_SEMANTICALANALYSIS_H_INCLUDED
