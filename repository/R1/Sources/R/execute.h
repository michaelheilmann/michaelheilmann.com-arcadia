#if !defined(R_EXECUTE_H_INCLUDED)
#define R_EXECUTE_H_INCLUDED

#include "R/Interpreter/Include.h"

void
R_executeProcedure
  (
    R_Interpreter_ProcessState* process,
    R_Procedure* procedure
  );

#endif // R_EXECUTE_H_INCLUDED
