#if !defined(ARCADIA_ENGINE_DEMO_APPLICATION_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_APPLICATION_H_INCLUDED

#include "Arcadia/DDL/Include.h"
#include "Arcadia/Visuals/Include.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Engine/Demo/Scene.h"
#include "Arcadia/Engine/Demo/SceneManager.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.Application", Arcadia_Engine_Demo_Application,
                          u8"Arcadia.Object");

struct Arcadia_Engine_Demo_ApplicationDispatch {
  Arcadia_ObjectDispatch parent;
};

struct Arcadia_Engine_Demo_Application {
  Arcadia_Object parent;
  /// @a Arcadia_BooleanValue_False if quit was not requested.
  /// @a Arcadia_BooleanValue_True if quit was requested.
  /// @default Arcadia_BooleanValue_False
  Arcadia_BooleanValue quitRequested;
  /// @brief A pointer to the engine.
  Arcadia_Engine* engine;
  /// @brief A list of windows. When a window is closed, it is removed from that list.
  /// If all windows were removed, an application quit request message is sent.
  Arcadia_List* windows;
  /// @brief A pointer to the window.
  Arcadia_Visuals_Window* window;
  /// @brief A pointer to the scene manager.
  Arcadia_Engine_Demo_SceneManager* sceneManager;
  /// @brief A pointer to the configuration
  Arcadia_DDL_Node* configuration;
};

Arcadia_Engine_Demo_Application*
Arcadia_Engine_Demo_Application_create
  (
    Arcadia_Thread* thread
  );

Arcadia_BooleanValue
Arcadia_Engine_Demo_Application_getQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self
  );

void
Arcadia_Engine_Demo_Application_setQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_BooleanValue quitRequested
  );

void
Arcadia_Engine_Demo_Application_onApplicationQuitRequestedEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_Visuals_ApplicationQuitRequestedEvent* event
  );

void
Arcadia_Engine_Demo_Application_onKeyboardKeyEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_Visuals_KeyboardKeyEvent* event
  );

void
Arcadia_Engine_Demo_Application_onWindowClosedEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_Visuals_WindowClosedEvent* event
  );

#endif // ARCADIA_ENGINE_DEMO_APPLICATION_H_INCLUDED
