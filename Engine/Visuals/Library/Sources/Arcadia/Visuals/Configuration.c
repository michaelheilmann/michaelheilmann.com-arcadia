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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Configuration.h"

static void
Arcadia_Visuals_Configuration_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Configuration* self
  );

static void
Arcadia_Visuals_Configuration_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Configuration* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Visuals_Configuration_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_Configuration_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Configuration", Arcadia_Visuals_Configuration,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Configuration_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Configuration* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->opengl.version.major);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->opengl.version.minor);

  Arcadia_Object_visit(thread, (Arcadia_Object*)self->depthBuffer.depthBits);

  Arcadia_Object_visit(thread, (Arcadia_Object*)self->colorBuffer.redBits);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->colorBuffer.greenBits);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->colorBuffer.blueBits);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->colorBuffer.alphaBits);
}

static void
Arcadia_Visuals_Configuration_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Configuration* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Configuration_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->opengl.version.major = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"4", sizeof(u8"4") - 1));
  self->opengl.version.minor = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"3", sizeof(u8"3") - 1));

  self->depthBuffer.depthBits = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"24", sizeof(u8"24") - 1));

  self->colorBuffer.redBits = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"8", sizeof(u8"8") - 1));
  self->colorBuffer.greenBits = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"8", sizeof(u8"8") - 1));
  self->colorBuffer.blueBits = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"8", sizeof(u8"8") - 1));
  self->colorBuffer.alphaBits = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"8", sizeof(u8"8") - 1));

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

Arcadia_Visuals_Configuration*
Arcadia_Visuals_Configuration_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_Configuration);
}
