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

#include "Arcadia/Visuals/Windows/Window.h"

#include "Arcadia/Visuals/Configuration.h"
#include "Arcadia/Visuals/Events/KeyboardKeyEvent.h"
#include "Arcadia/Visuals/Events/MouseButtonEvent.h"
#include "Arcadia/Visuals/Events/WindowClosedEvent.h"
#include "Arcadia/Visuals/Events/WindowPositionChangedEvent.h"
#include "Arcadia/Visuals/Events/WindowSizeChangedEvent.h"
#include "Arcadia/Visuals/Windows/_WindowText.h"
#include "Arcadia/Visuals/Windows/Wgl/WglFactory.h"
#include <limits.h>

static const char g_title[] = "Liminality";

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
Windows_mapKeyboardKey
  (
    Arcadia_Thread* thread,
    WORD source,
    Arcadia_Visuals_KeyboardKey* target
  );

static void
Arcadia_Visuals_Windows_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
Arcadia_Visuals_Windows_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
Arcadia_Visuals_Windows_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static Arcadia_BooleanValue
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue fullscreen
  );

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue quitRequested
  );

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static Arcadia_Visuals_Windows_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
  );

static Arcadia_Visuals_Windows_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
  );

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_String* title
  );

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
createContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_WglFactory* deviceInfo
  );

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  );

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static const char g_className[] = "Aracadia.Visuals.Windows.Window Window Class";

static Arcadia_BooleanValue g_quitRequested = Arcadia_BooleanValue_False;

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Windows_Window_constructImpl,
  .destruct = &Arcadia_Visuals_Windows_Window_destruct,
  .visit = &Arcadia_Visuals_Windows_Window_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Windows.Window", Arcadia_Visuals_Windows_Window,
                         u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window,
                         &_typeOperations);

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return DefWindowProc(hWnd, uMsg, wParam, lParam); // There is nothing we can do actually.
  }
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  switch (uMsg) {
    case WM_CLOSE: {
      g_quitRequested = Arcadia_BooleanValue_True;
      Arcadia_Visuals_Windows_Window* window = (Arcadia_Visuals_Windows_Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Visuals_WindowClosedEvent_create
          (
            thread,
            Arcadia_getTickCount(thread),
            (Arcadia_Visuals_Window*)window
          );
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
      }
      return 0;
    } break;
    case WM_KEYDOWN: {
      Arcadia_Visuals_Windows_Window* window = (Arcadia_Visuals_Windows_Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Visuals_KeyboardKey keyboardKey;
        Windows_mapKeyboardKey(thread, LOWORD(wParam), &keyboardKey);
        Arcadia_Visuals_Event* event =
          (Arcadia_Visuals_Event*)
            Arcadia_Visuals_KeyboardKeyEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                keyboardKey,
                Arcadia_Visuals_KeyboardKeyAction_Pressed
              );
        Arcadia_Visuals_Application_enqueEvent(thread, (Arcadia_Visuals_Application*)window->application, event);
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
      }
      return 0;
    } break;
    case WM_KEYUP: {
      Arcadia_Visuals_Windows_Window* window = (Arcadia_Visuals_Windows_Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Visuals_KeyboardKey keyboardKey;
        Windows_mapKeyboardKey(thread, LOWORD(wParam), &keyboardKey);
        Arcadia_Visuals_Event* event =
          (Arcadia_Visuals_Event*)
            Arcadia_Visuals_KeyboardKeyEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                keyboardKey,
                Arcadia_Visuals_KeyboardKeyAction_Released
              );
        Arcadia_Visuals_Application_enqueEvent(thread, (Arcadia_Visuals_Application*)window->application, event);
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
      }
      if (LOWORD(wParam) == VK_ESCAPE) {
        g_quitRequested = Arcadia_BooleanValue_True;
      }
      return 0;
    } break;
    case WM_SIZE: {
      Arcadia_Visuals_Windows_Window* window = (Arcadia_Visuals_Windows_Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      RECT rect;
      GetWindowRect(window->windowHandle, &rect);
      Arcadia_Integer32Value width = rect.right - rect.left;
      Arcadia_Integer32Value height = rect.bottom - rect.top;
      if (width != ((Arcadia_Visuals_Window*)window)->bounds.width ||
          height != ((Arcadia_Visuals_Window*)window)->bounds.height) {
        ((Arcadia_Visuals_Window*)window)->bounds.width = width;
        ((Arcadia_Visuals_Window*)window)->bounds.height = height;
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          Arcadia_Visuals_Event* event =
            (Arcadia_Visuals_Event*)
              Arcadia_Visuals_WindowSizeChangedEvent_create
                (
                  thread,
                  Arcadia_getTickCount(thread),
                  (Arcadia_Visuals_Window*)window,
                  width,
                  height
                );
          Arcadia_Visuals_Application_enqueEvent(thread, (Arcadia_Visuals_Application*)window->application, event);
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      }
      return 0;
    } break;
    case WM_MOVE: {
      Arcadia_Visuals_Windows_Window* window = (Arcadia_Visuals_Windows_Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0; // There is nothing we can do actually.
      }
      RECT rect;
      GetWindowRect(window->windowHandle, &rect);
      Arcadia_Integer32Value left = rect.left;
      Arcadia_Integer32Value top = rect.top;
      if (left != ((Arcadia_Visuals_Window*)window)->bounds.left ||
          top != ((Arcadia_Visuals_Window*)window)->bounds.top) {
        ((Arcadia_Visuals_Window*)window)->bounds.left = left;
        ((Arcadia_Visuals_Window*)window)->bounds.top = top;
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          Arcadia_Visuals_Event* event =
            (Arcadia_Visuals_Event*)
              Arcadia_Visuals_WindowPositionChangedEvent_create
                (
                  thread,
                  Arcadia_getTickCount(thread),
                  (Arcadia_Visuals_Window*)window,
                  left,
                  top
                );
          Arcadia_Visuals_Application_enqueEvent(thread, (Arcadia_Visuals_Application*)window->application, event);
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      }
      return 0;
    } break;
    default: {
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    } break;
  };
}

