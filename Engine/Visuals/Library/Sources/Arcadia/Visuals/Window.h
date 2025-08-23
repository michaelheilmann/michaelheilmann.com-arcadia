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

#if !defined(ARCADIA_VISUALS_WINDOW_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOW_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Engine/Include.h"
#include "Arcadia/Imaging/Include.h"
#include "Arcadia/Visuals/Icon.h"

// An instance of "Arcadia.Visuals.Window" is in "closed" state when it is created.
// A successful call to "Arcadia.Visuals.Window.open" puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to "Arcadia.Visuals.Window.close".
Arcadia_declareObjectType(u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Window {
  Arcadia_Object _parent;

  // #Arcadia_BooleanValue_True if the window is a fullscreen window.
  // #Arcadia_BooleanValue_False otherwise.
  // Default is #Arcadia_BooleanValue_False.
  Arcadia_BooleanValue fullscreen;

  // The title of the window.
  // Default is "Arcadia Engine Window".
  Arcadia_String* title;

  struct {
    /// The position of the left side of the window.
    /// Default is 0.
    Arcadia_Integer32Value left;
    /// The position of the top side of the window.
    /// Default is 0.
    Arcadia_Integer32Value top;
    /// The width of the window.
    /// Default is 1.
    Arcadia_Integer32Value width;
    /// The height of the window.
    /// Default is 1.
    Arcadia_Integer32Value height;
  } bounds;

  void (*open)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*close)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*getRequiredBigIconSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*getRequiredSmallIconSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  Arcadia_Visuals_Icon* (*getBigIcon)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*setBigIcon)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*);

  Arcadia_Visuals_Icon* (*getSmallIcon)(Arcadia_Thread*, Arcadia_Visuals_Window* self);
  void (*setSmallIcon)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*);

  Arcadia_String* (*getTitle)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*setTitle)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_String*);

  void (*getCanvasSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*beginRender)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*endRender)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*setPosition)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*getPosition)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*setSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*getSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  Arcadia_BooleanValue(*getFullscreen)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*setFullscreen)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_BooleanValue);

};

/// @brief Ensure this window is opened.
/// @param self A pointer to this window.
void
Arcadia_Visuals_Window_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Ensure this window is closed.
/// @param self A pointer to this window.
void
Arcadia_Visuals_Window_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Update this window.
/// @param thread A pointer to this thread.
/// @param self A pointer to this window.
void
Arcadia_Visuals_Window_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Get the size (width and height), in pixels, of a big window icon.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @post
/// On Success:
/// - <code>*width</code> was assigned the width, in pixels, required for a big window icon.
/// - <code>*height</code> was assigned the height, in pixels, required for a big window icon.
void
Arcadia_Visuals_Window_getRequiredBigIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
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
Arcadia_Visuals_Window_getRequiredSmallIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Get the big icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set or remove the big icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
Arcadia_Visuals_Window_setBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  );

/// @brief Get the small icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set or remove the small icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
Arcadia_Visuals_Window_setSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  );

/// @brief Get the title.
/// @param self A pointer to this window.
/// @return The title.
Arcadia_String*
Arcadia_Visuals_Window_getTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set the title.
/// @param self A pointer to this window.
/// @param title The title.
void
Arcadia_Visuals_Window_setTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_String* title
  );

/// @brief Get the canvas size.
/// @param self A pointer to this window.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// On success, that variable is assigned the width, in pixels, of the canvas.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// On success, that variable is assigned the height, in pixels, of the canvas.
void
Arcadia_Visuals_Window_getCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Begin rendering to this window.
/// @param self A pointer to ths window.
/// @warning The successful calls to Window_beginRender and Window_endRender must be balanced.
void
Arcadia_Visuals_Window_beginRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief End rendering to this window.
/// @param self A pointer to this window.
/// @warning The successful calls to Window_beginRender and Window_endRender must be balanced.
void
Arcadia_Visuals_Window_endRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param left, top Arcadia_Integer32Value values.
/// @post
/// This window was assigned the left position @a left.
/// This window was assigned the top position @ top.
void
Arcadia_Visuals_Window_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );


/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param left, top Pointers to Arcadia_Integer32Value variables.
/// @post
/// <code>*left</code> was assigned the left position of this window.
/// <code>*top</code> was assigned the top position of this window.
void
Arcadia_Visuals_Window_getPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

/// @brief Set the size of this window.
/// @param self A pointer to this window.
/// @param width, height Arcadia_Integer32Value values.
/// @post
/// This window was assigned the width @a width.
/// This window was assigned the height @ height.
void
Arcadia_Visuals_Window_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param width, height Pointers to Arcadia_Integer32Value variables.
/// @post
/// <code>*width</code> was assigned the width of this window.
/// <code>*height</code> was assigned the height of this window.
void
Arcadia_Visuals_Window_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Get if this window is a fullscreen window.
/// @param self A pointer to this window.
/// @return #Arcadia_BooleanValue_True if this window is a fullscreen window. #Arcadia_BooleanValue_False if this window is a non-fullscreen window.
Arcadia_BooleanValue
Arcadia_Visuals_Window_getFullscreen
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set if this window is a fullscreen window.
/// @param self A pointer to this window.
/// @param fullscreen #Arcadia_BooleanValue_True makes this window a fullscreen window. #Arcadia_BooleanValue_False makes this window a non-fullscreen window.
void
Arcadia_Visuals_Window_setFullscreen
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_BooleanValue fullscreen
  );

#endif // ARCADIA_VISUALS_WINDOW_H_INCLUDED
