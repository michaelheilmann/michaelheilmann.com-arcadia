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

#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/System.h"

#include "Arcadia/Visuals/Implementation/Configure.h"
#include "Arcadia/Visuals/Implementation/Windows/DisplayDevice.h"
#include "Arcadia/Visuals/Implementation/Windows/_GetDisplayDevices.h"
#include "Arcadia/Visuals/Implementation/Windows/Icon.h"
#include "Arcadia/Visuals/Implementation/OpenGL4/WGL/WindowBackend.h"
#include "Arcadia/Visuals/Implementation/Windows/_CharConv.h"

#if defined(Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled
  #include "Arcadia/Visuals/Implementation/Direct3D12/Backend.h"
#endif

#if defined(Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled
  #include "Arcadia/Visuals/Implementation/OpenGL4/Backend.h"
#endif

#if defined(Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled) && 1 == Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled
  #include "Arcadia/Visuals/Implementation/Vulkan/Backend.h"
#endif

static Arcadia_Visuals_Implementation_OpenGL4_WGL_System* g_instance = NULL;

static LRESULT CALLBACK
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_windowCallbackProcedure
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_mapKeyboardKey
  (
    Arcadia_Thread* thread,
    WORD source,
    Arcadia_Visuals_KeyboardKey* target
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  );

static Arcadia_Visuals_Windows_Icon*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self,
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  );

static Arcadia_Visuals_Window*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  );

static Arcadia_List*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  );

static void
destroyCallback
  (
    void* observer,
    void* observed
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Visuals_Implementation_OpenGL4_WGL_System_constructImpl,
  .destruct = &Arcadia_Visuals_Implementation_OpenGL4_WGL_System_destructImpl,
  .visit = &Arcadia_Visuals_Implementation_OpenGL4_WGL_System_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.WGL.System", Arcadia_Visuals_Implementation_OpenGL4_WGL_System,
                         u8"Arcadia.Visuals.System", Arcadia_Visuals_System,
                         &_typeOperations);

