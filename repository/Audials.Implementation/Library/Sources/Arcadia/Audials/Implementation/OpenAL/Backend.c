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

#define ARCADIA_AUDIALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/OpenAL/Backend.h"

#include "Arcadia/Audials/Implementation/OpenAL/System.h"

static void
Arcadia_Audials_OpenAL_Backend_openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  );

static void
Arcadia_Audials_OpenAL_Backend_closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  );
  
static Arcadia_String*
Arcadia_Audials_OpenAL_Backend_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  );

static void
Arcadia_Audials_OpenAL_Backend_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Audials_OpenAL_Backend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  );
  
static void
Arcadia_Audials_OpenAL_Backend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Audials_OpenAL_Backend_objectTypeOperations = {
  .construct = &Arcadia_Audials_OpenAL_Backend_construct,
  .destruct = &Arcadia_Audials_OpenAL_Backend_destruct,
  .visit = &Arcadia_Audials_OpenAL_Backend_visit,
};

static const Arcadia_Type_Operations _Arcadia_Audials_OpenAL_Backend_typeOperations = {
  .objectTypeOperations = &_Arcadia_Audials_OpenAL_Backend_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcadia.Audials.OpenAL.Backend", Arcadia_Audials_OpenAL_Backend,
                         u8"Arcadia.Audials.Backend", Arcadia_Audials_Backend,
                         &_Arcadia_Audials_OpenAL_Backend_typeOperations);

static void
Arcadia_Audials_OpenAL_Backend_openImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_OpenAL_Backend_closeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  )
{/*Intentionally empty.*/}
  
static Arcadia_String*
Arcadia_Audials_OpenAL_Backend_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  )
{ return Arcadia_String_createFromCxxString(thread, u8"Arcadia Audials OpenAL Backend"); }

static Arcadia_Audials_System*
Arcadia_Audials_OpenAL_Backend_createSystemImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  )
{
  return (Arcadia_Audials_System*)Arcadia_Audials_OpenAL_System_getOrCreate(thread);
}

static void
Arcadia_Audials_OpenAL_Backend_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Audials_OpenAL_Backend* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Audials_OpenAL_Backend_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);

  ((Arcadia_Audials_Backend*)_self)->open = (void (*)(Arcadia_Thread*, Arcadia_Audials_Backend*))&Arcadia_Audials_OpenAL_Backend_openImpl;
  ((Arcadia_Audials_Backend*)_self)->close = (void (*)(Arcadia_Thread*, Arcadia_Audials_Backend*))&Arcadia_Audials_OpenAL_Backend_closeImpl;
  ((Arcadia_Audials_Backend*)_self)->createSystem = (Arcadia_Audials_System* (*)(Arcadia_Thread*, Arcadia_Audials_Backend*))&Arcadia_Audials_OpenAL_Backend_createSystemImpl;
  ((Arcadia_Audials_Backend*)_self)->getName = (Arcadia_String *(*)(Arcadia_Thread*, Arcadia_Audials_Backend*)) & Arcadia_Audials_OpenAL_Backend_getNameImpl;

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

static void
Arcadia_Audials_OpenAL_Backend_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Audials_OpenAL_Backend_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_OpenAL_Backend* self
  )
{/*Intentionally empty.*/}

Arcadia_Audials_OpenAL_Backend*
Arcadia_Audials_OpenAL_Backend_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_OpenAL_Backend);
}
