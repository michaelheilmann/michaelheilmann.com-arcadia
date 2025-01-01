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

// Last modified: 2024-08-27

#if !defined(R_VALUE_H_INCLUDED)
#define R_VALUE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Atoms.h"

#include "Arcadia/Ring1/Implementation/Boolean.h"

#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"

#include "R/ImmutableByteArray.h"

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/ObjectReference.h"

#include "Arcadia/Ring1/Implementation/Real32.h"
#include "Arcadia/Ring1/Implementation/Real64.h"

#include "Arcadia/Ring1/Implementation/Size.h"

#include "Arcadia/Ring1/Implementation/Types.h"

#include "Arcadia/Ring1/Implementation/Void.h"

#define R_ValueTag_Atom (1)

#define R_ValueTag_Boolean (2)

#define R_ValueTag_ForeignProcedure (3)

#define R_ValueTag_ImmutableByteArray (4)

#define R_ValueTag_Integer16 (5)
#define R_ValueTag_Integer32 (6)
#define R_ValueTag_Integer64 (7)
#define R_ValueTag_Integer8 (8)

#define R_ValueTag_Natural16 (9)
#define R_ValueTag_Natural32 (10)
#define R_ValueTag_Natural64 (11)
#define R_ValueTag_Natural8 (12)

#define R_ValueTag_ObjectReference (13)

#define R_ValueTag_Real32 (14)
#define R_ValueTag_Real64 (15)

#define R_ValueTag_Size (16)

#define R_ValueTag_Type (17)

// The tag for type "Void" must be 0.
#define R_ValueTag_Void (0)

typedef struct R_Value {
  uint8_t tag;
  union {

  #define Define(Prefix, Suffix, Variable) \
    Prefix##_##Suffix##Value Variable##Value;

    Define(Arcadia, Atom, atom)

    Define(Arcadia, Boolean, boolean)

    Define(Arcadia, ForeignProcedure, foreignProcedure)

    Define(Arcadia, ImmutableByteArray, immutableByteArray)
    
    Define(Arcadia, Integer16, integer16)
    Define(Arcadia, Integer32, integer32)
    Define(Arcadia, Integer64, integer64)
    Define(Arcadia, Integer8, integer8)

    Define(Arcadia, Natural16, natural16)
    Define(Arcadia, Natural32, natural32)
    Define(Arcadia, Natural64, natural64)
    Define(Arcadia, Natural8, natural8)

    Define(R, ObjectReference, objectReference)

    Define(Arcadia, Real32, real32)
    Define(Arcadia, Real64, real64)

    Define(Arcadia, Size, size)

    Define(R, Type, type)
    
    Define(Arcadia, Void, void)

  #undef Define
  };
} R_Value;

static inline uint8_t
R_Value_getTag
  (
    R_Value const* value
  )
{ return value->tag; }

#define Define(Prefix, Suffix, Variable) \
  static inline Prefix##_##Suffix##Value \
  R_Value_get##Suffix##Value \
    ( \
      R_Value const* value \
    ) \
  {  return value->Variable##Value; } \
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
      Prefix##_##Suffix##Value const Variable##Value \
    ) \
  { \
    value->tag = R_ValueTag_##Suffix; \
    value->Variable##Value = Variable##Value; \
  }

Define(Arcadia, Atom, atom)

Define(Arcadia, Boolean, boolean)

Define(Arcadia, ForeignProcedure, foreignProcedure)

Define(Arcadia, ImmutableByteArray, immutableByteArray)

Define(Arcadia, Integer16, integer16)
Define(Arcadia, Integer32, integer32)
Define(Arcadia, Integer64, integer64)
Define(Arcadia, Integer8, integer8)

Define(Arcadia, Natural16, natural16)
Define(Arcadia, Natural32, natural32)
Define(Arcadia, Natural64, natural64)
Define(Arcadia, Natural8, natural8)

Define(R, ObjectReference, objectReference)

Define(Arcadia, Real32, real32)
Define(Arcadia, Real64, real64)

Define(Arcadia, Size, size)

Define(R, Type, type)

Define(Arcadia, Void, void)

#undef Define

void
R_Value_visit
  (
    R_Value* self
  );

Arcadia_TypeValue
R_Value_getType
  (
    Arcadia_Process* process,
    R_Value const* self
  );

Arcadia_BooleanValue
R_Value_isEqualTo
  (
    Arcadia_Process* process,
    R_Value const* self,
    R_Value const* other
  );

Arcadia_SizeValue
R_Value_hash
  (
    Arcadia_Process* process,
    R_Value const* self
  );

#endif // R_VALUE_H_INCLUDED
