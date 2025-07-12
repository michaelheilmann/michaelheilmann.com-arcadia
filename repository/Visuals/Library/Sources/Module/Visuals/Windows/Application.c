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

#include "Module/Visuals/Windows/Application.h"

#include "Module/Visuals/Windows/DisplayDevice.h"
#include "Module/Visuals/Windows/Icon.h"
#include "Module/Visuals/Windows/Window.h"

static Arcadia_Visuals_Windows_Application* g_instance = NULL;

static Arcadia_Visuals_Windows_Icon*
Arcadia_Visuals_Windows_Application_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

static Arcadia_Visuals_Windows_Window*
Arcadia_Visuals_Windows_Application_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self
  );

static BOOL
multiByteToWideChar
  (
    const char* p,
    size_t n,
    wchar_t** q,
    size_t* m
  );

static Arcadia_String*
Windows_fromChar
  (
    Arcadia_Thread* thread,
    CONST CHAR* p,
    size_t n
  );

static Arcadia_String*
Windows_fromWideChar
  (
    Arcadia_Thread* thread,
    CONST WCHAR* p,
    size_t n
  );

static Arcadia_String*
Arcadia_Visuals_Windows_Application_getAdapterName
  (
    Arcadia_Thread* thread,
    const CHAR* p
  );

static Arcadia_String*
Arcadia_Visuals_Windows_Application_getMonitorName
  (
    Arcadia_Thread* thread,
    const CHAR* p
  );

static Arcadia_List*
Arcadia_Visuals_Windows_Application_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self
  );

static void
destroyCallback
  (
    void* observer,
    void* observed
  );

static void
Arcadia_Visuals_Windows_Application_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

#if _DEBUG
static void
Arcadia_Visuals_Windows_Application_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self
  );
#endif

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_Application_constructImpl,
#if _DEBUG
  .destruct = &Arcadia_Visuals_Windows_Application_destructImpl,
#else
  .destruct = NULL,
#endif
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.Application", Arcadia_Visuals_Windows_Application, u8"Arcadia.Visuals.Application", Arcadia_Visuals_Application, &_typeOperations);

static Arcadia_Visuals_Windows_Icon*
Arcadia_Visuals_Windows_Application_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  )
{
  Arcadia_Visuals_Windows_Icon* icon = Arcadia_Visuals_Windows_Icon_create(thread, width, height, 47, 47, 47, 255);
  return icon;
}

static Arcadia_Visuals_Windows_Window*
Arcadia_Visuals_Windows_Application_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self
  )
{
  Arcadia_Visuals_Windows_Window* window = Arcadia_Visuals_Windows_Window_create(thread, self, NULL);
  return window;
}

static void
Arcadia_Visuals_Windows_Application_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_Application* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_Application_getType(thread);
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
  _self->instanceHandle = GetModuleHandle(NULL);
  if (!_self->instanceHandle) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  ((Arcadia_Visuals_Application*)_self)->createIcon = (Arcadia_Visuals_Icon * (*)(Arcadia_Thread*, Arcadia_Visuals_Application*, Arcadia_Integer32Value, Arcadia_Integer32Value, Arcadia_Natural8Value, Arcadia_Natural8Value, Arcadia_Natural8Value, Arcadia_Natural8Value)) & Arcadia_Visuals_Windows_Application_createIconImpl;
  ((Arcadia_Visuals_Application*)_self)->createWindow = (Arcadia_Visuals_Window * (*)(Arcadia_Thread*, Arcadia_Visuals_Application*)) & Arcadia_Visuals_Windows_Application_createWindowImpl;
  ((Arcadia_Visuals_Application*)_self)->getDisplayDevices = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_Application*)) & Arcadia_Visuals_Windows_Application_getDisplayDevicesImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

#if _DEBUG
static void
Arcadia_Visuals_Windows_Application_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self
  )
{ 
  fprintf(stdout, "%s:%d:%s\n", __FILE__, __LINE__, "Arcadia_Visuals_Windows_Application_destructImpl");
}
#endif

Arcadia_Visuals_Windows_Application*
Arcadia_Visuals_Windows_Application_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Windows_Application* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Windows_Application_getType(thread), 0, &argumentValues[0]);
  return self;
}

