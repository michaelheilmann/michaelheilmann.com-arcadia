#if !defined(R_BIGINTEGER_H_INCLUDED)
#define R_BIGINTEGER_H_INCLUDED

#include "R/Object.h"
#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#define R_Configuration_BigInteger_DigitType_Natural16 (1)
#define R_Configuration_BigInteger_DigitType_Natural32 (2)
#define R_Configuration_BigInteger_DigitType_Natural64 (3)
#define R_Configuration_BigInteger_DigitType_Natural8 (4)

#define R_Configuration_BigInteger_DigitType R_Configuration_BigInteger_DigitType_Natural8

#if R_Configuration_BigInteger_DigitType_Natural16 == R_Configuration_BigInteger_DigitType
  // Unsigned integer representing a single base Arcadia_Natural32Value_Maximum + 1 digit.
  // The base is Arcadia_Natural16Value_Maximum + 1 itself is not representable by the digit type.
  typedef Arcadia_Natural16Value R_BigInteger_Digit;
  // The number of bits of the digit type.
  #define R_BigInteger_Digit_NumberOfBits (16)
  // The maximal value of the digit type.
  #define R_BigInteger_Digit_Maximum Arcadia_Natural16Value_Maximum
  #define R_BigInteger_Digit_Literal(x) Arcadia_Natural16Value_Literal(x)
  typedef Arcadia_Natural32Value R_BigInteger_DoubleDigit;
  #define R_BigInteger_DoubleDigit_UpperBitsMask 0xffff0000
  #define R_BigInteger_DoubleDigit_LowerBitsMask 0x0000ffff
  #define R_BigInteger_DoubleDigit_UpperBitsShift 16
  #define R_BigInteger_DoubleDigit_LowerBitsShift 0
#elif R_Configuration_BigInteger_DigitType_Natural32 == R_Configuration_BigInteger_DigitType
  // Unsigned integer representing a single base Arcadia_Natural32Value_Maximum + 1 digit.
  // Digits range from 0 to Arcadia_Natural32Value_Maximum. The base is Arcadia_Natural32Value_Maximum + 1 itself is not representable by the digit type.
  typedef Arcadia_Natural32Value R_BigInteger_Digit;
  // The number of bits of the digit type.
  #define R_BigInteger_Digit_NumberOfBits (32)
  // The maximal value of the digit type.
  #define R_BigInteger_Digit_Maximum Arcadia_Natural32Value_Maximum
  #define R_BigInteger_Digit_Literal(x) Arcadia_Natural32Value_Literal(x)
  typedef Arcadia_Natural64Value R_BigInteger_DoubleDigit;
  #define R_BigInteger_DoubleDigit_UpperBitsMask 0xffffffff00000000
  #define R_BigInteger_DoubleDigit_LowerBitsMask 0x00000000ffffffff
  #define R_BigInteger_DoubleDigit_UpperBitsShift 16
  #define R_BigInteger_DoubleDigit_LowerBitsShift 0
#elif R_Configuration_BigInteger_DigitType_Natural64 == R_Configuration_BigInteger_DigitType
  #error("environment not (yet) supported")
#elif R_Configuration_BigInteger_DigitType_Natural8 == R_Configuration_BigInteger_DigitType
  // Unsigned integer representing a single base Arcadia_Natural8Value_Maximum + 1 digit.
  // Digits range from 0 to Arcadia_Natural8Value_Maximum. The base is Arcadia_Natural8Value_Maximum + 1 itself is not representable by the digit type.
  typedef Arcadia_Natural8Value R_BigInteger_Digit;
  // The number of bits of the digit type.
  #define R_BigInteger_Digit_NumberOfBits (8)
  // The maximal value of the digit type.
  #define R_BigInteger_Digit_Maximum Arcadia_Natural8Value_Maximum
  #define R_BigInteger_Digit_Literal(x) Arcadia_Natural8Value_Literal(x)  
  typedef Arcadia_Natural16Value R_BigInteger_DoubleDigit;
  #define R_BigInteger_DoubleDigit_UpperBitsMask 0xff00
  #define R_BigInteger_DoubleDigit_LowerBitsMask 0x00ff
  #define R_BigInteger_DoubleDigit_UpperBitsShift 8
  #define R_BigInteger_DoubleDigit_LowerBitsShift 0
