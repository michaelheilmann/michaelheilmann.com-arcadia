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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/WindowBackend.h"

static void
Arcadia_Visuals_WindowBackend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  );

static void
Arcadia_Visuals_WindowBackend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_WindowBackend_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_WindowBackend_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.WindowBackend", Arcadia_Visuals_WindowBackend,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_WindowBackend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_WindowBackend_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->title = Arcadia_String_createFromCxxString(thread, u8"Arcadia Engine Window");

  self->bounds.left = 0;
  self->bounds.top = 0;
  self->bounds.width = 1;
  self->bounds.height = 1;

  self->fullscreen = Arcadia_BooleanValue_False;

  self->window = NULL;

  self->open = NULL;
  self->close = NULL;
  self->update = NULL;

  self->getRequiredBigIconSize = NULL;
  self->getRequiredSmallIconSize = NULL;

  self->getBigIcon = NULL;
  self->setBigIcon = NULL;

  self->getSmallIcon = NULL;
  self->setSmallIcon = NULL;

  self->getTitle = NULL;
  self->setTitle  = NULL;

  self->getCanvasSize = NULL;

  self->beginRender = NULL;
  self->endRender = NULL;

  self->setPosition = NULL;
  self->getPosition = NULL;

  self->setSize = NULL;
  self->getSize = NULL;

  self->getFullscreen = NULL;
  self->setFullscreen = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_WindowBackend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{
  if (self->title) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->title);
  }
  if (self->window) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->window);
  }
}

void
Arcadia_Visuals_WindowBackend_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ self->open(thread, self); }

void
Arcadia_Visuals_WindowBackend_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ self->close(thread, self); }

void
Arcadia_Visuals_WindowBackend_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ self->update(thread, self); }

void
Arcadia_Visuals_WindowBackend_getRequiredBigIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getRequiredBigIconSize(thread, self, width, height); }

void
Arcadia_Visuals_WindowBackend_getRequiredSmallIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getRequiredSmallIconSize(thread, self, width, height); }

Arcadia_Visuals_Icon*
Arcadia_Visuals_WindowBackend_getBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ return self->getBigIcon(thread, self); }

void
Arcadia_Visuals_WindowBackend_setBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Visuals_Icon* icon
  )
{ self->setBigIcon(thread, self, icon); }

Arcadia_Visuals_Icon*
Arcadia_Visuals_WindowBackend_getSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ return self->getSmallIcon(thread, self); }

void
Arcadia_Visuals_WindowBackend_setSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Visuals_Icon* icon
  )
{ self->setSmallIcon(thread, self, icon); }

Arcadia_String*
Arcadia_Visuals_WindowBackend_getTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ return self->getTitle(thread, self); }

void
Arcadia_Visuals_WindowBackend_setTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_String* title
  )
{ self->setTitle(thread, self, title); }

void
Arcadia_Visuals_WindowBackend_getCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getCanvasSize(thread, self, width, height); }

void
Arcadia_Visuals_WindowBackend_beginRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ self->beginRender(thread, self); }

void
Arcadia_Visuals_WindowBackend_endRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ self->endRender(thread, self); }

void
Arcadia_Visuals_WindowBackend_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{ self->setPosition(thread, self, left, top); }

void
Arcadia_Visuals_WindowBackend_getPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{ self->getPosition(thread, self, left, top); }

void
Arcadia_Visuals_WindowBackend_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ self->setSize(thread, self, width, height); }

void
Arcadia_Visuals_WindowBackend_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getSize(thread, self, width, height); }

Arcadia_BooleanValue
Arcadia_Visuals_WindowBackend_getFullscreen
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self
  )
{ return self->getFullscreen(thread, self); }

void
Arcadia_Visuals_WindowBackend_setFullscreen
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_WindowBackend* self,
    Arcadia_BooleanValue fullscreen
  )
{ self->setFullscreen(thread, self, fullscreen); }
