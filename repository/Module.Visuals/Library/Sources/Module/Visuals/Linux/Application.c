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

#include "Module/Visuals/Linux/Application.h"

#include "Module/Visuals/Linux/GlxDeviceInfo.h"
#include "Module/Visuals/Linux/Icon.h"
#include "Module/Visuals/Linux/Window.h"

static int
errorHandler
  (
    Display *display,
    XErrorEvent *event
  );

static Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Linux_Application_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

static Arcadia_Visuals_Linux_Window*
Arcadia_Visuals_Linux_Application_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static void
Arcadia_Visuals_Linux_Application_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  );

static void
Arcadia_Visuals_Linux_Application_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_Application_constructImpl,
  .destruct = &Arcadia_Visuals_Linux_Application_destruct,
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

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.Application", Arcadia_Visuals_Linux_Application, u8"Arcadia.Visuals.Application", Arcadia_Visuals_Application, &_typeOperations);

static Arcadia_Visuals_Linux_Icon*
Arcadia_Visuals_Linux_Application_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  )
{
  Arcadia_Visuals_Linux_Icon* icon = Arcadia_Visuals_Linux_Icon_create(thread, width, height, 47, 47, 47, 255);
  return icon;
}

static Arcadia_Visuals_Linux_Window*
Arcadia_Visuals_Linux_Application_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  Arcadia_Visuals_Linux_Window* window = Arcadia_Visuals_Linux_Window_create(thread, self);
  return window;
}

static void
Arcadia_Visuals_Linux_Application_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* self
  )
{
  if (self->display) {
    XCloseDisplay(self->display);
    self->display = NULL;
  }
  fprintf(stdout, "%s:%d: GLX application destroyed\n", __FILE__, __LINE__);
}

static void
Arcadia_Visuals_Linux_Application_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_Application* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_Application_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  
  // (1) Open the default display.
  _self->display = XOpenDisplay(NULL);
  if (!_self->display) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);   
  }
  
  // (2) Create WM_DELETE_WINDOW atom.
  _self->WM_DELETE_WINDOW = XInternAtom(_self->display, "WM_DELETE_WINDOW", False);
  if (_self->WM_DELETE_WINDOW == None) {
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  
  // (3) Create _NET_WM_ICON atom.
  _self->_NET_WM_ICON = XInternAtom(_self->display, "_NET_WM_ICON", False);
  if (_self->_NET_WM_ICON == None) {
    XCloseDisplay(_self->display);
    _self->display = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  
  ((Arcadia_Visuals_Application*)_self)->createIcon = (Arcadia_Visuals_Icon* (*)(Arcadia_Thread*, Arcadia_Visuals_Application*, Arcadia_Integer32Value, Arcadia_Integer32Value, Arcadia_Natural8Value, Arcadia_Natural8Value, Arcadia_Natural8Value, Arcadia_Natural8Value))&Arcadia_Visuals_Linux_Application_createIconImpl;
  ((Arcadia_Visuals_Application*)_self)->createWindow = (Arcadia_Visuals_Window* (*)(Arcadia_Thread*, Arcadia_Visuals_Application*))&Arcadia_Visuals_Linux_Application_createWindowImpl;
  Arcadia_Object_setType(thread, _self, _type);
}

Arcadia_Visuals_Linux_Application*
Arcadia_Visuals_Linux_Application_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Linux_Application* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_Application_getType(thread), 0, &argumentValues[0]);
  return self;
}
