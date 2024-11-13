// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-11-11

#if !defined(MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED

#include "R.h"
#include "Module/Visuals/NativeWindowsIcon.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// The window is in "closed" state when it is creeated by NativeWindowsWindow_create.
// A successful call to NativeWindowsWindow_open puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to NativeWindowsWindow_close.
Rex_declareObjectType("NativeWindowsWindow", NativeWindowsWindow, "R.Object");

struct NativeWindowsWindow {
  R_Object _parent;
  HINSTANCE instanceHandle;
  HWND windowHandle;
  HDC windowDeviceContextHandle;

  R_String* title;
  NativeWindowsIcon* smallIcon;
  NativeWindowsIcon* bigIcon;
};

void
NativeWindowsWindow_construct
  (
    NativeWindowsWindow* self
  );

NativeWindowsWindow*
NativeWindowsWindow_create
  (
  );

/// @brief Ensure this window is opened.
/// @param self A pointer to this window.
void
NativeWindowsWindow_open
  (
    NativeWindowsWindow* self
  );

/// @brief Ensure the window is closed.
/// @param self A pointer to this window.
void
NativeWindowsWindow_close
  (
    NativeWindowsWindow* self
  );

R_BooleanValue
NativeWindowsWindow_getQuitRequested
  (
    NativeWindowsWindow* self
  );

void
NativeWindowsWindow_setQuitRequested
  (
    NativeWindowsWindow* self,
    R_BooleanValue quitRequested
  );

void
NativeWindowsWindow_update
  (
    NativeWindowsWindow* self
  );

void
NativeWindowsWindow_getRequiredBigIconSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  );

void
NativeWindowsWindow_getRequiredSmallIconSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  );

/// @brief Get the big icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
NativeWindowsIcon*
NativeWindowsWindow_getBigIcon 
  (
    NativeWindowsWindow* self
  );

/// @brief Set or remove the big icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
NativeWindowsWindow_setBigIcon
  (
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  );

/// @brief Get the small icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
NativeWindowsIcon*
NativeWindowsWindow_getSmallIcon
  (
    NativeWindowsWindow* self
  );

/// @brief Set or remove the small icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
NativeWindowsWindow_setSmallIcon
  (
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  );

/// @brief Get the title.
/// @param self A pointer to this window.
/// @return The title.
R_String*
NativeWindowsWindow_getTitle
  (
    NativeWindowsWindow* self
  );

/// @brief Set the title.
/// @param self A pointer to this window.
/// @param title The title.
void
NativeWindowsWindow_setTitle
  (
    NativeWindowsWindow* self,
    R_String* title
  );

/// @brief Get the canvas size.
/// @param self A pointer to this window.
/// @param width A pointer to a <code>R_Integer32Value</code> variable.
/// On success, that variable is assigned the width, in pixels, of the canvas.
/// @param height A pointer to a <code>R_Integer32Value</code> variable.
/// On success, that variable is assigned the height, in pixels, of the canvas.
void
NativeWindowsWindow_getCanvasSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  );

#endif // MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED
