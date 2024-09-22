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

#if !defined(R_MINIMUM_H_INCLUDED)
#define R_MINIMUM_H_INCLUDED

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#include "R/Size.h"

#define Define(Type) \
  static inline R_##Type##Value \
  R_minimum##Type##Value \
    ( \
      R_##Type##Value x, \
      R_##Type##Value y \
    ) \
  { return x < y ? x : y; } 

Define(Integer16)
Define(Integer32)
Define(Integer64)
Define(Integer8)

Define(Natural16)
Define(Natural32)
Define(Natural64)
Define(Natural8)

Define(Size)

#undef Define

#endif // R_MINIMUM_H_INCLUDED
