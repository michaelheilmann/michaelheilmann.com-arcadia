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

#if !defined(R_STACK_H_INCLUDED)
#define R_STACK_H_INCLUDED

#include "R/Object.h"
#include "R/Value.h"

Rex_declareObjectType(u8"R.Stack", R_Stack, u8"R.Object");

struct R_Stack {
  R_Object _parent;
  R_Value* elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

// https://michaelheilmann.com/repository/R1/#r-stack-create
R_Stack*
R_Stack_create
  (
    Arcadia_Process* process
  );

// https://michaelheilmann.com/repository/R1/#r-stack-clear
void
R_Stack_clear
  (
    R_Stack* self
  );

// https://michaelheilmann.com/repository/R1/#r-stack-getsize
Arcadia_SizeValue
R_Stack_getSize
  (
    R_Stack* self
  );

// https://michaelheilmann.com/repository/R1/#r-stack-push
void
R_Stack_push
  (
    Arcadia_Process* process,
    R_Stack* self,
    R_Value value
  );

// https://michaelheilmann.com/repository/R1/#r-stack-ppop
void
R_Stack_pop
  (
    Arcadia_Process* process,
    R_Stack* self
  );

// https://michaelheilmann.com/repository/R1/#r-stack-peek
R_Value
R_Stack_peek
  (
    Arcadia_Process* process,
    R_Stack* self
  );

// https://michaelheilmann.com/repository/R1/#r-stack-isempty
static inline Arcadia_BooleanValue R_Stack_isEmpty(R_Stack* self) {
  return Arcadia_SizeValue_Literal(0) == R_Stack_getSize(self);
}

#define Define(Type, Suffix, Variable) \
  void \
  R_Stack_push##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_Stack* self, \
      Type##Value variable##Value \
    ); \
\
  Arcadia_BooleanValue \
  R_Stack_is##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_Stack* self, \
      Arcadia_SizeValue index \
    ); \
\
  Type##Value \
  R_Stack_get##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_Stack* self, \
      Arcadia_SizeValue index \
    );

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_ForeignProcedure, ForeignProcedure, foreignProcedure)
Define(Arcadia_Integer8, Integer8, integer8)
Define(Arcadia_Integer16, Integer16, integer16)
Define(Arcadia_Integer32, Integer32, integer32)
Define(Arcadia_Integer64, Intege64, integer64)
Define(Arcadia_Natural8, Natural8, natural8)
Define(Arcadia_Natural16, Natural16, natural16)
Define(Arcadia_Natural32, Natural32, natural32)
Define(Arcadia_Natural64, Natural64, natural64)
Define(R_ObjectReference, ObjectReference, objectReference)
Define(Arcadia_Size, Size, size)
Define(Arcadia_Void, Void, void)

#undef Define

#endif // R_STACK_H_INCLUDED
