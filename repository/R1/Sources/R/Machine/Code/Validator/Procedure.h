#if !defined(R_MACHINE_CODE_VALIDATOR_PROCEDURE_H_INCLUDED)
#define R_MACHINE_CODE_VALIDATOR_PROCEDURE_H_INCLUDED

#include "R/Object.h"
#include "R/TypeNames.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType("Machine.Code.Validator.Procedure", Machine_Code_Validator_Procedure, "R.Object");

struct Machine_Code_Validator_Procedure {
  R_Object _parent;
  R_TypeName* typeName;
};

/// @param name The fully-qualified name of the procedure e.g. "X.A.f".
void
Machine_Code_Validator_Procedure_construct
  (
    Machine_Code_Validator_Procedure* self,
    R_TypeName* typeName
  );

Machine_Code_Validator_Procedure*
Machine_Code_Validator_Procedure_create
  (
    R_TypeName* typeName
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MACHINE_CODE_VALIDATOR_PROCEDURE_H_INCLUDED
