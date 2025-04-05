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

#include "R/Include.h"
#include "Module/Visuals/NativeIcon.h"
#include "Module/Visuals/PixelBuffer.h"

// The window is in "closed" state when it is creeated by NativeWindowsWindow_create.
// A successful call to NativeWindowsWindow_open puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to NativeWindowsWindow_close.
Arcadia_declareObjectType(u8"NativeWindow", NativeWindow, u8"Arcadia.Object");

struct NativeWindow {
  Arcadia_Object _parent;

  void (*open)(Arcadia_Thread*, NativeWindow*);

  void (*close)(Arcadia_Thread*, NativeWindow*);

  Arcadia_BooleanValue (*getQuitRequested)(Arcadia_Thread*, NativeWindow*);

  void (*setQuitRequested)(Arcadia_Thread*, NativeWindow*, Arcadia_BooleanValue);

  void (*update)(Arcadia_Thread*, NativeWindow*);

  void (*getRequiredBigIconSize)(Arcadia_Thread*, NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*getRequiredSmallIconSize)(Arcadia_Thread*, NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  NativeIcon* (*getBigIcon)(Arcadia_Thread*, NativeWindow*);
  void (*setBigIcon)(Arcadia_Thread*, NativeWindow*, NativeIcon*);

  NativeIcon* (*getSmallIcon)(Arcadia_Thread*, NativeWindow* self);
  void (*setSmallIcon)(Arcadia_Thread*, NativeWindow*, NativeIcon*);

  Arcadia_String* (*getTitle)(Arcadia_Thread*, NativeWindow*);
  void (*setTitle)(Arcadia_Thread*, NativeWindow*, Arcadia_String*);

  void (*getCanvasSize)(Arcadia_Thread*, NativeWindow*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*beginRender)(Arcadia_Thread*, NativeWindow*);
  void (*endRender)(Arcadia_Thread*, NativeWindow*);

};

/// @brief Ensure this window is opened.
/// @param self A pointer to this window.
void
NativeWindow_open
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief Ensure this window is closed.
/// @param self A pointer to this window.
void
NativeWindow_close
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief Get if this application should quit.
/// @param self A pointer to this window.
/// @return #Arcadia_BooleanValue_True if this application was requested to quit. #Arcadia_BooleanValue_False if this application was requested to continue.
Arcadia_BooleanValue
NativeWindow_getQuitRequested
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief Set if the application should quit.
/// @param self A pointer to this window.
/// @param quitRequested #Arcadia_BooleanValue requests the application to quit. #Arcadia_BooleanValue_False request the application to continue.
void
NativeWindow_setQuitRequested
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_BooleanValue quitRequested
  );

/// @brief Update this window.
/// @param self A pointer to this window.
void
NativeWindow_update
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief Set or remove the big icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
NativeWindow_setBigIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    NativeIcon* icon
  );

/// @brief Get the small icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
NativeIcon*
NativeWindow_getSmallIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief Set or remove the small icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
NativeWindow_setSmallIcon
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    NativeIcon* icon
  );

/// @brief Get the title.
/// @param self A pointer to this window.
/// @return The title.
Arcadia_String*
NativeWindow_getTitle
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief Set the title.
/// @param self A pointer to this window.
/// @param title The title.
void
NativeWindow_setTitle
  (
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_String* title
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
    Arcadia_Thread* thread,
    NativeWindow* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Begin rendering to a window.
/// @param self A pointer to ths window.
/// @warning The successful calls to Window_beginRender and Window_endRender must be balanced.
void
NativeWindow_beginRender
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

/// @brief End rendering to a window.
/// @param self A pointer to this window.
/// @warning The successful calls to Window_beginRender and Window_endRender must be balanced.
void
NativeWindow_endRender
  (
    Arcadia_Thread* thread,
    NativeWindow* self
  );

#endif // MODULE_VISUALS_NATIVEWINDOW_H_INCLUDED
