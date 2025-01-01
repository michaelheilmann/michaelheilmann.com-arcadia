// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-12-31

#if !defined(MODULE_VISUALS_NATIVEWINDOW_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOW_H_INCLUDED

#include "R.h"
#include "Module/Visuals/NativeWindowsIcon.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// The window is in "closed" state when it is creeated by NativeWindowsWindow_create.
// A successful call to NativeWindowsWindow_open puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to NativeWindowsWindow_close.
Rex_declareObjectType(u8"NativeWindow", NativeWindow, u8"R.Object");

struct NativeWindow {
  R_Object _parent;

  void (*open)(Arcadia_Process*, NativeWindow*);

  void (*close)(Arcadia_Process* process, NativeWindow*);

  Arcadia_BooleanValue (*getQuitRequested)(NativeWindow*);

  void (*setQuitRequested)(NativeWindow*, Arcadia_BooleanValue);

  void (*update)(NativeWindow*);

  void (*getRequiredBigIconSize)(NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*getRequiredSmallIconSize)(NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  NativeIcon* (*getBigIcon)(NativeWindow*);
  void (*setBigIcon)(NativeWindow*, NativeIcon*);

  NativeIcon* (*getSmallIcon)(NativeWindow* self);
  void (*setSmallIcon)(NativeWindow*, NativeIcon*);

  R_String* (*getTitle)(NativeWindow*);
  void (*setTitle)(Arcadia_Process*, NativeWindow*, R_String*);

  void (*getCanvasSize)(NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

};

/// @brief Ensure this window is opened.
/// @param self A pointer to this window.
void
NativeWindow_open
  (
    Arcadia_Process* process,
    NativeWindow* self
  );

/// @brief Ensure this window is closed.
/// @param self A pointer to this window.
void
NativeWindow_close
  (
    Arcadia_Process* process,
    NativeWindow* self
  );

/// @brief Get if this application should quit.
/// @param self A pointer to this window.
/// @return #Arcadia_BooleanValue_True if this application was requested to quit. #Arcadia_BooleanValue_False if this application was requested to continue.
Arcadia_BooleanValue
NativeWindow_getQuitRequested
  (
    NativeWindow* self
  );

/// @brief Set if the application should quit.
/// @param self A pointer to this window.
/// @param quitRequested #Arcadia_BooleanValue requests the application to quit. #Arcadia_BooleanValue_False request the application to continue.
void
NativeWindow_setQuitRequested
  (
    NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  );

/// @brief Update this window.
/// @param self A pointer to this window.
void
NativeWindow_update
  (
    NativeWindow* self
  );

/// @brief Get the size (width and height), in pixels, of a big window icon.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @post
/// On Success:
/// - <code>*width</code> was assigned the width, in pixels, required for a big window icon. 
/// - <code>*height</code> was assigned the height, in pixels, required for a big window icon.
void
NativeWindow_getRequiredBigIconSize
  (
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Get the size (width and height), in pixels, of a small window icon.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @post
/// On Success:
/// - <code>*width</code> was assigned the width, in pixels, required for a small window icon. 
/// - <code>*height</code> was assigned the height, in pixels, required for a small window icon.
void
NativeWindow_getRequiredSmallIconSize
  (
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Get the big icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
NativeIcon*
NativeWindow_getBigIcon 
  (
    NativeWindow* self
  );

/// @brief Set or remove the big icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
NativeWindow_setBigIcon
  (
    NativeWindow* self,
    NativeIcon* icon
  );

/// @brief Get the small icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
NativeIcon*
NativeWindow_getSmallIcon
  (
    NativeWindow* self
  );

/// @brief Set or remove the small icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
NativeWindow_setSmallIcon
  (
    NativeWindow* self,
    NativeIcon* icon
  );

/// @brief Get the title.
/// @param self A pointer to this window.
/// @return The title.
R_String*
NativeWindow_getTitle
  (
    NativeWindow* self
  );

/// @brief Set the title.
/// @param self A pointer to this window.
/// @param title The title.
void
NativeWindow_setTitle
  (
    Arcadia_Process* process,
    NativeWindow* self,
    R_String* title
  );

/// @brief Get the canvas size.
/// @param self A pointer to this window.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// On success, that variable is assigned the width, in pixels, of the canvas.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// On success, that variable is assigned the height, in pixels, of the canvas.
void
NativeWindow_getCanvasSize
  (
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

#endif // MODULE_VISUALS_NATIVEWINDOW_H_INCLUDED
