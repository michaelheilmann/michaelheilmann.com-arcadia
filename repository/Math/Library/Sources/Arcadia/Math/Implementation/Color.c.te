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
#include "Arcadia/Math/Implementation/Color@{numberOfComponents}@{componentSuffix}.h"

Arcadia_StaticAssert(@{minimumComponentValue} <= @{maximumComponentValue}, "minimum component value must be smaller than or equal to the maximum component value");

static void
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Math.Color@{numberOfComponents}@{componentSuffix}", Arcadia_Math_Color@{numberOfComponents}@{componentSuffix},
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}*
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Math_Color@{numberOfComponents}@{componentSuffix});
}

Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}*
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_createWithValues
  (
    Arcadia_Thread* thread,
    @{componentType} const* values
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  for (Arcadia_SizeValue i = 0, n = @{numberOfComponents}; i < n; ++i) {
    Arcadia_ValueStack_push@{componentSuffix}Value(thread, values[i]);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, @{numberOfComponents});
  ARCADIA_CREATEOBJECT(Arcadia_Math_Color@{numberOfComponents}@{componentSuffix});
}

static void
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0; i < @{numberOfComponents}; ++i) {
    self->components[i] = @{minimumComponentValue};
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_assign
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* self,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* other
  )
{
  if (self != other) {
    for (Arcadia_SizeValue i = 0; i < @{numberOfComponents}; ++i) {
      self->components[i] = other->components[i];
    }
  }
}

void
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_invert
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* self,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{numberOfComponents}; ++i) {
    self->components[i] = @{maximumComponentValue} - self->components[i];
  }
}

void
Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}_add
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* self,
    Arcadia_Math_Color@{numberOfComponents}@{componentSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{numberOfComponents}; ++i) {
    if (self->components[i] > @{maximumComponentValue}) {
      self->components[i] = @{maximumComponentValue};
    }
  }
}
