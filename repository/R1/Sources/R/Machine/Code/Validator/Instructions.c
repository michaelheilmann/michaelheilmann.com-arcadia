#include "R/Machine/Code/Validator/Instructions.h"

#include "R/nextPowerOfTwoGt.h"
#include "R/isPowerOfTwo.h"
#include "R/JumpTarget.h"
#include "R/UnmanagedMemory.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Machine_Code_Validator_Instructions_destruct
  (
    Machine_Code_Validator_Instructions* self
  );

static void
Machine_Code_Validator_Instructions_visit
  (
    Machine_Code_Validator_Instructions* self
  );

static void
Machine_Code_Validator_Instructions_destruct
  (
    Machine_Code_Validator_Instructions* self
  )
{
  if (self->instructions) {
    R_deallocateUnmanaged_nojump(self->instructions);
    self->instructions = NULL;
  }
}

static void
Machine_Code_Validator_Instructions_visit
  (
    Machine_Code_Validator_Instructions* self
  )
{
  if (self->instructions) {
    for (R_SizeValue i = 0, n = self->numberOfInstructions; i < n; ++i) {
      R_Object_visit(self->instructions[i]);
    }
  }
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &Machine_Code_Validator_Instructions_destruct,
  .visit = &Machine_Code_Validator_Instructions_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("Machine.Code.Validator.Instructions", Machine_Code_Validator_Instructions, "R.Object", R_Object, &_typeOperations);

void
Machine_Code_Validator_Instructions_construct
  (
    Machine_Code_Validator_Instructions* self
  )
{
  R_Type* _type = _Machine_Code_Validator_Instructions_getType();
  R_Object_construct((R_Object*)self);
  self->numberOfInstructions = 0;
  self->instructions = NULL;
  if (!R_allocateUnmanaged_nojump((void**) & self->instructions, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_Instructions*
Machine_Code_Validator_Instructions_create
  (  
  )
{
  Machine_Code_Validator_Instructions* self = R_allocateObject(_Machine_Code_Validator_Instructions_getType());
  Machine_Code_Validator_Instructions_construct(self);
  return self;
}

void
Machine_Code_Validator_Instruction_append
  (
    Machine_Code_Validator_Instructions* self,
    Machine_Code_Validator_Instruction* instruction
  )
{
  if (R_isPowerOfTwoSizeValue(self->numberOfInstructions)) {
    static R_SizeValue const maximumNumberOfInstructions = 1 << 30;
    R_SizeValue newNumberOfInstructions = R_nextPowerOfTwoGtSizeValue(self->numberOfInstructions);
    if (!R_reallocateUnmanaged_nojump((void**)&self->instructions, newNumberOfInstructions * sizeof(Machine_Code_Validator_Instruction*))) {
      R_jump();
    }
  }
  self->instructions[self->numberOfInstructions++] = instruction;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
