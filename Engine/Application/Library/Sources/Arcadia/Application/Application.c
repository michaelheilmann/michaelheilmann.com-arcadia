#include "Arcadia/Application/Application.h"

static void
Arcadia_Engine_Application_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  );

static void
Arcadia_Engine_Application_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_ApplicationDispatch* self
  );

static void
Arcadia_Engine_Application_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Application_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Application_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Application_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Application_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Application_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Application_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Application", Arcadia_Engine_Application,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Application_typeOperations);

static void
Arcadia_Engine_Application_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Application);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->quitRequested = Arcadia_BooleanValue_False;
  self->configuration = NULL;
  self->engine = Arcadia_Engine_getOrCreate(thread);
  self->windows = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  //
  Arcadia_LeaveConstructor(Arcadia_Engine_Application);
}

static void
Arcadia_Engine_Application_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_ApplicationDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Application_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  )
{
  if (self->engine) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->engine);
  }
  if (self->windows) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->windows);
  }
  if (self->configuration) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->configuration);
  }
}

void
Arcadia_Engine_Application_startup
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Application, startup, self); }

void
Arcadia_Engine_Application_shutdown
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Application, shutdown, self); }

Arcadia_BooleanValue
Arcadia_Engine_Application_getQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self
  )
{ return self->quitRequested; }

void
Arcadia_Engine_Application_setQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Application* self,
    Arcadia_BooleanValue quitRequested
  )
{ self->quitRequested = quitRequested; }
