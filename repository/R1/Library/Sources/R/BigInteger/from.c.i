
static void
Digits_fromInteger64
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BooleanValue* sign,
    R_Integer64Value v
  )
{
  R_BooleanValue sign1 = v >= R_Integer64Value_Literal(0);
  R_Natural64Value u;
  if (v == R_Integer64Value_Minimum) {
    u = ((R_Natural64Value)(R_Integer16Value_Minimum + 1)) + 1;
  } else {
    u = (R_Natural64Value)(v < 0 ? -v : v);
  }
  Digits_fromNatural64(digits, size, capacity, sign, u);
  *sign = sign1;
}

static void
Digits_fromNatural64
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BooleanValue* sign,
    R_Natural64Value v
  )
{
  R_BooleanValue sign1 = R_BooleanValue_True;
  size_t capacity1 = 0;
  size_t size1 = 0;
  R_BigInteger_DigitType* digits1 = NULL;

  R_Natural64Value v1;

  // (1) compute the number of digits
  v1 = v;
  do {
    v1 = v1 / R_BigInteger_DigitBase;
    capacity1++;
  } while (v1 > 0);
  
  // (2) allocate the digits
  if (Digits_allocate(&digits1, capacity1)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }

  // (3) compute the digit values
  v1 = v;
  do {
    R_BigInteger_DigitType d = v1 % R_BigInteger_DigitBase;
    digits1[size1++] = d;
    v1 = v1 / R_BigInteger_DigitBase;
  } while (v1 > 0);

  // (4) store the information
  *digits = digits1;
  *capacity = capacity1;
  *size = size1;
  *sign = sign1;
}
