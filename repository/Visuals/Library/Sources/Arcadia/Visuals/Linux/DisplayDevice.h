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

#if !defined(ARCADIA_VISUALS_LINUX_DISPLAYDEVICE_H_INCLUDED)
#define ARCADIA_VISUALS_LINUX_DISPLAYDEVICE_H_INCLUDED

#include "Arcadia/Visuals/DisplayDevice.h"

// https://www.x.org/releases/current/doc/index.html
// https://www.x.org/releases/current/doc/randrproto/randrproto.txt
#include <X11/extensions/Xrandr.h>

typedef struct Arcadia_Visuals_Linux_Application Arcadia_Visuals_Linux_Application;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Linux.DisplayDevice", Arcadia_Visuals_Linux_DisplayDevice,
                          u8"Arcadia.Visuals.DisplayDevice");

struct Arcadia_Visuals_Linux_DisplayDevice {
  Arcadia_Visuals_DisplayDevice _parent;
  // The application.
  Arcadia_Visuals_Linux_Application* application;
  struct {
    int left;
    int top;
    int right;
    int bottom;
  } bounds;
  // An unique ID.
  // This is usually the stringified value of output.
  Arcadia_String* id;
  // A human-readable name.
  // TODO The name is not necessarily unique, it is the device name as provided by the EDID.
  //      Make sure the name is unique programmatically.
  Arcadia_String* name;
  // The X11 ID of the output. RROutput type is an alias of XID type which is an alias of CARD32 type.
  RROutput output;
  // The X11 ID of the mode. RRMode type is an alias of XID type which is an alias of CARD32 type.
  RRMode mode;
};

Arcadia_Visuals_Linux_DisplayDevice*
Arcadia_Visuals_Linux_DisplayDevice_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Linux_Application* application,
    Arcadia_String* id,
    Arcadia_String* name
  );

#endif // ARCADIA_VISUALS_LINUX_DISPLAYDEVICE_H_INCLUDED