#else
  #error("environment not (yet) supported")
#endif

// a big integer represents an integer
// s * (d0 * b^0 + d1 * b^1 + ... + d[n-1] * b^[n-1]) 
// where
// - s denotes the sign (+1 for plus, -1 for minus)
// - b > 0 is the basis
// and n > 0 is the number of digits
// The following invariant is preserved
// - zero is always represented by n = 1, d0 = 0, and s = 1
// - d[n-1] != 0 unless n = 1
//
// If we select a good basis (e.g., UINT8_MAX or UINT64_MAX) we can represent most numbers by a single digit.
// The current basis is UINT64_MAX.
Rex_declareObjectType("R.BigInteger", R_BigInteger, "R.Object");

struct R_BigInteger {
  R_Object _parent;
  Arcadia_BooleanValue sign;
  R_BigInteger_Digit* digits;
  Arcadia_SizeValue size, capacity;
};

R_BigInteger*
R_BigInteger_create
  (
    Arcadia_Process* process,
    R_Value v
  );

// compute
// @code
// a + b
// @endcode
R_BigInteger*
R_BigInteger_add
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  );

// compute
// @code
// a - b
// @endcode
R_BigInteger*
R_BigInteger_subtract
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  );

// compute
// @code
// |a|
// @endcode
R_BigInteger*
R_BigInteger_magnitude
  (
    Arcadia_Process* process,
    R_BigInteger* a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The following functions are for convenience when writing C code.

// return -1 if |a| is less than |b|
// return +1 if |a| is greater than |b|
// return 0 otherwise
Arcadia_Integer8Value
R_BigInteger_compareMagnitudes
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

// return -1 if a is less than b
// return +1 if a is greater than b
// return 0 otherwise
Arcadia_Integer8Value
R_BigInteger_compare
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

Arcadia_BooleanValue
R_BigInteger_isZero
  (
    R_BigInteger* a
  );

Arcadia_BooleanValue
R_BigInteger_isNegative
  (
    R_BigInteger* a
  );

Arcadia_BooleanValue
R_BigInteger_isPositive
  (
    R_BigInteger* a
  );

// assign the values of b to a
// @error #Arcadia_Status_ArgumentInvalid @a is null
// @error #Arcadia_Status_ArgumentInvalid @b is null
// @error #Arcadia_Status_AllocationFailed allocation failed
void
R_BigInteger_assign
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  );

void
R_BigInteger_addInPlace  
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  );

void
R_BigInteger_subtractInPlace
  (
    Arcadia_Process* process,
    R_BigInteger* a,
    R_BigInteger* b
  );

R_BigInteger*
R_BigInteger_fromInteger16
  (
    Arcadia_Process* process,
    Arcadia_Integer16Value v
  );

R_BigInteger*
R_BigInteger_fromInteger32
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value v
  );

R_BigInteger*
R_BigInteger_fromInteger64
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value v
  );

R_BigInteger*
R_BigInteger_fromInteger8
  (
    Arcadia_Process* process,
    Arcadia_Integer8Value v
  );

R_BigInteger*
R_BigInteger_fromNatural16
  (
    Arcadia_Process* process,
    Arcadia_Natural16Value v
  );

R_BigInteger*
R_BigInteger_fromNatural32
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value v
  );

R_BigInteger*
R_BigInteger_fromNatural64
  (
    Arcadia_Process* process,
    Arcadia_Natural64Value v
  );

R_BigInteger*
R_BigInteger_fromNatural8
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value v
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_BIGINTEGER_H_INCLUDED
