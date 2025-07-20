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
#include "Arcadia/Visuals/Include.h"
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

static void
_validateBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_String* key,
    Arcadia_BooleanValue defaultValue
  )
{
  Arcadia_SizeValue i;
  i = _find(thread, node, 0, key);
  // Remove any candidates (key, value) where value is not in Values.
  while (i != Arcadia_SizeValue_Maximum) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* childNode = Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (childNode->value->type != Arcadia_DataDefinitionLanguage_Tree_NodeType_Boolean) {
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
        (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_BooleanNode_createBoolean(thread, defaultValue)
      );
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, e);
  }
  // There is now exactly one (key, value) where value in Values. 
}

static void
_validateString
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_String* key,
    Arcadia_String* defaultValue
  )
{
  Arcadia_SizeValue i;
  i = _find(thread, node, 0, key);
  // Remove any candidates (key, value) where value is not in Values.
  while (i != Arcadia_SizeValue_Maximum) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* childNode = Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (childNode->value->type != Arcadia_DataDefinitionLanguage_Tree_NodeType_Boolean) {
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
          (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_StringNode_createString(thread, defaultValue)
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, e);
  }
  // There is now exactly one (key, value) where value in Values. 
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

// validate an enumeration of strings
static void
_validateStringEnumeration
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_String* key,
    Arcadia_List* values,
    Arcadia_SizeValue defaultValueIndex
  )
{
  Arcadia_SizeValue i;
  i = _find(thread, node, 0, key);
  // Remove any candidates (key, value) where value is not in Values.
  while (i != Arcadia_SizeValue_Maximum) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* childNode = Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (childNode->value->type != Arcadia_DataDefinitionLanguage_Tree_NodeType_String) {
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      i = _find(thread, node, i, key);
      continue;
    }
    Arcadia_Value receivedValue = Arcadia_Value_makeObjectReferenceValue(((Arcadia_DataDefinitionLanguage_Tree_StringNode*)childNode->value)->value);
    Arcadia_BooleanValue found = Arcadia_BooleanValue_False;
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)values); i < n; ++i) {
      Arcadia_Value expectedValue = Arcadia_List_getAt(thread, values, i);
      if (Arcadia_Value_isEqualTo(thread, &receivedValue, &expectedValue)) {
        found = Arcadia_BooleanValue_True;
        break;
      }
    }
    if (!found) {
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      i = _find(thread, node, i, key);
      continue;
    }
    i = _find(thread, node, i + 1, key);
  }
  // Add a candidate (key, default) if there is no candidate (key, value) where value in Values.
  i = _find(thread, node, 0, key);
  if (Arcadia_SizeValue_Maximum == i) {
    Arcadia_String* defaultValue = (Arcadia_String*)Arcadia_List_getObjectReferenceValueAt(thread, values, defaultValueIndex);
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* e =
      Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create
        (
          thread,
          Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, key),
          (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_StringNode_createString(thread, defaultValue)
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, e);
  }
  // There is now exactly one (key, value) where value in Values. 
}

// (1) Remove all a, a = (x,y), x = key, type(y) != List.
// (2) If there are multiple a1, a2, ..., an such that a[i] = (x[i],y[i]), x[i] = key, type(y[i]) = List
//     => remove a2, ..., an.
// (2) If exists a, a = (x,y), x = key, type(y) = Map,
//     => exit with success.
// (3) Otherwise add a, a = (x,y), x = key, y = [ ]
static void
_validateList
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node,
    Arcadia_String* key
  )
{
  Arcadia_SizeValue i;
  i = _find(thread, node, 0, key);
  // Remove any (x,y) where x = key and type(y) = List.
  while (i != Arcadia_SizeValue_Maximum) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* childNode = Arcadia_List_getObjectReferenceValueAt(thread, node->entries, i);
    if (childNode->value->type != Arcadia_DataDefinitionLanguage_Tree_NodeType_List) {
      Arcadia_List_removeAt(thread, node->entries, i, 1);
      i = _find(thread, node, i, key);
      continue;
    }
    i = _find(thread, node, i + 1, key);
  }
  // Add a (x, y) with x = key and y = { ... } if there is no (x, y) with x = key and type(y) = List.
  i = _find(thread, node, 0, key);
  if (Arcadia_SizeValue_Maximum == i) {
    Arcadia_DataDefinitionLanguage_Tree_MapEntryNode* e =
      Arcadia_DataDefinitionLanguage_Tree_MapEntryNode_create
        (
          thread,
          Arcadia_DataDefinitionLanguage_Tree_NameNode_create(thread, key),
          (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_ListNode_create(thread)
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, node->entries, e);
  }
  // There is now exactly one entry (x, y) with x = key and type(y) = List exists.
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
updateVerticalSynchronization
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  )
{
  Arcadia_String* key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"verticalSynchronization", sizeof(u8"verticalSynchronization") - 1)));
  _validateBoolean(thread, node, key, Arcadia_BooleanValue_False);
}

