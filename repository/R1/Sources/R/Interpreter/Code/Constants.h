// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

// Last modified: 2024-12-07

#if !defined(R_INTERPRETER_CODE_CONSTANTS_H_INCLUDED)
#define R_INTERPRETER_CODE_CONSTANTS_H_INCLUDED

#include "R/Boolean.h"
#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"
#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"
#include "R/Object.h"
#include "R/String.h"
#include "R/Size.h"

/**
 * @brief A set of constants.
 * @details 
 * Each array element contains a constant. A constant is one of the following values
 * - boolean values
 * - integer(8|16|32|64) values
 * - natural(8|16|32|64) values
 * - size values
 * - string values
 * - void values
 */
Rex_declareObjectType("R.Interpreter.Code.Constants", R_Interpreter_Code_Constants, R_Object);

typedef struct Constant Constant;

struct R_Interpreter_Code_Constants {
  R_Object _parent;
  /** @brief A pointer to an array of cp constants. The first sz R_Value object contain the values of constants, the remaining cp - sz R_Value objects contain void values. */
  R_Value* p;
  /** @brief The size of the constant array. */
  R_SizeValue sz;
  /** @brief The capacity of the constant array. */
  R_SizeValue cp;
};

R_Interpreter_Code_Constants*
R_Interpreter_Code_Constants_create
  (
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateBoolean
  (
    R_Interpreter_Code_Constants* self,
    R_BooleanValue booleanValue
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateForeignProcedure
  (
    R_Interpreter_Code_Constants* self,
    R_ForeignProcedureValue foreignProcedureValue
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger16
  (
    R_Interpreter_Code_Constants* self,
    R_Integer16Value integer16Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger32
  (
    R_Interpreter_Code_Constants* self,
    R_Integer32Value integer32Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger64
  (
    R_Interpreter_Code_Constants* self,
    R_Integer64Value integer64Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger8
  (
    R_Interpreter_Code_Constants* self,
    R_Integer8Value natural8Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural16
  (
    R_Interpreter_Code_Constants* self,
    R_Natural16Value natural16Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural32
  (
    R_Interpreter_Code_Constants* self,
    R_Natural32Value natural32Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural64
  (
    R_Interpreter_Code_Constants* self,
    R_Natural64Value natural64Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural8
  (
    R_Interpreter_Code_Constants* self,
    R_Natural8Value natural8Value
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateSize
  (
    R_Interpreter_Code_Constants* self,
    R_SizeValue sizeValue
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateString
  (
    R_Interpreter_Code_Constants* self,
    R_String* stringValue
  );

R_Natural32Value
R_Interpreter_Code_Constants_getOrCreateVoid
  (
    R_Interpreter_Code_Constants* self,
    R_VoidValue voidValue
  );

R_Value const*
R_Interpreter_Code_Constants_getAt
  (
    R_Interpreter_Code_Constants const* self,
    R_Natural32Value index
  );

#endif // R_INTERPRETER_CODE_CONSTANTS_H_INCLUDED
