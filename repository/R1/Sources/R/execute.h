#if !defined(R_EXECUTE_H_INCLUDED)
#define R_EXECUTE_H_INCLUDED

#include "R/Machine/Code/Include.h"

void
R_executeProcedure
  (
    R_Value const* constants,
    R_Procedure* procedure
  );

#endif // R_EXECUTE_H_INCLUDED