static BOOL
multiByteToWideChar
  (
    const char* p,
    size_t n,
    wchar_t** q,
    size_t* m
  )
{
  int l = MultiByteToWideChar(CP_ACP, 0, p, n, NULL, 0);
  if (l <= 0) {
    return FALSE;
  }
  wchar_t* r = malloc(sizeof(wchar_t) * l);
  if (!r) {
    return FALSE;
  }
  if (MultiByteToWideChar(CP_ACP, 0, p, n, r, l) <= 0) {
    free(r);
    r = NULL;
    return FALSE;
  }
  *q = r;
  *m = l;
  return TRUE;
}

static Arcadia_String*
Windows_fromChar
  (
    Arcadia_Thread* thread,
    CONST CHAR* p,
    size_t n
  )
{ 
  return Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, p, n)));
}

static Arcadia_String*
Windows_fromWideChar
  (
    Arcadia_Thread* thread,
    CONST WCHAR* p,
    size_t n
  )
{
  int m = WideCharToMultiByte(CP_UTF8, 0, p, -1, NULL, 0, NULL, NULL);
  if (!m) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  CHAR* q = malloc(sizeof(char) * m);
  if (!q) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!WideCharToMultiByte(CP_UTF8, 0, p, -1, q, m, NULL, NULL)) {
    free(q);
    q = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* s;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    s = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, q, m)));
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  free(q);
  q = NULL;
  return s;
}

static Arcadia_String*
Arcadia_Visuals_Windows_Application_getAdapterName
  (
    Arcadia_Thread* thread,
    const CHAR* p
  )
{
  DWORD deviceIndex = 0;
  while (1) {
    DISPLAY_DEVICEA deviceInfo = { 0 };
    deviceInfo.cb = sizeof(deviceInfo);
    if (!EnumDisplayDevicesA(NULL, deviceIndex, &deviceInfo, 0)) {
      break;
    }
    deviceIndex++;
    if (!strcmp(deviceInfo.DeviceName, p)) {
      return Windows_fromChar(thread, deviceInfo.DeviceString, strlen(deviceInfo.DeviceString));
    }
  }
  return NULL;
}

