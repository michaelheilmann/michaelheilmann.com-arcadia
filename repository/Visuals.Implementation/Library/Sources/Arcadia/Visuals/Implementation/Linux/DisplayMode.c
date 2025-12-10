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

#include "Arcadia/Visuals/Implementation/Linux/DisplayMode.h"

#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/BackendContext.h"
#include "Arcadia/Visuals/Implementation/Linux/DisplayDevice.h"
#include <stdio.h> // @todo Remove references to `stdio.h`.

static void
Arcadia_Visuals_Linux_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static void
Arcadia_Visuals_Linux_DisplayMode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayModeDispatch* self
  );

static void
Arcadia_Visuals_Linux_DisplayMode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getHorizontalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getVerticalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getColorDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getFrequencyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static void
Arcadia_Visuals_Linux_DisplayMode_applyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_DisplayMode_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Linux_DisplayMode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.DisplayMode", Arcadia_Visuals_Linux_DisplayMode,
                         u8"Arcadia.Visuals.DisplayMode", Arcadia_Visuals_DisplayMode,
                         &_typeOperations);

static void
Arcadia_Visuals_Linux_DisplayMode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_DisplayMode_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 5 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->device = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 5, _Arcadia_Visuals_Linux_DisplayDevice_getType(thread));
  self->horizontalResolution = Arcadia_ValueStack_getInteger32Value(thread, 4);
  self->verticalResolution = Arcadia_ValueStack_getInteger32Value(thread, 3);
  self->colorDepth = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->frequency = Arcadia_ValueStack_getInteger32Value(thread, 1);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 5 + 1);
}

static void
Arcadia_Visuals_Linux_DisplayMode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayModeDispatch* self
  )
{
  ((Arcadia_Visuals_DisplayModeDispatch*)self)->getHorizontalResolution = (Arcadia_Integer32Value(*)(Arcadia_Thread*,Arcadia_Visuals_DisplayMode*)) & Arcadia_Visuals_Linux_DisplayMode_getHorizontalResolutionImpl;
  ((Arcadia_Visuals_DisplayModeDispatch*)self)->getVerticalResolution = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Linux_DisplayMode_getVerticalResolutionImpl;
  ((Arcadia_Visuals_DisplayModeDispatch*)self)->getColorDepth = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Linux_DisplayMode_getColorDepthImpl;
  ((Arcadia_Visuals_DisplayModeDispatch*)self)->getFrequency = (Arcadia_Integer32Value(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) &Arcadia_Visuals_Linux_DisplayMode_getFrequencyImpl;
  ((Arcadia_Visuals_DisplayModeDispatch*)self)->apply = (void(*)(Arcadia_Thread*, Arcadia_Visuals_DisplayMode*)) & Arcadia_Visuals_Linux_DisplayMode_applyImpl;
}

static void
Arcadia_Visuals_Linux_DisplayMode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{
  if (self->device) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->device);
  }
}

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getHorizontalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->horizontalResolution; }

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getVerticalResolutionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->verticalResolution; }

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getColorDepthImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->colorDepth; }

static Arcadia_Integer32Value
Arcadia_Visuals_Linux_DisplayMode_getFrequencyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{ return self->frequency; }

static void
Arcadia_Visuals_Linux_DisplayMode_applyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayMode* self
  )
{
  Arcadia_StringBuffer* log = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBackCxxString(thread, log, __FILE__);
  Arcadia_StringBuffer_insertBackCxxString(thread, log, u8":");
  Arcadia_StringBuffer_insertBackCxxInt(thread, log, __LINE__);
  Arcadia_StringBuffer_insertBackCxxString(thread, log, u8": setting mode for display ");
  Arcadia_StringBuffer_insertBackString(thread, log, self->device->name);
  Arcadia_StringBuffer_insertBackCxxString(thread, log, u8" \n");
  fwrite(Arcadia_StringBuffer_getBytes(thread, log), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, log), stdout);

  int defaultScreen;
  Window rootWindow;
  XRRScreenResources* screenResources = NULL;;
  XRROutputInfo *outputInfo = NULL;
  XRRCrtcInfo* crtcInfo = NULL;

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    rootWindow = XDefaultRootWindow(self->device->backendContext->display);
    defaultScreen = DefaultScreen(self->device->backendContext->display);
    screenResources = XRRGetScreenResources(self->device->backendContext->display, rootWindow);
    if (!screenResources) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    outputInfo = XRRGetOutputInfo(self->device->backendContext->display, screenResources, self->device->output);
    if (!screenResources) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    crtcInfo = XRRGetCrtcInfo(self->device->backendContext->display, screenResources, outputInfo->crtc);
    if (!crtcInfo) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }

    if (self->modeId != crtcInfo->mode) {
      Status status;
      XGrabServer(self->device->backendContext->display);
      status = XRRSetCrtcConfig(self->device->backendContext->display, screenResources, outputInfo->crtc,
                                CurrentTime, 0, 0, None, crtcInfo->rotation, NULL, 0);
      if (status != Success) {
        XUngrabServer(self->device->backendContext->display);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      int mm_width = self->horizontalResolution * DisplayWidthMM(self->device->backendContext->display, defaultScreen)
                   / DisplayWidth(self->device->backendContext->display, defaultScreen);
      int mm_height = self->verticalResolution * DisplayHeightMM(self->device->backendContext->display, defaultScreen)
                    / DisplayHeight(self->device->backendContext->display, defaultScreen);

      XSync(self->device->backendContext->display, False);

      XRRSetScreenSize(self->device->backendContext->display, rootWindow,
                       self->horizontalResolution, self->verticalResolution,
                       mm_width, mm_height);

      XSync(self->device->backendContext->display, False);

      status = XRRSetCrtcConfig(self->device->backendContext->display, screenResources, outputInfo->crtc, CurrentTime,
                                crtcInfo->x, crtcInfo->y, self->modeId, crtcInfo->rotation, &self->device->output, 1);
      XUngrabServer(self->device->backendContext->display);
      if (status != Success) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
    }

    Arcadia_Visuals_Linux_DisplayDevice_updateBounds(thread, self->device);

    XRRFreeCrtcInfo(crtcInfo);
    crtcInfo = NULL;
    XRRFreeOutputInfo(outputInfo);
    outputInfo = NULL;
    XRRFreeScreenResources(screenResources);
    screenResources = NULL;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (crtcInfo) {
      XRRFreeCrtcInfo(crtcInfo);
      crtcInfo = NULL;
    }
    if (outputInfo) {
      XRRFreeOutputInfo(outputInfo);
      outputInfo = NULL;
    }
    if (screenResources) {
      XRRFreeScreenResources(screenResources);
      screenResources = NULL;
    }
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
  }
}

Arcadia_Visuals_Linux_DisplayMode*
Arcadia_Visuals_Linux_DisplayMode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* device,
    Arcadia_Integer32Value horizontalResolution,
    Arcadia_Integer32Value verticalResolution,
    Arcadia_Integer32Value colorDepth,
    Arcadia_Integer32Value frequency
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (device) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, device);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushInteger32Value(thread, horizontalResolution),
  Arcadia_ValueStack_pushInteger32Value(thread, verticalResolution),
  Arcadia_ValueStack_pushInteger32Value(thread, colorDepth),
  Arcadia_ValueStack_pushInteger32Value(thread, frequency),
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Linux_DisplayMode);
}