static void
Windows_mapKeyboardKey
  (
    Arcadia_Thread* thread,
    WORD source,
    Arcadia_Visuals_KeyboardKey* target
  )
{
#define Define(Source, Target) \
  case Source: { \
    *target = Target; \
  } break;

  switch (source) {
      Define('A', Arcadia_Visuals_KeyboardKey_A)
      Define(VK_ACCEPT, Arcadia_Visuals_KeyboardKey_Accept)
      Define(VK_ADD, Arcadia_Visuals_KeyboardKey_Add)
      Define(VK_APPS, Arcadia_Visuals_KeyboardKey_Applications)

      Define('B', Arcadia_Visuals_KeyboardKey_B)
      Define(VK_BACK, Arcadia_Visuals_KeyboardKey_Backspace)

      Define(VK_BROWSER_BACK, Arcadia_Visuals_KeyboardKey_BrowserBack)
      Define(VK_BROWSER_FAVORITES, Arcadia_Visuals_KeyboardKey_BrowserFavorites)
      Define(VK_BROWSER_FORWARD, Arcadia_Visuals_KeyboardKey_BrowserForward)
      Define(VK_BROWSER_HOME, Arcadia_Visuals_KeyboardKey_BrowserHome)
      Define(VK_BROWSER_REFRESH, Arcadia_Visuals_KeyboardKey_BrowserRefresh)
      Define(VK_BROWSER_SEARCH, Arcadia_Visuals_KeyboardKey_BrowserSearch)
      Define(VK_BROWSER_STOP, Arcadia_Visuals_KeyboardKey_BrowserStop)

      Define('C', Arcadia_Visuals_KeyboardKey_C)
      Define(VK_CAPITAL, Arcadia_Visuals_KeyboardKey_Capital /*Arcadia_Visuals_KeyboardKey_CapsLock*/) // "Capital" and "CapsLock" are aliases of each other.

      Define(VK_CLEAR, Arcadia_Visuals_KeyboardKey_Clear)
      Define(VK_CONVERT, Arcadia_Visuals_KeyboardKey_Convert)

      Define('D', Arcadia_Visuals_KeyboardKey_D)
      Define('0', Arcadia_Visuals_KeyboardKey_D0)
      Define('1', Arcadia_Visuals_KeyboardKey_D1)
      Define('2', Arcadia_Visuals_KeyboardKey_D2)
      Define('3', Arcadia_Visuals_KeyboardKey_D3)
      Define('4', Arcadia_Visuals_KeyboardKey_D4)
      Define('5', Arcadia_Visuals_KeyboardKey_D5)
      Define('6', Arcadia_Visuals_KeyboardKey_D6)
      Define('7', Arcadia_Visuals_KeyboardKey_D7)
      Define('8', Arcadia_Visuals_KeyboardKey_D8)
      Define('9', Arcadia_Visuals_KeyboardKey_D9)

      Define(VK_OEM_5, Arcadia_Visuals_KeyboardKey_DeadCircumflex) // "^" aka "VK_OEM_5" in WinAPI.
      Define(VK_OEM_6, Arcadia_Visuals_KeyboardKey_DeadGrave) // "`" aka "VK_OEM_6" in WinAPI.
      Define(VK_DECIMAL, Arcadia_Visuals_KeyboardKey_Decimal) // Decimal separator on NumPad
      Define(VK_DELETE, Arcadia_Visuals_KeyboardKey_Delete)
      Define(VK_DIVIDE, Arcadia_Visuals_KeyboardKey_Divide)
      Define(VK_DOWN, Arcadia_Visuals_KeyboardKey_DownArrow /*Arcadia_Visuals_KeyboardKey_Down*/) // "Down Arrow" and "Down" are aliases of each other.

      Define('E', Arcadia_Visuals_KeyboardKey_E)
      Define(VK_END, Arcadia_Visuals_KeyboardKey_End)
      Define(VK_ESCAPE, Arcadia_Visuals_KeyboardKey_Escape)

      Define('F', Arcadia_Visuals_KeyboardKey_F)
      Define(VK_F1, Arcadia_Visuals_KeyboardKey_F1)
      Define(VK_F10, Arcadia_Visuals_KeyboardKey_F10)
      Define(VK_F11, Arcadia_Visuals_KeyboardKey_F11)
      Define(VK_F12, Arcadia_Visuals_KeyboardKey_F12)
      Define(VK_F13, Arcadia_Visuals_KeyboardKey_F13)
      Define(VK_F14, Arcadia_Visuals_KeyboardKey_F14)
      Define(VK_F15, Arcadia_Visuals_KeyboardKey_F15)
      Define(VK_F16, Arcadia_Visuals_KeyboardKey_F16)
      Define(VK_F17, Arcadia_Visuals_KeyboardKey_F17)
      Define(VK_F18, Arcadia_Visuals_KeyboardKey_F18)
      Define(VK_F19, Arcadia_Visuals_KeyboardKey_F19)
      Define(VK_F2, Arcadia_Visuals_KeyboardKey_F2)
      Define(VK_F20, Arcadia_Visuals_KeyboardKey_F20)
      Define(VK_F21, Arcadia_Visuals_KeyboardKey_F21)
      Define(VK_F22, Arcadia_Visuals_KeyboardKey_F22)
      Define(VK_F23, Arcadia_Visuals_KeyboardKey_F23)
      Define(VK_F24, Arcadia_Visuals_KeyboardKey_F24)
      Define(VK_F3, Arcadia_Visuals_KeyboardKey_F3)
      Define(VK_F4, Arcadia_Visuals_KeyboardKey_F4)
      Define(VK_F5, Arcadia_Visuals_KeyboardKey_F5)
      Define(VK_F6, Arcadia_Visuals_KeyboardKey_F6)
      Define(VK_F7, Arcadia_Visuals_KeyboardKey_F7)
      Define(VK_F8, Arcadia_Visuals_KeyboardKey_F8)
      Define(VK_F9, Arcadia_Visuals_KeyboardKey_F9)
      Define(VK_FINAL, Arcadia_Visuals_KeyboardKey_FinalMode)

      Define('G', Arcadia_Visuals_KeyboardKey_G)

      Define('H', Arcadia_Visuals_KeyboardKey_H)

      Define(VK_HANGUL/*VK_KANA*/, Arcadia_Visuals_KeyboardKey_HangulMode) // "IME Hangul Mode" and "IME Hanguel Mode" are aliases of each other.
      Define(VK_HANJA/*VK_KANJI*/, Arcadia_Visuals_KeyboardKey_HanjaMode) // "IME Hanja Mode" and "IME Kanji Mode" are aliases of each other.
      Define(VK_HOME, Arcadia_Visuals_KeyboardKey_Home)

      Define('I', Arcadia_Visuals_KeyboardKey_I)
      Define(VK_INSERT, Arcadia_Visuals_KeyboardKey_Insert)


      Define('J', Arcadia_Visuals_KeyboardKey_J)
      Define(VK_JUNJA, Arcadia_Visuals_KeyboardKey_JunjaMode)	// IME Junja Mode key.

      Define('K', Arcadia_Visuals_KeyboardKey_K)

      Define('L', Arcadia_Visuals_KeyboardKey_L)
      Define(VK_LEFT, Arcadia_Visuals_KeyboardKey_LeftArrow /*Arcadia_Visuals_KeyboardKey_Left*/) // "Left Arrow" and "Left" are aliases of each other.
      Define(VK_LCONTROL, Arcadia_Visuals_KeyboardKey_LeftControl)
      Define(VK_LMENU, Arcadia_Visuals_KeyboardKey_LeftMenu)
      Define(VK_LSHIFT, Arcadia_Visuals_KeyboardKey_LeftShift)
      Define(VK_LWIN, Arcadia_Visuals_KeyboardKey_LeftWindows)

      Define('M', Arcadia_Visuals_KeyboardKey_M)

      Define(VK_MODECHANGE, Arcadia_Visuals_KeyboardKey_ModeChange)
      Define(VK_MULTIPLY, Arcadia_Visuals_KeyboardKey_Multiply)

      Define('N', Arcadia_Visuals_KeyboardKey_N)
#if 0
      Define(NonConvert, 29, "IME NonConvert")
      Define(NumberSign, 227, "Number Sign") // "#" aka "VK_OEM_2" in WinAPI.
      Define(NumLock, "Num Lock")
#endif
      Define(VK_NUMPAD0, Arcadia_Visuals_KeyboardKey_NumPad0)
      Define(VK_NUMPAD1, Arcadia_Visuals_KeyboardKey_NumPad1)
      Define(VK_NUMPAD2, Arcadia_Visuals_KeyboardKey_NumPad2)
      Define(VK_NUMPAD3, Arcadia_Visuals_KeyboardKey_NumPad3)
      Define(VK_NUMPAD4, Arcadia_Visuals_KeyboardKey_NumPad4)
      Define(VK_NUMPAD5, Arcadia_Visuals_KeyboardKey_NumPad5)
      Define(VK_NUMPAD6, Arcadia_Visuals_KeyboardKey_NumPad6)
      Define(VK_NUMPAD7, Arcadia_Visuals_KeyboardKey_NumPad7)
      Define(VK_NUMPAD8, Arcadia_Visuals_KeyboardKey_NumPad8)
      Define(VK_NUMPAD9, Arcadia_Visuals_KeyboardKey_NumPad9)
      Define(VK_SEPARATOR, Arcadia_Visuals_KeyboardKey_NumPadEnter) // NumPad Enter

      Define('O', Arcadia_Visuals_KeyboardKey_O)
      Define(VK_OEM_COMMA, Arcadia_Visuals_KeyboardKey_Comma /*Arcadia_Visuals_KeyboardKey_Less*/) 
      Define(VK_OEM_MINUS, Arcadia_Visuals_KeyboardKey_Minus)

      Define('P', Arcadia_Visuals_KeyboardKey_P)
      Define(VK_NEXT, Arcadia_Visuals_KeyboardKey_PageDown)
      Define(VK_PRIOR, Arcadia_Visuals_KeyboardKey_PageUp)
      Define(VK_PAUSE, Arcadia_Visuals_KeyboardKey_Pause)
      Define(VK_OEM_PERIOD, Arcadia_Visuals_KeyboardKey_Period)
      Define(VK_PRINT, Arcadia_Visuals_KeyboardKey_Print)
      Define(VK_OEM_PLUS, Arcadia_Visuals_KeyboardKey_Plus)

      Define('Q', Arcadia_Visuals_KeyboardKey_Q)

      Define('R', Arcadia_Visuals_KeyboardKey_R)
      Define(VK_RCONTROL, Arcadia_Visuals_KeyboardKey_RightControl)
      Define(VK_RETURN, Arcadia_Visuals_KeyboardKey_Return)
      Define(VK_RIGHT, Arcadia_Visuals_KeyboardKey_RightArrow /*Arcadia_Visuals_KeyboardKey_Right*/) // "Right Arrow" and "Right" are aliases of each other.
      Define(VK_RMENU, Arcadia_Visuals_KeyboardKey_RightMenu)
      Define(VK_RSHIFT, Arcadia_Visuals_KeyboardKey_RightShift)
      Define(VK_RWIN, Arcadia_Visuals_KeyboardKey_RightWindows)

      Define('S', Arcadia_Visuals_KeyboardKey_S)
      Define(VK_SCROLL, Arcadia_Visuals_KeyboardKey_ScrollLock)
      Define(VK_SLEEP, Arcadia_Visuals_KeyboardKey_Sleep)
      Define(VK_SPACE, Arcadia_Visuals_KeyboardKey_Space)
      Define(VK_SUBTRACT, Arcadia_Visuals_KeyboardKey_Subtract)

      Define('T', Arcadia_Visuals_KeyboardKey_T)
      Define(VK_TAB, Arcadia_Visuals_KeyboardKey_Tabulator)

      Define('U', Arcadia_Visuals_KeyboardKey_U)
      Define(VK_UP, Arcadia_Visuals_KeyboardKey_UpArrow /*Arcadia_Visuals_KeyboardKey_Up*/) // "Up Arrow" and "Up" are aliases of each other.

      Define('V', Arcadia_Visuals_KeyboardKey_V)

      Define('W', Arcadia_Visuals_KeyboardKey_W)

      Define('X', Arcadia_Visuals_KeyboardKey_X)

      Define('Y', Arcadia_Visuals_KeyboardKey_Y)

      Define('Z', Arcadia_Visuals_KeyboardKey_Z)

    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NotImplemented);
      Arcadia_Thread_popJumpTarget(thread);
    } break;
  };

