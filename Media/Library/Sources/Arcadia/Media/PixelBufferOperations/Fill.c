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

#define ARCADIA_MEDIA_PRIVATE (1)
#include "Arcadia/Media/PixelBufferOperations/Fill.h"

static void
Arcadia_Media_PixelBufferOperations_Fill_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_Fill* self
  );

static void
Arcadia_Media_PixelBufferOperations_Fill_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_FillDispatch* self
  );

static void
Arcadia_Media_PixelBufferOperations_Fill_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_Fill* self
  );

static void
Arcadia_Media_PixelBufferOperations_Fill_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_Fill* self,
    Arcadia_Media_PixelBuffer* target
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Media_PixelBufferOperations_Fill_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Media_PixelBufferOperations_Fill_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Media.PixelBufferOperations.Fill", Arcadia_Media_PixelBufferOperations_Fill,
                         u8"Arcadia.Media.PixelBufferOperation", Arcadia_Media_PixelBufferOperation,
                         &_typeOperations);

static void
Arcadia_Media_PixelBufferOperations_Fill_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_Fill* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Media_PixelBufferOperations_Fill_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->definition = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_PixelBufferOperations_FillOperationDefinition_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_Media_PixelBufferOperations_Fill_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_FillDispatch* self
  )
{
  ((Arcadia_Media_PixelBufferOperationDispatch*)self)->apply = (void (*)(Arcadia_Thread*, Arcadia_Media_PixelBufferOperation*, Arcadia_Media_PixelBuffer*)) & Arcadia_Media_PixelBufferOperations_Fill_apply;
}

static void
Arcadia_Media_PixelBufferOperations_Fill_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_Fill* self
  )
{
  if (self->definition) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definition);
  }
}

static void
Arcadia_Media_PixelBufferOperations_Fill_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperations_Fill* self,
    Arcadia_Media_PixelBuffer* target
  )
{
  if (NULL == self->definition->color->definition) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ADL_ColorDefinition* color = (Arcadia_ADL_ColorDefinition*)self->definition->color->definition;
  Arcadia_Natural8Value red = color->red;
  Arcadia_Natural8Value green = color->green;
  Arcadia_Natural8Value blue = color->blue;
  Arcadia_Media_PixelBuffer_fillRectangle(thread, target, 0, 0, target->width, target->height, red, green, blue, 255);
}

Arcadia_Media_PixelBufferOperations_Fill*
Arcadia_Media_PixelBufferOperations_Fill_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_PixelBufferOperations_FillOperationDefinition* definition
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (definition) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definition);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Media_PixelBufferOperations_Fill);
}
