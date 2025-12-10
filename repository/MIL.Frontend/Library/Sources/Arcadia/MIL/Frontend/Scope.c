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

#include "Arcadia/MIL/Frontend/Scope.h"

#include "Arcadia/MIL/Frontend/Symbol.h"

static void
Arcadia_MIL_Scope_Entry_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_Entry* self
  );

static void
Arcadia_MIL_Scope_Entry_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_EntryDispatch* self
  );

static void
Arcadia_MIL_Scope_Entry_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_Entry* self
  );

static void
Arcadia_MIL_Scope_Entry_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_Entry* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_Scope_Entry_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_Scope_Entry_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MIL_Scope_Entry_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Scope_Entry_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_MIL_Scope_Entry_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_Scope_Entry_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Scope.Entry", Arcadia_MIL_Scope_Entry,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_MIL_Scope_Entry_typeOperations);

static void
Arcadia_MIL_Scope_Entry_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_Entry* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Scope_Entry_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->name = NULL;
  self->nextSibling = NULL;
  self->shadowed = NULL;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_Scope_Entry_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_EntryDispatch* self
  )
{ }

static void
Arcadia_MIL_Scope_Entry_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_Entry* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MIL_Scope_Entry_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope_Entry* self
  )
{
  if (self->nextSibling) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->nextSibling);
  }
  if (self->shadowed) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->shadowed);
  }
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
}

Arcadia_MIL_Scope_Entry*
Arcadia_MIL_Scope_Entry_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Scope_Entry);
}

static void
Arcadia_MIL_Scope_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self
  );

static void
Arcadia_MIL_Scope_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ScopeDispatch* self
  );

static void
Arcadia_MIL_Scope_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self
  );

static void
Arcadia_MIL_Scope_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_Scope_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_Scope_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MIL_Scope_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Scope_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_MIL_Scope_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_Scope_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Scope", Arcadia_MIL_Scope,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_MIL_Scope_typeOperations);

static void
Arcadia_MIL_Scope_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Scope_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->siblings = NULL;
  //
  self->hash.buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_MIL_Scope_Entry*) * 8);
  for (Arcadia_SizeValue i = 0; i < 8; ++i) {
    self->hash.buckets[i] = NULL;
  }
  self->hash.capacity = 8;
  self->hash.size = 0;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_Scope_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ScopeDispatch* self
  )
{ }

static void
Arcadia_MIL_Scope_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self
  )
{
  if (self->hash.buckets) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->hash.buckets);
    self->hash.buckets = NULL;
  }
}

static void
Arcadia_MIL_Scope_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self
  )
{
  Arcadia_MIL_Scope_Entry* node = self->siblings;
  while (node) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)node);
    node = node->nextSibling;
  }
  for (Arcadia_SizeValue i = 0, n = self->hash.capacity; i < n; ++i) {
    Arcadia_MIL_Scope_Entry* node = self->hash.buckets[i];
    while (node) {
      Arcadia_Object_visit(thread, (Arcadia_Object*)node);
      node = node->shadowed;
    }
  }
}

Arcadia_MIL_Scope*
Arcadia_MIL_Scope_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Scope);
}

void
Arcadia_MIL_Scope_enter
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self,
    Arcadia_MIL_Symbol* symbol
  )
{
  Arcadia_String* name = symbol->name;
  Arcadia_SizeValue hash = Arcadia_Object_getHash(thread, (Arcadia_Object*)name);
  Arcadia_SizeValue index = hash % self->hash.capacity;

  Arcadia_MIL_Scope_Entry* e = Arcadia_MIL_Scope_Entry_create(thread);
  //
  e->name = name;
  //
  e->nextSibling = self->siblings;
  self->siblings = e;
  //
  e->shadowed = self->hash.buckets[index];
  self->hash.buckets[index] = e;
  //
  self->hash.size++;
}
