#include "R/Machine/Code/Validator/Procedure.h"

#include "R/UnmanagedMemory.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Machine_Code_Validator_Procedure_destruct
  (
    Machine_Code_Validator_Procedure* self
  );

static void
Machine_Code_Validator_Procedure_destruct
  (
    Machine_Code_Validator_Procedure* self
  )
{ 
  R_TypeName_visit(self->typeName);
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &Machine_Code_Validator_Procedure_destruct,
  .visit = NULL,
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

Rex_defineObjectType("Machine.Code.Validator.Procedure", Machine_Code_Validator_Procedure, "R.Object", R_Object, &_typeOperations);

void
Machine_Code_Validator_Procedure_construct
  (
    Machine_Code_Validator_Procedure* self,
    R_TypeName* typeName
  )
{
  R_Type* _type = _Machine_Code_Validator_Procedure_getType();
  R_Object_construct((R_Object*)self);
  self->typeName = typeName;
  R_Object_setType((R_Object*)self, _type);
}

Machine_Code_Validator_Procedure*
Machine_Code_Validator_Procedure_create
  (
    R_TypeName* typeName
  )
{
  Machine_Code_Validator_Procedure* self = R_allocateObject(_Machine_Code_Validator_Procedure_getType());
  Machine_Code_Validator_Procedure_construct(self, typeName);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
