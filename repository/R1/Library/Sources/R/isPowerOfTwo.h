// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-28

#if !defined(R_ISPOWEROFTWO_H_INCLUDED)
#define R_ISPOWEROFTWO_H_INCLUDED

#include "R/Boolean.h"

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#include "R/Size.h"

R_BooleanValue
R_isPowerOfTwoInteger8Value
  (
    R_Integer8Value x
  );

R_BooleanValue
R_isPowerOfTwoInteger16Value
  (
    R_Integer16Value x
  );

R_BooleanValue
R_isPowerOfTwoInteger32Value
  (
    R_Integer32Value x
  );

R_BooleanValue
R_isPowerOfTwoInteger64Value
  (
    R_Integer64Value x
  );

R_BooleanValue
R_isPowerOfTwoNatural8Value
  (
    R_Natural8Value x
  );

R_BooleanValue
R_isPowerOfTwoNatural16Value
  (
    R_Natural16Value x
  );

R_BooleanValue
R_isPowerOfTwoNatural32Value
  (
    R_Natural32Value x
  );

R_BooleanValue
R_isPowerOfTwoNatural64Value
  (
    R_Natural64Value x
  );

R_BooleanValue
R_isPowerOfTwoSizeValue
  (
    R_SizeValue x
  );

#endif // R_ISPOWEROFTWO_H_INCLUDED