// "windowMode" :
// Must be unary and must be one of "windowed" or "borderless".
// Default is "windowed".
// 
// "monitor":
// Must be unary and must be a non-negative integer.
// Default is 0.
// 
// "horizontalResolution":
// Must be unary and must be a non-negative integer.
// Default is the resolution of the monitor.
// 
// "verticalResolution" :
// Must be unary and a must be a non-negative integer.
// Default is the vertical resolution of the monitor.
static void
updateDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  )
{
  Arcadia_String* key;

  Arcadia_List* values = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBack(thread, values,
                          Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"windowed", sizeof(u8"windowed") - 1)))));
  Arcadia_List_insertBack(thread, values,
                          Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"borderless", sizeof(u8"borderless") - 1)))));
  key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"windowMode", sizeof(u8"windowMode") - 1)));
  _validateStringEnumeration(thread, node, key, values, 0);

  key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"monitor", sizeof(u8"monitor") - 1)));
  _validateIntegerRange(thread, node, key, Arcadia_Integer32Value_Literal(0), Arcadia_Integer32Value_Maximum, Arcadia_Integer32Value_Literal(0));

  key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"horizontalResolution", sizeof(u8"horizontalResolution") - 1)));
  _validateIntegerRange(thread, node, key, Arcadia_Integer32Value_Literal(0), Arcadia_Integer32Value_Maximum, Arcadia_Integer32Value_Literal(1024));

  key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"verticalResolution", sizeof(u8"verticalResolution") - 1)));
  _validateIntegerRange(thread, node, key, Arcadia_Integer32Value_Literal(0), Arcadia_Integer32Value_Maximum, Arcadia_Integer32Value_Literal(768));
}

static void
updateVisualsConfiguration
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_MapNode* node
  )
{
  Arcadia_String* key;
  Arcadia_DataDefinitionLanguage_Tree_MapNode* sectionNode;
  
  key = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"visuals", sizeof(u8"visuals") - 1)));
  _validateMap(thread, node, key);
  sectionNode = (Arcadia_DataDefinitionLanguage_Tree_MapNode*)((Arcadia_DataDefinitionLanguage_Tree_MapEntryNode*)Arcadia_List_getObjectReferenceValueAt(thread, node->entries, _find(thread, node, 0, key)))->value;
  updateDisplayMode(thread, sectionNode);
  updateVerticalSynchronization(thread, sectionNode);
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

