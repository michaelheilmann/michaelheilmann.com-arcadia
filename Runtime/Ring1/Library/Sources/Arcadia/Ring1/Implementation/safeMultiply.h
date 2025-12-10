// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_SAFEMULTIPLY_H_INCLUDED)
#define ARCADIA_RING1_SAFEMULTIPLY_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/Size.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Perform a safe multiplication of two Arcadia_Natural(16|32|64|8)Value values.
/// @param multiplier The multiplier.
/// @param multiplicand The multiplicand.
/// @param [out] productHigh A pointer to an Arcadia_Natural(16|32|64|8)Value variable.
/// @param [out] productLow A pointer to an Arcadia_Natural(16|32|64|8)Value variable.
/// @return
/// #Arcadia_BooleanValue_True if the result fits into *productLow.
/// #Arcadia_BooleanValue_False otherwise.
/// @post
/// If the mathemamtical product can be represented by Arcadia_Natural(16|32|64|8)Value then its bits are stored in *productLow, *productHigh is set to zero, and #Arcadia_BooleanValue_True is returned.
/// Otherwise the upper bits of the mathematical product are stored in *productHigh, its lower bits in *productLow, and #Arcadia_BooleanValue_False is returned.
Arcadia_BooleanValue
Arcadia_safeMultiplyNatural16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value multiplier,
    Arcadia_Natural16Value multiplicand,
    Arcadia_Natural16Value* productHigh,
    Arcadia_Natural16Value* productLow
  );

Arcadia_BooleanValue
Arcadia_safeMultiplyNatural32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value multiplier,
    Arcadia_Natural32Value multiplicand,
    Arcadia_Natural32Value* productHigh,
    Arcadia_Natural32Value* productLow
  );

Arcadia_BooleanValue
Arcadia_safeMultiplyNatural64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  );

Arcadia_BooleanValue
Arcadia_safeMultiplyNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value multiplier,
    Arcadia_Natural8Value multiplicand,
    Arcadia_Natural8Value* productHigh,
    Arcadia_Natural8Value* productLow
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_BooleanValue
Arcadia_safeMultiplySizeValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue multiplier,
    Arcadia_SizeValue multiplicand,
    Arcadia_SizeValue* productHigh,
    Arcadia_SizeValue* productLow
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Perform a safe multiplication of two Arcadia_Integer(8|16|32|64)Value values.
/// @param multiplier The multiplier.
/// @param multiplicand The multiplicand.
/// @param [out] productHigh A pointer to an Arcadia_Integer(8|16|32|64)Value variable.
/// @param [out] productLow A pointer to an Arcadia_Integer(8|16|32|64)Value variable.
/// @return
/// #Arcadia_BooleanValue_True if the result fits into *product.
/// #Arcadia_BooleanValue_False otherwise.
/// @post
/// If the mathemamtical product can be represented by Arcadia_Integer(8|16|32|64)Value then its bits are stored in *productLow, *productHigh is set to zero, and #Arcadia_BooleanValue_True is returned.
/// Otherwise the upper bits of the mathematical product are stored in *productHigh, its lower bits in *productLow, and #Arcadia_BooleanValue_False is returned.
/// @remarks
/// Wrapped around means:
/// If an integer multiplication overflows, then the result is the low-order bits of the mathematical product as represented in some sufficiently large two's-complement format.
/// As a result, if overflow occurs, then the sign of the result may not be the same as the sign of the mathematical product of the two operand values.
Arcadia_BooleanValue
Arcadia_safeMultiplyInteger16Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value multiplier,
    Arcadia_Integer16Value multiplicand,
    Arcadia_Integer16Value* upperProduct,
    Arcadia_Integer16Value* lowerProduct
  );

Arcadia_BooleanValue
Arcadia_safeMultiplyInteger32Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value multiplier,
    Arcadia_Integer32Value multiplicand,
    Arcadia_Integer32Value* upperProduct,
    Arcadia_Integer32Value* lowerProduct
  );

Arcadia_BooleanValue
Arcadia_safeMultiplyInteger64Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value multiplier,
    Arcadia_Integer64Value multiplicand,
    Arcadia_Integer64Value* upperProduct,
    Arcadia_Integer64Value* lowerProduct
  );

Arcadia_BooleanValue
Arcadia_safeMultiplyInteger8Value
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value multiplier,
    Arcadia_Integer8Value multiplicand,
    Arcadia_Integer8Value* upperProduct,
    Arcadia_Integer8Value* lowerProduct
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // ARCADIA_RING1_SAFEMULTIPLY_H_INCLUDED
