#include "R/BigInteger/from.h"

#include "R/BigInteger/digits.h"

void
Digits_fromInteger64
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    Arcadia_Integer64Value v
  )
{
  Arcadia_BooleanValue sign1 = v >= Arcadia_Integer64Value_Literal(0);
  Arcadia_Natural64Value u;
  if (v == Arcadia_Integer64Value_Minimum) {
    u = ((Arcadia_Natural64Value)(Arcadia_Integer16Value_Minimum + 1)) + 1;
  } else {
    u = (Arcadia_Natural64Value)(v < 0 ? -v : v);
  }
  Digits_fromNatural64(process, digits, size, capacity, sign, u);
  *sign = sign1;
}

void
Digits_fromNatural64
  (
    Arcadia_Process* process,
    R_BigInteger_Digit** digits,
    Arcadia_SizeValue* size,
    Arcadia_SizeValue* capacity,
    Arcadia_BooleanValue* sign,
    Arcadia_Natural64Value v
  )
{
  size_t size1, capacity1;
  R_BigInteger_Digit* digits1 = NULL;
  // (1) Compute sign.
  Arcadia_BooleanValue sign1 = Arcadia_BooleanValue_True;
  if (R_BigInteger_Digit_Maximum >= Arcadia_Natural64Value_Maximum) {
    // (2) Compute size and capacity.
    size1 = 1;
    capacity1 = 1;
    // (3) Allocate the digits.
    Digits_allocate(process, &digits1, capacity1);
    // (4) Compute digits.
    digits1[0] = v;
  } else {
    static const Arcadia_Natural64Value base = ((Arcadia_Natural64Value)R_BigInteger_Digit_Maximum) + 1; 
    Arcadia_Natural64Value v1;
    // (2) Compute capacity.
    capacity1 = 0;
    v1 = v;
    do {
      v1 = v1 / base;
      capacity1++;
    } while (v1 > 0);
    
    // (2) Allocate the digits.
    Digits_allocate(process, &digits1, capacity1);

    // (3) Compute size and digits.
    size1 = 0;
    v1 = v;
    do {
      R_BigInteger_Digit d = v1 % base;
      digits1[size1++] = d;
      v1 = v1 / base;
    } while (v1 > 0);
  }
  // (4) Store the information.
  *digits = digits1;
  *capacity = capacity1;
  *size = size1;
  *sign = sign1;
}
