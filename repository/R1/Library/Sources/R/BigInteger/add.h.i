
static R_BooleanValue 
isZero
  (
    R_BigInteger* a
  );

// precondition: the magnitude of a must be greater than the magnitude of b
// Examples where this is applied:
// - a + b where the signs are different for example 2 + (-3) = -(|3|-|2|)
// - a - b where a and b are positive for example 2 - 3 = -(|3|-|2|)
// - ...
static void
Digits_subtractMagnitude
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BigInteger* a,
    R_BigInteger* b
  );

static void
Digits_addMagnitude
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BigInteger* a,
    R_BigInteger* b
  );

static void
Digits_add
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BooleanValue* sign,
    R_BigInteger* a,
    R_BigInteger* b
  );
