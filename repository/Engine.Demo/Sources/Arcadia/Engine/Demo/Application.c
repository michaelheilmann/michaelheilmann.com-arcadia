#include "Arcadia/Engine/Demo/Application.h"

#include "Arcadia/Engine/Demo/Configuration.h"

static void
Arcadia_Engine_Demo_Application_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self
  );

static void
Arcadia_Engine_Demo_Application_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ApplicationDispatch* self
  );

static void
Arcadia_Engine_Demo_Application_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_Application_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Demo_Application_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_Application_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_Application_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_Application_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.Application", Arcadia_Engine_Demo_Application,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Demo_Application_typeOperations);

static void
Arcadia_Engine_Demo_Application_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_Application_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->quitRequested = Arcadia_BooleanValue_False;
  self->configuration = (Arcadia_DDL_Node*)Cfg_loadConfiguration(thread);
  self->engine = Arcadia_Engine_getOrCreate(thread);
  self->windows = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->window = NULL;
  self->sceneManager = Arcadia_Engine_Demo_SceneManager_create(thread, self->engine);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Engine_Demo_Application_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_ApplicationDispatch* self
  )
{ }

static void
Arcadia_Engine_Demo_Application_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self
  )
{
  if (self->engine) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->engine);
  }
  if (self->windows) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->windows);
  }
  if (self->window) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->window);
  }
  if (self->sceneManager) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->sceneManager);
  }
  if (self->configuration) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->configuration);
  }
}

Arcadia_Engine_Demo_Application*
Arcadia_Engine_Demo_Application_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Demo_Application);
}

Arcadia_BooleanValue
Arcadia_Engine_Demo_Application_getQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self
  )
{ return self->quitRequested; }

void
Arcadia_Engine_Demo_Application_setQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_BooleanValue quitRequested
  )
{ self->quitRequested = quitRequested; }

void
Arcadia_Engine_Demo_Application_onApplicationQuitRequestedEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_Visuals_ApplicationQuitRequestedEvent* event
  )
{ Arcadia_Engine_Demo_Application_setQuitRequested(thread, self, Arcadia_BooleanValue_True); }

void
Arcadia_Engine_Demo_Application_onKeyboardKeyEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_Visuals_KeyboardKeyEvent* event
  )
{
  if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, event) == Arcadia_Visuals_KeyboardKeyAction_Released &&
    Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, event) == Arcadia_Visuals_KeyboardKey_Escape) {
    Arcadia_Engine_Demo_Application_setQuitRequested(thread, self, Arcadia_BooleanValue_True);
  } else if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, event) == Arcadia_Visuals_KeyboardKeyAction_Released &&
    Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, event) == Arcadia_Visuals_KeyboardKey_R) {
    Arcadia_logf(Arcadia_LogFlags_Info, "re-initializing backends\n");
  }
}

static Arcadia_BooleanValue
filterWindows
  (
    Arcadia_Thread* thread,
    Arcadia_Value context,
    Arcadia_Value value
  )
{
  if (Arcadia_Value_isEqualTo(thread, &context, &value)) {
    return Arcadia_BooleanValue_False;
  } else {
    return Arcadia_BooleanValue_True;
  }
}

void
Arcadia_Engine_Demo_Application_onWindowClosedEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Application* self,
    Arcadia_Visuals_WindowClosedEvent* event
  )
{
  Arcadia_List_filter(thread, self->windows, Arcadia_Value_makeObjectReferenceValue(event->window), &filterWindows);
  Arcadia_Engine_Demo_Application_setQuitRequested(thread, self, Arcadia_BooleanValue_True);
}
