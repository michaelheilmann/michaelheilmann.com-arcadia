// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_LIST_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_LIST_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.List", Arcadia_List, u8"Arcadia.Object");

struct Arcadia_List {
  Arcadia_Object _parent;
  Arcadia_Value* elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_create
Arcadia_List*
Arcadia_List_create
  (
    Arcadia_Thread* thread
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_clear
void
Arcadia_List_clear
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_getSize
Arcadia_SizeValue
Arcadia_List_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_append
void
Arcadia_List_append
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value value
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_prepend
void
Arcadia_List_prepend
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value value
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_insertAt
void
Arcadia_List_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_getAt
Arcadia_Value
Arcadia_List_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_remove
void
Arcadia_List_remove
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  );

// https://michaelheilmann.com/repository/Arcadia.Ring2/#Arcadia_List_isEmpty
static inline Arcadia_BooleanValue
Arcadia_List_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  )
{
  return Arcadia_SizeValue_Literal(0) == Arcadia_List_getSize(thread, self);
}

#define Define(Type, Suffix, Variable) \
  void \
  Arcadia_List_append##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Type##Value Variable##Value \
    ); \
\
  void \
  Arcadia_List_prepend##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Type##Value Variable##Value \
    ); \
\
  void \
  Arcadia_List_insert##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index, \
      Type##Value Variable##Value \
    ); \
\
  Arcadia_BooleanValue \
  Arcadia_List_is##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index \
    ); \
\
  Type##Value \
  Arcadia_List_get##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index \
    );

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_ForeignProcedure, ForeignProcedure, foreignProcedure)
Define(Arcadia_Integer8, Integer8, integer8)
Define(Arcadia_Integer16, Integer16, integer16)
Define(Arcadia_Integer32, Integer32, integer32)
Define(Arcadia_Integer64, Integer64, integer64)
Define(Arcadia_Natural8, Natural8, natural8)
Define(Arcadia_Natural16, Natural16, natural16)
Define(Arcadia_Natural32, Natural32, natural32)
Define(Arcadia_Natural64, Natural64, natural64)
Define(Arcadia_ObjectReference, ObjectReference, objectReference)
Define(Arcadia_Size, Size, size)
Define(Arcadia_Void, Void, void)

#undef Define

#endif // ARCADIA_RING2_IMPLEMENTATION_LIST_H_INCLUDED
