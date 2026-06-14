// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAYBUILDER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAYBUILDER_H_INCLUDED

#if !defined(ARCADIA_RING1_MODULE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Object.h"
#include "Arcadia/Ring1/Implementation/swap.h"
typedef struct Arcadia_ByteArray Arcadia_ByteArray;

Arcadia_declareObjectType(u8"Arcadia.ByteArrayBuilder", Arcadia_ByteArrayBuilder,
                          u8"Arcadia.Object");

struct Arcadia_ByteArrayBuilderDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_ByteArrayBuilder {
  Arcadia_Object _parent;
  char* p;
  Arcadia_SizeValue sz;
  Arcadia_SizeValue cp;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_create
Arcadia_ByteArrayBuilder*
Arcadia_ByteArrayBuilder_create
  (
    Arcadia_Thread* thread
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_endsWith_pn
Arcadia_BooleanValue
Arcadia_ByteArrayBuilder_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_startsWith_pn
Arcadia_BooleanValue
Arcadia_ByteArrayBuilder_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_insertBackBytes
void
Arcadia_ByteArrayBuilder_insertBackBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_insertFrontBytes
void
Arcadia_ByteArrayBuilder_insertFrontBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_insertBytes
void
Arcadia_ByteArrayBuilder_insertBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder* self,
    Arcadia_SizeValue index,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_isEqualTo
Arcadia_BooleanValue
Arcadia_ByteArrayBuilder_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self,
    Arcadia_ByteArrayBuilder const* other
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_isEqualTo_pn
Arcadia_BooleanValue
Arcadia_ByteArrayBuilder_isEqualTo_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Bytebuffer_clear
void
Arcadia_ByteArrayBuilder_clear
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_getSize
Arcadia_SizeValue
Arcadia_ByteArrayBuilder_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_getNumberOfBytes
Arcadia_SizeValue
Arcadia_ByteArrayBuilder_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_getBytes
Arcadia_Natural8Value const*
Arcadia_ByteArrayBuilder_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_getAt
Arcadia_Natural8Value
Arcadia_ByteArrayBuilder_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder const* self,
    Arcadia_SizeValue index
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_ByteArrayBuilder_swap
static inline void
Arcadia_ByteArrayBuilder_swap
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder* self,
    Arcadia_ByteArrayBuilder* other
  )
{
  Arcadia_swapPointer(thread, (void**)&self->p, (void**)&other->p);
  Arcadia_swapSize(thread, &self->sz, &other->sz);
  Arcadia_swapSize(thread, &self->cp, &other->cp);
}

Arcadia_ByteArray*
Arcadia_ByteArrayBuilder_toByteArray
  (
    Arcadia_Thread* thread,
    Arcadia_ByteArrayBuilder* self
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECTS_BYTEARRAYBUILDER_H_INCLUDED
