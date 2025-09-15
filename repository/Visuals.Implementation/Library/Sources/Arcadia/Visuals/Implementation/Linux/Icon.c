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

#include "Arcadia/Visuals/Implementation/Linux/Icon.h"

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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.Icon", Arcadia_Visuals_Linux_Icon,
                         u8"Arcadia.Visuals.Icon", Arcadia_Visuals_Icon,
                         &_typeOperations);

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
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }

  if (Arcadia_ValueStack_getSize(thread) < 1 || 6 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Imaging_PixelBuffer* pixelBuffer = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Imaging_PixelBuffer_getType(thread));
  pixelBuffer = Arcadia_Imaging_PixelBuffer_createClone(thread, pixelBuffer);
  Arcadia_Imaging_PixelBuffer_setPixelFormat(thread, pixelBuffer, Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8);
  
  Arcadia_Natural32Value dummy, numberOfPixels, numberOfBytes;
  if (!Arcadia_safeMultiplyNatural32Value(thread, (Arcadia_Natural32Value)Arcadia_Imaging_PixelBuffer_getWidth(thread, pixelBuffer),
                                                  (Arcadia_Natural32Value)Arcadia_Imaging_PixelBuffer_getHeight(thread, pixelBuffer), &dummy, &numberOfPixels)) {
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
  _self->width = Arcadia_Imaging_PixelBuffer_getWidth(thread, pixelBuffer);
  _self->height = Arcadia_Imaging_PixelBuffer_getHeight(thread, pixelBuffer);
  _self->bytes = Arcadia_Memory_allocateUnmanaged(thread, numberOfBytes);
  _self->bytes[0] = (Arcadia_Natural32Value)_self->width;
  _self->bytes[1] = (Arcadia_Natural32Value)_self->height;
  unsigned long* p = &_self->bytes[2];
  for (Arcadia_SizeValue y = 0; y < _self->height; ++y) {
    for (Arcadia_SizeValue x = 0; x < _self->width; ++x) {
      Arcadia_Natural8Value red, green, blue, alpha;
      Arcadia_Imaging_PixelBuffer_getPixelRgba(thread, pixelBuffer, x, y, &red, &green, &blue, &alpha);
      *p++ = alpha << 24
           | blue << 16
           | green << 8
           | red << 0;
    }
  }
  Arcadia_Object_setType(thread, _self, _type);
  Arcadia_ValueStack_popValues(thread, 5 + 1);
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
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  )
{ 
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, pixelBuffer);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Linux_Icon);
}
