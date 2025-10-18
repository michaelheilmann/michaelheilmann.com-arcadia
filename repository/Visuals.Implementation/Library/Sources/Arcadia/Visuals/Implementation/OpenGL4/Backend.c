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

#define ARCADIA_VISUALS_IMPLEMENTATION_PRIVATE (1)
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
Arcadia_Visuals_Implementation_OpenGL4_Backend_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  );

static Arcadia_Visuals_BackendContext*
Arcadia_Visuals_Implementation_OpenGL4_Backend_createBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Backend_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Backend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  );

static void
Arcadia_Visuals_Implementation_OpenGL4_Backend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Visuals_Implementation_OpenGL4_Backend_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) &Arcadia_Visuals_Implementation_OpenGL4_Backend_construct,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_Backend_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_OpenGL4_Backend_visit,
};

static const Arcadia_Type_Operations _Arcadia_Visuals_Implementation_OpenGL4_Backend_typeOperations = {
  .objectTypeOperations = &_Arcadia_Visuals_Implementation_OpenGL4_Backend_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.OpenGL4.Backend", Arcadia_Visuals_Implementation_OpenGL4_Backend,
                         u8"Arcadia.Visuals.Backend", Arcadia_Visuals_Backend,
                         &_Arcadia_Visuals_Implementation_OpenGL4_Backend_typeOperations);

static Arcadia_String*
Arcadia_Visuals_Implementation_OpenGL4_Backend_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  )
{ return Arcadia_String_createFromCxxString(thread, u8"Arcadia Visuals OpenGL 4 Backend"); }

static Arcadia_Visuals_BackendContext*
Arcadia_Visuals_Implementation_OpenGL4_Backend_createBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  )
{
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  return (Arcadia_Visuals_BackendContext*)Arcadia_Visuals_Implementation_OpenGL4_WGL_BackendContext_getOrCreate(thread);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  return (Arcadia_Visuals_BackendContext*)Arcadia_Visuals_Implementation_OpenGL4_GLX_BackendContext_getOrCreate(thread);
#else
  #error("environment system not (yet) supported")
#endif
}

static void
Arcadia_Visuals_Implementation_OpenGL4_Backend_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_OpenGL4_Backend_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);

  ((Arcadia_Engine_Backend*)self)->createBackendContext = (Arcadia_Engine_BackendContext* (*)(Arcadia_Thread*, Arcadia_Engine_Backend*))& Arcadia_Visuals_Implementation_OpenGL4_Backend_createBackendContextImpl;
  ((Arcadia_Engine_Backend*)self)->getName = (Arcadia_String *(*)(Arcadia_Thread*, Arcadia_Engine_Backend*))&Arcadia_Visuals_Implementation_OpenGL4_Backend_getNameImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Visuals_Implementation_OpenGL4_Backend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_OpenGL4_Backend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_OpenGL4_Backend* self
  )
{/*Intentionally empty.*/}

Arcadia_Visuals_Implementation_OpenGL4_Backend*
Arcadia_Visuals_Implementation_OpenGL4_Backend_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Implementation_OpenGL4_Backend);
}
