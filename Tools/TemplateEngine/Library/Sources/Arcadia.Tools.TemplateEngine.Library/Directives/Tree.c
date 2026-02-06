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

#include "Arcadia.Tools.TemplateEngine.Library/Directives/Tree.h"

static void
Directives_Tree_destruct
  (
    Arcadia_Thread* thread,
    Directives_Tree* self
  );

static void
Directives_Tree_visit
  (
    Arcadia_Thread* thread,
    Directives_Tree* self
  );

static void
Directives_Tree_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Tree* self
  );

static void
Directives_Tree_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_TreeDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Directives_Tree_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*) & Directives_Tree_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Directives_Tree_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.Directives.Tree", Directives_Tree,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Directives_Tree_destruct
  (
    Arcadia_Thread* thread,
    Directives_Tree* self
  )
{/*Intentionally empty.*/}

static void
Directives_Tree_visit
  (
    Arcadia_Thread* thread,
    Directives_Tree* self
  )
{
  switch (self->type) {
    case Directives_TreeKind_At: {
      // Intentionally empty.
    } break;
    case Directives_TreeKind_GetVariable: {
      Arcadia_Object_visit(thread, (Arcadia_Object*)self->getVariable.name);
    } break;
    case Directives_TreeKind_String: {
      Arcadia_Object_visit(thread, (Arcadia_Object*)self->string);
    } break;
    case Directives_TreeKind_Invoke: {
      Arcadia_Object_visit(thread, (Arcadia_Object*)self->invoke.name);
      Arcadia_Object_visit(thread, (Arcadia_Object*)self->invoke.arguments);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
Directives_Tree_constructImpl
  (
    Arcadia_Thread* thread,
    Directives_Tree* self
  )
{
  Arcadia_TypeValue _type = _Directives_Tree_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Natural8Value numberOfArguments = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->type = Arcadia_ValueStack_getInteger32Value(thread, numberOfArguments);
  switch (self->type) {
    case Directives_TreeKind_At: {

    } break;
    case Directives_TreeKind_GetVariable: {
      self->getVariable.name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
    } break;
    case Directives_TreeKind_String: {
      self->string = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
    } break;
    case Directives_TreeKind_Invoke: {
      self->invoke.name = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
      self->invoke.arguments = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArguments + 1);
}

static void
Directives_Tree_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Directives_TreeDispatch* self
  )
{ }

Directives_Tree*
Directives_Tree_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, type);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Directives_Tree);
}

Directives_Tree*
Directives_Tree_createInvoke
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_List* arguments
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, Directives_TreeKind_Invoke);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)arguments);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Directives_Tree);
}

Directives_Tree*
Directives_Tree_createAt
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, Directives_TreeKind_At);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Directives_Tree);
}

Directives_Tree*
Directives_Tree_createGetVariable
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, Directives_TreeKind_GetVariable);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Directives_Tree);
}