static Arcadia_String*
Arcadia_Visuals_Windows_Application_getMonitorName
  (
    Arcadia_Thread* thread,
    const CHAR* p
  )
{
  UINT32 pathCount, modeCount;
  HRESULT hResult = GetDisplayConfigBufferSizes(QDC_ALL_PATHS, &pathCount, &modeCount);
  if (S_OK != hResult) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  DISPLAYCONFIG_PATH_INFO* paths = malloc(sizeof(DISPLAYCONFIG_PATH_INFO) * pathCount);
  if (!paths) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  DISPLAYCONFIG_MODE_INFO* modes = malloc(sizeof(DISPLAYCONFIG_MODE_INFO) * modeCount);
  if (!modes) {
    free(paths);
    paths = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  hResult = QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths, &modeCount, modes, NULL);
  if (S_OK != hResult) {
    free(modes);
    modes = NULL;
    free(paths);
    paths = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  wchar_t* q; size_t m;
  multiByteToWideChar(p, strlen(p) + 1, &q, &m);

  Arcadia_String* name = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    for (UINT32 i = 0; i < pathCount; ++i) {

      DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceDeviceNameInfo = { 0 };
      sourceDeviceNameInfo.header.adapterId = paths[i].targetInfo.adapterId;
      sourceDeviceNameInfo.header.id = paths[i].sourceInfo.id;
      sourceDeviceNameInfo.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
      sourceDeviceNameInfo.header.size = sizeof(sourceDeviceNameInfo);
      hResult = DisplayConfigGetDeviceInfo(&sourceDeviceNameInfo.header);
      if (S_OK != hResult) {
        free(q);
        q = NULL;
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      if (wcsncmp(sourceDeviceNameInfo.viewGdiDeviceName, q, m)) {
        continue;
      }
      DISPLAYCONFIG_TARGET_DEVICE_NAME targetDeviceName =  { 0 };
      targetDeviceName.header.adapterId = paths[i].targetInfo.adapterId;
      targetDeviceName.header.id = paths[i].targetInfo.id;
      targetDeviceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
      targetDeviceName.header.size = sizeof(targetDeviceName);
      hResult = DisplayConfigGetDeviceInfo(&targetDeviceName.header);
      if (S_OK != hResult) {
        free(q);
        q = NULL;
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      name = Windows_fromWideChar(thread, targetDeviceName.monitorFriendlyDeviceName, wcslen(targetDeviceName.monitorFriendlyDeviceName));
      break;
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    free(q);
    q = NULL;
    free(modes);
    modes = NULL;
    free(paths);
    paths = NULL;
    Arcadia_Thread_jump(thread);
  }
  free(q);
  q = NULL;
  free(modes);
  modes = NULL;
  free(paths);
  paths = NULL;
  return name;
}

typedef struct EnumDisplayMonitorsContext {
  Arcadia_Thread* thread;
  Arcadia_List* displayDevices;
} EnumDisplayMonitorsContext;

static BOOL CALLBACK
enumDisplayMonitorsCallback
  (
    HMONITOR hMonitor,
    HDC hDeviceContext,
    LPRECT lpClipRect,
    LPARAM dwData
  )
{
  EnumDisplayMonitorsContext* enumDisplayMonitorsContext = (EnumDisplayMonitorsContext*)dwData;

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(enumDisplayMonitorsContext->thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {

    MONITORINFOEX monitorInfoEx = { 0 };
    monitorInfoEx.cbSize = sizeof(monitorInfoEx);
    if (!GetMonitorInfoA(hMonitor, (LPMONITORINFO)&monitorInfoEx)) {
      Arcadia_Thread_setStatus(enumDisplayMonitorsContext->thread, Arcadia_Status_EnvironmentFailed);
      return FALSE;
    }

    // (1) Get the ID.
    Arcadia_String* id = Windows_fromChar(enumDisplayMonitorsContext->thread, monitorInfoEx.szDevice, strlen(monitorInfoEx.szDevice));
    // (2) Get the monitor name.
    Arcadia_String* monitorName = Arcadia_Visuals_Windows_Application_getMonitorName(enumDisplayMonitorsContext->thread, monitorInfoEx.szDevice);
    // (2) Get the adapter name
    Arcadia_String* adapterName = Arcadia_Visuals_Windows_Application_getAdapterName(enumDisplayMonitorsContext->thread, monitorInfoEx.szDevice);

    Arcadia_Visuals_Windows_DisplayDevice *displayDevice = Arcadia_Visuals_Windows_DisplayDevice_create(enumDisplayMonitorsContext->thread, id, adapterName, monitorName);
    displayDevice->left = monitorInfoEx.rcMonitor.left;
    displayDevice->top = monitorInfoEx.rcMonitor.top;
    displayDevice->right = monitorInfoEx.rcMonitor.right;
    displayDevice->bottom = monitorInfoEx.rcMonitor.bottom;
    displayDevice->hMonitor = hMonitor;

    Arcadia_List_insertBackObjectReferenceValue(enumDisplayMonitorsContext->thread, enumDisplayMonitorsContext->displayDevices,
                                                (Arcadia_ObjectReferenceValue)displayDevice);

    Arcadia_Thread_popJumpTarget(enumDisplayMonitorsContext->thread);
  } else {
    Arcadia_Thread_popJumpTarget(enumDisplayMonitorsContext->thread);
    return FALSE;
  }
  return TRUE;
}

static Arcadia_List*
Arcadia_Visuals_Windows_Application_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* self
  )
{
  Arcadia_List* displayDevices = Arcadia_List_create(thread);

  // "EnumDisplayMonitors" vs. "EnumDisplayDevices":
  // Monitors can be disabled and remapped by the control panel Display applet.
  // With "EnumDisplayDevices" you get the "raw" view, "EnumDisplayMonitors" gives you the mapped view.
  // You should only care about the mapped view provided by "EnumDisplayMonitors".

  EnumDisplayMonitorsContext enumDisplayMonitorsContext = {
    .thread = thread,
    .displayDevices = displayDevices,
  };
  Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  EnumDisplayMonitors(NULL, NULL, &enumDisplayMonitorsCallback, (LPARAM)&enumDisplayMonitorsContext);
  if (Arcadia_Thread_getStatus(thread)) {
    Arcadia_Thread_jump(thread);
  }
  return displayDevices;
}

static void
destroyCallback
  (
    void* argument1,
    void* argument2
  )
{
  g_instance = NULL;
}

Arcadia_Visuals_Windows_Application*
Arcadia_Visuals_Windows_Application_getOrCreate
  (
    Arcadia_Thread* thread
  )
{ 
  if (!g_instance) {
    Arcadia_Visuals_Windows_Application* instance = Arcadia_Visuals_Windows_Application_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
