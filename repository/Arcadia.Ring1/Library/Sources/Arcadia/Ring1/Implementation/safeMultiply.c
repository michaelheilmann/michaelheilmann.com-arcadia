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

// Last modified: 2025-01-26

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/safeMultiply.h"

void
Arcadia_safeMultiply_n16
  (
    Arcadia_Process1* process,
    Arcadia_Natural16Value multiplier,
    Arcadia_Natural16Value multiplicand,
    Arcadia_Natural16Value* productHigh,
    Arcadia_Natural16Value* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  Arcadia_Natural32Value a = multiplier;
  Arcadia_Natural32Value b = multiplicand;
  Arcadia_Natural32Value c = a * b;
  *productHigh = c >> 16;
  *productLow = (Arcadia_Natural16Value)(c & 0xffff);
}

void
Arcadia_safeMultiply_n32
  (
    Arcadia_Process1* process,
    Arcadia_Natural32Value multiplier,
    Arcadia_Natural32Value multiplicand,
    Arcadia_Natural32Value* productHigh,
    Arcadia_Natural32Value* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  Arcadia_Natural64Value a = multiplier;
  Arcadia_Natural64Value b = multiplicand;
  Arcadia_Natural64Value c = a * b;
  *productHigh = c >> 32;
  *productLow = (Arcadia_Natural32Value)(c & 0xffffffff);
}

#if Arcadia_Configuration_CompilerC_Msvc == Arcadia_Configuration_CompilerC && \
    Arcadia_Configuration_InstructionSetArchitecture_X64 == Arcadia_Configuration_InstructionSetArchitecture

#include <intrin.h>

void
Arcadia_safeMultiply_n64_x64msvc
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  unsigned long long productLow_;
  unsigned long long productHigh_;
  productLow_ = _umul128(multiplier, multiplicand, &productHigh_);
  *productHigh = productHigh_;
  *productLow = productLow_;
}
#endif

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC

void
Arcadia_safeMultiply_n64_gcc
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  unsigned __int128 product = (unsigned __int128)multiplier * (unsigned __int128)multiplicand;
  *productHigh = product >> 64;
  *productLow = (uint64_t)product;
}

#endif

// adapted from xmrig (https://github.com/xmrig/xmrig/blob/master/src/base/tools/cryptonote/umul128.h).
void
Arcadia_safeMultiply_n64_default
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  // multiplier   = ab = a * 2^32 + b
  // multiplicand = cd = c * 2^32 + d
  // ab * cd = a * c * 2^64 + (a * d + b * c) * 2^32 + b * d
  Arcadia_Natural64Value a = multiplier >> 32;
  Arcadia_Natural64Value b = multiplier & 0xffffffff;
  Arcadia_Natural64Value c = multiplicand >> 32;
  Arcadia_Natural64Value d = multiplicand & 0xffffffff;
  
  //uint64_t ac = a * c;
  Arcadia_Natural64Value ad = a * d; // cannot overflow as a,d,b,d are all smaller than or equal to 2^32-1.
                                     // Hence ad is in worst case (2^32-1)^2 = 2^64 - 2^33 + 1 << 2^64 - 1
  //uint64_t bc = b * c;
  Arcadia_Natural64Value bd = b * d; // see comment for ad
  
  Arcadia_Natural64Value adbc = ad + (b * c); // CAN overflow
  Arcadia_Natural64Value adbcCarry = adbc < ad ? 1 : 0;
    
  // multiplier * multiplicand = productHigh * 2^64 + productLow
  Arcadia_Natural64Value productLow_ = bd + (adbc << 32); // CAN overflow
  Arcadia_Natural64Value productLowCarry = productLow_ < bd ? 1 : 0;
  Arcadia_Natural64Value productHigh_ = (a * c) + (adbc >> 32) + (adbcCarry << 32) + productLowCarry;

  *productHigh = productHigh_;
  *productLow = productLow_;
}

