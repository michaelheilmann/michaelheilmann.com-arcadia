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

#include "Module/Visuals/Linux/Icon.h"

static void
Arcadia_Visuals_Linux_Icon_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Linux_Icon_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Icon* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_Icon_constructImpl,
  .destruct = &Arcadia_Visuals_Linux_Icon_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.Icon", Arcadia_Visuals_Linux_Icon, u8"Arcadia.Visuals.Icon", Arcadia_Visuals_Icon, &_typeOperations);

static void
Arcadia_Visuals_Linux_Icon_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_Icon* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_Icon_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }

  if (6 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  if (!Arcadia_Value_isInteger32Value(&argumentValues[0])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer32Value width = Arcadia_Value_getInteger32Value(&argumentValues[0]);
  if (width < 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }

  if (!Arcadia_Value_isInteger32Value(&argumentValues[1])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer32Value height = Arcadia_Value_getInteger32Value(&argumentValues[1]);
  if (height < 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }

  if (!Arcadia_Value_isNatural8Value(&argumentValues[2])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value red = Arcadia_Value_getNatural8Value(&argumentValues[2]);

  if (!Arcadia_Value_isNatural8Value(&argumentValues[3])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value green = Arcadia_Value_getNatural8Value(&argumentValues[3]);

  if (!Arcadia_Value_isNatural8Value(&argumentValues[4])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value blue = Arcadia_Value_getNatural8Value(&argumentValues[4]);

  if (!Arcadia_Value_isNatural8Value(&argumentValues[5])) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value alpha = Arcadia_Value_getNatural8Value(&argumentValues[5]);

  Arcadia_Natural32Value dummy, numberOfPixels, numberOfBytes;
  if (!Arcadia_safeMultiplyNatural32Value(thread, (Arcadia_Natural32Value)width, (Arcadia_Natural32Value)height, &dummy, &numberOfPixels)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (Arcadia_Natural32Value_Maximum - 2 < numberOfPixels) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_safeMultiplyNatural32Value(thread, numberOfPixels + 2, sizeof(unsigned long), &dummy, &numberOfBytes)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->numberOfBytes = numberOfBytes;
  _self->width = width;
  _self->height = height;
  _self->bytes = Arcadia_Memory_allocateUnmanaged(thread, numberOfBytes);
  _self->bytes[0] = (Arcadia_Natural32Value)width;
  _self->bytes[1] = (Arcadia_Natural32Value)height;
  unsigned long* p = &_self->bytes[2];
  for (Arcadia_SizeValue i = 0; i < width * height; ++i) {
    *p++ = alpha << 24
         | blue << 16
         | green << 8
         | red << 0;
  }
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Visuals_Linux_Icon_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Icon* self
  )
{
  if (self->bytes) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->bytes);
    self->bytes = NULL;
  }
}

Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Linux_Icon_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeInteger32Value(width),
    Arcadia_Value_makeInteger32Value(height),
    Arcadia_Value_makeNatural8Value(red),
    Arcadia_Value_makeNatural8Value(green),
    Arcadia_Value_makeNatural8Value(blue),
    Arcadia_Value_makeNatural8Value(alpha),
  };
  Arcadia_Visuals_Linux_Icon* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_Icon_getType(thread), 6, &argumentValues[0]);
  return self;
}
