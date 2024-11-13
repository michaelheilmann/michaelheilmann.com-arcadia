#include "R/Machine/Code/Validator/Instruction.h"

#include "R/UnmanagedMemory.h"
#include "R/Status.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_Instruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_Instruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_Instruction_objectTypeOperations,
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

Rex_defineObjectType("Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, "R.Object", R_Object, &_Machine_Code_Validator_Instruction_typeOperations);

void
Machine_Code_Validator_Instruction_construct
  (
    Machine_Code_Validator_Instruction* self
  )
{
  R_Type* _type = _Machine_Code_Validator_Instruction_getType();
  R_Object_construct((R_Object*)self);
  R_Object_setType((R_Object*)self, _type);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_AddInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_AddInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_AddInstruction_objectTypeOperations,
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

Rex_defineObjectType("Machine.Code.Validator.AddInstruction", Machine_Code_Validator_AddInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_AddInstruction_typeOperations);

void
Machine_Code_Validator_AddInstruction_construct
  (
    Machine_Code_Validator_AddInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_AddInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_AddInstruction*
Machine_Code_Validator_AddInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_AddInstruction* self = R_allocateObject(_Machine_Code_Validator_AddInstruction_getType());
  Machine_Code_Validator_AddInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_AndInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_AndInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_AndInstruction_objectTypeOperations,
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

Rex_defineObjectType("Machine.Code.Validator.Andnstruction", Machine_Code_Validator_AndInstruction, "Machine.Code.Validtor.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_AndInstruction_typeOperations);

void
Machine_Code_Validator_AndInstruction_construct
  (
    Machine_Code_Validator_AndInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_AndInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_AndInstruction*
Machine_Code_Validator_AndInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_AndInstruction* self = R_allocateObject(_Machine_Code_Validator_AndInstruction_getType());
  Machine_Code_Validator_AndInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_ConcatenateInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_ConcatenateInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_ConcatenateInstruction_objectTypeOperations,
  .add = NULL,
  . and = NULL,
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
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("Machine.Code.Validator.ConcatenateInstruction", Machine_Code_Validator_ConcatenateInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_ConcatenateInstruction_typeOperations);

void
Machine_Code_Validator_ConcatenateInstruction_construct
  (
    Machine_Code_Validator_ConcatenateInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_ConcatenateInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_ConcatenateInstruction*
Machine_Code_Validator_ConcatenateInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_ConcatenateInstruction* self = R_allocateObject(_Machine_Code_Validator_ConcatenateInstruction_getType());
  Machine_Code_Validator_ConcatenateInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_DivideInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_DivideInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_DivideInstruction_objectTypeOperations,
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

Rex_defineObjectType("Machine.Code.Validator.DivideInstruction", Machine_Code_Validator_DivideInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_DivideInstruction_typeOperations);

void
Machine_Code_Validator_DivideInstruction_construct
  (
    Machine_Code_Validator_DivideInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_DivideInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_DivideInstruction*
Machine_Code_Validator_DivideInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_DivideInstruction* self = R_allocateObject(_Machine_Code_Validator_DivideInstruction_getType());
  Machine_Code_Validator_DivideInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_MultiplyInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_MultiplyInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_MultiplyInstruction_objectTypeOperations,
  .add = NULL,
  . and = NULL,
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
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("Machine.Code.Validator.MultiplyInstruction", Machine_Code_Validator_MultiplyInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_MultiplyInstruction_typeOperations);

void
Machine_Code_Validator_MultiplyInstruction_construct
  (
    Machine_Code_Validator_MultiplyInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_MultiplyInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_MultiplyInstruction*
Machine_Code_Validator_MultiplyInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_MultiplyInstruction* self = R_allocateObject(_Machine_Code_Validator_MultiplyInstruction_getType());
  Machine_Code_Validator_MultiplyInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_NegateInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_NegateInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_NegateInstruction_objectTypeOperations,
  .add = NULL,
  . and = NULL,
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
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("Machine.Code.Validator.NegateInstruction", Machine_Code_Validator_NegateInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_NegateInstruction_typeOperations);

void
Machine_Code_Validator_NegateInstruction_construct
  (
    Machine_Code_Validator_NegateInstruction* self,
    R_Natural32Value target,
    R_Natural32Value operand
  )
{
  R_Type* _type = _Machine_Code_Validator_NegateInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->operand = operand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_NegateInstruction*
Machine_Code_Validator_NegateInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value operand
  )
{
  Machine_Code_Validator_NegateInstruction* self = R_allocateObject(_Machine_Code_Validator_NegateInstruction_getType());
  Machine_Code_Validator_NegateInstruction_construct(self, target, operand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_NotInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_NotInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_NotInstruction_objectTypeOperations,
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

Rex_defineObjectType("Machine.Code.Validator.NotInstruction", Machine_Code_Validator_NotInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_NotInstruction_typeOperations);

void
Machine_Code_Validator_NotInstruction_construct
  (
    Machine_Code_Validator_NotInstruction* self,
    R_Natural32Value target,
    R_Natural32Value operand
  )
{
  R_Type* _type = _Machine_Code_Validator_NotInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->operand = operand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_NotInstruction*
Machine_Code_Validator_NotInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value operand
  )
{
  Machine_Code_Validator_NotInstruction* self = R_allocateObject(_Machine_Code_Validator_NotInstruction_getType());
  Machine_Code_Validator_NotInstruction_construct(self, target, operand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_OrInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_OrInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_OrInstruction_objectTypeOperations,
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

Rex_defineObjectType("Machine.Code.Validator.OrInstruction", Machine_Code_Validator_OrInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_OrInstruction_typeOperations);

void
Machine_Code_Validator_OrInstruction_construct
  (
    Machine_Code_Validator_OrInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_OrInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_OrInstruction*
Machine_Code_OrInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_OrInstruction* self = R_allocateObject(_Machine_Code_Validator_OrInstruction_getType());
  Machine_Code_Validator_OrInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const R_ObjectType_Operations _Machine_Code_Validator_SubtractInstruction_objectTypeOperations = {
  .constructor = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _Machine_Code_Validator_SubtractInstruction_typeOperations = {
  .objectTypeOperations = &_Machine_Code_Validator_SubtractInstruction_objectTypeOperations,
  .add = NULL,
  . and = NULL,
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
  . or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("Machine.Code.Validator.SubtractInstruction", Machine_Code_Validator_SubtractInstruction, "Machine.Code.Validator.Instruction", Machine_Code_Validator_Instruction, &_Machine_Code_Validator_SubtractInstruction_typeOperations);

void
Machine_Code_Validator_SubtractInstruction_construct
  (
    Machine_Code_Validator_SubtractInstruction* self,
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  R_Type* _type = _Machine_Code_Validator_SubtractInstruction_getType();
  Machine_Code_Validator_Instruction_construct((Machine_Code_Validator_Instruction*)self);
  self->target = target;
  self->firstOperand = firstOperand;
  self->secondOperand = secondOperand;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_SubtractInstruction*
Machine_Code_Validator_SubtractInstruction_create
  (
    R_Natural32Value target,
    R_Natural32Value firstOperand,
    R_Natural32Value secondOperand
  )
{
  Machine_Code_Validator_SubtractInstruction* self = R_allocateObject(_Machine_Code_Validator_SubtractInstruction_getType());
  Machine_Code_Validator_SubtractInstruction_construct(self, target, firstOperand, secondOperand);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
