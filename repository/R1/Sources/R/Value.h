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

#include "R/Atoms.h"

#include "R/Boolean.h"

#include "R/ForeignFunctionReference.h"

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#include "R/ObjectReference.h"

#include "R/Size.h"

#include "R/Void.h"

#define R_ValueTag_Atom (1)

#define R_ValueTag_Boolean (2)

#define R_ValueTag_ForeignFunctionReference (3)

#define R_ValueTag_Integer16 (4)
#define R_ValueTag_Integer32 (5)
#define R_ValueTag_Integer64 (6)
#define R_ValueTag_Integer8 (7)

#define R_ValueTag_Natural16 (8)
#define R_ValueTag_Natural32 (9)
#define R_ValueTag_Natural64 (10)
#define R_ValueTag_Natural8 (11)

#define R_ValueTag_ObjectReference (12)

#define R_ValueTag_Size (13)

// The tag for type "Void" must be 0.
#define R_ValueTag_Void (0)

typedef struct R_Value{
  uint8_t tag;
  union {

  #define Define(Suffix,  Prefix) \
    R_##Suffix##Value Prefix##Value;

    Define(Atom, atom)

    Define(Boolean, boolean)

    Define(ForeignFunctionReference, foreignFunctionReference)
    
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
  R_Value_get##Suffix##Value \
    ( \
      R_Value const* value \
    ) \
  {  return value->Prefix##Value; } \
\
  static inline bool \
  R_Value_is##Suffix##Value \
    ( \
      R_Value const* value \
    ) \
  { return R_ValueTag_##Suffix == value->tag; } \
  \
  static inline void \
  R_Value_set##Suffix##Value \
    ( \
      R_Value* value, \
      R_##Suffix##Value const Prefix##Value \
    ) \
  { \
    value->tag = R_ValueTag_##Suffix; \
    value->Prefix##Value = Prefix##Value; \
  }

Define(Atom, atom)

Define(Boolean, boolean)

Define(ForeignFunctionReference, foreignFunctionReference)

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

void
R_Value_visit
  (
    R_Value* self
  );

#endif // R_VALUE_H_INCLUDED
