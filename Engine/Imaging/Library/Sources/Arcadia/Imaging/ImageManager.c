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

#include "Arcadia/Imaging/ImageManager.h"

#include "Arcadia/Imaging/ImageWriter.h"

#include "Arcadia/Imaging/IcoImageWriter.h"
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Imaging/Windows/BmpImageWriter.h"
  #include "Arcadia/Imaging/Windows/PngImageWriter.h"
  #include "Arcadia/Imaging/Windows/TifImageWriter.h"
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Imaging/Linux/BmpImageWriter.h"
  #include "Arcadia/Imaging/Linux/PngImageWriter.h"
#else
  #error("environment not (yet) supported")
#endif

static Arcadia_Imaging_ImageManager* g_instance = NULL;

static void
Arcadia_Imaging_ImageManager_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static Arcadia_Imaging_ImageManager*
Arcadia_Imaging_ImageManager_create
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_Imaging_ImageManager_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageManager* self
  );

static void
Arcadia_Imaging_ImageManager_destroyCallback
  (
    void* observer,
    void* observed
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Imaging_ImageManager_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Imaging_ImageManager_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.ImageManager", Arcadia_Imaging_ImageManager,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Imaging_ImageManager_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Imaging_ImageManager* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Imaging_ImageManager_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->writers = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Imaging_ImageWriter* writer = NULL;
 
  writer = (Arcadia_Imaging_ImageWriter*)IcoImageWriter_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, _self->writers, writer);
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  writer = (Arcadia_Imaging_ImageWriter*)Arcadia_Imaging_Windows_BmpImageWriter_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, _self->writers, writer);
  writer = (Arcadia_Imaging_ImageWriter*)Arcadia_Imaging_Windows_PngImageWriter_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, _self->writers, writer);
  writer = (Arcadia_Imaging_ImageWriter*)Arcadia_Imaging_Windows_TifImageWriter_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, _self->writers, writer);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  writer = (Arcadia_Imaging_ImageWriter*)Arcadia_Imaging_Linux_PngImageWriter_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, _self->writers, writer);
  writer = (Arcadia_Imaging_ImageWriter*)Arcadia_Imaging_Linux_BmpImageWriter_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, _self->writers, writer);
#else
  #error("environment not (yet) supported")
#endif
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static Arcadia_Imaging_ImageManager*
Arcadia_Imaging_ImageManager_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Imaging_ImageManager* self = Arcadia_allocateObject(thread, _Arcadia_Imaging_ImageManager_getType(thread), 0, &argumentValues[0]);
  return self;
}

static void
Arcadia_Imaging_ImageManager_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageManager* self
  )
{
  if (self->writers) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->writers);
  }
}

static void
Arcadia_Imaging_ImageManager_destroyCallback
  (
    void* observer,
    void* observed
  )
{
  g_instance = NULL;
}

Arcadia_Imaging_ImageManager*
Arcadia_Imaging_ImageManager_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Imaging_ImageManager* instance = Arcadia_Imaging_ImageManager_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &Arcadia_Imaging_ImageManager_destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}

static Arcadia_BooleanValue
filter
  (
    Arcadia_Thread* thread,
    Arcadia_Value context,
    Arcadia_Value value
  )
{
  Arcadia_Imaging_ImageWriter* writer = Arcadia_Value_getObjectReferenceValue(&value);
  Arcadia_List* supportedExtensions = (Arcadia_List*)Arcadia_Imaging_ImageWriter_getSupportedTypes(thread, writer);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)supportedExtensions); i < n; ++i) {
    Arcadia_Value a = Arcadia_List_getAt(thread, supportedExtensions, i);
    Arcadia_Value b = context;
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}

Arcadia_List*
Arcadia_Imaging_ImageManager_getWriters
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageManager* self,
    Arcadia_String* extension
  )
{
  Arcadia_List* list = Arcadia_List_filter(thread, self->writers, Arcadia_Value_makeObjectReferenceValue(extension), &filter);
  return list;
}
