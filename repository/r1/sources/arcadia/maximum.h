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

// Last modified: 2024-08-25

#if !defined(ARCADIA_MAXIMUM_H_INCLUDED)
#define ARCADIA_MAXIMUM_H_INCLUDED

#include "arcadia/integer16.h"
#include "arcadia/integer32.h"
#include "arcadia/integer64.h"
#include "arcadia/integer8.h"

#include "arcadia/natural16.h"
#include "arcadia/natural32.h"
#include "arcadia/natural64.h"
#include "arcadia/natural8.h"

#include "arcadia/size.h"

static inline R_Integer16Value
R_maximum_i16
  (
    R_Integer16Value x,
    R_Integer16Value y
  )
{ return x > y ? x : y; }

static inline R_Integer32Value
R_maximum_i32
  (
    R_Integer32Value x,
    R_Integer32Value y
  )
{ return x > y ? x : y; }

static inline R_Integer64Value
R_maximum_i64
  (
    R_Integer64Value x,
    R_Integer64Value y
  )
{ return x > y ? x : y; }

static inline R_Integer8Value
R_maximum_i8
  (
    R_Integer8Value x,
    R_Integer8Value y
  )
{ return x > y ? x : y; }

static inline R_Natural16Value
R_maximum_n16
  (
    R_Natural16Value x,
    R_Natural16Value y
  )
{ return x > y ? x : y; }

static inline R_Natural32Value
R_maximum_n32
  (
    R_Natural32Value x,
    R_Natural32Value y
  )
{ return x > y ? x : y; }

static inline R_Natural64Value
R_maximum_n64
  (
    R_Natural64Value x,
    R_Natural64Value y
  )
{ return x > y ? x : y; }

static inline R_Natural8
R_maximum_n8
  (
    R_Natural8 x,
    R_Natural8 y
  )
{ return x > y ? x : y; }

static inline R_SizeValue
R_maximum_sz
  (
    R_SizeValue x,
    R_SizeValue y
  )
{ return x > y ? x : y; }

#endif // ARCADIA_MAXIMUM_H_INCLUDED
