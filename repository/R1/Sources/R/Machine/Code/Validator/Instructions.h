#if !defined(R_MACHINE_CODE_VALIDATOR_INSTRUCTIONS_H_INCLUDED)
#define R_MACHINE_CODE_VALIDATOR_INSTRUCTIONS_H_INCLUDED

#include "R/Object.h"
#include "R/Natural32.h"
typedef struct Machine_Code_Validator_Instruction Machine_Code_Validator_Instruction;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.Instructions", Machine_Code_Validator_Instructions, "R.Object");

struct Machine_Code_Validator_Instructions {
  R_Object _parent;
  // If this is a power of two (0,1,2,4,...) then we need to reallocate to the next power of two.
  R_SizeValue numberOfInstructions;
  Machine_Code_Validator_Instruction** instructions;
};

void
Machine_Code_Validator_Instructions_construct
  (
    Machine_Code_Validator_Instructions* self
  );

Machine_Code_Validator_Instructions*
Machine_Code_Validator_Instructions_create
  (
  );

/// @brief Append an instruction to this instruction list.
/// @param self This instruction list.
/// @param instruction The instruction.
void
Machine_Code_Validator_Instruction_append
  (
    Machine_Code_Validator_Instructions* self,
    Machine_Code_Validator_Instruction* instruction
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MACHINE_CODE_VALIDATOR_INSTRUCTIONS_H_INCLUDED
