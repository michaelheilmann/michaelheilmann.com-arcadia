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

#include "Arcadia.Tools.TemplateEngine.Library/DependenciesContext.h"

#include "Arcadia/DDL/Include.h"

static void
DependenciesContext_constructImpl
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  );

static void
DependenciesContext_destruct
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  );

static void
DependenciesContext_visit
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & DependenciesContext_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*) & DependenciesContext_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & DependenciesContext_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.DependenciesContext", DependenciesContext,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
DependenciesContext_constructImpl
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  )
{
  Arcadia_TypeValue _type = _DependenciesContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->dependenciesFilePath = NULL;
  self->dependencies = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
DependenciesContext_destruct
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  )
{/*Intentionally empty.*/}

static void
DependenciesContext_visit
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  )
{
  if (self->dependencies) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->dependencies);
  }
  if (self->dependenciesFilePath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->dependenciesFilePath);
  }
  if (self->dependencies) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->dependencies);
  }
}

DependenciesContext*
DependenciesContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(DependenciesContext);
}

static void
writePath
  (
    Arcadia_Thread* thread,
    DependenciesContext* self,
    Arcadia_String* pathString,
    Arcadia_UTF8Writer* writer
  )
{
  Arcadia_UTF8Reader* reader = (Arcadia_UTF8Reader*)Arcadia_UTF8StringReader_create(thread, pathString);
  while (Arcadia_UTF8Reader_hasCodePoint(thread, reader)) {
    Arcadia_Natural32Value codePoint = Arcadia_UTF8Reader_getCodePoint(thread, reader);
    if (codePoint == ' ') {
      Arcadia_Natural32Value t[] = { '\\', codePoint };
      Arcadia_UTF8Writer_writeCodePoints(thread, writer, t, 2);
    } else {
      Arcadia_UTF8Writer_writeCodePoints(thread, writer, &codePoint, 1);
    }
    Arcadia_UTF8Reader_next(thread, reader);
  }
}

void
DependenciesContext_write
  (
    Arcadia_Thread* thread,
    DependenciesContext* self
  )
{
  if (!self->dependenciesFilePath) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_List* tosList = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  // (1) Create a buffer to write to.
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_UTF8Writer* writer = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, byteBuffer); 
  // (2) Iterate over the keys.
  Arcadia_List* froms = Arcadia_Map_getKeys(thread, self->dependencies);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)froms); i < n; ++i) {
    // (2.1) Get the "from" string.
    Arcadia_String* from = (Arcadia_String*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, froms, i, _Arcadia_String_getType(thread));
    // (2.2) Get the "tos" list.
    Arcadia_Set* tosSet = (Arcadia_Set*)Arcadia_Map_getObjectReferenceValueChecked(thread, self->dependencies, Arcadia_Value_makeObjectReferenceValue(from), _Arcadia_Set_getType(thread));
    Arcadia_Collection_clear(thread, (Arcadia_Collection*)tosList);
    Arcadia_Set_getAll(thread, tosSet, tosList);
    // (2.3) Write the "from" string.
    writePath(thread, self, from, writer);
    Arcadia_UTF8Writer_writeString(thread, writer, Arcadia_String_createFromCxxString(thread, u8" :"));
    for (Arcadia_SizeValue j = 0, m = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tosList); j < m; ++j) {
      // (2.4) Get the "to" string.
      Arcadia_String* to = (Arcadia_String*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tosList, j, _Arcadia_String_getType(thread));
      // (2.5) Write the "to" string.
      Arcadia_UTF8Writer_writeString(thread, writer, Arcadia_String_createFromCxxString(thread, u8" "));
      writePath(thread, self, to, writer);
    }
    Arcadia_UTF8Writer_writeString(thread, writer, Arcadia_String_createFromCxxString(thread, u8"\r\n"));
  }
  // (3) Write the file contents.
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), self->dependenciesFilePath, byteBuffer);
}

void
DependencyContext_onFile
  (
    Arcadia_Thread* thread,
    DependenciesContext* self,
    Arcadia_FilePath* path
  )
{
  Arcadia_String* fromString = Arcadia_FilePath_toNative(thread, Arcadia_FilePath_getFullPath(thread, path));
  Arcadia_Value temporary = Arcadia_Map_get(thread, self->dependencies, Arcadia_Value_makeObjectReferenceValue(fromString));
  if (Arcadia_Value_isVoidValue(&temporary)) {
    Arcadia_Set* toStringSet = (Arcadia_Set*)Arcadia_HashSet_create(thread);
    Arcadia_Map_set(thread, self->dependencies, Arcadia_Value_makeObjectReferenceValue(fromString),
                                                Arcadia_Value_makeObjectReferenceValue(toStringSet), NULL, NULL);
  }
}

void
DependencyContext_onDependency
  (
    Arcadia_Thread* thread,
    DependenciesContext* self,
    Arcadia_FilePath* from,
    Arcadia_FilePath* to
  )
{
  Arcadia_String* fromString = Arcadia_FilePath_toNative(thread, Arcadia_FilePath_getFullPath(thread, from));
  Arcadia_String* toString = Arcadia_FilePath_toNative(thread, Arcadia_FilePath_getFullPath(thread, to));
  Arcadia_Value temporary = Arcadia_Map_get(thread, self->dependencies, Arcadia_Value_makeObjectReferenceValue(fromString));
  Arcadia_Set* toStringSet = NULL;
  if (Arcadia_Value_isVoidValue(&temporary)) {
    toStringSet = (Arcadia_Set*)Arcadia_HashSet_create(thread);
    Arcadia_Map_set(thread, self->dependencies, Arcadia_Value_makeObjectReferenceValue(fromString),
                                                Arcadia_Value_makeObjectReferenceValue(toStringSet), NULL, NULL);
  } else {
    toStringSet = Arcadia_Value_getObjectReferenceValueChecked(thread, temporary, _Arcadia_Set_getType(thread));
  }
  Arcadia_Set_add(thread, toStringSet, Arcadia_Value_makeObjectReferenceValue(toString), NULL);
}