#undef Define
}

static void
Arcadia_Visuals_Windows_Window_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (NULL != self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (NULL != self->windowHandle) {
    SetWindowLongPtr(self->windowHandle, GWLP_USERDATA, (LONG_PTR)NULL);
    DeleteObject(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (NULL != self->application) {
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->application);
    self->application = NULL;
  }
}

static void
Arcadia_Visuals_Windows_Window_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->application) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->application);
  }
  if (self->title) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->title);
  }
  if (self->smallIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->smallIcon);
  }
  if (self->bigIcon) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->bigIcon);
  }
}

static void
Arcadia_Visuals_Windows_Window_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Windows_Window* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Windows_Window_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->application = NULL;
  _self->title = NULL;
  _self->classAtom = 0;
  _self->windowHandle = NULL;
  _self->deviceContextHandle = NULL;
  _self->glResourceContextHandle = NULL;
  _self->bigIcon = NULL;
  _self->smallIcon = NULL;
  _self->fullscreen = Arcadia_BooleanValue_False;

  _self->title = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, g_title, sizeof(g_title) - 1));
  _self->application = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Visuals_Windows_Application_getType(thread));
  Arcadia_Object_lock(thread, (Arcadia_Object*)_self->application);

  ((Arcadia_Visuals_Window*)_self)->open = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & openImpl;
  ((Arcadia_Visuals_Window*)_self)->close = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & closeImpl;

  ((Arcadia_Visuals_Window*)_self)->getQuitRequested = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getQuitRequestedImpl;
  ((Arcadia_Visuals_Window*)_self)->setQuitRequested = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*,Arcadia_BooleanValue)) & setQuitRequestedImpl;

  ((Arcadia_Visuals_Window*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) &updateImpl;

  ((Arcadia_Visuals_Window*)_self)->getRequiredBigIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredBigIconSizeImpl;
  ((Arcadia_Visuals_Window*)_self)->getRequiredSmallIconSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getRequiredSmallIconSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->getBigIcon = (Arcadia_Visuals_Icon *(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getBigIconImpl;
  ((Arcadia_Visuals_Window*)_self)->setBigIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*)) & setBigIconImpl;

  ((Arcadia_Visuals_Window*)_self)->getSmallIcon = (Arcadia_Visuals_Icon *(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getSmallIconImpl;
  ((Arcadia_Visuals_Window*)_self)->setSmallIcon = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*)) & setSmallIconImpl;

  ((Arcadia_Visuals_Window*)_self)->getTitle = (Arcadia_String*(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getTitleImpl;
  ((Arcadia_Visuals_Window*)_self)->setTitle = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_String*)) & setTitleImpl;

  ((Arcadia_Visuals_Window*)_self)->getCanvasSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getCanvasSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->beginRender = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*))&beginRenderImpl;
  ((Arcadia_Visuals_Window*)_self)->endRender = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*))&endRenderImpl;

  ((Arcadia_Visuals_Window*)_self)->getPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getPositionImpl;
  ((Arcadia_Visuals_Window*)_self)->setPosition = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setPositionImpl;

  ((Arcadia_Visuals_Window*)_self)->getSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*)) & getSizeImpl;
  ((Arcadia_Visuals_Window*)_self)->setSize = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & setSizeImpl;

  ((Arcadia_Visuals_Window*)_self)->getFullscreen = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Visuals_Window*)) & getFullscreenImpl;
  ((Arcadia_Visuals_Window*)_self)->setFullscreen = (void(*)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_BooleanValue)) & setFullscreenImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->windowHandle) {
    return;
  }

  if (!self->classAtom) {
    // Register the window class.
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = self->application->instanceHandle;
    wc.lpszClassName = g_className;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.

    self->classAtom = RegisterClass(&wc);
    if (!self->classAtom) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }

  if (!self->windowHandle) {
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    DWORD dwExStyle = 0;
    self->windowHandle =
      CreateWindowEx
        (
          dwExStyle,                          // extended window style
          g_className,                        // window class
          g_title,                            // window text
          dwStyle,                            // window style
          CW_USEDEFAULT,                      // left
          CW_USEDEFAULT,                      // top
          CW_USEDEFAULT,                      // width
          CW_USEDEFAULT,                      // height
          NULL,                               // parent window
          NULL,                               // menu
          self->application->instanceHandle,  // instance handle
          NULL                                // additional application data
        );

    if (!self->windowHandle) {
      UnregisterClass(g_className, self->application->instanceHandle);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    SetWindowLongPtr(self->windowHandle, GWLP_USERDATA, (LONG_PTR)self);
    MoveWindow(self->windowHandle, ((Arcadia_Visuals_Window*)self)->bounds.left,
                                   ((Arcadia_Visuals_Window*)self)->bounds.top,
                                   ((Arcadia_Visuals_Window*)self)->bounds.width,
                                   ((Arcadia_Visuals_Window*)self)->bounds.height,
                                   TRUE);
  }

  self->deviceContextHandle = GetDC(self->windowHandle);
  if (!self->deviceContextHandle) {
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->application->instanceHandle);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Windows_setWindowText(thread, self->windowHandle, self->title);
    Arcadia_Visuals_Windows_WglFactory* wglFactory = Arcadia_Visuals_Windows_WglFactory_create(thread);
    Arcadia_Visuals_Windows_WglFactory_open(thread, wglFactory);
    createContext(thread, self, wglFactory);
    Arcadia_Visuals_Windows_WglFactory_close(thread, wglFactory);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
    UnregisterClass(g_className, self->application->instanceHandle);
    Arcadia_Thread_jump(thread);
  }

  ShowWindow(self->windowHandle, SW_SHOW);
}