static Arcadia_DataDefinitionLanguage_Tree_MapNode*
loadConfiguration
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(thread);
  Arcadia_FilePath* file;

  // (1) Ensure the organization's configuration folder exists.
  file = Arcadia_FileSystem_getConfigurationFolder(thread, fileSystem);
  Arcadia_FileSystem_createDirectory(thread, fileSystem, file);

  // (2) Ensure the product's configuration folder exists.
  file = Arcadia_FilePath_clone(thread, file);
  Arcadia_FilePath_append(thread, file, Arcadia_FilePath_parseGeneric(thread, u8"Demo", sizeof(u8"Demo") - 1));
  Arcadia_FileSystem_createDirectory(thread, fileSystem, file);

  // (3) Ensure the product's configuration file exists.
  file = Arcadia_FilePath_clone(thread, file);
  Arcadia_FilePath_append(thread, file, Arcadia_FilePath_parseGeneric(thread, u8"Configuration.txt", sizeof(u8"Configuration.txt") - 1));
  if (!Arcadia_FileSystem_regularFileExists(thread, fileSystem, file)) {
    // Create a configuration file with an empty map.
    Arcadia_DataDefinitionLanguage_Unparser* unparser = Arcadia_DataDefinitionLanguage_Unparser_create(thread);
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
    Arcadia_DataDefinitionLanguage_Unparser_run(thread, unparser, (Arcadia_DataDefinitionLanguage_Tree_Node*)Arcadia_DataDefinitionLanguage_Tree_MapNode_create(thread),
                                                (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, byteBuffer));
    Arcadia_FileSystem_setFileContents(thread, fileSystem, file, byteBuffer);
  }

  // (4) Product's configuration file exists.
  // If syntactical or semantical analysis fails, replace its contents by an empty configuration file.
  Arcadia_DataDefinitionLanguage_Tree_MapNode* rootNode = NULL;
  Arcadia_JumpTarget jumpTarget;

  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis = Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create(thread);
    Arcadia_ByteBuffer* byteBuffer = Arcadia_FileSystem_getFileContents(thread, fileSystem, file);
    Arcadia_DataDefinitionLanguage_Parser* parser = Arcadia_DataDefinitionLanguage_Parser_create(thread);
    Arcadia_DataDefinitionLanguage_Parser_setInput(thread, parser,
                                                   (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, byteBuffer));
    Arcadia_DataDefinitionLanguage_Tree_Node* node = Arcadia_DataDefinitionLanguage_Parser_run(thread, parser);
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, (Arcadia_Object*)node), _Arcadia_DataDefinitionLanguage_Tree_MapNode_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run(thread, semanticalAnalysis, node);
    rootNode = (Arcadia_DataDefinitionLanguage_Tree_MapNode*)node;
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    // Create a configuration file with an empty map.
    Arcadia_DataDefinitionLanguage_Unparser* unparser = Arcadia_DataDefinitionLanguage_Unparser_create(thread);
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
    rootNode = Arcadia_DataDefinitionLanguage_Tree_MapNode_create(thread);
    Arcadia_DataDefinitionLanguage_Unparser_run(thread, unparser, (Arcadia_DataDefinitionLanguage_Tree_Node*)rootNode,
                                                (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, byteBuffer));
    Arcadia_FileSystem_setFileContents(thread, fileSystem, file, byteBuffer);
  }

  // (5) Product configuration file exists.
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
    updateVisualsConfiguration(thread, rootNode);
    updateAudialsConfiguration(thread, rootNode);
    Arcadia_DataDefinitionLanguage_Unparser* unparser = Arcadia_DataDefinitionLanguage_Unparser_create(thread);
    Arcadia_DataDefinitionLanguage_Unparser_run(thread, unparser, (Arcadia_DataDefinitionLanguage_Tree_Node*)rootNode,
                                                (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, byteBuffer));
    Arcadia_FileSystem_setFileContents(thread, fileSystem, file, byteBuffer);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
  return rootNode;
}

