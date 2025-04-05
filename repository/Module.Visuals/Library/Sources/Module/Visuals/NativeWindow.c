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

// Last modified: 2024-12-31

#include "Module/Visuals/NativeWindow.h"

static void
NativeWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeWindow_constructImpl,
  .destruct = NULL,
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

Arcadia_defineObjectType(u8"NativeWindow", NativeWindow, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
NativeWindow_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  NativeWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _NativeWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->open = NULL;
  _self->close = NULL;
  _self->getQuitRequested = NULL;
  _self->setQuitRequested = NULL;
  _self->update = NULL;
  _self->getRequiredBigIconSize = NULL;
  _self->getRequiredSmallIconSize = NULL;
  _self->getBigIcon = NULL;
  _self->setBigIcon = NULL;
  _self->getSmallIcon = NULL;
  _self->setSmallIcon = NULL;
  _self->getTitle = NULL;
  _self->setTitle  = NULL;
  _self->getCanvasSize = NULL;
  _self->beginRender = NULL;
  _self->endRender = NULL;
  Arcadia_Object_setType(thread, _self, _type);
}

void
NativeWindow_open
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ self->open(thread, self); }

void
NativeWindow_close
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  ) 
{ self->close(thread, self); }

Arcadia_BooleanValue
NativeWindow_getQuitRequested
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ return self->getQuitRequested(thread, self); }

void
NativeWindow_setQuitRequested
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  )
{ self->setQuitRequested(thread, self, quitRequested); }

void
NativeWindow_update
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ self->update(thread, self); }

void
NativeWindow_getRequiredBigIconSize
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getRequiredBigIconSize(thread, self, width, height); }

void
NativeWindow_getRequiredSmallIconSize
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getRequiredSmallIconSize(thread, self, width, height); }

NativeIcon*
NativeWindow_getBigIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ return self->getBigIcon(thread, self); }

void
NativeWindow_setBigIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    NativeIcon* icon
  )
{ self->setBigIcon(thread, self, icon); }

NativeIcon*
NativeWindow_getSmallIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ return self->getSmallIcon(thread, self); }

void
NativeWindow_setSmallIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    NativeIcon* icon
  )
{ self->setSmallIcon(thread, self, icon); }

Arcadia_String*
NativeWindow_getTitle
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ return self->getTitle(thread, self); }

void
NativeWindow_setTitle
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_String* title
  )
{ self->setTitle(thread, self, title); }

void
NativeWindow_getCanvasSize
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getCanvasSize(thread, self, width, height); }

void
NativeWindow_beginRender
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ self->beginRender(thread, self); }

void
NativeWindow_endRender
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  )
{ self->endRender(thread, self); }
