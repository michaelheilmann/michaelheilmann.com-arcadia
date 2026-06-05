// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_ENGINE_VISUALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Visuals/Implementation/OpenGL4/Backend.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows

  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>

  #include <GL/glcorearb.h>

  #include "Arcadia/Visuals/Implementation/OpenGL4/WGL/BackendContext.h"

#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem

  #include <GL/glcorearb.h>

  #include "Arcadia/Visuals/Implementation/OpenGL4/GLX/BackendContext.h"

#else

  #error("environment system not (yet) supported")

#endif

static Arcadia_String*
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  );

static Arcadia_Visuals_BackendContext*
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_createBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  );

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  );

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_BackendDispatch* self
  );

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  );

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.Backend", Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend,
                         u8"Arcadia.Engine.Visuals.Backend", Arcadia_Engine_Visuals_Backend,
                         &_Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_typeOperations);

static Arcadia_String*
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  )
{ return Arcadia_String_createFromCxxString(thread, u8"Arcadia Visuals OpenGL 4 Backend"); }

static Arcadia_Visuals_BackendContext*
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_createBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  return (Arcadia_Visuals_BackendContext*)Arcadia_Engine_Visuals_Implementation_OpenGL4_WGL_BackendContext_getOrCreate(thread);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  return (Arcadia_Visuals_BackendContext*)Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_BackendContext_getOrCreate(thread);
#else
  #error("environment system not (yet) supported")
#endif
}

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_LeaveConstructor(Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend);
}

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_BackendDispatch* self
  )
{
  ((Arcadia_Engine_BackendDispatch*)self)->createBackendContext = (Arcadia_Engine_BackendContext * (*)(Arcadia_Thread*, Arcadia_Engine_Backend*)) & Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_createBackendContextImpl;
  ((Arcadia_Engine_BackendDispatch*)self)->getName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_Engine_Backend*)) & Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_getNameImpl;
}

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend* self
  )
{/*Intentionally empty.*/}

Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend*
Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_Implementation_OpenGL4_Backend);
}
