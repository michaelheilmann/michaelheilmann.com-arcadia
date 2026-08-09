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

#include "Arcadia/MILC/Backend/EnumerationSymbolWriter.h"

#include "Arcadia/MILC/Include.h"
#include "Arcadia/MILC/AST/Include.h"
#include "Arcadia/MILC/Backend/SymbolInfo.h"
#include "Arcadia/MILC/Backend/Implementation.h"
#include "Arcadia/MILC/Backend/EnumerationConstantSymbolInfo.h"

static const char* COPYRIGHT =
  "// The author of this software is Michael Heilmann (contact@michaelheilmann.com).\n"
  "//\n"
  "// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).\n"
  "//\n"
  "// Permission to use, copy, modify, and distribute this software for any\n"
  "// purpose without fee is hereby granted, provided that this entire notice\n"
  "// is included in all copies of any software which is or includes a copy\n"
  "// or modification of this software and in all copies of the supporting\n"
  "// documentation for such software.\n"
  "//\n"
  "// THIS SOFTWARE IS BEING PROVIDED \"AS IS\", WITHOUT ANY EXPRESS OR IMPLIED\n"
  "// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY\n"
  "// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY\n"
  "// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.\n"
  ;

static Arcadia_String*
nameToPathString
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

static Arcadia_String*
nameToCxxUpperCaseName
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

static void
onWriteEnumerationSourceFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  );

static void
onWriteEnumerationHeaderFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  );

static void
onWriteSourceFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  );

static void
onWriteHeaderFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  );

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriterDispatch* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self
  );

static void
Arcadia_MILC_Backend_EnumerationSymbolWriter_writeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_CXXFileType fileType,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.Backend.EnumerationSymbolWriter", Arcadia_MILC_Backend_EnumerationSymbolWriter,
                         u8"Arcadia.MILC.Backend.SymbolWriter", Arcadia_MILC_Backend_SymbolWriter,
                         &_typeOperations);

static Arcadia_String*
nameToPathString
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_StringBuilder* sb = Arcadia_StringBuilder_create(thread);
  Arcadia_UnicodeCodePointReader* ucpr = (Arcadia_UnicodeCodePointReader*)Arcadia_ByteReader_UnicodeCodePointReader_create(thread, (Arcadia_ByteReader*)Arcadia_String_ByteReader_create(thread, string));
  while (Arcadia_UnicodeCodePointReader_hasValue(thread, ucpr)) {
    Arcadia_Natural32Value uc = Arcadia_UnicodeCodePointReader_getValue(thread, ucpr);
    if (uc == '.') {
      uc = '/';
    }
    Arcadia_StringBuilder_insertBackCodePoint(thread, sb, uc);
    Arcadia_UnicodeCodePointReader_nextValue(thread, ucpr);
  }
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(sb));
}

static Arcadia_String*
nameToCxxUpperCaseName
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  )
{
  Arcadia_StringBuilder* sb = Arcadia_StringBuilder_create(thread);
  Arcadia_UnicodeCodePointReader* ucpr = (Arcadia_UnicodeCodePointReader*)Arcadia_ByteReader_UnicodeCodePointReader_create(thread, (Arcadia_ByteReader*)Arcadia_String_ByteReader_create(thread, string));
  while (Arcadia_UnicodeCodePointReader_hasValue(thread, ucpr)) {
    Arcadia_Natural32Value uc = Arcadia_UnicodeCodePointReader_getValue(thread, ucpr);
    if (uc == '.') {
      uc = '_';
    }
    Arcadia_StringBuilder_insertBackCodePoint(thread, sb, uc);
    Arcadia_UnicodeCodePointReader_nextValue(thread, ucpr);
  }
  Arcadia_StringBuilder_toUpperASCII(thread, sb, NULL, NULL);
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(sb));
}

static void
onWriteEnumerationSourceFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  )
{ 
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "static const Arcadia_Type_Operations _typeOperations = {\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "  Arcadia_Type_Operations_Initializer,\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "};\n");

  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "Arcadia_defineEnumerationType(u8\"");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->symbol->name);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\", ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxName);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ",\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "                              &_typeOperations);\n");
}

