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

#include "Arcadia/Engine/Demo/Configuration.h"
#include <stdlib.h>
#include <string.h>

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Audials/Include.h"
#include "Arcadia/Audials/Implementation/Include.h"
#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Include.h"
#include "Arcadia/Ring1/Include.h"
#include "Arcadia/DataDefinitionLanguage/Include.h"

static Arcadia_SizeValue
_find
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* self,
    Arcadia_SizeValue index,
    Arcadia_String* key
  )
{ 
  for (Arcadia_SizeValue i = index, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->entries); i < n; ++i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* entry = Arcadia_List_getObjectReferenceValueAt(thread, self->entries, i);
    Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(entry->key->value);
    Arcadia_Value b = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      return i;
    }
  }
  return Arcadia_SizeValue_Maximum;
}

// validate a range of integers [low, high]
static void
_validateIntegerRange
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_String* key,
    Arcadia_Integer32Value minimumValue,
    Arcadia_Integer32Value maximumValue,
    Arcadia_Integer32Value defaultValue
  )
{
  if (!(minimumValue <= maximumValue && minimumValue <= defaultValue && defaultValue <= maximumValue)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue i;
  i = _find(thread, node, 0, key);
  // Remove any candidates (key, value) where value is not in Values.
  while (i != Arcadia_SizeValue_Maximum) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* childNode = Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (childNode->value->type != Arcadia_DataDefinitionLanguage_Tree_NodeType_Number) {
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      i = _find(thread, node, i, key);
      continue;
    }
    Arcadia_String* valueString = ((Arcadia_DataDefinitionLanguage_Tree_NumberNode*)childNode->value)->value;
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_Integer64Value valueInteger64Value = Arcadia_String_toInteger64(thread, valueString);
      if (valueInteger64Value < minimumValue || valueInteger64Value > maximumValue) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      i = _find(thread, node, i, key);
      continue;
    }
    i = _find(thread, node, i + 1, key);
  }
  // Add a candidate (key, default) if there is no candidate (key, value) where value in Values.
  i = _find(thread, node, 0, key);
  if (Arcadia_SizeValue_Maximum == i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* e =
      Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create
        (
          thread,
          Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, key),
          (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_NumberNode_createInteger64(thread, defaultValue)
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, e);
  }
  // There is now exactly one (key, value) where value in Values. 
}

// (1) Remove all a, a = (x,y), x = key, type(y) != Map.
// (2) If there are multiple a1, a2, ..., an such that a[i] = (x[i],y[i]), x[i] = key, type(y[i]) = Map
//     => remove a2, ..., an.
// (2) If exists a, a = (x,y), x = key, type(y) = Map,
//     => exit with success.
// (3) Otherwise add a, a = (x,y), x = key, y = { }
static void
_validateMap
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_String* key
  )
{
  Arcadia_SizeValue i;
  i = _find(thread, node, 0, key);
  // Remove any (x,y) where x = key and type(y) = Map.
  while (i != Arcadia_SizeValue_Maximum) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* childNode = Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (childNode->value->type != Arcadia_DataDefinitionLanguage_Tree_NodeType_Map) {
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      i = _find(thread, node, i, key);
      continue;
    }
    i = _find(thread, node, i + 1, key);
  }
  // Add a (x, y) with x = key and y = { ... } if there is no (x, y) with x = key and type(y) = Map.
  i = _find(thread, node, 0, key);
  if (Arcadia_SizeValue_Maximum == i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* e =
      Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create
        (
          thread,
          Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, key),
          (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_MapNode_create(thread)
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, e);
  }
  // There is now exactly one entry (x, y) with x = key and type(y) = Map exists.
}

static void
updateMasterVolume
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  )
{
  Arcadia_String* key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"masterVolume", sizeof(u8"masterVolume") - 1)));
  _validateIntegerRange(thread, node, key, Arcadia_Integer64Value_Literal(0), Arcadia_Integer64Value_Literal(10), Arcadia_Integer64Value_Literal(10));
}

static void
updateAudialsConfiguration
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  )
{
  Arcadia_String* key;
  Arcadia_DataDefinitionLanguage_Tree_MapNode* sectionNode;

  key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"audials", sizeof(u8"audials") - 1)));
  _validateMap(thread, node, key);
  sectionNode = (Arcadia_DataDefinitionLanguage_Tree_MapNode*)((Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, _find(thread, node, 0, key)))->value;
  updateMasterVolume(thread, sectionNode);
}

