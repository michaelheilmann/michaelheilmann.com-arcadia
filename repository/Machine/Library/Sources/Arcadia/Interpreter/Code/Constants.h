// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(R_INTERPRETER_CODE_CONSTANTS_H_INCLUDED)
#define R_INTERPRETER_CODE_CONSTANTS_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

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
Arcadia_declareObjectType(u8"R.Interpreter.Code.Constants", R_Interpreter_Code_Constants, u8"Arcadia.Object");

typedef struct Constant Constant;

struct R_Interpreter_Code_Constants {
  Arcadia_Object _parent;
  /** @brief A pointer to an array of cp constants. The first sz Arcadia_Value object contain the values of constants, the remaining cp - sz Arcadia_Value objects contain void values. */
  Arcadia_Value* p;
  /** @brief The size of the constant array. */
  Arcadia_SizeValue sz;
  /** @brief The capacity of the constant array. */
  Arcadia_SizeValue cp;
};

R_Interpreter_Code_Constants*
R_Interpreter_Code_Constants_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateBoolean
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_BooleanValue booleanValue
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateForeignProcedure
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_ForeignProcedureValue foreignProcedureValue
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer16Value integer16Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer32Value integer32Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger64
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer64Value integer64Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer8Value natural8Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural16Value natural16Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural32Value natural32Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural64
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural64Value natural64Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural8Value natural8Value
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateSize
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_SizeValue sizeValue
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateString
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_String* stringValue
  );

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateVoid
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_VoidValue voidValue
  );

Arcadia_Value const*
R_Interpreter_Code_Constants_getAt
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants const* self,
    Arcadia_Natural32Value index
  );

#endif // R_INTERPRETER_CODE_CONSTANTS_H_INCLUDED