static LRESULT CALLBACK
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_windowCallbackProcedure
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
      Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend* window = (Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }   
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Engine_Event* event =
          (Arcadia_Engine_Event*)
            Arcadia_Visuals_WindowClosedEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                (Arcadia_Visuals_Window*)((Arcadia_Visuals_WindowBackend*)window)->window
              );
        Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
      }
      return 0;
    } break;
    case WM_KEYDOWN: {
      Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend* window = (Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Visuals_KeyboardKey keyboardKey;
        Arcadia_Visuals_Implementation_OpenGL4_WGL_System_mapKeyboardKey(thread, LOWORD(wParam), &keyboardKey);
        Arcadia_Engine_Event* event =
          (Arcadia_Engine_Event*)
            Arcadia_Visuals_KeyboardKeyEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                Arcadia_Visuals_KeyboardKeyAction_Pressed,
                keyboardKey
              );
        Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
      }
      return 0;
    } break;
    case WM_KEYUP: {
      Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend* window = (Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        Arcadia_Visuals_KeyboardKey keyboardKey;
        Arcadia_Visuals_Implementation_OpenGL4_WGL_System_mapKeyboardKey(thread, LOWORD(wParam), &keyboardKey);
        Arcadia_Engine_Event* event =
          (Arcadia_Engine_Event*)
            Arcadia_Visuals_KeyboardKeyEvent_create
              (
                thread,
                Arcadia_getTickCount(thread),
                Arcadia_Visuals_KeyboardKeyAction_Released,
                keyboardKey
              );
        Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
        Arcadia_Thread_popJumpTarget(thread);
      } else {
        Arcadia_Thread_popJumpTarget(thread);
      }
      return 0;
    } break;
    case WM_SIZE: {
      Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend* window = (Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0;
      }
      RECT rect;
      GetWindowRect(window->windowHandle, &rect);
      Arcadia_Integer32Value width = rect.right - rect.left;
      Arcadia_Integer32Value height = rect.bottom - rect.top;
      if (width != ((Arcadia_Visuals_WindowBackend*)window)->bounds.width ||
          height != ((Arcadia_Visuals_WindowBackend*)window)->bounds.height) {
        ((Arcadia_Visuals_WindowBackend*)window)->bounds.width = width;
        ((Arcadia_Visuals_WindowBackend*)window)->bounds.height = height;
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          Arcadia_Engine_Event* event =
            (Arcadia_Engine_Event*)
              Arcadia_Visuals_WindowSizeChangedEvent_create
                (
                  thread,
                  Arcadia_getTickCount(thread),
                  (Arcadia_Visuals_Window*)((Arcadia_Visuals_WindowBackend*)window)->window,
                  width,
                  height
                );
          Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
          Arcadia_Thread_popJumpTarget(thread);
        } else {
          Arcadia_Thread_popJumpTarget(thread);
        }
      }
      return 0;
    } break;
    case WM_MOVE: {
      Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend* window = (Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
      if (!window) {
        return 0; // There is nothing we can do actually.
      }
      RECT rect;
      GetWindowRect(window->windowHandle, &rect);
      Arcadia_Integer32Value left = rect.left;
      Arcadia_Integer32Value top = rect.top;
      if (left != ((Arcadia_Visuals_WindowBackend*)window)->bounds.left ||
          top != ((Arcadia_Visuals_WindowBackend*)window)->bounds.top) {
        ((Arcadia_Visuals_WindowBackend*)window)->bounds.left = left;
        ((Arcadia_Visuals_WindowBackend*)window)->bounds.top = top;
        Arcadia_JumpTarget jumpTarget;
        Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
        if (Arcadia_JumpTarget_save(&jumpTarget)) {
          Arcadia_Engine_Event* event =
            (Arcadia_Engine_Event*)
              Arcadia_Visuals_WindowPositionChangedEvent_create
                (
                  thread,
                  Arcadia_getTickCount(thread),
                  (Arcadia_Visuals_Window*)((Arcadia_Visuals_WindowBackend*)window)->window,
                  left,
                  top
                );
          Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
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
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_mapKeyboardKey
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
      Define('0', Arcadia_Visuals_KeyboardKey_Zero)
      Define('1', Arcadia_Visuals_KeyboardKey_One)
      Define('2', Arcadia_Visuals_KeyboardKey_Two)
      Define('3', Arcadia_Visuals_KeyboardKey_Three)
      Define('4', Arcadia_Visuals_KeyboardKey_Four)
      Define('5', Arcadia_Visuals_KeyboardKey_Five)
      Define('6', Arcadia_Visuals_KeyboardKey_Six)
      Define('7', Arcadia_Visuals_KeyboardKey_Seven)
      Define('8', Arcadia_Visuals_KeyboardKey_Eight)
      Define('9', Arcadia_Visuals_KeyboardKey_Nine)

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
      Define(VK_NUMPAD0, Arcadia_Visuals_KeyboardKey_NumPadZero)
      Define(VK_NUMPAD1, Arcadia_Visuals_KeyboardKey_NumPadOne)
      Define(VK_NUMPAD2, Arcadia_Visuals_KeyboardKey_NumPadTwo)
      Define(VK_NUMPAD3, Arcadia_Visuals_KeyboardKey_NumPadThree)
      Define(VK_NUMPAD4, Arcadia_Visuals_KeyboardKey_NumPadFour)
      Define(VK_NUMPAD5, Arcadia_Visuals_KeyboardKey_NumPadFive)
      Define(VK_NUMPAD6, Arcadia_Visuals_KeyboardKey_NumPadSix)
      Define(VK_NUMPAD7, Arcadia_Visuals_KeyboardKey_NumPadSeven)
      Define(VK_NUMPAD8, Arcadia_Visuals_KeyboardKey_NumPadEight)
      Define(VK_NUMPAD9, Arcadia_Visuals_KeyboardKey_NumPadNine)
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
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  )
{
  MSG msg = { 0 };
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT) {
      Arcadia_Engine_Event* event =
        (Arcadia_Engine_Event*)
        Arcadia_Visuals_ApplicationQuitRequestedEvent_create
          (
            thread,
            Arcadia_getTickCount(thread),
            (Arcadia_Visuals_System*)self
          );
      Arcadia_Engine_enqueEvent(thread, Arcadia_Engine_getOrCreate(thread), event);
    }
  }
}

static Arcadia_Visuals_Windows_Icon*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_createIconImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self,
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  )
{
  Arcadia_Visuals_Windows_Icon* icon = Arcadia_Visuals_Windows_Icon_create(thread, pixelBuffer);
  return icon;
}