static void
print
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self,
    const Arcadia_Natural8Value* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_SizeValue currentNumberOfAttempts = 0, maximumNumberOfAttempts = 3;
  Arcadia_SizeValue n = 0, m = 0;
  while (n < numberOfBytes && currentNumberOfAttempts < maximumNumberOfAttempts) {
    Arcadia_FileHandle_write(thread, self->fileHandle, bytes + n, numberOfBytes - n, &m);
    n += m;
    currentNumberOfAttempts++;
  }
}

static Arcadia_String*
getVisualsBackend
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* configuration
  )
{
  char const* path[] = {
    u8"visuals",
    u8"backend",
  };
  return Cfg2_getString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2);
}

static void
Cfg2_setDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration,
    Arcadia_Integer32Value horizontalResolution,
    Arcadia_Integer32Value verticalResolution,
    Arcadia_Integer32Value colorDepth
  )
{
  {
    char const* path[] = {
      u8"visuals",
      u8"horizontalResolution",
    };
    Cfg2_setInteger32(thread, configuration, path, 2, horizontalResolution);
  }
  {
    char const* path[] = {
      u8"visuals",
      u8"verticalResolution",
    };
    Cfg2_setInteger32(thread, configuration, path, 2, verticalResolution);
  }
  {
    char const* path[] = {
      u8"visuals",
      u8"colorDepth",
    };
    Cfg2_setInteger32(thread, configuration, path, 2, colorDepth);
  }
}

static void
Cfg2_getDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration,
    Arcadia_Integer32Value* horizontalResolution,
    Arcadia_Integer32Value* verticalResolution,
    Arcadia_Integer32Value* colorDepth
  )
{
  Arcadia_Integer32Value temporary[3];
  {
    char const* path[] = {
      u8"visuals",
      u8"horizontalResolution",
    };
    temporary[0] = Cfg2_getInteger32(thread, configuration, path, 2);
  }
  {
    char const* path[] = {
      u8"visuals",
      u8"verticalResolution",
    };
    temporary[1] = Cfg2_getInteger32(thread, configuration, path, 2);
  }
  {
    char const* path[] = {
      u8"visuals",
      u8"colorDepth",
    };
    temporary[2] = Cfg2_getInteger32(thread, configuration, path, 2);
  }
  if (horizontalResolution) *horizontalResolution = temporary[0];
  if (verticalResolution) *verticalResolution = temporary[1];
  if (colorDepth) *colorDepth = temporary[2];
}

static void
Cfg2_setVerticalSynchronization
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration,
    Arcadia_BooleanValue value
  )
{
  char const* path[] = {
    u8"visuals",
    u8"verticalSynchronization",
  };
  Cfg2_setBoolean(thread, configuration, path, 2, value);
}

static Arcadia_BooleanValue
Cfg2_getVerticalSynchronization
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration
  )
{
  char const* path[] = {
    u8"visuals",
    u8"verticalSynchronization",
  };
  return Cfg2_getBoolean(thread, configuration, path, 2);
}

static Arcadia_BooleanValue
findTypeByName
  (
    Arcadia_Thread* thread,
    Arcadia_Value x,
    Arcadia_Value y
  )
{
  Arcadia_Type* yy = Arcadia_Value_getTypeValue(&y);
  Arcadia_Atom* b = Arcadia_Type_getName(yy);
  Arcadia_String* a = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&x);
  return Arcadia_String_getNumberOfBytes(thread, a) == Arcadia_Atom_getNumberOfBytes(thread, b)
      && !Arcadia_Memory_compare(thread, Arcadia_String_getBytes(thread, a), Arcadia_Atom_getBytes(thread, b), Arcadia_String_getNumberOfBytes(thread, a));
}

