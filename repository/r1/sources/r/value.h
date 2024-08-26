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

#if !defined(R_VALUE_H_INCLUDED)
#define R_VALUE_H_INCLUDED

#include "r/boolean.h"

#include "r/integer16.h"
#include "r/integer32.h"
#include "r/integer64.h"
#include "r/integer8.h"

#include "r/natural16.h"
#include "r/natural32.h"
#include "r/natural64.h"
#include "r/natural8.h"

#include "r/objectreference.h"

#include "r/size.h"

#include "r/void.h"

#define R_ValueTag_Boolean (1)

#define R_ValueTag_Integer16 (2)
#define R_ValueTag_Integer32 (3)
#define R_ValueTag_Integer64 (4)
#define R_ValueTag_Integer8 (5)

#define R_ValueTag_Natural16 (6)
#define R_ValueTag_Natural32 (7)
#define R_ValueTag_Natural64 (8)
#define R_ValueTag_Natural8 (9)

#define R_ValueTag_ObjectReference (10)

#define R_ValueTag_Size (11)

// The tag for type "Void" must be 0.
#define R_ValueTag_Void (0)

typedef struct R_Value{
  uint8_t tag;
  union {

  #define Define(Suffix,  Prefix) \
    R_##Suffix##Value Prefix##Value;

    Define(Boolean, boolean)
    
    Define(Integer16, integer16)
    Define(Integer32, integer32)
    Define(Integer64, integer64)
    Define(Integer8, integer8)

    Define(Natural16, natural16)
    Define(Natural32, natural32)
    Define(Natural64, natural64)
    Define(Natural8, natural8)

    Define(ObjectReference, objectReference)

    Define(Size, size)
    
    Define(Void, void)

  #undef Define
  };
} R_Value;

static inline uint8_t
R_Value_getTag
  (
    R_Value const* value
  )
{ return value->tag; }

#define Define(Suffix, Prefix) \
  static inline R_##Suffix##Value \
  R_Value_get##Suffix \
    ( \
      R_Value const* value \
    ) \
  {  return value->Prefix##Value; } \
\
  static inline bool \
  R_Value_is##Suffix \
    ( \
      R_Value const* value \
    ) \
  { return R_ValueTag_##Suffix == value->tag; } \
  \
  static inline void \
  R_Value_set##Suffix \
    ( \
      R_Value* value, \
      R_##Suffix##Value const Prefix##Value \
    ) \
  { \
    value->tag = R_ValueTag_##Suffix; \
    value->Prefix##Value = Prefix##Value; \
  }

Define(Boolean, boolean)

Define(Integer16, integer16)
Define(Integer32, integer32)
Define(Integer64, integer64)
Define(Integer8, integer8)

Define(Natural16, natural16)
Define(Natural32, natural32)
Define(Natural64, natural64)
Define(Natural8, natural8)

Define(ObjectReference, objectReference)

Define(Size, size)

Define(Void, void)

#undef Define

#endif // R_VALUE_H_INCLUDED
