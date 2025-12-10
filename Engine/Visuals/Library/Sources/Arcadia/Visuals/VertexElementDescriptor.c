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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/VertexDescriptor.h"

static void
Arcadia_Visuals_VertexElementDescriptor_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VertexElementDescriptor* self
  );

static void
Arcadia_Visuals_VertexElementDescriptor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VertexElementDescriptorDispatch* self
  );

static void
Arcadia_Visuals_VertexElementDescriptor_isEqualTo
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_Visuals_VertexElementDescriptor_isNotEqualTo
  (
    Arcadia_Thread* thread
  );

static const Arcadia_ObjectType_Operations _Arcadia_Visuals_VertexElementDescriptor_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Visuals_VertexElementDescriptor_construct,
};

static const Arcadia_Type_Operations _Arcadia_Visuals_VertexElementDescriptor_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Visuals_VertexElementDescriptor_objectTypeOperations,
  .equalTo = &Arcadia_Visuals_VertexElementDescriptor_isEqualTo,
  .notEqualTo = &Arcadia_Visuals_VertexElementDescriptor_isNotEqualTo
};

Arcadia_defineObjectType(u8"Arcardia.Visuals.VertexElementDescriptor", Arcadia_Visuals_VertexElementDescriptor,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Visuals_VertexElementDescriptor_typeOperations);

static void
Arcadia_Visuals_VertexElementDescriptor_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VertexElementDescriptor* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VertexElementDescriptor_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->offset = Arcadia_ValueStack_getNatural32Value(thread, 3);
  self->semantics = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->syntactics = Arcadia_ValueStack_getInteger32Value(thread, 1);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 3 + 1);
}

static void
Arcadia_Visuals_VertexElementDescriptor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VertexElementDescriptorDispatch* self
  )
{ }

static void
Arcadia_Visuals_VertexElementDescriptor_isEqualTo
  (
    Arcadia_Thread* thread
  )
{
  if (Arcadia_ValueStack_getSize(thread) < 3) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 2);
  Arcadia_Visuals_VertexElementDescriptor* xx = (Arcadia_Visuals_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValueChecked(thread, x, _Arcadia_Visuals_VertexElementDescriptor_getType(thread));


  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1);
  Arcadia_ValueStack_popValues(thread, 3);
  if (!Arcadia_Value_isInstanceOf(thread, &y, _Arcadia_Visuals_VertexElementDescriptor_getType(thread))) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  } else {
    Arcadia_Visuals_VertexElementDescriptor* yy = (Arcadia_Visuals_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValue(&y);
    Arcadia_ValueStack_pushBooleanValue(thread, xx->offset == yy->offset &&
                                                xx->semantics == yy->semantics &&
                                                xx->syntactics == yy->syntactics);
  }
}

static void
Arcadia_Visuals_VertexElementDescriptor_isNotEqualTo
  (
    Arcadia_Thread* thread
  )
{
  if (Arcadia_ValueStack_getSize(thread) < 3) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 2);
  Arcadia_Visuals_VertexElementDescriptor* xx = (Arcadia_Visuals_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValueChecked(thread, x, _Arcadia_Visuals_VertexElementDescriptor_getType(thread));

  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1);
  Arcadia_ValueStack_popValues(thread, 3);
  if (!Arcadia_Value_isInstanceOf(thread, &y, _Arcadia_Visuals_VertexElementDescriptor_getType(thread))) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
  } else {
    Arcadia_Visuals_VertexElementDescriptor* yy = (Arcadia_Visuals_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValue(&y);
    Arcadia_ValueStack_pushBooleanValue(thread, xx->offset != yy->offset ||
                                                xx->semantics != yy->semantics ||
                                                xx->syntactics != yy->syntactics);
  }
}

Arcadia_Visuals_VertexElementDescriptor*
Arcadia_Visuals_VertexElementDescriptor_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value offset,
    Arcadia_Visuals_VertexElementSemantics semantics,
    Arcadia_Visuals_VertexElementSyntactics syntactics
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural32Value(thread, offset);
  Arcadia_ValueStack_pushInteger32Value(thread, semantics);
  Arcadia_ValueStack_pushInteger32Value(thread, syntactics);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VertexElementDescriptor);
}