static void
closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (!self->windowHandle) {
    return;
  }
  if (self->glResourceContextHandle) {
    if (self->glResourceContextHandle == wglGetCurrentContext()) {
      wglMakeCurrent(self->deviceContextHandle, NULL);
    }
    wglDeleteContext(self->glResourceContextHandle);
    self->glResourceContextHandle = NULL;
  }
  if (self->deviceContextHandle) {
    ReleaseDC(self->windowHandle, self->deviceContextHandle);
    self->deviceContextHandle = NULL;
  }
  if (self->windowHandle) {
    SetWindowLongPtr(self->windowHandle, GWLP_USERDATA, (LONG_PTR)NULL);
    DestroyWindow(self->windowHandle);
    self->windowHandle = NULL;
  }
  if (self->classAtom) {
    UnregisterClass(g_className, self->application->instanceHandle);
    self->classAtom = 0;
  }
}

static Arcadia_BooleanValue
getFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->fullscreen; }

static void
setFullscreenImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue fullscreen
  )
{
  if (self->windowHandle) {
    if (self->fullscreen != fullscreen) {
      DWORD dwStyle = 0;
      if (fullscreen) {
        dwStyle |= WS_POPUP;
      } else {
        dwStyle |= WS_OVERLAPPEDWINDOW;
      }
      SetWindowLongPtr(self->windowHandle, GWL_STYLE, dwStyle);
      if (!SetWindowPos(self->windowHandle,
                        HWND_TOPMOST,
                        ((Arcadia_Visuals_Window*)self)->bounds.left,
                        ((Arcadia_Visuals_Window*)self)->bounds.top,
                        ((Arcadia_Visuals_Window*)self)->bounds.width,
                        ((Arcadia_Visuals_Window*)self)->bounds.height,
                        SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_SHOWWINDOW)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
        Arcadia_Thread_jump(thread);
      }
      self->fullscreen = fullscreen;
    }
  } else {
    self->fullscreen = fullscreen;
  }
}

