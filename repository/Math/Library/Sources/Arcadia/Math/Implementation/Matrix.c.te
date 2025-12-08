// The author of this software is Michael Heilmann (contact@@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@@michaelheilmann.com).
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

#define ARCADIA_MATH_PRIVATE (1)
#include "Arcadia/Math/Implementation/Matrix@{dimensionality}@{scalarSuffix}.h"

static void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Math.Matrix@{dimensionality}@{scalarSuffix}", Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix},
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}*
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix});
}

Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}*
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_createWithValues
  (
    Arcadia_Thread* thread,
    @{scalarType} const* values
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  for (Arcadia_SizeValue i = 0, n = @{dimensionality} * @{dimensionality}; i < n; ++i) {
    Arcadia_ValueStack_push@{scalarSuffix}Value(thread, values[i]);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, @{dimensionality} * @{dimensionality});
  ARCADIA_CREATEOBJECT(Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix});
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_setIdentity
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self
  )
{
  Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_setZero(thread, self);
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    self->elements[i][i] = @{oneScalarLiteral};
  }
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_setZero
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
      self->elements[i][j] = @{zeroScalarLiteral};
    }
  }
}

static void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
      self->elements[i][j] = @{zeroScalarLiteral};
    }
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_assign
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  )
{
  if (self != other) {
    for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
      for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
        self->elements[i][j] = other->elements[i][j];
      }
    }
  }
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_additiveInverse
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
      self->elements[i][j] = -other->elements[i][j];
    }
  }
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_add
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
      self->elements[i][j] += other->elements[i][j];
    }
  }
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
      self->elements[i][j] -= other->elements[i][j];
    }
  }
}

void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other,
    @{scalarType} t
  )
{
  if (t == @{zeroScalarLiteral}) {
    /* Intentionally empty. */
  } else if (t == @{oneScalarLiteral}) {
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_assign(thread, self, other);
  } else {
    @{scalarType} s = @{oneScalarLiteral} - t;
    for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
      for (Arcadia_SizeValue j = 0; j < @{dimensionality}; ++j) {
        self->elements[i][j] = s * self->elements[i][j] + t * self->elements[i][j];
      }
    }
  }
}
