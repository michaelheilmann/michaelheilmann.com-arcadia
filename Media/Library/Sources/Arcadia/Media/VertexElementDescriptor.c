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

#define ARCADIA_MEDIA_MODULE (1)
#include "Arcadia/Media/VertexElementDescriptor.h"

static void
Arcadia_Media_VertexElementDescriptor_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  );

static void
Arcadia_Media_VertexElementDescriptor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptorDispatch* self
  );

static void
Arcadia_Media_VertexElementDescriptor_isEqualTo
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_Media_VertexElementDescriptor_isNotEqualTo
  (
    Arcadia_Thread* thread
  );

static const Arcadia_ObjectType_Operations _Arcadia_Media_VertexElementDescriptor_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Media_VertexElementDescriptor_construct,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Media_VertexElementDescriptor_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_Media_VertexElementDescriptor_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Media_VertexElementDescriptor_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.VertexElementDescriptor", Arcadia_Media_VertexElementDescriptor,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Media_VertexElementDescriptor_typeOperations);

static void
Arcadia_Media_VertexElementDescriptor_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Media_VertexElementDescriptor);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->source = Arcadia_Natural8Value_Literal(0);
  self->offset = Arcadia_ValueStack_getNatural32Value(thread, 3);
  self->semantics = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->syntactics = Arcadia_ValueStack_getInteger32Value(thread, 1);
  //
  Arcadia_LeaveConstructor(Arcadia_Media_VertexElementDescriptor);
}

static void
Arcadia_Media_VertexElementDescriptor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptorDispatch* self
  )
{
  ((Arcadia_ObjectDispatch*)self)->isEqualTo = &Arcadia_Media_VertexElementDescriptor_isEqualTo;
  ((Arcadia_ObjectDispatch*)self)->isNotEqualTo = &Arcadia_Media_VertexElementDescriptor_isNotEqualTo;
}

static void
Arcadia_Media_VertexElementDescriptor_isEqualTo
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
  Arcadia_Media_VertexElementDescriptor* xx = (Arcadia_Media_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValueChecked(thread, x, _Arcadia_Media_VertexElementDescriptor_getType(thread));


  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1);
  Arcadia_ValueStack_popValues(thread, 3);
  if (!Arcadia_Value_isInstanceOf(thread, &y, _Arcadia_Media_VertexElementDescriptor_getType(thread))) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  } else {
    Arcadia_Media_VertexElementDescriptor* yy = (Arcadia_Media_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValue(&y);
    Arcadia_ValueStack_pushBooleanValue(thread, xx->offset == yy->offset &&
                                                xx->semantics == yy->semantics &&
                                                xx->syntactics == yy->syntactics);
  }
}

static void
Arcadia_Media_VertexElementDescriptor_isNotEqualTo
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
  Arcadia_Media_VertexElementDescriptor* xx = (Arcadia_Media_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValueChecked(thread, x, _Arcadia_Media_VertexElementDescriptor_getType(thread));

  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1);
  Arcadia_ValueStack_popValues(thread, 3);
  if (!Arcadia_Value_isInstanceOf(thread, &y, _Arcadia_Media_VertexElementDescriptor_getType(thread))) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
  } else {
    Arcadia_Media_VertexElementDescriptor* yy = (Arcadia_Media_VertexElementDescriptor*)Arcadia_Value_getObjectReferenceValue(&y);
    Arcadia_ValueStack_pushBooleanValue(thread, xx->offset != yy->offset ||
                                                xx->semantics != yy->semantics ||
                                                xx->syntactics != yy->syntactics);
  }
}

Arcadia_Media_VertexElementDescriptor*
Arcadia_Media_VertexElementDescriptor_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value offset,
    Arcadia_Media_VertexElementSemantics semantics,
    Arcadia_Media_VertexElementSyntactics syntactics
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural32Value(thread, offset);
  Arcadia_ValueStack_pushInteger32Value(thread, semantics);
  Arcadia_ValueStack_pushInteger32Value(thread, syntactics);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Media_VertexElementDescriptor);
}

Arcadia_Natural8Value
Arcadia_Media_VertexElementDescriptor_getSource
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  )
{ return self->source; }

Arcadia_Natural32Value
Arcadia_Media_VertexElementDescriptor_getOffset
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  )
{ return self->offset; }

Arcadia_Media_VertexElementSemantics
Arcadia_Media_VertexElementDescriptor_getSemantics
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  )
{ return self->semantics; }

Arcadia_Media_VertexElementSyntactics
Arcadia_Media_VertexElementDescriptor_getSyntactics
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  )
{ return self->syntactics; }

Arcadia_Natural32Value
Arcadia_Media_VertexElementDescriptor_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Media_VertexElementDescriptor* self
  )
{ 
  switch (self->syntactics) {
    case Arcadia_Media_VertexElementSyntactics_Real32: {
      return sizeof(Arcadia_Real32Value) * 1;
    } break;
    case Arcadia_Media_VertexElementSyntactics_Real32Real32: {
      return sizeof(Arcadia_Real32Value) * 2;
    } break;
    case Arcadia_Media_VertexElementSyntactics_Real32Real32Real32: {
      return sizeof(Arcadia_Real32Value) * 3;
    } break;
    case Arcadia_Media_VertexElementSyntactics_Real32Real32Real32Real32: {
      return sizeof(Arcadia_Real32Value) * 4;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}
