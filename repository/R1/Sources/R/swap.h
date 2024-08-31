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

// Last modified: 2024-09-07

#if !defined(R_SWAP_H_INCLUDED)
#define R_SWAP_H_INCLUDED

#include "R/Boolean.h"

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "r/Natural8.h"

#include "R/Size.h"

#include "R/Void.h"

#define Define(Type, Suffix) \
  static inline void \
  R_swap_##Suffix \
    ( \
      R_##Type##Value* x, \
      R_##Type##Value* y \
    ) \
  { \
    R_##Type##Value t = *x; \
    *x = *y; \
    *y = t; \
  }

Define(Boolean, b)

Define(Integer16, i16)
Define(Integer32, i32)
Define(Integer64, i64)
Define(Integer8, i8)

Define(Natural16, n16)
Define(Natural32, n32)
Define(Natural64, n64)
Define(Natural8, n8)

Define(Size, s)

Define(Void, v)

#undef Define

static inline void
R_swap_p
  (
    void** x,
    void** y
  )
{
  void* t = *x;
  *x = *y;
  *y = t;
}

#endif // R_SWAP_H_INCLUDED
