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

#include "Arcadia/Visuals/Linux/DisplayDevice.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Linux/DisplayMode.h"

static void
Arcadia_Visuals_Linux_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Linux_DisplayDevice_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static void
makeDisplayModes
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    XRRScreenResources* screenResources,
    XRROutputInfo* outputInfo,
    Arcadia_List* displayModes
  );

static Arcadia_List*
Arcadia_Visuals_Linux_DisplayDevice_getAvailableDisplayModesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getIdImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  );
  
static void
Arcadia_Visuals_Linux_DisplayDevice_getBoundsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Linux_DisplayDevice_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Linux_DisplayDevice_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Linux.DisplayDevice", Arcadia_Visuals_Linux_DisplayDevice,
                         u8"Arcadia.Visuals.DisplayDevice", Arcadia_Visuals_DisplayDevice,
                         &_typeOperations);

static void
Arcadia_Visuals_Linux_DisplayDevice_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Linux_DisplayDevice* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Linux_DisplayDevice_getType(thread);
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
  _self->application = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Visuals_Linux_Application_getType(thread));
  _self->id = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  _self->name = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[2], _Arcadia_String_getType(thread));
  _self->output = 0;
  _self->mode = 0;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getAvailableDisplayModes = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Linux_DisplayDevice_getAvailableDisplayModesImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getId = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Linux_DisplayDevice_getIdImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*)) & Arcadia_Visuals_Linux_DisplayDevice_getNameImpl;
  ((Arcadia_Visuals_DisplayDevice*)_self)->getBounds = (void (*)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & Arcadia_Visuals_Linux_DisplayDevice_getBoundsImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Visuals_Linux_DisplayDevice_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{
  if (self->application) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->application); 
  }
  if (self->id) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->id);  
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
}

static void
makeDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    XRRScreenResources* screenResources,
    RRCrtc crtc,
    RRMode modeId,
    Arcadia_List* displayModes
  )
{
  const XRRModeInfo* modeInfo = NULL;
  for (int i = 0; i < screenResources->nmode; ++i) {
    const XRRModeInfo* currentModeInfo = &(screenResources->modes[i]);
    if (currentModeInfo->id == modeId) {
      modeInfo = currentModeInfo;
      break;
    }
  }
  if (!modeInfo) {
    return;
  }
  Rotation rotation = 0;
  XFixed scaleWidth = 0x10000, scaleHeight = 0x10000;
  int width = 0, height = 0;
  int refreshRateNumerator, refreshRateDenominator;
  {
    XRRCrtcInfo* crtcInfo = XRRGetCrtcInfo(self->application->display, screenResources, crtc);
    if (crtcInfo) {
      rotation = crtcInfo->rotation;
      XRRFreeCrtcInfo(crtcInfo);
      crtcInfo = NULL;
    }
  }
  {
    XRRCrtcTransformAttributes *crtcTransformAttributes = NULL;
    if (XRRGetCrtcTransform(self->application->display, crtc, &crtcTransformAttributes) && crtcTransformAttributes) {
      scaleWidth = crtcTransformAttributes->currentTransform.matrix[0][0];
      scaleHeight = crtcTransformAttributes->currentTransform.matrix[1][1];
      XFree(crtcTransformAttributes);
      crtcTransformAttributes = NULL;
    }
  }
  {
    static const int RR_RotationLeft = (1 << 1);
    static const int RR_RotationRight = (1 << 3);
    if (rotation & (RR_RotationLeft | RR_RotationRight)) {
      width = (modeInfo->height * scaleWidth + 0xffff) >> 16;
      height = (modeInfo->width * scaleHeight + 0xffff) >> 16;
    } else {
      width = (modeInfo->width * scaleWidth + 0xffff) >> 16;
      height = (modeInfo->height * scaleHeight + 0xffff) >> 16;
    }
  }
  {
    int vTotal = modeInfo->vTotal;
    if (modeInfo->modeFlags & RR_DoubleScan) {
      // "doublescan" doubles scan lines.
      vTotal *= 2;
    }
    if (modeInfo->modeFlags & RR_Interlace) {
      // "interlace" halfs scan lines.
      vTotal /= 2;
    }
    if (modeInfo->hTotal && vTotal) {
      refreshRateNumerator = modeInfo->dotClock;
      refreshRateDenominator = (modeInfo->hTotal * vTotal);
    } else {
      return; // Ignore that one.
    }
    Arcadia_Visuals_Linux_DisplayMode* displayMode =
      Arcadia_Visuals_Linux_DisplayMode_create
        (
          thread,
          self,
          width,
          height,
          0,
          refreshRateNumerator / refreshRateDenominator
        );
    displayMode->modeId = modeInfo->id;
    Arcadia_List_insertBackObjectReferenceValue(thread, displayModes, displayMode);
  }
}

static Arcadia_List*
Arcadia_Visuals_Linux_DisplayDevice_getAvailableDisplayModesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{
  Arcadia_List* displayModes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Window rootWindow = XDefaultRootWindow(self->application->display);
  XRRScreenResources* screenResources = XRRGetScreenResources(self->application->display, rootWindow);
  XRROutputInfo *outputInfo = XRRGetOutputInfo(self->application->display, screenResources, self->output);
  if (outputInfo && outputInfo->connection != RR_Disconnected) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      for (int i = 0; i < outputInfo->nmode; ++i) {
        makeDisplayMode(thread, self, screenResources, outputInfo->crtc, outputInfo->modes[i], displayModes);
      }
      XRRFreeOutputInfo(outputInfo);
      XRRFreeScreenResources(screenResources);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread); 
      XRRFreeOutputInfo(outputInfo);
      XRRFreeScreenResources(screenResources);
      Arcadia_Thread_jump(thread);
    }
  }
  return displayModes;
}

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getIdImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{ return self->id; }

static Arcadia_String*
Arcadia_Visuals_Linux_DisplayDevice_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self
  )
{ return self->name; }

static void
Arcadia_Visuals_Linux_DisplayDevice_getBoundsImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_DisplayDevice* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top,
    Arcadia_Integer32Value* right,
    Arcadia_Integer32Value* bottom
  )
{
  *left = self->bounds.left;
  *top = self->bounds.top;
  *right = self->bounds.right;
  *bottom = self->bounds.bottom;
}

Arcadia_Visuals_Linux_DisplayDevice*
Arcadia_Visuals_Linux_DisplayDevice_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* application,
    Arcadia_String* id,
    Arcadia_String* name
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(application),
    Arcadia_Value_makeObjectReferenceValue(id),
    Arcadia_Value_makeObjectReferenceValue(name),
  };
  Arcadia_Visuals_Linux_DisplayDevice* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Linux_DisplayDevice_getType(thread), 3, &argumentValues[0]);
  return self;
}
