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
#include "Arcadia/Media/PixelBufferOperation.h"

static void
Arcadia_Media_PixelBufferOperation_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperation* self
  );

static void
Arcadia_Media_PixelBufferOperation_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperationDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Media_PixelBufferOperation_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Media.PixelBufferOperation", Arcadia_Media_PixelBufferOperation,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Media_PixelBufferOperation_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperation* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Media_PixelBufferOperation);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_Media_PixelBufferOperation);
}

static void
Arcadia_Media_PixelBufferOperation_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperationDispatch* self
  )
{ }

void
Arcadia_Media_PixelBufferOperation_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Media_PixelBufferOperation* self,
    Arcadia_Media_PixelBuffer* target
  )
{ Arcadia_VirtualCall(Arcadia_Media_PixelBufferOperation, apply, self, target); }
