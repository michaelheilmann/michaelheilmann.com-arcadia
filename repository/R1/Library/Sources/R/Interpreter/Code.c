// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R/Interpreter/Code.h"

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"

static Arcadia_Value*
R_InterpreterState_decodeTarget
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(process, code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Register != indexKind) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  return R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
}

static Arcadia_Value const*
R_InterpreterState_decodeOperand
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(process, code, &call->instructionIndex, &indexKind, &indexValue);
  Arcadia_Value const* value = indexKind == R_Machine_Code_IndexKind_Constant ?
                         R_Interpreter_Code_Constants_getAt(process, constants, indexValue) : R_Interpreter_ThreadState_getRegisterAt(thread, indexValue);
  return value;
}

static Arcadia_String*
R_InterpreterState_decodeStringConstant
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_Code_Constants* constants = R_Interpreter_ProcessState_getConstants(interpreterProcess);
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  R_Machine_Code_IndexKind indexKind;
  Arcadia_Natural32Value indexValue;
  R_Interpreter_Code_decodeIndex(process, code, &call->instructionIndex, &indexKind, &indexValue);
  if (R_Machine_Code_IndexKind_Constant != indexKind) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, R_Interpreter_Code_Constants_getAt(process, constants, indexValue)), _Arcadia_String_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_SemanticalError);
    Arcadia_Process_jump(process);
  }
  return (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(R_Interpreter_Code_Constants_getAt(process, constants, indexValue));
}

static Arcadia_Natural32Value
R_InterpreterState_decodeCount
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess
  )
{
  R_Interpreter_ThreadState* thread = R_Interpreter_ProcessState_getCurrentThread(interpreterProcess);
  R_CallState* call = R_Interpreter_ThreadState_getCurrentCall(thread);
  R_Interpreter_Code* code = call->procedure->code;

  Arcadia_Natural32Value countValue;
  R_Interpreter_Code_decodeCount(process, code, &call->instructionIndex, &countValue);
  return countValue;
}

static void
R_Interpreter_Code_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Interpreter_Code_destruct
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Code_constructImpl,
  .destruct = &R_Interpreter_Code_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"R.Interpreter.Code", R_Interpreter_Code, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Interpreter_Code_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Interpreter_Code* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Code_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  Arcadia_Process_allocateUnmanaged(process, &_self->p, 0);
  Arcadia_Object_setType(process, _self, _type);
}

static void
R_Interpreter_Code_destruct
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self
  )
{
  if (self->p) {
    Arcadia_Process_deallocateUnmanaged(process, self->p);
    self->p = NULL;
  }
}

R_Interpreter_Code*
R_Interpreter_Code_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Interpreter_Code* self = R_allocateObject(process, _R_Interpreter_Code_getType(process), 0, &argumentValues[0]);
  return self;
}

void
R_Interpreter_Code_append
  (
    R_Interpreter_Code* self,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  R_DynamicArrayUtilities_ensureFreeCapacity(&self->p, sizeof(Arcadia_Natural8Value), self->sz, &self->cp, numberOfBytes, R_DynamicArrayUtilities_GrowthStrategy4);
  c_memcpy(self->p + self->sz, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

void
R_Interpreter_Code_appendIndexNatural8
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self,
    R_Machine_Code_IndexKind indexKind,
    Arcadia_Natural8Value indexValue
  )
{
  R_Interpreter_Code_appendIndexNatural32(process, self, indexKind, indexValue);
}

void
R_Interpreter_Code_appendIndexNatural16
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self,
    R_Machine_Code_IndexKind indexKind,
    Arcadia_Natural16Value indexValue
  )
{
  R_Interpreter_Code_appendIndexNatural32(process, self, indexKind, indexValue);
}

