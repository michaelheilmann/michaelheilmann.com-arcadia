
static void
Digits_fromInteger64
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BooleanValue* sign,
    R_Integer64Value v
  );

static void
Digits_fromNatural64
  (
    R_BigInteger_DigitType** digits,
    R_SizeValue* size,
    R_SizeValue* capacity,
    R_BooleanValue* sign,
    R_Natural64Value v
  );
