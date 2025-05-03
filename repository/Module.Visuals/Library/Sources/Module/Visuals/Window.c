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

#include "Module/Visuals/Window.h"

static void
Arcadia_Visuals_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Window_constructImpl,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

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
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
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
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

void
Arcadia_Visuals_Window_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ self->open(thread, self); }

void
Arcadia_Visuals_Window_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  ) 
{ self->close(thread, self); }

Arcadia_BooleanValue
Arcadia_Visuals_Window_getQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return self->getQuitRequested(thread, self); }

void
Arcadia_Visuals_Window_setQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_BooleanValue quitRequested
  )
{ self->setQuitRequested(thread, self, quitRequested); }

void
Arcadia_Visuals_Window_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ self->update(thread, self); }

void
Arcadia_Visuals_Window_getRequiredBigIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getRequiredBigIconSize(thread, self, width, height); }

void
Arcadia_Visuals_Window_getRequiredSmallIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getRequiredSmallIconSize(thread, self, width, height); }

Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return self->getBigIcon(thread, self); }

void
Arcadia_Visuals_Window_setBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  )
{ self->setBigIcon(thread, self, icon); }

Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return self->getSmallIcon(thread, self); }

void
Arcadia_Visuals_Window_setSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  )
{ self->setSmallIcon(thread, self, icon); }

Arcadia_String*
Arcadia_Visuals_Window_getTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ return self->getTitle(thread, self); }

void
Arcadia_Visuals_Window_setTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_String* title
  )
{ self->setTitle(thread, self, title); }

void
Arcadia_Visuals_Window_getCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{ self->getCanvasSize(thread, self, width, height); }

void
Arcadia_Visuals_Window_beginRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ self->beginRender(thread, self); }

void
Arcadia_Visuals_Window_endRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  )
{ self->endRender(thread, self); }
