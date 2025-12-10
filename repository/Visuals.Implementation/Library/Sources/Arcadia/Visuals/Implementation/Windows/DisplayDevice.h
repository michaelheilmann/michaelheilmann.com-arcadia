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

#if !defined(ARCADIA_VISUALS_WINDOWS_DISPLAYDEVICE_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_DISPLAYDEVICE_H_INCLUDED


#include "Arcadia/Visuals/Include.h"
#if !defined(WIN32_LEAN_AND_MEAN)
  #define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOCOMM)
  #define NOCOMM
#endif
#include <Windows.h>
typedef struct Arcadia_Visuals_Windows_DisplayMode Arcadia_Visuals_Windows_DisplayMode;


Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.DisplayDevice", Arcadia_Visuals_Windows_DisplayDevice,
                          u8"Arcadia.Visuals.DisplayDevice");

struct Arcadia_Visuals_Windows_DisplayDeviceDispatch {
  Arcadia_Visuals_DisplayDeviceDispatch _parent;
};

struct Arcadia_Visuals_Windows_DisplayDevice {
  Arcadia_Visuals_DisplayDevice _parent;
  // The ID of the adapter / monitor combination.
  // Example: \\.\DISPLAY
  Arcadia_String* id;
  // The human-readable name of the monitor.
  // This is not necessarily unique.
  // Example: MAG274QRF-QD
  Arcadia_String* monitor;
  // The human-readable name of the adapter.
  // This is not necessarily unique.
  // Example: NVIDIA GeForce RTX 4070 Ti
  Arcadia_String* adapter;
  /// The handle of the monitor.
  HMONITOR hMonitor;
  /// The rectangle of the monitor in the virtual display space.
  Arcadia_Integer32Value left, top, right, bottom;

  /// The current display mode of this display device.
  Arcadia_Visuals_Windows_DisplayMode* currentDisplayMode;
  /// The list of available display modes of this display device.
  Arcadia_List* availableDisplayModes;
};

Arcadia_Visuals_Windows_DisplayDevice*
Arcadia_Visuals_Windows_DisplayDevice_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* id,
    Arcadia_String* adapter,
    Arcadia_String* monitor
  );

#endif // ARCADIA_VISUALS_WINDOWS_DISPLAYDEVICE_H_INCLUDED
