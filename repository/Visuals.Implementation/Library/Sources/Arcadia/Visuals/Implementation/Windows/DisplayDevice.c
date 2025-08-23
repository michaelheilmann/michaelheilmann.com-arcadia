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

#include "Arcadia/Visuals/Implementation/Windows/DisplayDevice.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Windows/DisplayMode.h"

static void
Arcadia_Visuals_Windows_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Windows_DisplayDevice_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  );

static Arcadia_Visuals_Windows_DisplayMode*
Arcadia_Visuals_Windows_DisplayDevice_getCurrentDisplayModeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  );

static Arcadia_List*
Arcadia_Visuals_Windows_DisplayDevice_getAvailableDisplayModesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  );

static Arcadia_String*
Arcadia_Visuals_Windows_DisplayDevice_getIdImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  );

static Arcadia_String*
Arcadia_Visuals_Windows_DisplayDevice_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  );

static void
Arcadia_Visuals_Windows_DisplayDevice_getBoundsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_DisplayDevice_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Windows_DisplayDevice_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.DisplayDevice", Arcadia_Visuals_Windows_DisplayDevice,
                         u8"Arcadia.Visuals.DisplayDevice", Arcadia_Visuals_DisplayDevice,
                         &_typeOperations);

static void
Arcadia_Visuals_Windows_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_DisplayDevice* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_DisplayDevice_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->id = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  _self->adapter = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  _self->monitor = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[2], _Arcadia_String_getType(thread));
  _self->availableDisplayModes = NULL;
  _self->currentDisplayMode = NULL;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getCurrentDisplayMode = (Arcadia_Visuals_DisplayMode * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Windows_DisplayDevice_getCurrentDisplayModeImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getAvailableDisplayModes = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Windows_DisplayDevice_getAvailableDisplayModesImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getId = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Windows_DisplayDevice_getIdImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Windows_DisplayDevice_getNameImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getBounds = (void (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & Arcadia_Visuals_Windows_DisplayDevice_getBoundsImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Visuals_Windows_DisplayDevice_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  )
{
  if (self->id) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->id);
  }
  if (self->adapter) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->adapter);
  }
  if (self->monitor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->monitor);
  }
  if (self->currentDisplayMode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->currentDisplayMode);
  }
  if (self->availableDisplayModes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->availableDisplayModes);
  }
}

static Arcadia_Visuals_Windows_DisplayMode*
Arcadia_Visuals_Windows_DisplayDevice_getCurrentDisplayModeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  )
{
  if (!self->currentDisplayMode) {
    Arcadia_StringBuffer* deviceModeName = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBack(thread, deviceModeName, Arcadia_Value_makeObjectReferenceValue(self->id));
    Arcadia_Natural32Value zeroTerminator = 0x0;
    Arcadia_StringBuffer_insertCodePointsBack(thread, deviceModeName, &zeroTerminator, 1);

    DEVMODEA devMode = { 0 };
    if (!EnumDisplaySettingsA(deviceModeName->elements, ENUM_CURRENT_SETTINGS, &devMode)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (0 == (devMode.dmFields & DM_PELSWIDTH)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (0 == (devMode.dmFields & DM_PELSHEIGHT)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (0 == (devMode.dmFields & DM_BITSPERPEL)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    if (0 == (devMode.dmFields & DM_DISPLAYFREQUENCY)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    self->currentDisplayMode =
      Arcadia_Visuals_Windows_DisplayMode_create
        (
          thread,
          self,
          devMode.dmPelsWidth,
          devMode.dmPelsHeight,
          devMode.dmBitsPerPel,
          devMode.dmDisplayFrequency
        );
  }
  return self->currentDisplayMode;
}

static Arcadia_List*
Arcadia_Visuals_Windows_DisplayDevice_getAvailableDisplayModesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  )
{
  if (!self->availableDisplayModes) {
    Arcadia_List* availableDisplayModes = (Arcadia_List*)Arcadia_ArrayList_create(thread);

    Arcadia_StringBuffer* deviceModeName = Arcadia_StringBuffer_create(thread);
    Arcadia_StringBuffer_insertBack(thread, deviceModeName, Arcadia_Value_makeObjectReferenceValue(self->id));
    Arcadia_Natural32Value zeroTerminator = 0x0;
    Arcadia_StringBuffer_insertCodePointsBack(thread, deviceModeName, &zeroTerminator, 1);

    DWORD iModeNum = 0;
    while (true) {
      DEVMODEA devMode = { 0 };
      if (!EnumDisplaySettingsA(deviceModeName->elements, iModeNum, &devMode)) {
        break;
      }
      iModeNum++;
      if (0 == (devMode.dmFields & DM_PELSWIDTH)) {
        continue;
      }
      if (0 == (devMode.dmFields & DM_PELSHEIGHT)) {
        continue;
      }
      if (0 == (devMode.dmFields & DM_BITSPERPEL)) {
        continue;
      }
      if (0 == (devMode.dmFields & DM_DISPLAYFREQUENCY)) {
        continue;
      }
      Arcadia_Visuals_Windows_DisplayMode* displayMode =
        Arcadia_Visuals_Windows_DisplayMode_create
          (
            thread,
            self,
            devMode.dmPelsWidth,
            devMode.dmPelsHeight,
            devMode.dmBitsPerPel,
            devMode.dmDisplayFrequency
          );
      Arcadia_List_insertBackObjectReferenceValue(thread, availableDisplayModes, (Arcadia_ObjectReferenceValue)displayMode);
      iModeNum++;
      self->availableDisplayModes = availableDisplayModes;
    }
  }
  Arcadia_List * availableDisplayModes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0; i < Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->availableDisplayModes); ++i) {
    Arcadia_List_insertBack(thread, availableDisplayModes, Arcadia_List_getAt(thread, self->availableDisplayModes, i));
  }
  return availableDisplayModes;
}

static Arcadia_String*
Arcadia_Visuals_Windows_DisplayDevice_getIdImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  )
{ return self->id; }

static Arcadia_String*
Arcadia_Visuals_Windows_DisplayDevice_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self
  )
{
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(self->adapter));
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"/");
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(self->monitor));
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuffer));
}

static void
Arcadia_Visuals_Windows_DisplayDevice_getBoundsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  )
{
  *left = self->left;
  *top = self->top;
  *right = self->right;
  *bottom = self->bottom;
}

Arcadia_Visuals_Windows_DisplayDevice*
Arcadia_Visuals_Windows_DisplayDevice_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* id,
    Arcadia_String* adapter,
    Arcadia_String* monitor
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(id),
    Arcadia_Value_makeObjectReferenceValue(adapter),
    Arcadia_Value_makeObjectReferenceValue(monitor),
  };
  Arcadia_Visuals_Windows_DisplayDevice* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Windows_DisplayDevice_getType(thread), 3, &argumentValues[0]);
  return self;
}