void
Arcadia_safeMultiply_n64
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  )
{
#if Arcadia_Configuration_CompilerC_Msvc == Arcadia_Configuration_CompilerC && \
    Arcadia_Configuration_InstructionSetArchitecture_X64 == Arcadia_Configuration_InstructionSetArchitecture
  Arcadia_safeMultiply_n64_x64msvc(process, multiplier, multiplicand, productHigh,  productLow);
#elif Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
  Arcadia_safeMultiply_n64_gcc(process, multiplier, multiplicand, productHigh, productLow);
#else
  Arcadia_safeMultiply_n64_default(process, multiplier, multiplicand, productHigh, productLow);
#endif
}

void
Arcadia_safeMultiply_n8
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value multiplier,
    Arcadia_Natural8Value multiplicand,
    Arcadia_Natural8Value* productHigh,
    Arcadia_Natural8Value* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
  Arcadia_Natural16Value a = multiplier;
  Arcadia_Natural16Value b = multiplicand;
  Arcadia_Natural16Value c = a * b;
  *productHigh = c >> 8;
  *productLow = (Arcadia_Natural8Value)(c & 0xffff);
}

void
Arcadia_safeMultiply_sz
  (
    Arcadia_Process1* process,
    Arcadia_SizeValue multiplier,
    Arcadia_SizeValue multiplicand,
    Arcadia_SizeValue* productHigh,
    Arcadia_SizeValue* productLow
  )
{
  if (!productHigh | !productLow) {
    Arcadia_Process1_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process1_jump(process);
  }
#if Arcadia_Configuration_CompilerC_Msvc == Arcadia_Configuration_CompilerC
  #if Arcadia_Configuration_InstructionSetArchitecture_X64 == Arcadia_Configuration_InstructionSetArchitecture
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum == Arcadia_Natural64Value_Maximum && Arcadia_SizeValue_NumberOfBits == Arcadia_Natural64Value_NumberOfBits, "environment not (yet) supported");
    Arcadia_Natural64Value productLow_, productHigh_;
    Arcadia_safeMultiply_n64(process, multiplier, multiplicand, &productHigh_, &productLow_);
    *productHigh = productHigh_;
    *productLow = productLow_; 
  #elif Arcadia_Configuration_InstructionSetArchitecture_X86 == Arcadia_Configuration_InstructionSetArchitecture
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum == Arcadia_Natural32Value_Maximum && Arcadia_SizeValue_NumberOfBits == Arcadia_Natural32Value_NumberOfBits, "environment not (yet) supported");
    Arcadia_Natural32Value productLow_, productHigh_;
    Arcadia_safeMultiply_n32(process, multiplier, multiplicand, &productHigh_, &productLow_);
    *productHigh = productHigh_;
    *productLow = productLow_;
  #else
    #error ("environemnt not (yet) supported");
  #endif
#elif Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
  #if Arcadia_Configuration_InstructionSetArchitecture_X64 == Arcadia_Configuration_InstructionSetArchitecture_X64
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum == Arcadia_Natural64Value_Maximum && Arcadia_SizeValue_NumberOfBits == Arcadia_Natural64Value_NumberOfBits, "environment not (yet) supported");
    Arcadia_Natural64Value productLow_, productHigh_;
    Arcadia_safeMultiply_n64(process, multiplier, multiplicand, &productHigh_, &productLow_);
    *productHigh = productHigh_;
    *productLow = productLow_;
  #elif Arcadia_Configuration_InstructionSetArchitecture_X86 == Arcadia_Configuration_InstructionSetArchitecture
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum == Arcadia_Natural32Value_Maximum && Arcadia_SizeValue_NumberOfBits == Arcadia_Natural32Value_NumberOfBits, "environment not (yet) supported");
    Arcadia_Natural32Value productLow_, productHigh_;
    Arcadia_safeMultiply_n32(process, multiplier, multiplicand, &productHigh_, &productLow_);
    *productHigh = productHigh_;
    *productLow = productLow_;
  #else
    #error("environemnt not (yet) supported");
  #endif
#else
  #error ("environemnt not (yet) supported");
#endif
}
