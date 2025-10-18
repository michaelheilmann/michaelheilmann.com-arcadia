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
#include "Arcadia/Visuals/Context.h"

static void
Arcadia_Visuals_Context_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self
  );

static void
Arcadia_Visuals_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self
  );
  
static void
Arcadia_Visuals_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Visuals_Context_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Visuals_Context_construct,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Context_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Context_visit,
};

static const Arcadia_Type_Operations _Arcadia_Visuals_Context_typeOperations = {
  .objectTypeOperations = &_Arcadia_Visuals_Context_objectTypeOperations,
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

Arcadia_defineObjectType(u8"Arcardia.Visuals.Context", Arcadia_Visuals_Context,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Visuals_Context_typeOperations);

static void
Arcadia_Visuals_Context_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Context_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->getClearColor = NULL;
  self->getClearDepth = NULL;
  self->getViewport = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Visuals_Context_getClearColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value* red,
    Arcadia_Real32Value* green,
    Arcadia_Real32Value* blue,
    Arcadia_Real32Value* alpha
  ) 
{ self->getClearColor(thread, self, red, green, blue, alpha); }

void
Arcadia_Visuals_Context_getClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value* depth
  )
{ self->getClearDepth(thread, self, depth); }

void
Arcadia_Visuals_Context_getViewport
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value* left,
    Arcadia_Real32Value* bottom,
    Arcadia_Real32Value* right,
    Arcadia_Real32Value* top
  )
{ self->getViewport(thread, self, left, bottom, right, top); }

void
Arcadia_Visuals_Context_setViewport
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value left,
    Arcadia_Real32Value bottom,
    Arcadia_Real32Value right,
    Arcadia_Real32Value top
  )
{ self->setViewport(thread, self, left, bottom, right, top); }

void
Arcadia_Visuals_Context_setClearColor
(
  Arcadia_Thread* thread,
  Arcadia_Visuals_Context* self,
  Arcadia_Real32Value red,
  Arcadia_Real32Value green,
  Arcadia_Real32Value blue,
  Arcadia_Real32Value alpha
)   {
 self->setClearColor(thread, self, red, green, blue, alpha); }

void
Arcadia_Visuals_Context_setClearDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Context* self,
    Arcadia_Real32Value depth
  )
{ self->setClearDepth(thread, self, depth); }
