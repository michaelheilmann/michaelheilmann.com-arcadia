#if !defined(R_BIGINTEGER_H_INCLUDED)
#define R_BIGINTEGER_H_INCLUDED

#include "R/Object.h"
#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"
#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#define R_Configuration_BigInteger_DigitType_Natural16 (1)
#define R_Configuration_BigInteger_DigitType_Natural32 (2)
#define R_Configuration_BigInteger_DigitType_Natural64 (3)
#define R_Configuration_BigInteger_DigitType_Natural8 (4)

#define R_Configuration_BigInteger_DigitType R_Configuration_BigInteger_DigitType_Natural8

#if R_Configuration_BigInteger_DigitType_Natural16 == R_Configuration_BigInteger_DigitType
  typedef R_Natural16Value R_BigInteger_DigitType;
  #define R_BigInteger_DigitBase R_Natural16Value_Maximum
  #define R_BigInteger_DigitLiteral(x) R_Natural16Value_Literal(x)
  typedef R_Natural32Value R_BigInteger_DoubleDigitType;
  #define R_BigInteger_DoubleDigitUpperBitsMask 0xffff0000
  #define R_BigInteger_DoubleDigitLowerBitsMask 0x0000ffff
  #define R_BigInteger_DoubleDigitUpperBitsShift 16
  #define R_BigInteger_DoubleDigitLowerBitsShift 0
#elif R_Configuration_BigInteger_DigitType_Natural32 == R_Configuration_BigInteger_DigitType
  typedef R_Natural32Value R_BigInteger_DigitType;
  #define R_BigInteger_DigitBase R_Natural32Value_Maximum
  #define R_BigInteger_DigitLiteral(x) R_Natural32Value_Literal(x)
  typedef R_Natural64Value R_BigInteger_DoubleDigitType;
  #define R_BigInteger_DoubleDigitUpperBitsMask 0xffffffff00000000
  #define R_BigInteger_DoubleDigitLowerBitsMask 0x00000000ffffffff
  #define R_BigInteger_DoubleDigitUpperBitsShift 16
  #define R_BigInteger_DoubleDigitLowerBitsShift 0
#elif R_Configuration_BigInteger_DigitType_Natural64 == R_Configuration_BigInteger_DigitType
  #error("environment not (yet) supported")
#elif R_Configuration_BigInteger_DigitType_Natural8 == R_Configuration_BigInteger_DigitType
  typedef R_Natural8Value R_BigInteger_DigitType;
  #define R_BigInteger_DigitBase R_Natural8Value_Maximum
  #define R_BigInteger_DigitLiteral(x) R_Natural8Value_Literal(x)  
  typedef R_Natural16Value R_BigInteger_DoubleDigitType;
  #define R_BigInteger_DoubleDigitUpperBitsMask 0xff00
  #define R_BigInteger_DoubleDigitLowerBitsMask 0x00ff
  #define R_BigInteger_DoubleDigitUpperBitsShift 8
  #define R_BigInteger_DoubleDigitLowerBitsShift 0
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
  R_BooleanValue sign;
  R_BigInteger_DigitType* digits;
  R_SizeValue size, capacity;
};

R_BigInteger*
R_BigInteger_create
  (
    R_Value v
  );

R_BigInteger*
R_BigInteger_add
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

R_BigInteger*
R_BigInteger_subtract
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// The following functions are for convenience when writing C code.

// return -1 if |a| is less than |b|
// return +1 if |a| is greater than |b|
// return 0 otherwise
R_Integer8Value
R_BigInteger_compareMagnitudes
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

// return -1 if a is less than b
// return +1 if a is greater than b
// return 0 otherwise
R_Integer8Value
R_BigInteger_compare
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

// assign the values of b to a
// @error #R_Status_ArgumentInvalid @a is null
// @error #R_Status_ArgumentInvalid @b is null
// @error #R_Status_AllocationFailed allocation failed
void
R_BigInteger_assign
(
  R_BigInteger* a,
  R_BigInteger* b
);

void
R_BigInteger_addInPlace  
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

void
R_BigInteger_subtractInPlace
  (
    R_BigInteger* a,
    R_BigInteger* b
  );

R_BigInteger*
R_BigInteger_fromInteger16
  (
    R_Integer16Value v
  );

R_BigInteger*
R_BigInteger_fromInteger32
  (
    R_Integer32Value v
  );

R_BigInteger*
R_BigInteger_fromInteger64
  (
    R_Integer64Value v
  );

R_BigInteger*
R_BigInteger_fromInteger8
  (
    R_Integer8Value v
  );

R_BigInteger*
R_BigInteger_fromNatural16
  (
    R_Natural16Value v
  );

R_BigInteger*
R_BigInteger_fromNatural32
  (
    R_Natural32Value v
  );

R_BigInteger*
R_BigInteger_fromNatural64
  (
    R_Natural64Value v
  );

R_BigInteger*
R_BigInteger_fromNatural8
  (
    R_Natural8Value v
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_BIGINTEGER_H_INCLUDED
