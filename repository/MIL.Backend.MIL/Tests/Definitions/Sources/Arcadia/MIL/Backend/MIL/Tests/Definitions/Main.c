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

#include "Arcadia/MIL/Frontend/Include.h"

#include <string.h>

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_List* constructorParameters = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, constructorParameters, Arcadia_MIL_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"red"), Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8")));
  Arcadia_List_insertBackObjectReferenceValue(thread, constructorParameters, Arcadia_MIL_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"green"), Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8")));
  Arcadia_List_insertBackObjectReferenceValue(thread, constructorParameters, Arcadia_MIL_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"blue"), Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8")));
  Arcadia_MIL_AST_ConstructorDefinitionNode* constructor = Arcadia_MIL_AST_ConstructorDefinitionNode_create(thread, NULL, constructorParameters, NULL);

  Arcadia_List* classBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, constructor);
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, Arcadia_MIL_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"red"), Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8")));
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, Arcadia_MIL_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"green"), Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8")));
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, Arcadia_MIL_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"blue"), Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8")));

  Arcadia_MIL_AST_ClassDefinitionNode_create
    (
      thread,
      Arcadia_String_createFromCxxString(thread, u8"Arcadia.AssetDefinitionLanguage.ColorDefinition"),
      Arcadia_String_createFromCxxString(thread, u8"Arcadia.AssetDefinitionLanguage.Definition"),
      classBody
    );
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
