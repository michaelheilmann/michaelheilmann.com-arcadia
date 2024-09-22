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

// Last modified: 2024-09-27

#if !defined(R_HASH_H_INCLUDED)
#define R_HASH_H_INCLUDED

#include "R/Boolean.h"

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#include "R/Real32.h"
#include "R/Real64.h"

#include "R/Size.h"

#include "R/Void.h"

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashBooleanValue
  (
    R_BooleanValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashInteger16Value
  (
    R_Integer16Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashInteger32Value
  (
    R_Integer32Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashInteger64Value
  (
    R_Integer64Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashInteger8Value
  (
    R_Integer8Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashNatural16Value
  (
    R_Natural16Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashNatural32Value
  (
    R_Natural32Value x
  );
  
// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashNatural64Value
  (
    R_Natural64Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashNatural8Value
  (
    R_Natural8Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashReal32Value
  (
    R_Real32Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashReal64Value
  (
    R_Real64Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashSizeValue
  (
    R_SizeValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
R_SizeValue
R_hashVoidValue
  (
    R_VoidValue x
  );

#endif // R_HASH_H_INCLUDED
