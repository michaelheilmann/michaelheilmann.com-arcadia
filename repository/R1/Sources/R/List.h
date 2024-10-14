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

#if !defined(R_LIST_H_INCLUDED)
#define R_LIST_H_INCLUDED

#include "R/Object.h"
#include "R/Value.h"

Rex_declareObjectType("R.List", R_List, "R.Object");

struct R_List {
  R_Object _parent;
  R_Value* elements;
  R_SizeValue size;
  R_SizeValue capacity;
};

void
R_List_construct
  (
    R_List* self
  );

// https://michaelheilmann.com/repository/R1/#r-list-create
R_List*
R_List_create
  (
  );

// https://michaelheilmann.com/repository/R1/#r-list-clear
void
R_List_clear
  (
    R_List* self
  );

// https://michaelheilmann.com/repository/R1/#r-list-getsize
R_SizeValue
R_List_getSize
  (
    R_List* self
  );

// https://michaelheilmann.com/repository/R1/#r-list-append
void
R_List_append
  (
    R_List* self,
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-list-prepend
void
R_List_prepend
  (
    R_List* self,
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-list-insertat
void
R_List_insertAt
  (
    R_List* self,
    R_SizeValue index,
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-list-getat
R_Value
R_List_getAt
  (
    R_List* self,
    R_SizeValue index
  );

// https://michaelheilmann.com/repository/R1/#r-list-remove
void
R_List_remove
  (
    R_List* self,
    R_SizeValue index,
    R_SizeValue count
  );

// https://michaelheilmann.com/repository/R1/#r-list-isempty
static inline R_BooleanValue
R_List_isEmpty
  (
    R_List* self
  )
{
  return R_SizeValue_Literal(0) == R_List_getSize(self);
}

#define Define(Suffix, Prefix) \
  void \
  R_List_append##Suffix##Value \
    ( \
      R_List* self, \
      R_##Suffix##Value Prefix##Value \
    ); \
\
  void \
  R_List_prepend##Suffix##Value \
    ( \
      R_List* self, \
      R_##Suffix##Value Prefix##Value \
    ); \
\
  void \
  R_List_insert##Suffix##ValueAt \
    ( \
      R_List* self, \
      R_SizeValue index, \
      R_##Suffix##Value Prefix##Value \
    ); \
\
  R_BooleanValue \
  R_List_is##Suffix##ValueAt \
    ( \
      R_List* self, \
      R_SizeValue index \
    ); \
\
  R_##Suffix##Value \
  R_List_get##Suffix##ValueAt \
    ( \
      R_List* self, \
      R_SizeValue index \
    );

Define(Boolean, boolean)
Define(ForeignFunctionReference, foreignFunctionReference)
Define(Integer8, integer8)
Define(Integer16, integer16)
Define(Integer32, integer32)
Define(Integer64, integer64)
Define(Natural8, natural8)
Define(Natural16, natural16)
Define(Natural32, natural32)
Define(Natural64, natural64)
Define(ObjectReference, objectReference)
Define(Size, size)
Define(Void, void)

#undef Define

#endif // R_LIST_H_INCLUDED