static Arcadia_BooleanValue
getQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return g_quitRequested; }

static void
setQuitRequestedImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_BooleanValue quitRequested
  )
{ g_quitRequested = quitRequested; }

static void
updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  MSG msg = { 0 };
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT) {
      g_quitRequested = Arcadia_BooleanValue_True;
    }
  }
}

static void
getRequiredBigIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXICON);
  *height = GetSystemMetrics(SM_CYICON);
}

static void
getRequiredSmallIconSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = GetSystemMetrics(SM_CXSMICON);
  *height = GetSystemMetrics(SM_CYSMICON);
}

static Arcadia_Visuals_Windows_Icon*
getBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->bigIcon; }

static void
setBigIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
  )
{
  self->bigIcon = icon;
  if (self->windowHandle) {
    if (self->bigIcon) {
      SendMessage(self->windowHandle, WM_SETICON, ICON_BIG, (LPARAM)self->bigIcon->hIcon);
    } else {
      SendMessage(self->windowHandle, WM_SETICON, ICON_BIG, (LPARAM)NULL);
    }
  }
}

static Arcadia_Visuals_Windows_Icon*
getSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->smallIcon; }

static void
setSmallIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_Icon* icon
  )
{
  self->smallIcon = icon;
  if (self->windowHandle) {
    if (self->smallIcon) {
      SendMessage(self->windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)self->smallIcon->hIcon);
    } else {
      SendMessage(self->windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)NULL);
    }
  }
}

