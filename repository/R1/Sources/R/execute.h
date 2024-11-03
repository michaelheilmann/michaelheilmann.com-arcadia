#if !defined(R_EXECUTE_H_INCLUDED)
#define R_EXECUTE_H_INCLUDED

#include "R/Machine/Code/Include.h"

void
R_execute
  (
    R_Value const* constants,
    R_Value* registers,
    void const* instructions,
    R_SizeValue numberOfInstructions
  );

#endif // R_CI_H_INCLUDED