void
Arcadia_Engine_Demo_startupAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration
  )
{
  // (1) Register audials backends.
  {
  #if Arcadia_Audials_Implementation_Configuration_OpenAL_Backend_Enabled
    Arcadia_Set_add(thread, engine->audialsBackendTypes, Arcadia_Value_makeTypeValue(_Arcadia_Audials_OpenAL_Backend_getType(thread)), NULL);
  #endif
  }
  // (2) Select audials system.
  {
    char const* path[] = {
      u8"audials",
      u8"backend",
    };
    Arcadia_Audials_Backend* backend = NULL;
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_String* backendTypeName = Cfg2_getString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2);
      Arcadia_Value backendTypeValue = Arcadia_HashSet_findFirst(thread, (Arcadia_HashSet*)engine->audialsBackendTypes, Arcadia_Value_makeObjectReferenceValue(backendTypeName), &findTypeByName);
      if (!Arcadia_Value_isTypeValue(&backendTypeValue)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Type* backendType = Arcadia_Value_getTypeValue(&backendTypeValue);
      if (!Arcadia_Type_isSubType(thread, backendType, _Arcadia_Audials_Backend_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Value argumentValues[] = {
        Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
      };
      Arcadia_ValueStack_pushNatural8Value(thread, 0);
      backend = (Arcadia_Audials_Backend*)Arcadia_allocateObject(thread, backendType, 0, &argumentValues[0]);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_String* backendTypeName = Arcadia_String_createFromCxxString(thread, u8"Arcadia.Audials.OpenAL.Backend");
      Cfg2_setString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2, backendTypeName);
      Arcadia_Value backendTypeValue = Arcadia_HashSet_findFirst(thread, (Arcadia_HashSet*)engine->audialsBackendTypes, Arcadia_Value_makeObjectReferenceValue(backendTypeName), &findTypeByName);
      if (!Arcadia_Value_isTypeValue(&backendTypeValue)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Type* backendType = Arcadia_Value_getTypeValue(&backendTypeValue);
      if (!Arcadia_Type_isSubType(thread, backendType, _Arcadia_Audials_Backend_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Value argumentValues[] = {
        Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
      };
      backend = (Arcadia_Audials_Backend*)Arcadia_allocateObject(thread, backendType, 0, &argumentValues[0]);
    }
    Arcadia_Audials_System* temporary = Arcadia_Audials_System_createSystem(thread, backend);
    Arcadia_Object_lock(thread, (Arcadia_Object*)temporary);
    engine->audialsSystem = (Arcadia_Engine_System*)temporary;
  }
}

void
Arcadia_Engine_Demo_startupVisuals
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration,
    Arcadia_Visuals_DisplayDevice** pDisplayDevice,
    Arcadia_String** pWindowMode,
    Arcadia_Visuals_Window** pWindow
  )
{
  // (1) Register visuals backends.
  {
#if Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled
  Arcadia_Set_add(thread, engine->visualBackendTypes, Arcadia_Value_makeTypeValue(_Arcadia_Visuals_OpenGL4_Backend_getType(thread)), NULL);
#endif
  }
  // (2) Select visuals system.
  {
    char const* path[] = {
      u8"visuals",
      u8"backend",
    };
    Arcadia_Visuals_Backend* backend = NULL;
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_String* backendTypeName = Cfg2_getString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2);
      Arcadia_Value backendTypeValue = Arcadia_HashSet_findFirst(thread, (Arcadia_HashSet*)engine->visualBackendTypes, Arcadia_Value_makeObjectReferenceValue(backendTypeName), &findTypeByName);
      if (!Arcadia_Value_isTypeValue(&backendTypeValue)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Type* backendType = Arcadia_Value_getTypeValue(&backendTypeValue);
      if (!Arcadia_Type_isSubType(thread, backendType, _Arcadia_Visuals_Backend_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Value argumentValues[] = {
        Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
      };
      Arcadia_ValueStack_pushNatural8Value(thread, 0);
      backend = (Arcadia_Visuals_Backend*)Arcadia_allocateObject(thread, backendType, 0, &argumentValues[0]);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_String* backendTypeName = Arcadia_String_createFromCxxString(thread, u8"Arcadia.Visuals.OpenGL4.Backend");
      Cfg2_setString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2, backendTypeName);
      Arcadia_Value backendTypeValue = Arcadia_HashSet_findFirst(thread, (Arcadia_HashSet*)engine->visualBackendTypes, Arcadia_Value_makeObjectReferenceValue(backendTypeName), &findTypeByName);
      if (!Arcadia_Value_isTypeValue(&backendTypeValue)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Type* backendType = Arcadia_Value_getTypeValue(&backendTypeValue);
      if (!Arcadia_Type_isSubType(thread, backendType, _Arcadia_Visuals_Backend_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_NotFound);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Value argumentValues[] = {
        Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
      };
      backend = (Arcadia_Visuals_Backend*)Arcadia_allocateObject(thread, backendType, 0, &argumentValues[0]);
    }
    Arcadia_Visuals_System* temporary = Arcadia_Visuals_System_createSystem(thread, backend);
    Arcadia_Object_lock(thread, (Arcadia_Object*)temporary);
    engine->visualsSystem = (Arcadia_Engine_System*)temporary;
  }
  // (3) Select display device (aka "monitor").
  {
    Arcadia_List* displayDevices = Arcadia_Visuals_System_getDisplayDevices(thread, (Arcadia_Visuals_System*)engine->visualsSystem);
    Arcadia_Visuals_Diagnostics_dumpDevices(thread, (Arcadia_Visuals_System*)engine->visualsSystem);
    Arcadia_Integer32Value displayDeviceIndex = 0;
    char const* path[] = {
      u8"visuals",
      u8"monitor",
    };
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      displayDeviceIndex = Cfg2_getInteger32(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2);
      if (displayDeviceIndex < 0 || displayDeviceIndex >= Arcadia_Collection_getSize(thread, (Arcadia_Collection*)displayDevices)) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Cfg2_setInteger32(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2, displayDeviceIndex);
    }
    // If we don't have at least one display device, bail out.
    if (!Arcadia_Collection_getSize(thread, (Arcadia_Collection*)displayDevices)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    }
    *pDisplayDevice = (Arcadia_Visuals_DisplayDevice*)Arcadia_List_getObjectReferenceValueAt(thread, displayDevices, displayDeviceIndex);
  }
  // (4) Get the window mode.
  {
    Arcadia_String* windowMode = NULL;
    char const* path[] = {
      u8"visuals",
      u8"windowMode",
    };
    const char* values[] = {
      u8"windowed",
      u8"borderless fullscreen window",
      u8"fullscreen",
    };
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      windowMode = Cfg2_getString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2);
      Arcadia_BooleanValue found = Arcadia_BooleanValue_False;
      for (Arcadia_SizeValue i = 0, n = 3; i < n; ++i) {
        Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(windowMode);
        Arcadia_Value b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, values[i], strlen(values[i])))));
        if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
          found = Arcadia_BooleanValue_True;
          break;
        }
      }
      if (!found) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      windowMode = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"windowed", sizeof(u8"windowed") - 1)));
      Cfg2_setString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2, windowMode);
    }
    *pWindowMode = windowMode;
  }
  // (5) Create and open a window, set its size and position according to the display device it is located on.
  {
    Arcadia_Visuals_Window* window = Arcadia_Visuals_System_createWindow(thread, (Arcadia_Visuals_System*)engine->visualsSystem);
    Arcadia_Object_lock(thread, (Arcadia_Object*)window);
    Arcadia_Visuals_Window_open(thread, window);
    Arcadia_Integer32Value left, top, right, bottom;
    Arcadia_Visuals_DisplayDevice_getBounds(thread, *pDisplayDevice, &left, &top, &right, &bottom);
    Arcadia_Visuals_Window_setPosition(thread, window, left, top);
    Arcadia_Visuals_Window_setSize(thread, window, right - left, bottom - top);
    *pWindow = window;
  }
  // (6) Set window mode and resolution.
  {
    Arcadia_JumpTarget jumpTarget;

    // Set window mode.
    Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(*pWindowMode);
    Arcadia_Value b;

    // Although the resolution is ignored by non-full screen window modes,
    // add a reasonable default to the configuration if no value or a broken value is in the configuration.
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_Integer32Value horizontalResolution, verticalResolution, colorDepth;
      Cfg2_getDisplayMode(thread, configuration, &horizontalResolution, &verticalResolution, &colorDepth);
      if (colorDepth < 8 || horizontalResolution < 320 || verticalResolution < 240) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
      Arcadia_Visuals_DisplayMode* displayMode = Arcadia_Visuals_DisplayDevice_getCurrentDisplayMode(thread, *pDisplayDevice);
      Cfg2_setDisplayMode(thread, configuration, Arcadia_Visuals_DisplayMode_getHorizontalResolution(thread, displayMode),
                                                 Arcadia_Visuals_DisplayMode_getVerticalResolution(thread, displayMode),
                                                 Arcadia_Visuals_DisplayMode_getColorDepth(thread, displayMode));
    }
    // Although vertical synchronization is ignored by non-full screen window moudes,
    // add a reasonable default to the configuration if no value or a broken value is in the configuration.
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Cfg2_getVerticalSynchronization(thread, configuration);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
      Cfg2_setVerticalSynchronization(thread, configuration, Arcadia_BooleanValue_False);
    }
    // Set the window mode and resolution.
    b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"windowed", sizeof(u8"windowed") - 1))));
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      Arcadia_Visuals_Window_setFullscreen(thread, *pWindow, Arcadia_BooleanValue_False);
    }
    b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"borderless fullscreen window", sizeof(u8"borderless fullscreen window") - 1))));
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      Arcadia_Visuals_Window_setFullscreen(thread, *pWindow, Arcadia_BooleanValue_True);
    }
    b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"fullscreen", sizeof(u8"fullscreen") - 1))));
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      Arcadia_Visuals_Window_setFullscreen(thread, *pWindow, Arcadia_BooleanValue_True);
      Arcadia_Visuals_DisplayMode* bestDisplayMode = NULL;
      Arcadia_Integer32Value horizontalResolution, verticalResolution, colorDepth;
      Cfg2_getDisplayMode(thread, configuration, &horizontalResolution, &verticalResolution, &colorDepth);
      Arcadia_List* list = Arcadia_Visuals_DisplayDevice_getAvailableDisplayModes(thread, *pDisplayDevice);
      for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)list); i < n; ++i) {
        Arcadia_Visuals_DisplayMode* displayMode = (Arcadia_Visuals_DisplayMode*)Arcadia_List_getObjectReferenceValueAt(thread, list, i);
        if (horizontalResolution == Arcadia_Visuals_DisplayMode_getHorizontalResolution(thread, displayMode) &&
          verticalResolution == Arcadia_Visuals_DisplayMode_getVerticalResolution(thread, displayMode) &&
          colorDepth == Arcadia_Visuals_DisplayMode_getColorDepth(thread, displayMode)) {
          bestDisplayMode = displayMode;
          break;
        }
      }
      if (!bestDisplayMode) {
        bestDisplayMode = Arcadia_Visuals_DisplayDevice_getCurrentDisplayMode(thread, *pDisplayDevice);
        Cfg2_setDisplayMode(thread, configuration, Arcadia_Visuals_DisplayMode_getHorizontalResolution(thread, bestDisplayMode),
          Arcadia_Visuals_DisplayMode_getVerticalResolution(thread, bestDisplayMode),
          Arcadia_Visuals_DisplayMode_getColorDepth(thread, bestDisplayMode));
      }
      if (bestDisplayMode) {
        Arcadia_Integer32Value left, top, right, bottom;
        Arcadia_Visuals_DisplayMode_apply(thread, bestDisplayMode);
        Arcadia_Visuals_DisplayDevice_getBounds(thread, *pDisplayDevice, &left, &top, &right, &bottom);
        Arcadia_Visuals_Window_setPosition(thread, *pWindow, left, top);
        Arcadia_Visuals_Window_setSize(thread, *pWindow, right - left, bottom - top);
      }
    }
  }
  // (7) Set the window icons and the window title.
  {
    Arcadia_Visuals_Icon* icon;
    Arcadia_Integer32Value width, height;
    // Set the big icon.
    Arcadia_Visuals_Window_getRequiredBigIconSize(thread, *pWindow, &width, &height);
    icon = Arcadia_Visuals_System_createIcon(thread, (Arcadia_Visuals_System*)engine->visualsSystem, width, height, 47, 47, 47, 255);
    Arcadia_Visuals_Window_setBigIcon(thread, *pWindow, icon);

    // Set the small icon.
    Arcadia_Visuals_Window_getRequiredSmallIconSize(thread, *pWindow, &width, &height);
    icon = Arcadia_Visuals_System_createIcon(thread, (Arcadia_Visuals_System*)engine->visualsSystem, width, height, 47, 47, 47, 255);
    Arcadia_Visuals_Window_setSmallIcon(thread, *pWindow, icon);

    // Set the title.
    Arcadia_Visuals_Window_setTitle(thread, *pWindow, Arcadia_String_createFromCxxString(thread, u8"Michael Heilmann's Liminality"));
  }
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char **argv
  )
{
  Arcadia_BooleanValue quit = Arcadia_BooleanValue_False;
  Arcadia_Engine* engine = NULL;
  Arcadia_Visuals_Window* window = NULL;
  Arcadia_BooleanValue audialsInitialized = Arcadia_BooleanValue_False;
  Arcadia_DataDefinitionLanguage_Tree_Node* configuration = NULL;

  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    
    {
      Arcadia_DataDefinitionLanguage_Tree_Node* temporary = (Arcadia_DataDefinitionLanguage_Tree_Node*)Cfg_loadConfiguration(thread);
      Arcadia_Object_lock(thread,  (Arcadia_Object*)temporary);
      configuration = temporary;
    }

    {
      Arcadia_Engine* temporary = Arcadia_Engine_getOrCreate(thread);
      Arcadia_Object_lock(thread, (Arcadia_Object*)temporary);
      engine = temporary;
    }
    Arcadia_String* windowMode = NULL;
    Arcadia_Visuals_DisplayDevice* displayDevice = NULL;
    Arcadia_Engine_Demo_startupVisuals(thread, engine, configuration, &displayDevice, &windowMode, &window);

    Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
    Arcadia_FileHandle* fileHandle = Arcadia_FileHandle_create(thread, fileSystem);
    Arcadia_FileHandle_openStandardOutput(thread, fileHandle);

    // (1) Initialize Audials.
    Arcadia_Engine_Demo_startupAudials(thread, engine, configuration);
    Audials_startup(thread);
    audialsInitialized = Arcadia_BooleanValue_True;

    // (2) Play sine wave.
    Audials_playSine(thread);

    Arcadia_Process_stepArms(process);

    // (8) Enter the message loop.
    while (!quit) {
      Arcadia_Process_stepArms(process);
      Arcadia_Audials_System_update(thread, (Arcadia_Audials_System*)engine->audialsSystem);
      Arcadia_Visuals_System_update(thread, (Arcadia_Visuals_System*)engine->visualsSystem);
      Arcadia_Visuals_Window_beginRender(thread, window);
      Arcadia_Visuals_Window_endRender(thread, window);

      Arcadia_Engine_Event* event = Arcadia_Engine_dequeEvent(thread, engine);
      if (NULL != event && Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_KeyboardKeyEvent_getType(thread))) {
        Arcadia_Visuals_KeyboardKeyEvent* keyboardKeyEvent = (Arcadia_Visuals_KeyboardKeyEvent*)event;
        if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKeyAction_Released &&
            Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKey_Escape) {
          quit = Arcadia_BooleanValue_True;
        }
      }
    }

    // (9) Ensure the window is closed.
    Arcadia_Visuals_Window_close(thread, window);

    if (audialsInitialized) {
      Audials_shutdown(thread);
      audialsInitialized = Arcadia_BooleanValue_False;
    }

    Cfg_saveConfiguration(thread, configuration);

    Arcadia_Thread_popJumpTarget(thread);

    // (10) Clean the message queue. FIXME: The messages prevent the engine from being gc'ed.
    while (Arcadia_Engine_dequeEvent(thread, engine)) {
      fprintf(stdout, "%s:%d: purging message\n", __FILE__, __LINE__);
    }

    if (window) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (engine->audialsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->audialsSystem);
      engine->audialsSystem = NULL;
    }
    if (engine->visualsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->visualsSystem);
      engine->visualsSystem = NULL;
    }
    if (engine) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine);
      engine = NULL;
    }
    if (configuration) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)configuration);
      configuration = NULL;
    }
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    if (audialsInitialized) {
      Audials_shutdown(thread);
      audialsInitialized = Arcadia_BooleanValue_False;
    }

    if (window) {
      // (9) Ensure the window is closed.
      Arcadia_Visuals_Window_close(thread, window);
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (engine->audialsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->audialsSystem);
      engine->audialsSystem = NULL;
    }
    if (engine->visualsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->visualsSystem);
      engine->visualsSystem = NULL;
    }
    if (engine) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine);
      engine = NULL;
    }
    if (configuration) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)configuration);
      configuration = NULL;
    }
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  Arcadia_Status status = Arcadia_Thread_getStatus(Arcadia_Process_getThread(process));
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
