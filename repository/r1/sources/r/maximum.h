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

// Last modified: 2024-08-27

#if !defined(R_MAXIMUM_H_INCLUDED)
#define R_MAXIMUM_H_INCLUDED

#include "r/integer16.h"
#include "r/integer32.h"
#include "r/integer64.h"
#include "r/integer8.h"

#include "r/natural16.h"
#include "r/natural32.h"
#include "r/natural64.h"
#include "r/natural8.h"

#include "r/size.h"

#define Define(Type, Suffix) \
  static inline R_##Type##Value \
  R_maximum_##Suffix \
    ( \
      R_##Type##Value x, \
      R_##Type##Value y \
    ) \
  { return x > y ? x : y; }

Define(Integer16, i16)
Define(Integer32, i32)
Define(Integer64, i64)
Define(Integer8, i8)

Define(Natural16, n16)
Define(Natural32, n32)
Define(Natural64, n64)
Define(Natural8, n8)

Define(Size, s)

#undef Define

#endif // R_MAXIMUM_H_INCLUDED
