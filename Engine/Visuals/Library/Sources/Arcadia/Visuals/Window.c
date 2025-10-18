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
    Arcadia_Visuals_Window* self
  );

static void
Arcadia_Visuals_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

static void
Arcadia_Visuals_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Window_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Window_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Window_visit,
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
    Arcadia_Visuals_Window* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Window_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->backend = NULL;
  self->bigIcon = NULL;
  self->smallIcon = NULL;
  self->title = Arcadia_String_createFromCxxString(thread, u8"Arcadia Engine Window");
  self->fullscreen = Arcadia_BooleanValue_False;
  self->bounds.left = 0;
  self->bounds.top = 0;
  self->bounds.width = 1;
  self->bounds.height = 1;

  self->open = NULL;
  self->close = NULL;

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
Arcadia_Visuals_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{}

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
    Arcadia_Visuals_WindowBackend_setSize(thread, self->backend, self->bounds.width, self->bounds.height);
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
{ 
  if (!self->backend) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotImplemented);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Visuals_WindowBackend_getCanvasSize(thread, self->backend, width, height);
}

void
Arcadia_Visuals_Window_beginRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{
  if (!self->backend) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotImplemented);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Visuals_WindowBackend_beginRender(thread, self->backend);
}

void
Arcadia_Visuals_Window_endRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{
  if (!self->backend) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotImplemented);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Visuals_WindowBackend_endRender(thread, self->backend);
}

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
