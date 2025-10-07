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

#include "Arcadia/Visuals/Implementation/Windows/DisplayMode.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Windows/DisplayDevice.h"

static void
Arcadia_Visuals_Windows_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static void
Arcadia_Visuals_Windows_DisplayMode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getHorizontalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getVerticalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getColorDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getFrequencyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static void
Arcadia_Visuals_Windows_DisplayMode_applyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Windows_DisplayMode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Windows_DisplayMode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.DisplayMode", Arcadia_Visuals_Windows_DisplayMode,
                         u8"Arcadia.Visuals.DisplayMode", Arcadia_Visuals_DisplayMode,
                         &_typeOperations);

static void
Arcadia_Visuals_Windows_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_DisplayMode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (5 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->device = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 5, _Arcadia_Visuals_Windows_DisplayDevice_getType(thread));
  self->horizontalResolution = Arcadia_ValueStack_getInteger32Value(thread, 4);
  self->verticalResolution = Arcadia_ValueStack_getInteger32Value(thread, 3);
  self->colorDepth = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->frequency = Arcadia_ValueStack_getInteger32Value(thread, 1);

  ((Arcadia_Visuals_DisplayMode*)self)->getHorizontalResolution = (Arcadia_Integer32Value(*)(Arcadia_Thread*,Arcadia_Visuals_DisplayMode*)) & Arcadia_Visuals_Windows_DisplayMode_getHorizontalResolutionImpl;
  ((Arcadia_Visuals_DisplayMode*)self)->getVerticalResolution = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Windows_DisplayMode_getVerticalResolutionImpl;
  ((Arcadia_Visuals_DisplayMode*)self)->getColorDepth = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Windows_DisplayMode_getColorDepthImpl;
  ((Arcadia_Visuals_DisplayMode*)self)->getFrequency = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Windows_DisplayMode_getFrequencyImpl;
  ((Arcadia_Visuals_DisplayMode*)self)->apply = (void(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) & Arcadia_Visuals_Windows_DisplayMode_applyImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Windows_DisplayMode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{
  if (self->device) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->device);
  }
}

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getHorizontalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{ return self->horizontalResolution; }

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getVerticalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{ return self->verticalResolution; }

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getColorDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{ return self->colorDepth; }

static Arcadia_Integer32Value
Arcadia_Visuals_Windows_DisplayMode_getFrequencyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{ return self->frequency; }

static void
Arcadia_Visuals_Windows_DisplayMode_applyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayMode* self
  )
{
  Arcadia_StringBuffer* deviceName = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBack(thread, deviceName, Arcadia_Value_makeObjectReferenceValue(self->device->id));
  Arcadia_Natural32Value zeroTerminator = 0x0;
  Arcadia_StringBuffer_insertCodePointsBack(thread, deviceName, &zeroTerminator, 1);
  // Find the corresponding display mode.
  DWORD iModeNum = 0;
  while (true) {
    DEVMODEA devMode = { 0 };
    if (!EnumDisplaySettingsA(deviceName->elements, iModeNum, &devMode)) {
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
    if (devMode.dmBitsPerPel == self->colorDepth &&
        devMode.dmPelsWidth == self->horizontalResolution &&
        devMode.dmPelsHeight == self->verticalResolution &&
        devMode.dmDisplayFrequency == self->frequency) {
      // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-changedisplaysettingsexa
      LONG lResult = ChangeDisplaySettingsExA(deviceName->elements, &devMode, NULL, CDS_FULLSCREEN, NULL);
      switch (lResult) {
        case DISP_CHANGE_SUCCESSFUL: {

        } break;
        case DISP_CHANGE_BADDUALVIEW: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        case DISP_CHANGE_BADFLAGS: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        case DISP_CHANGE_BADMODE: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        case DISP_CHANGE_BADPARAM: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        case DISP_CHANGE_FAILED: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        case DISP_CHANGE_NOTUPDATED: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        case DISP_CHANGE_RESTART: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
          Arcadia_Thread_jump(thread);
        } break;
      };
    }
  }
}

Arcadia_Visuals_Windows_DisplayMode*
Arcadia_Visuals_Windows_DisplayMode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* device,
    Arcadia_Integer32Value horizontalResolution,
    Arcadia_Integer32Value verticalResolution,
    Arcadia_Integer32Value colorDepth,
    Arcadia_Integer32Value frequency
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (device) { Arcadia_ValueStack_pushObjectReferenceValue(thread, device); } else { Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void); }
  Arcadia_ValueStack_pushInteger32Value(thread, horizontalResolution);
  Arcadia_ValueStack_pushInteger32Value(thread, verticalResolution);
  Arcadia_ValueStack_pushInteger32Value(thread, colorDepth);
  Arcadia_ValueStack_pushInteger32Value(thread, frequency);
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Windows_DisplayMode);
}
