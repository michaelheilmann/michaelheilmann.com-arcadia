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

#include <stdio.h> // @todo Remove references to `stdio.h`.
#include <stdlib.h>
#include <string.h>
#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "Arcadia.Tools.GenerateRyuLookupTables/generateReal32Table.h"
#include "Arcadia.Tools.GenerateRyuLookupTables/generateReal64Table.h"
#include "Arcadia.Tools.GenerateRyuLookupTables/Configure.h"

void
main1
  (
    Arcadia_Thread* thread,
    int argc,
    char** argv
  )
{
  Arcadia_Value target;
  Arcadia_Value_setVoidValue(&target, Arcadia_VoidValue_Void);
  Arcadia_List* arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argument = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, argv[argi], strlen(argv[argi])));
    Arcadia_List_insertBackObjectReferenceValue(thread, arguments, (Arcadia_ObjectReferenceValue)argument);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)arguments); i < n; ++i) {
    Arcadia_String* argument = (Arcadia_String*)Arcadia_List_getObjectReferenceValueAt(thread, arguments, i);
    Arcadia_UTF8StringReader* r = Arcadia_UTF8StringReader_create(thread, argument);
    Arcadia_String* key = NULL,
                  * value = NULL;
    if (!Arcadia_CommandLine_parseArgument(thread, (Arcadia_UTF8Reader*)r, &key, &value)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (Arcadia_String_isEqualTo_pn(thread, key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_Value_setObjectReferenceValue(&target, value);
    } else {
      Arcadia_CommandLine_raiseUnknownArgumentError(thread, key, value);
    }
    fwrite(Arcadia_String_getBytes(thread, key), 1, Arcadia_String_getNumberOfBytes(thread, key), stdout);
    if (value) {
      fwrite(u8"=", 1, sizeof(u8"=") - 1, stdout);
      fwrite(Arcadia_String_getBytes(thread, value), 1, Arcadia_String_getNumberOfBytes(thread, value), stdout);
    }
    fwrite(u8"\n", 1, sizeof(u8"\n") - 1, stdout);
  }
  if (Arcadia_Value_isVoidValue(&target)) {
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"target", sizeof(u8"target") - 1)));
  }

  Arcadia_String* pathPrefixString = (Arcadia_String*)Arcadia_Value_getObjectReferenceValue(&target);
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_FilePath* pathPrefix = Arcadia_FilePath_parseNative(thread, pathPrefixString);
  Arcadia_StringBuffer* resultString = Arcadia_StringBuffer_create(thread);
  Arcadia_ByteBuffer* resultBytes = Arcadia_ByteBuffer_create(thread);
  Arcadia_FilePath* path;

  Arcadia_Tools_RyuLookupTableGenerator_generateReal64Table(thread, Arcadia_BooleanValue_True, resultString);
  Arcadia_ByteBuffer_insertBackBytes(thread, resultBytes, Arcadia_StringBuffer_getBytes(thread, resultString), Arcadia_StringBuffer_getNumberOfBytes(thread, resultString));
  path = Arcadia_FilePath_clone(thread, pathPrefix);
  Arcadia_FilePath_append(thread, path, Arcadia_FilePath_parseGeneric(thread, u8"BigTablesReal64.i", sizeof("BigTablesReal64.i") - 1));
  Arcadia_FileSystem_setFileContents(thread, fileSystem, path, resultBytes);
  Arcadia_StringBuffer_clear(thread, resultString);
  Arcadia_ByteBuffer_clear(thread, resultBytes);

  Arcadia_Tools_RyuLookupTableGenerator_generateReal64Table(thread, Arcadia_BooleanValue_False, resultString);
  Arcadia_ByteBuffer_insertBackBytes(thread, resultBytes, Arcadia_StringBuffer_getBytes(thread, resultString), Arcadia_StringBuffer_getNumberOfBytes(thread, resultString));
  path = Arcadia_FilePath_clone(thread, pathPrefix);
  Arcadia_FilePath_append(thread, path, Arcadia_FilePath_parseGeneric(thread, u8"SmallTablesReal64.i", sizeof("SmallTablesReal64.i") - 1));
  Arcadia_FileSystem_setFileContents(thread, fileSystem, path, resultBytes);
  Arcadia_StringBuffer_clear(thread, resultString);
  Arcadia_ByteBuffer_clear(thread, resultBytes);

  Arcadia_Tools_RyuLookupTableGenerator_generateReal32Table(thread, resultString);
  Arcadia_ByteBuffer_insertBackBytes(thread, resultBytes, Arcadia_StringBuffer_getBytes(thread, resultString), Arcadia_StringBuffer_getNumberOfBytes(thread, resultString));
  path = Arcadia_FilePath_clone(thread, pathPrefix);
  Arcadia_FilePath_append(thread, path, Arcadia_FilePath_parseGeneric(thread, u8"TablesReal32.i", sizeof("TablesReal32.i") - 1));
  Arcadia_FileSystem_setFileContents(thread, fileSystem, path, resultBytes);
  Arcadia_StringBuffer_clear(thread, resultString);
  Arcadia_ByteBuffer_clear(thread, resultBytes);
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
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(thread, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(thread);
  Arcadia_Status status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
