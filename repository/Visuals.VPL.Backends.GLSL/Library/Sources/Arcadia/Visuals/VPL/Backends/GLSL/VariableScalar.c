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

#include "Arcadia/Visuals/VPL/Backends/GLSL/VariableScalar.h"

#include <string.h>

static void
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar* self
  );

static void
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalarDispatch* self
  );

static void
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.VariableScalar", Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 4 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->location = Arcadia_ValueStack_getInteger32Value(thread, 4);
  self->isInput = Arcadia_ValueStack_getBooleanValue(thread, 3);
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  self->type = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 4 + 1);
}

static void
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalarDispatch* self
  )
{ }

static void
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->type);
  }
}

Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar*
Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value location,
    Arcadia_BooleanValue isInput,
    Arcadia_String* name,
    Arcadia_String* type
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, location);
  Arcadia_ValueStack_pushBooleanValue(thread, isInput);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (type) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)type);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar);
}