void
R_Interpreter_Code_appendIndexNatural32
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self,
    R_Machine_Code_IndexKind indexKind,
    Arcadia_Natural16Value index
  )
{
  Arcadia_Natural8Value a = 0;
  switch (indexKind) {
    case R_Machine_Code_IndexKind_Constant: {
      a |= R_Machine_Code_ConstantIndexFlag;
    } break;
    case R_Machine_Code_IndexKind_Register: {
      a |= R_Machine_Code_RegisterIndexFlag;
    } break;
    case R_Machine_Code_IndexKind_Invalid: {
      a |= R_Machine_Code_InvalidIndexFlag;
    } break;
    case R_Machine_Code_IndexKind_Reserved: {
      a |= R_Machine_Code_ReservedIndexFlag;
    } break;
    default: {
      // Cannot be encoded.
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  };
  if (index <= 31) {
    // We must encode 5 Bits in one Byte.
    // The Byte stores 5 Bits.
    uint8_t x = (index & 0b000011111);
    x |= a;
    R_Interpreter_Code_append(self, &x, 1);
  } else if (index <= 511) {
    // We must encode 9 Bits in two Bytes.
    // The first Byte stores 3 Bits, the 2nd Byte stores 6 Bits.
    uint8_t x = (index & 0b111000000) >> 6;
    x |= a;
    x |= 0b00110000;
    uint8_t y = (index & 0b000111111) >> 0;
    y |= 128/*0b10000000*/;
    R_Interpreter_Code_append(self, &x, 1);
    R_Interpreter_Code_append(self, &y, 1);
  } else if (index <= 16383) {
    // We must encode 14 Bits in three Bytes.
    // The first Byte uses 2 Bits, the 2nd to the 3rd Byte each use 6 Bits.
    uint8_t x = (index & 0b11000000000000) >> 12;
    x |= a;
    x |= 0b00111000;
    uint8_t y = (index & 0b00111111000000) >> 6;
    y |= 128;
    uint8_t z = (index & 0b00000000111111) >> 0;
    z |= 128;
    R_Interpreter_Code_append(self, &x, 1);
    R_Interpreter_Code_append(self, &y, 1);
    R_Interpreter_Code_append(self, &z, 1);
  } else if (index <= 524287) {
    // We must encode 19 Bits in four Bytes.
    // The first Byte uses 1 Byte, the 2nd to the 4th Byte each use 6 Bits.
    uint8_t x = (index & 0b1000000000000000000) >> 18;
    x |= a;
    x |= 0b00111100;
    uint8_t y = (index & 0b0111111000000000000) >> 12;
    y |= 128;
    uint8_t z = (index & 0b0000000111111000000) >> 6;
    z |= 128;
    uint8_t w = (index & 0b0000000000000111111) >> 0;
    w |= 128;
    R_Interpreter_Code_append(self, &x, 1);
    R_Interpreter_Code_append(self, &y, 1);
    R_Interpreter_Code_append(self, &z, 1);
    R_Interpreter_Code_append(self, &w, 1);
  } else {
    // Cannot be encoded.
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
}

void
R_Interpreter_Code_appendCountNatural8
  (
    R_Interpreter_Code* self,
    Arcadia_Natural8Value countValue
  )
{
  R_Interpreter_Code_appendCountNatural32(self, countValue);
}

void
R_Interpreter_Code_appendCountNatural16
  (
    R_Interpreter_Code* self,
    Arcadia_Natural16Value countValue
  )
{
  R_Interpreter_Code_appendCountNatural32(self, countValue);
}

void
R_Interpreter_Code_appendCountNatural32
  (
    R_Interpreter_Code* self,
    Arcadia_Natural32Value countValue
  )
{
  R_Interpreter_Code_append(self, (Arcadia_Natural8Value const*)&countValue, sizeof(Arcadia_Natural32Value));
}

void
R_Interpreter_Code_decodeCount
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self,
    Arcadia_Natural32Value* current,
    Arcadia_Natural32Value* countValue
  )
{
  uint8_t* p = self->p + *current;
  if (self->sz - *current < 4) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  *countValue = 0;

  *countValue = *p;
  p++;
  *countValue |= ((Arcadia_Natural32Value)(*p)) << 8;
  p++;
  *countValue |= ((Arcadia_Natural32Value)(*p)) << 16;
  p++;
  *countValue |= ((Arcadia_Natural32Value)(*p)) << 24;
  p++;
  (*current) += 4;
}

void
R_Interpreter_Code_decodeIndex
  (
    Arcadia_Process* process,
    R_Interpreter_Code* self,
    Arcadia_Natural32Value* current,
    R_Machine_Code_IndexKind* indexKind,
    Arcadia_Natural32Value* indexValue
  )
{
  uint8_t* oldp = self->p + *current;
  uint8_t* p = self->p + *current;
  switch ((*p) & 0b11000000) {
    case R_Machine_Code_ConstantIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Constant;
    } break;
    case R_Machine_Code_InvalidIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Invalid;
    } break;
    case R_Machine_Code_RegisterIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Register;
    } break;
    case R_Machine_Code_ReservedIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Reserved;
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  };
  uint8_t a = (*p) & (~0b11000000);
  if ((a & 0x20/*0b00100000*/) == 0x00/*0b00000000*/) {
    // 5 bits in total, fit into an uint8_t.
    uint8_t x0 = a & ~0x20;
    p++;
    uint32_t v = x0;
    *indexValue = v;
  } else if ((a & 0x38/*0b00111000*/) == 0x30/*0b00110000*/) {
    uint8_t x0 = a & ~0x38;
    p++;
    uint8_t x1 = (*p) & ~0xC0;
    p++;
    uint32_t v = x0 << 6
               | x1 << 0
               ;
    *indexValue = v;
  } else if ((a & 0x3C/*0b00111100*/) == 0x38/*0b00111000*/) {
    uint8_t x0 = a & ~0x3C;
    p++;
    uint8_t x1 = (*p) & ~0xC0;
    p++;
    uint8_t x2 = (*p) & ~0xC0;
    p++;
    uint32_t v = x0 << 12
               | x1 << 6
               | x2 << 0;
    *indexValue = v;
  } else if ((a & 0x3E/*0b00111110*/) == 0x3C/*00111100*/) {
    uint8_t x0 = a & ~0x3E;
    p++;
    uint8_t x1 = (*p) & ~0xC0;
    p++;
    uint8_t x2 = (*p) & ~0xC0;
    p++;
    uint8_t x3 = (*p) & ~0xC0;
    p++;
    uint32_t v = x0 << 18
               | x1 << 12
               | x2 << 6
               | x3 << 0;
    *indexValue = v;
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  (*current) += p - oldp;
}
