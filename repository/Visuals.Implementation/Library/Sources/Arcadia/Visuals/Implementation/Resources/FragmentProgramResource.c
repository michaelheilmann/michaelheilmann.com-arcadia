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

#include "Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h"

#include "Arcadia/Visuals/Implementation/VPL/GLSL/Include.h"
#include "Arcadia/Visuals/Implementation/BackendContext.h"
#include <assert.h>

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResourceDispatch* self
  );

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResource* self
  );

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_FragmentProgramResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_FragmentProgramResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_FragmentProgramResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.FragmentProgramResource", Arcadia_Visuals_Implementation_FragmentProgramResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_FragmentProgramResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->dirty = Arcadia_BooleanValue_True;
  Arcadia_Visuals_VPL_Program* program = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_VPL_Program_getType(thread));
  Arcadia_ByteBuffer* codeBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* t = Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_create(thread);
  Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader(thread, t, program, codeBuffer);
  Arcadia_ImmutableByteArray* code = Arcadia_ImmutableByteArray_create(thread, Arcadia_ByteBuffer_getBytes(thread, codeBuffer),
                                                                               Arcadia_ByteBuffer_getNumberOfBytes(thread, codeBuffer));
  self->code = code;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResourceDispatch* self
  )
{ }

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_FragmentProgramResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_FragmentProgramResource* self
  )
{
  if (self->code) {
    Arcadia_ImmutableByteArray_visit(thread, self->code);
  }
}
