#if !defined(ARCADIA_VPL_SEMANTICALANALYSIS_H_INCLUDED)
#define ARCADIA_VPL_SEMANTICALANALYSIS_H_INCLUDED

#include "Arcadia/Languages/Include.h"
typedef struct Arcadia_VPL_BuiltinType Arcadia_VPL_BuiltinType;
typedef struct Arcadia_VPL_Program Arcadia_VPL_Program;

Arcadia_declareObjectType(u8"Arcadia.VPL.SemanticalAnalysis", Arcadia_VPL_SemanticalAnalysis,
                          Arcadia_Object);

struct Arcadia_VPL_SemanticalAnalysisDispatch {
  Arcadia_ObjectDispatch _parent;
};  
                         
struct Arcadia_VPL_SemanticalAnalysis {
  Arcadia_Object _parent;
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
    Arcadia_VPL_Program* program
  );

#endif // ARCADIA_VPL_SEMANTICALANALYSIS_H_INCLUDED