static Arcadia_String*
getTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{ return self->title; }

static void
setTitleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_String* title
  )
{
  if (!title) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->title = title;
  if (self->windowHandle) {
    Windows_setWindowText(thread, self->windowHandle, title);
  }
}

static void
getCanvasSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  if (!self->windowHandle) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  RECT clientRectangle;
  if (!GetClientRect(self->windowHandle, &clientRectangle)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_StaticAssert(LONG_MAX <= INT32_MAX, "<internal error>");
  *width = clientRectangle.right - clientRectangle.left;
  *height = clientRectangle.bottom - clientRectangle.top;
}

static int
stringToInteger
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  )
{
  Arcadia_Integer64Value target = Arcadia_String_toInteger64(thread, source);
  if (target < INT_MIN || target > INT_MAX) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }
  return (int)target;
}

static Arcadia_BooleanValue
isConfigurationSupported
  (
    Arcadia_Thread* thread,
    Arcadia_List* configurations,
    Arcadia_Visuals_Configuration* configuration
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)configurations); i < n; ++i) {
    Arcadia_Visuals_Configuration* element = Arcadia_List_getObjectReferenceValueAt(thread, configurations, i);
    Arcadia_Value a, b;
    a = Arcadia_Value_makeObjectReferenceValue(element->opengl.version.major);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->opengl.version.major);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->opengl.version.minor);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->opengl.version.minor);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.redBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.redBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.greenBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.greenBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.blueBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.blueBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->colorBuffer.alphaBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->colorBuffer.alphaBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    a = Arcadia_Value_makeObjectReferenceValue(element->depthBuffer.depthBits);
    b = Arcadia_Value_makeObjectReferenceValue(configuration->depthBuffer.depthBits);
    if (!Arcadia_Value_isEqualTo(thread, &a, &b)) {
      continue;
    }
    return Arcadia_BooleanValue_True;
  }
  return Arcadia_BooleanValue_False;
}