static void
onWriteEnumerationHeaderFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  )
{ 
  Arcadia_Map* symbolInfos = Arcadia_MILC_Backend_Implementation_getInstance(thread, context)->symbolInfos;

  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "Arcadia_declareEnumerationType");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "(");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\"");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->symbol->name);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\"");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ",\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "                               ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxName);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ")");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ";\n");

  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "enum ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxName);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, " {\n");

  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_List* constantSymbols = ((Arcadia_MILC_EnumerationSymbol*)symbolInfo->symbol)->members;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)constantSymbols); i < n; ++i) {
    Arcadia_MILC_EnumerationConstantSymbol* constantSymbol = (Arcadia_MILC_EnumerationConstantSymbol*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, constantSymbols, i, _Arcadia_MILC_EnumerationConstantSymbol_getType(thread));
    Arcadia_Value temporary = Arcadia_Map_get(thread, symbolInfos, Arcadia_Value_makeObjectReferenceValue(constantSymbol));
    Arcadia_MILC_Backend_EnumerationConstantSymbolInfo* constantSymbolInfo;
    if (Arcadia_Value_isVoidValue(&temporary)) {
      constantSymbolInfo = Arcadia_MILC_Backend_EnumerationConstantSymbolInfo_create(thread, context, (Arcadia_MILC_Symbol*)constantSymbol);
      Arcadia_Map_set(thread, symbolInfos, Arcadia_Value_makeObjectReferenceValue(constantSymbol), Arcadia_Value_makeObjectReferenceValue(constantSymbolInfo), NULL, NULL);
    } else {
      constantSymbolInfo = (Arcadia_MILC_Backend_EnumerationConstantSymbolInfo*)Arcadia_Value_getObjectReferenceValueChecked(thread, temporary, _Arcadia_MILC_Backend_EnumerationConstantSymbolInfo_getType(thread));
    }
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "  ");
    Arcadia_StringBuilder_insertBackString(thread, stringBuilder, constantSymbolInfo->cxxName);
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, " = ");
    Arcadia_StringBuilder_insertBackString(thread, stringBuilder, constantSymbol->ast->initializer->value);
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ",\n");
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  }

  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "};");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
}

static void
onWriteSourceFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  )
{ 
  if (symbolInfo->symbol->completer) {
    Arcadia_MILC_Completer_complete(thread, symbolInfo->symbol->completer, context, symbolInfo->symbol);
  }

  Arcadia_StringBuilder_clear(thread, stringBuilder);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, COPYRIGHT);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");

  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#define ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, nameToCxxUpperCaseName(thread, ((Arcadia_MILC_Symbol*)symbolInfo->symbol->enclosing)->name));
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "_PRIVATE (1)");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#include \"");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, nameToPathString(thread, symbolInfo->symbol->name));
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ".h\"");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");

  onWriteEnumerationSourceFile(thread, self, context, symbolInfo, stringBuilder);
}

static void
onWriteHeaderFile
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  )
{ 
  if (symbolInfo->symbol->completer) {
    Arcadia_MILC_Completer_complete(thread, symbolInfo->symbol->completer, context, symbolInfo->symbol);
  }

  Arcadia_StringBuilder_clear(thread, stringBuilder);
  // #ifndef 
  // #define
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, COPYRIGHT);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#ifndef ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxNameUpperCase);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "_H_INCLUDED");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#define ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxNameUpperCase);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "_H_INCLUDED");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#include \"Arcadia/Ring1/Include.h\"");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");

  onWriteEnumerationHeaderFile(thread, self, context, symbolInfo, stringBuilder);

  // #endif
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#endif // ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxNameUpperCase);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "_H_INCLUDED");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
}

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Backend_EnumerationSymbolWriter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_Backend_EnumerationSymbolWriter);
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self
  )
{/*Intentionally empty.*/}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriterDispatch* self
  )
{
  ((Arcadia_MILC_Backend_SymbolWriterDispatch*)self)->write = (void (*)(Arcadia_Thread*, Arcadia_MILC_Backend_SymbolWriter*, Arcadia_MILC_Context*, Arcadia_MILC_Backend_CXXFileType, Arcadia_MILC_Backend_SymbolInfo*,Arcadia_StringBuilder*)) & Arcadia_MILC_Backend_EnumerationSymbolWriter_writeImpl;
}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_Backend_EnumerationSymbolWriter_writeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_EnumerationSymbolWriter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Backend_CXXFileType fileType,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_StringBuilder* stringBuilder
  )
{
  switch (fileType) {
    case Arcadia_MILC_Backend_CXXFileType_C: {
      onWriteSourceFile(thread, self, context, symbolInfo, stringBuilder);
    } break;
    case Arcadia_MILC_Backend_CXXFileType_H: {
      onWriteHeaderFile(thread, self, context, symbolInfo, stringBuilder);
    } break;
  };
}

Arcadia_MILC_Backend_EnumerationSymbolWriter*
Arcadia_MILC_Backend_EnumerationSymbolWriter_create
  (
    Arcadia_Thread* thread
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Backend_EnumerationSymbolWriter);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_Backend_EnumerationSymbolWriter);
}
