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

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/MILC/AST/Include.h"
#include <stdlib.h>
#include <string.h>

static Arcadia_ImmutableList*
makeNatural8
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_List* temporary = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, u8"Arcadia"));
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, u8"Natural8"));
  return Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(temporary));
}

static Arcadia_String* mapType(Arcadia_Thread* thread, Arcadia_String* source) {
  Arcadia_Map* map = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  Arcadia_Map_set(thread, map, Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Arcadia.Integer")),
                               Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Arcadia_Integer32Value")),
                               NULL, NULL);
  Arcadia_Map_set(thread, map, Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Arcadia.String")),
                               Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Arcadia_String*")),
                               NULL, NULL);
}

static void
main1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_List* constructorParameters = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, constructorParameters, Arcadia_MILC_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"red"), Arcadia_MILC_AST_IdentifierNode_create(thread, makeNatural8(thread))));
  Arcadia_List_insertBackObjectReferenceValue(thread, constructorParameters, Arcadia_MILC_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"green"), Arcadia_MILC_AST_IdentifierNode_create(thread, makeNatural8(thread))));
  Arcadia_List_insertBackObjectReferenceValue(thread, constructorParameters, Arcadia_MILC_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"blue"), Arcadia_MILC_AST_IdentifierNode_create(thread, makeNatural8(thread))));
  Arcadia_MILC_AST_ConstructorDefinitionNode* constructor = Arcadia_MILC_AST_ConstructorDefinitionNode_create(thread, NULL, constructorParameters, NULL);

  Arcadia_List* classBody = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, constructor);
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, Arcadia_MILC_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"red"), Arcadia_MILC_AST_IdentifierNode_create(thread, makeNatural8(thread))));
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, Arcadia_MILC_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"green"), Arcadia_MILC_AST_IdentifierNode_create(thread, makeNatural8(thread))));
  Arcadia_List_insertBackObjectReferenceValue(thread, classBody, Arcadia_MILC_AST_FieldDefinitionNode_create(thread, Arcadia_String_createFromCxxString(thread, u8"blue"), Arcadia_MILC_AST_IdentifierNode_create(thread, makeNatural8(thread))));

  Arcadia_ImmutableList* className = NULL,
                       * extendedClassName = NULL;

  Arcadia_List* temporary = (Arcadia_List*)Arcadia_ArrayList_create(thread);

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)temporary);
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, "Arcadia"));
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, "AssetDefinitionLanguage"));
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, "ColorDefinition"));
  className = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(temporary));

  Arcadia_Collection_clear(thread, (Arcadia_Collection*)temporary);
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, "Arcadia"));
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, "AssetDefinitionLanguage"));
  Arcadia_List_insertBackObjectReferenceValue(thread, temporary, Arcadia_String_createFromCxxString(thread, "Definition"));
  extendedClassName = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(temporary));

  Arcadia_MILC_AST_ClassDefinitionNode_create
    (
      thread,
      Arcadia_MILC_AST_IdentifierNode_create(thread, className),
      Arcadia_MILC_AST_IdentifierNode_create(thread, extendedClassName),
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
  if (!Arcadia_Tests_safeExecute(&main1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