static void
createContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Visuals_Windows_WglFactory* wglFactory
  )
{
  // (1) Get supported configuration.
  Arcadia_List* supportedConfigurations = Arcadia_Visuals_Windows_WglFactory_getConfigurations(thread, wglFactory);
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)supportedConfigurations); i < n; ++i) {
    Arcadia_Visuals_Configuration* supportedConfiguration = Arcadia_List_getObjectReferenceValueAt(thread, supportedConfigurations, i);
    Arcadia_StringBuffer_clear(thread, stringBuffer);

    fprintf(stdout, u8"index: %zu\n", i);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"red bits: ", sizeof(u8"red bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.redBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"green bits: ", sizeof(u8"green bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.greenBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"blue bits: ", sizeof(u8"blue bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.blueBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"alpha bits: ", sizeof(u8"alpha bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->colorBuffer.alphaBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"depth bits: ", sizeof(u8"depth bits: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->depthBuffer.depthBits));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"OpenGL major version: ", sizeof(u8"OpenGL major version: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->opengl.version.major));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"OpenGL minor version: ", sizeof(u8"OpenGL minor version: ") - 1);
    Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeObjectReferenceValue(supportedConfiguration->opengl.version.minor));
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

    fwrite(Arcadia_StringBuffer_getBytes(thread, stringBuffer), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, stringBuffer), stdout);

    fprintf(stdout, u8"\n");
  }
  // (2) Get desired configuration.
  Arcadia_Visuals_Configuration* desiredConfiguration = Arcadia_Visuals_Configuration_create(thread);
  // (3) Check if desired configuration is in supported configurations. If yes, continue. If no, fail.
  if (!isConfigurationSupported(thread, supportedConfigurations, desiredConfiguration)) {
    fprintf(stderr, "%s:%d: visuals configuration not supported\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  const int pixelFormatAttribs[] = {
    WGL_ACCELERATION_ARB, // WGL_ACCELERATION_ARB
    WGL_FULL_ACCELERATION_ARB, // WGL_FULL_ACCELERATION_ARB
    WGL_DEPTH_BITS_ARB, stringToInteger(thread, desiredConfiguration->depthBuffer.depthBits), // WGL_DEPTH_BITS_ARB
    WGL_DRAW_TO_WINDOW_ARB, 1, // WGL_DRAW_TO_WINDOW_ARB
    WGL_RED_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.redBits), // WGL_RED_BITS_ARB
    WGL_GREEN_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.greenBits), // WGL_GREEN_BITS_ARB
    WGL_BLUE_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.blueBits), // WGL_BLUE_BITS_ARB
    WGL_ALPHA_BITS_ARB, stringToInteger(thread, desiredConfiguration->colorBuffer.alphaBits), // WGL_ALPHA_BITS_ARB
    WGL_PIXEL_TYPE_ARB,  WGL_TYPE_RGBA_ARB, // WGL_PIXEL_TYPE_ARB // WGL_TYPE_RGBA_ARB
    WGL_SUPPORT_OPENGL_ARB, 1, // WGL_SUPPORT_OPENGL_ARB
    WGL_COLOR_BITS_ARB,	32, // WGL_COLOR_BITS_ARB
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  int pixelFormatIndex;
  int numberOfPixelFormats;
  wglFactory->_wglChoosePixelFormat(self->deviceContextHandle, &pixelFormatAttribs[0], NULL, 1, &pixelFormatIndex, &numberOfPixelFormats);
  if (!numberOfPixelFormats) {
    fprintf(stderr, "%s:%d: failed to select pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  PIXELFORMATDESCRIPTOR pixelFormatDescriptors;
  if (!DescribePixelFormat(self->deviceContextHandle, pixelFormatIndex, sizeof(pixelFormatDescriptors), &pixelFormatDescriptors)) {
    fprintf(stderr, "%s:%d: failed to describe pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!SetPixelFormat(self->deviceContextHandle, pixelFormatIndex, &pixelFormatDescriptors)) {
    fprintf(stderr, "%s:%d: failed to set pixel format\n", __FILE__, __LINE__);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  int contextAttribs[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, stringToInteger(thread, desiredConfiguration->opengl.version.major),
    WGL_CONTEXT_MINOR_VERSION_ARB, stringToInteger(thread, desiredConfiguration->opengl.version.minor),
    WGL_CONTEXT_FLAGS_ARB, 0,
    0
  };
  self->glResourceContextHandle = wglFactory->_wglCreateContextAttribs(self->deviceContextHandle, NULL, &contextAttribs[0]);
  if (!self->glResourceContextHandle) {
    fprintf(stderr, "%s:%d: failed to create OpenGL/WGL context version %"PRIu8".%"PRIu8"\n", \
                     __FILE__, __LINE__, \
                    stringToInteger(thread, desiredConfiguration->opengl.version.major), \
                    stringToInteger(thread, desiredConfiguration->opengl.version.minor));
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  fprintf(stdout, "%s:%d: OpenGL version %"PRIu8".%"PRIu8" selected\n", \
                  __FILE__, __LINE__, \
                  stringToInteger(thread, desiredConfiguration->opengl.version.major), \
                  stringToInteger(thread, desiredConfiguration->opengl.version.minor));
}

static void
beginRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (!wglMakeCurrent(self->deviceContextHandle, self->glResourceContextHandle)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Integer32Value width, height;
  Arcadia_Visuals_Window_getCanvasSize(thread, (Arcadia_Visuals_Window*)self, &width, &height);
  glViewport(0, 0, width, height);
  glClearColor(193.0f/255.0f, 216.0f/255.0f, 195.0f/255.0f, 255.0f/255.0f);
  glClearDepth(1.f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

static void
endRenderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self
  )
{
  if (self->glResourceContextHandle == wglGetCurrentContext()) {
    if (!SwapBuffers(self->deviceContextHandle)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
  }
}

static void
getPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  )
{
  *left = ((Arcadia_Visuals_Window*)self)->bounds.top;
  *top = ((Arcadia_Visuals_Window*)self)->bounds.left;
}

static void
setPositionImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  )
{
  ((Arcadia_Visuals_Window*)self)->bounds.left = left;
  ((Arcadia_Visuals_Window*)self)->bounds.top = top;
  if (self->windowHandle) {
    MoveWindow(self->windowHandle, ((Arcadia_Visuals_Window*)self)->bounds.left,
                                   ((Arcadia_Visuals_Window*)self)->bounds.top,
                                   ((Arcadia_Visuals_Window*)self)->bounds.width,
                                   ((Arcadia_Visuals_Window*)self)->bounds.height,
                                   FALSE);
  }
}

static void
getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  )
{
  *width = ((Arcadia_Visuals_Window*)self)->bounds.width;
  *height = ((Arcadia_Visuals_Window*)self)->bounds.height;
}

static void
setSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  ((Arcadia_Visuals_Window*)self)->bounds.width = width;
  ((Arcadia_Visuals_Window*)self)->bounds.height = height;
  if (self->windowHandle) {
    MoveWindow(self->windowHandle, ((Arcadia_Visuals_Window*)self)->bounds.left,
                                    ((Arcadia_Visuals_Window*)self)->bounds.top,
                                    ((Arcadia_Visuals_Window*)self)->bounds.width,
                                    ((Arcadia_Visuals_Window*)self)->bounds.height,
                                    FALSE);
  }
}

Arcadia_Visuals_Windows_Window*
Arcadia_Visuals_Windows_Window_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_Application* application,
    Arcadia_Visuals_Windows_DisplayDevice* displayDevice
  )
{
  Arcadia_Value argumentValues[] = {
    application ? Arcadia_Value_makeObjectReferenceValue(application) : Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    displayDevice ? Arcadia_Value_makeObjectReferenceValue(displayDevice) : Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Visuals_Windows_Window* self = Arcadia_allocateObject(thread, _Arcadia_Visuals_Windows_Window_getType(thread), 2, &argumentValues[0]);
  return self;
}