static Arcadia_Visuals_Window*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_createWindowImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  )
{
  Arcadia_Visuals_WindowBackend* windowBackend = (Arcadia_Visuals_WindowBackend*)Arcadia_Visuals_Implementation_OpenGL4_WGL_WindowBackend_create(thread, self, NULL);
  Arcadia_Visuals_Window* window = Arcadia_Visuals_Window_create(thread);
  Arcadia_WeakReference* windowWeakReference =
    Arcadia_WeakReference_create
      (
        thread,
        Arcadia_Value_makeObjectReferenceValue(windowBackend)
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, ((Arcadia_Visuals_System*)self)->windows, (Arcadia_Object*)windowWeakReference);
  window->backend = windowBackend;
  windowBackend->window = window;
  return window;
}

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Visuals_Implementation_OpenGL4_WGL_System* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_WGL_System_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->defaultWindowCallbackProcedure = &Arcadia_Visuals_Implementation_OpenGL4_WGL_System_windowCallbackProcedure;
  _self->instanceHandle = GetModuleHandle(NULL);
  if (!_self->instanceHandle) {
    _self->defaultWindowCallbackProcedure = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
    _self->instanceHandle = NULL;
    _self->defaultWindowCallbackProcedure = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  
  _self->className = _strdup(u8"Aracadia.Visuals.WGL.Window|WindowClass");
  if (!_self->className) {
    _self->instanceHandle = NULL;
    _self->defaultWindowCallbackProcedure = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);  
  }

  WNDCLASS wc = { 0 };
  wc.lpfnWndProc = _self->defaultWindowCallbackProcedure;
  wc.hInstance = _self->instanceHandle;
  wc.lpszClassName = _self->className;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.
  _self->classAtom = RegisterClass(&wc);
  if (!_self->classAtom) {
    free(_self->className);
    _self->className = NULL;
    _self->instanceHandle = NULL;
    _self->defaultWindowCallbackProcedure = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }

  _self->glResourceContextHandle = NULL;

  ((Arcadia_Visuals_System*)_self)->createIcon = (Arcadia_Visuals_Icon * (*)(Arcadia_Thread*, Arcadia_Visuals_System*, Arcadia_Imaging_PixelBuffer*)) & Arcadia_Visuals_Implementation_OpenGL4_WGL_System_createIconImpl;
  ((Arcadia_Visuals_System*)_self)->createWindow = (Arcadia_Visuals_Window * (*)(Arcadia_Thread*, Arcadia_Visuals_System*)) & Arcadia_Visuals_Implementation_OpenGL4_WGL_System_createWindowImpl;
  ((Arcadia_Visuals_System*)_self)->getDisplayDevices = (Arcadia_List* (*)(Arcadia_Thread*, Arcadia_Visuals_System*)) & Arcadia_Visuals_Implementation_OpenGL4_WGL_System_getDisplayDevicesImpl;
  ((Arcadia_Visuals_System*)_self)->update = (void(*)(Arcadia_Thread*, Arcadia_Visuals_System*)) & Arcadia_Visuals_Implementation_OpenGL4_WGL_System_updateImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  )
{
  if (self->classAtom) {
    UnregisterClass(self->className, self->instanceHandle);
    self->classAtom = 0;
  }
  if (self->className) {
    free(self->className),
    self->className = NULL;
  }
  if (self->instanceHandle) {
    self->instanceHandle = NULL;
  }
  if (self->defaultWindowCallbackProcedure) {
    self->defaultWindowCallbackProcedure = NULL;
  }
}

static void
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  )
{ }

static Arcadia_List*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_getDisplayDevicesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* self
  )
{
  return _getDisplayDevices(thread);
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

Arcadia_Visuals_Implementation_OpenGL4_WGL_System*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_WGL_System);
}

Arcadia_Visuals_Implementation_OpenGL4_WGL_System*
Arcadia_Visuals_Implementation_OpenGL4_WGL_System_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Visuals_Implementation_OpenGL4_WGL_System* instance = Arcadia_Visuals_Implementation_OpenGL4_WGL_System_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