static void
print
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    const Arcadia_Natural8Value* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_SizeValue currentNumberOfAttempts = 0, maximumNumberOfAttempts = 3;
  Arcadia_SizeValue n = 0, m = 0;
  while (n < numberOfBytes && currentNumberOfAttempts < maximumNumberOfAttempts) {
    Arcadia_FileHandle_write(thread, self, bytes + n, numberOfBytes - n, &m);
    n += m;
    currentNumberOfAttempts++;
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
  Arcadia_Visuals_Application* application = NULL;
  Arcadia_Visuals_Window* window = NULL;
  Arcadia_BooleanValue audialsInitialized = Arcadia_BooleanValue_False;

  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
  #if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
    application = (Arcadia_Visuals_Application*)Arcadia_Visuals_Windows_Application_getOrCreate(thread);
  #elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
    application = (Arcadia_Visuals_Application*)Arcadia_Visuals_Linux_Application_getOrCreate(thread);
  #else
    #error("environment system not (yet) supported")
  #endif
    
    Arcadia_Object_lock(thread, (Arcadia_Object*)application);

    Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(thread);
    Arcadia_FileHandle* fileHandle = Arcadia_FileHandle_create(thread, fileSystem);
    Arcadia_FileHandle_openStandardOutput(thread, fileHandle);
    Arcadia_List* displayDevices = Arcadia_Visuals_Application_getDisplayDevices(thread,application);

    print(thread, fileHandle, u8"display devices:\n", sizeof(u8"display devices:\n"));
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)displayDevices); i < n; ++i) {
      Arcadia_Visuals_DisplayDevice* displayDevice =
        (Arcadia_Visuals_DisplayDevice*)Arcadia_List_getObjectReferenceValueAt(thread, displayDevices, i);
      
      Arcadia_String* a;

      print(thread, fileHandle, u8"  ", sizeof(u8"  ") - 1);
      a = Arcadia_String_createFromSize(thread, i);
      print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
      print(thread, fileHandle, u8") id: ", sizeof(u8") id: ") - 1);
      a = Arcadia_Visuals_DisplayDevice_getId(thread, displayDevice);
      print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
      print(thread, fileHandle, u8", name: ", sizeof(u8", name: ") - 1);
      a = Arcadia_Visuals_DisplayDevice_getName(thread, displayDevice);
      print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
      print(thread, fileHandle, u8"\n", sizeof(u8"\n") - 1);

      Arcadia_List* displayModes = Arcadia_Visuals_DisplayDevice_getAvailableDisplayModes(thread, displayDevice);
      for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)displayModes); i < n; ++i) {
        Arcadia_Visuals_DisplayMode* displayMode = (Arcadia_Visuals_DisplayMode*)Arcadia_List_getObjectReferenceValueAt(thread, displayModes, i);
        print(thread,fileHandle, u8"    ", sizeof(u8"    ") - 1);
        print(thread, fileHandle, u8"horizontal resolution: ", sizeof(u8"horizontal resolution: ") - 1);
        a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getHorizontalResolution(thread, displayMode));
        print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
        print(thread, fileHandle, u8", vertical resolution: ", sizeof(u8", vertical resolution: ") - 1);
        a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getVerticalResolution(thread, displayMode));
        print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
        print(thread, fileHandle, u8", color depth: ", sizeof(u8", color depth: ") - 1);
        a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getColorDepth(thread, displayMode));
        print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
        print(thread, fileHandle, u8", frequency: ", sizeof(u8", frequency: ") - 1);
        a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getFrequency(thread, displayMode));
        print(thread, fileHandle, Arcadia_String_getBytes(thread, a), Arcadia_String_getNumberOfBytes(thread, a));
        print(thread, fileHandle, u8"\n", sizeof(u8"\n") - 1);
      }
    }
    Arcadia_DataDefinitionLanguage_Tree_MapNode* configuration = loadConfiguration(thread);
    // (1) Get the display device.
    Arcadia_Visuals_DisplayDevice* displayDevice = NULL;
    {
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
      displayDevice =
        (Arcadia_Visuals_DisplayDevice*)Arcadia_List_getObjectReferenceValueAt(thread, displayDevices, displayDeviceIndex);
    }
    // (2) Get the window mode.
    Arcadia_String* windowMode = NULL;
    {
      Arcadia_String* windowModeString = NULL;
      char const* path[] = {
        u8"visuals",
        u8"windowMode",
      };
      const char* values[] = {
        u8"windowed",
        u8"borderless",
      };
      Arcadia_JumpTarget jumpTarget;
      Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
      if (Arcadia_JumpTarget_save(&jumpTarget)) {
        windowModeString = Cfg2_getString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2);
        Arcadia_BooleanValue found = Arcadia_BooleanValue_False;
        for (Arcadia_SizeValue i = 0, n = 2; i < n; ++i) {
          Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(windowModeString);
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
        windowModeString = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"windowed", sizeof(u8"windowed") - 1)));
        Cfg2_setString(thread, (Arcadia_DataDefinitionLanguage_Tree_Node*)configuration, path, 2, windowModeString);
      }
      windowMode = windowModeString;
    }

    // (1) Initialize Audials.
    Audials_startup(thread);
    audialsInitialized = Arcadia_BooleanValue_True;

    // (2) Play sine wave.
    Audials_playSine(thread);

    // (3) Create a window.
    window = Arcadia_Visuals_Application_createWindow(thread, application);
    Arcadia_Object_lock(thread, (Arcadia_Object*)window);

    // (4) Ensure the window is opened.
    //Arcadia_Visuals_DisplayMode* currentDisplayMode = Arcadia_Visuals_DisplayDevice_getCurrentDisplayMode(thread, displayDevice);
    Arcadia_Visuals_Window_open(thread, window);
  
    // (5) Set the window size and position.
    Arcadia_Integer32Value left, top, right, bottom;
    Arcadia_Visuals_DisplayDevice_getBounds(thread, displayDevice, &left, &top, &right, &bottom);
    Arcadia_Visuals_Window_setPosition(thread, window, left, top);
    Arcadia_Visuals_Window_setSize(thread, window, right - left, bottom - top);
    
    // (6) Set the window mode.
    Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(windowMode),
                  b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"windowed", sizeof(u8"windowed") - 1))));
    if (Arcadia_Value_isEqualTo(thread, &a, &b)) {
      Arcadia_Visuals_Window_setFullscreen(thread, window, Arcadia_BooleanValue_True);
    } else {
      Arcadia_Visuals_Window_setFullscreen(thread, window, Arcadia_BooleanValue_False);
    }
    Arcadia_Visuals_Window_setPosition(thread, window, left, top);
    Arcadia_Visuals_Window_setSize(thread, window, right - left + 1, bottom - top + 1);
    
    
    Arcadia_Integer32Value width;
    Arcadia_Integer32Value height;
    Arcadia_Visuals_Icon* icon;

    // (5) Set the big icon.
    Arcadia_Visuals_Window_getRequiredBigIconSize(thread, window, &width, &height);
    icon = Arcadia_Visuals_Application_createIcon(thread, application, width, height, 47, 47, 47, 255);
    Arcadia_Visuals_Window_setBigIcon(thread, window, icon);

    // (6) Set the small icon.
    Arcadia_Visuals_Window_getRequiredSmallIconSize(thread, window, &width, &height);
    icon = Arcadia_Visuals_Application_createIcon(thread, application, width, height, 47, 47, 47, 255);
    Arcadia_Visuals_Window_setSmallIcon(thread, window, icon);

    // (7) Set the title.
    Arcadia_Visuals_Window_setTitle(thread, window, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"Michael Heilmann's Liminality", sizeof(u8"Michael Heilmann's Liminality") - 1)));

    Arcadia_Process_stepArms(process);

    // (8) Enter the message loop.
    while (!Arcadia_Visuals_Window_getQuitRequested(thread, window)) {
      Arcadia_Process_stepArms(process);
      Arcadia_Visuals_Window_update(thread, window);
      Arcadia_Visuals_Window_beginRender(thread, window);
      Arcadia_Visuals_Window_endRender(thread, window);
    }

    // (9) Ensure the window is closed.
    Arcadia_Visuals_Window_close(thread, window);

    if (audialsInitialized) {
      Audials_shutdown(thread);
      audialsInitialized = Arcadia_BooleanValue_False;
    }

    Arcadia_Thread_popJumpTarget(thread);

    if (window) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (application) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application);
      application = NULL;
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
    if (application) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)application);
      application = NULL;
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
