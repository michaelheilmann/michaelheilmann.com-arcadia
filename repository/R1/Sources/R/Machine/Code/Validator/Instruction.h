#if !defined(R_MACHINE_CODE_INSTRUCTION_H_INCLUDED)
#define R_MACHINE_CODE_INSTRUCTION_H_INCLUDED

#include "R/Object.h"
#include "R/Natural32.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, "R.Object");

struct Machine_Code_Validator_Instruction {
  R_Object parent;
};

void
Machine_Code_Validator_Instruction_construct
  (
    Machine_Code_Validator_Instruction* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.AddInstructions", Machine_Code_Validator_AddInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_AddInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct an "add" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_AddInstruction_construct
  (
    Machine_Code_Validator_AddInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_AddInstruction*
Machine_Code_Validator_AddInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.AndInstructions", Machine_Code_Validator_AndInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_AndInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct an "and" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_AndInstruction_construct
  (
    Machine_Code_Validator_AndInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_AndInstruction*
Machine_Code_Validator_AndInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.ConcatenateInstructions", Machine_Code_Validator_ConcatenateInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_ConcatenateInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct a "concatenate" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_ConcatenateInstruction_construct
  (
    Machine_Code_Validator_ConcatenateInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_ConcatenateInstruction*
Machine_Code_Validator_ConcatenateInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.DivideInstruction", Machine_Code_Validator_DivideInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_DivideInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct a "divide" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_DivideInstruction_construct
  (
    Machine_Code_Validator_DivideInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_DivideInstruction*
Machine_Code_Validator_DivideInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.MultiplyInstructions", Machine_Code_Validator_MultiplyInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_MultiplyInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct a "multiply" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_MultiplyInstruction_construct
  (
    Machine_Code_Validator_MultiplyInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_MultiplyInstruction*
Machine_Code_Validator_MultiplyInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.NegateInstructions", Machine_Code_Validator_NegateInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_NegateInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value operand;
};

/// @brief Construct a "negate" instruction object.
/// @param target The target register.
/// @param operand The operand register.
void
Machine_Code_Validator_NegateInstruction_construct
  (
    Machine_Code_Validator_NegateInstruction* self,
    R_Natural32Value target,
    R_Natural32Value operand
  );

Machine_Code_Validator_NegateInstruction*
Machine_Code_Validator_NegateInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.NotInstructions", Machine_Code_Validator_NotInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_NotInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value operand;
};

/// @brief Construct a "not" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_NotInstruction_construct
  (
    Machine_Code_Validator_NotInstruction* self,
    R_Natural32Value target,
    R_Natural32Value operand
  );

Machine_Code_Validator_NotInstruction*
Machine_Code_Validator_NotInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value operand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.OrInstructions", Machine_Code_Validator_OrInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_OrInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct a "or" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_OrInstruction_construct
  (
    Machine_Code_Validator_OrInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_OrInstruction*
Machine_Code_Validator_OrInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.SubtractInstructions", Machine_Code_Validator_SubtractInstruction, "Machine.Code.Validator.Instruction");

struct Machine_Code_Validator_SubtractInstruction {
  Machine_Code_Validator_Instruction _parent;
  R_Natural32Value target;
  R_Natural32Value firstOperand;
  R_Natural32Value secondOperand;
};

/// @brief Construct a "subtract" instruction object.
/// @param target The target register.
/// @param firstOperand The first operand register.
/// @param secondOperand The second operand register.
void
Machine_Code_Validator_SubtractInstruction_construct
  (
    Machine_Code_Validator_SubtractInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

Machine_Code_Validator_SubtractInstruction*
Machine_Code_Validator_SubtractInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MACHINE_CODE_INSTRUCTION_H_INCLUDED
