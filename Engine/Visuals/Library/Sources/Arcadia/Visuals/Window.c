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
#include "Arcadia/Visuals/Window.h"

static void
Arcadia_Visuals_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Window_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Window_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Window* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Window_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->backend = NULL;
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;
  _self->title = Arcadia_String_createFromCxxString(thread, u8"Arcadia Engine Window");
  _self->fullscreen = Arcadia_BooleanValue_False;
  _self->bounds.left = 0;
  _self->bounds.top = 0;
  _self->bounds.width = 1;
  _self->bounds.height = 1;

  _self->open = NULL;
  _self->close = NULL;

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

  _self->setPosition = NULL;
  _self->getPosition = NULL;

  _self->setSize = NULL;
  _self->getSize = NULL;

  _self->getFullscreen = NULL;
  _self->setFullscreen = NULL;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{
  if (self->title) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->title);
  }
  if (self->backend) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->backend);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->smallIcon);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->bigIcon);
  }
}

void
Arcadia_Visuals_Window_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{
  if (self->backend) {
    Arcadia_Visuals_WindowBackend_open(thread, self->backend);
    Arcadia_Visuals_WindowBackend_setFullscreen(thread, self->backend, self->fullscreen);
    Arcadia_Visuals_WindowBackend_setPosition(thread, self->backend, self->bounds.left, self->bounds.top);
    Arcadia_Visuals_WindowBackend_setSize(thread, self->backend, self->bounds.width, self->bounds.width);
    Arcadia_Visuals_WindowBackend_setTitle(thread, self->backend, self->title);
  }
}

void
Arcadia_Visuals_Window_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{
  if (self->backend) {
    Arcadia_Visuals_WindowBackend_close(thread, self->backend);
  }
}

void
Arcadia_Visuals_Window_getRequiredBigIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ Arcadia_Visuals_WindowBackend_getRequiredBigIconSize(thread, self->backend, width, height); }

void
Arcadia_Visuals_Window_getRequiredSmallIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ Arcadia_Visuals_WindowBackend_getRequiredSmallIconSize(thread, self->backend, width, height); }

Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return Arcadia_Visuals_WindowBackend_getBigIcon(thread, self->backend); }

void
Arcadia_Visuals_Window_setBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  )
{ Arcadia_Visuals_WindowBackend_setBigIcon(thread, self->backend, icon); }

Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return Arcadia_Visuals_WindowBackend_getSmallIcon(thread, self->backend); }

void
Arcadia_Visuals_Window_setSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  )
{ Arcadia_Visuals_WindowBackend_setSmallIcon(thread, self->backend, icon); }

Arcadia_String*
Arcadia_Visuals_Window_getTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return self->title; }

void
Arcadia_Visuals_Window_setTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_String* title
  )
{
  self->title = title;
  if (self->backend) {
    Arcadia_Visuals_WindowBackend_setTitle(thread, self->backend, title);
  }
}

void
Arcadia_Visuals_Window_getCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ Arcadia_Visuals_WindowBackend_getCanvasSize(thread, self->backend, width, height); }

void
Arcadia_Visuals_Window_beginRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ Arcadia_Visuals_WindowBackend_beginRender(thread, self->backend); }

void
Arcadia_Visuals_Window_endRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ Arcadia_Visuals_WindowBackend_endRender(thread, self->backend); }

void
Arcadia_Visuals_Window_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{
  self->bounds.left = left;
  self->bounds.top = top;
  if (self->backend) {
    Arcadia_Visuals_WindowBackend_setPosition(thread, self->backend, left, top);
  }
}

void
Arcadia_Visuals_Window_getPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{
  *left = self->bounds.left;
  *top = self->bounds.top;
}

void
Arcadia_Visuals_Window_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  self->bounds.width = width;
  self->bounds.height = height;
  if (self->backend) {
    Arcadia_Visuals_WindowBackend_setSize(thread, self->backend, width, height);
  }
}

void
Arcadia_Visuals_Window_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = self->bounds.width;
  *height = self->bounds.height;
}

Arcadia_BooleanValue
Arcadia_Visuals_Window_getFullscreen
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{
  return self->fullscreen;
}

void
Arcadia_Visuals_Window_setFullscreen
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_BooleanValue fullscreen
  )
{
  self->fullscreen = fullscreen;
  if (self->backend) {
    Arcadia_Visuals_WindowBackend_setFullscreen(thread, self->backend, fullscreen);
  }
}

Arcadia_Visuals_Window*
Arcadia_Visuals_Window_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Window);
}
