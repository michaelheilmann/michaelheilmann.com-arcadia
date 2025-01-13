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

// Last modified: 2024-09-27

#if !defined(ARCADIA_RING1_IMPLEMENTATION_HASH_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_HASH_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Atoms.h"

#include "Arcadia/Ring1/Implementation/Boolean.h"

#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/Real32.h"
#include "Arcadia/Ring1/Implementation/Real64.h"

#include "Arcadia/Ring1/Implementation/Size.h"

#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/Void.h"

Arcadia_SizeValue
Arcadia_hashAtomValue
  (
    Arcadia_AtomValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashBooleanValue
  (
    Arcadia_BooleanValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashForeignProcedureValue
  (
    Arcadia_ForeignProcedureValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashInteger16Value
  (
    Arcadia_Integer16Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashInteger32Value
  (
    Arcadia_Integer32Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashInteger64Value
  (
    Arcadia_Integer64Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashInteger8Value
  (
    Arcadia_Integer8Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashNatural16Value
  (
    Arcadia_Natural16Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashNatural32Value
  (
    Arcadia_Natural32Value x
  );
  
// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashNatural64Value
  (
    Arcadia_Natural64Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashNatural8Value
  (
    Arcadia_Natural8Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashReal32Value
  (
    Arcadia_Real32Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashReal64Value
  (
    Arcadia_Real64Value x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashSizeValue
  (
    Arcadia_SizeValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashTypeValue
  (
    Arcadia_TypeValue x
  );

// https://michaelheilmann.com/repository/R1/#r-hash
Arcadia_SizeValue
Arcadia_hashVoidValue
  (
    Arcadia_VoidValue x
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_HASH_H_INCLUDED
