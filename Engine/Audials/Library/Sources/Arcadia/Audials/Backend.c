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

#include "Arcadia/Audials/Backend.h"

static void
Arcadia_Audials_Backend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Audials_Backend_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.Backend", Arcadia_Audials_Backend,
                         u8"Arcadia.Engine.Backend", Arcadia_Engine_Backend,
                         &_typeOperations);

static void
Arcadia_Audials_Backend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Audials_Backend* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Audials_Backend_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->close = NULL;
  _self->createSystem = NULL;
  _self->getName = NULL;
  _self->open = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

void
Arcadia_Audials_Backend_open
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  )
{ self->open(thread, self); }

void
Arcadia_Audials_Backend_close
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  )
{ self->close(thread, self); }

Arcadia_String*
Arcadia_Audials_Backend_getName
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  )
{ return self->getName(thread, self); }

Arcadia_Audials_System*
Arcadia_Audials_System_createSystem
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Backend* self
  )
{ return self->createSystem(thread, self); }
