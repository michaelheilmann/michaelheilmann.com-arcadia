#if !defined(R_EXECUTE_H_INCLUDED)
#define R_EXECUTE_H_INCLUDED

#include "R/Interpreter/Include.h"

void
R_executeProcedure
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    R_Interpreter_Procedure* procedure
  );

#endif // R_EXECUTE_H_INCLUDED
