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

#include "Arcadia/MILC/Backend/Implementation.h"

#include "Arcadia/MILC/Backend/SymbolInfo.h"
#include "Arcadia/MILC/Completer.h"
#include "Arcadia/MILC/Backend/EnumerationConstantSymbolInfo.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_ImplementationDispatch* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self
  );

static void
onWriteEnumerationConstant
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Backend_EnumerationConstantSymbolInfo* symbolInfo,
    Arcadia_MILC_Context* context
  );

static void
onWriteSymbolInfo
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_MILC_Context* context 
  );
  
static void
onVisitSymbol
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );
  
static void
onVisitScope
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Context* context,
    Arcadia_Languages_Scope* scope
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

Arcadia_defineObjectType(u8"Arcadia.MILC.Backend.Implementation", Arcadia_MILC_Backend_Implementation,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Backend_Implementation);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_Backend_Implementation);
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self
  )
{/*Intentionally empty.*/}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_ImplementationDispatch* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self
  )
{/*Intentionally empty.*/}

static void
onVisitSymbol
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{ 
  /// Only top level symbols are considered here.
  switch (symbol->kind) {
    case Arcadia_MILC_SymbolKind_Module: {
      onVisitScope(thread, self, context, ((Arcadia_MILC_ModuleSymbol*)symbol)->scope);
    } break;
    default: {
      Arcadia_MILC_Backend_SymbolInfo* symbolInfo = Arcadia_MILC_Backend_SymbolInfo_create(thread, context, symbol);
      Arcadia_StringBuilder* stringBuilder = Arcadia_StringBuilder_create(thread);
      Arcadia_MILC_Backend_SymbolInfo_dump(thread, symbolInfo, 2, stringBuilder);
      Arcadia_Log_information(thread, context->log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuilder)));

      Arcadia_Map_set(thread, context->backendSymbolInfos, Arcadia_Value_makeObjectReferenceValue(symbol), Arcadia_Value_makeObjectReferenceValue(symbolInfo), NULL, NULL);
    } break;
  }
}

static void
onVisitScope
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Context* context,
    Arcadia_Languages_Scope* scope
  )
{ 
  Arcadia_List* symbols = Arcadia_Map_getValues(thread, scope->entries);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)symbols); i < n; ++i) {
    Arcadia_MILC_Symbol* symbol = (Arcadia_MILC_Symbol*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, symbols, i, _Arcadia_MILC_Symbol_getType(thread));
    onVisitSymbol(thread, self, context, symbol);
  }
}

Arcadia_MILC_Backend_Implementation*
Arcadia_MILC_Backend_Implementation_create
  (
    Arcadia_Thread* thread
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Backend_Implementation);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_Backend_Implementation);
}

static void
onWriteEnumerationConstant
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Backend_EnumerationConstantSymbolInfo* symbolInfo,
    Arcadia_MILC_Context* context
  )
{ }

static void
onWriteSymbolInfo
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo,
    Arcadia_MILC_Context* context
  )
{ 
  if (symbolInfo->symbol->completer) {
    Arcadia_MILC_Completer_complete(thread, symbolInfo->symbol->completer, context, symbolInfo->symbol);
  }
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

  Arcadia_StringBuilder* stringBuilder = Arcadia_StringBuilder_create(thread);
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_ByteArrayBuilder* byteArrayBuilder = Arcadia_ByteArrayBuilder_create(thread);

  Arcadia_StringBuilder_clear(thread, stringBuilder);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, COPYRIGHT);
  Arcadia_ByteArrayBuilder_clear(thread, byteArrayBuilder);
  Arcadia_ByteArrayBuilder_insertBackBytes(thread, byteArrayBuilder, Arcadia_StringBuilder_getBytes(thread, stringBuilder), Arcadia_StringBuilder_getNumberOfBytes(thread, stringBuilder));
  Arcadia_FileSystem_setFileContents(thread, fileSystem, symbolInfo->cxxSourceFilePath, byteArrayBuilder);

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
  if (symbolInfo->symbol->kind == Arcadia_MILC_SymbolKind_Enumeration) {
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

#if 1
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
    Arcadia_List* constantSymbols = Arcadia_Map_getValues(thread, ((Arcadia_MILC_EnumerationSymbol*)symbolInfo->symbol)->scope->entries);
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)constantSymbols); i < n; ++i) {
      Arcadia_MILC_EnumerationConstantSymbol* constantSymbol = (Arcadia_MILC_EnumerationConstantSymbol*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, constantSymbols, i, _Arcadia_MILC_EnumerationConstantSymbol_getType(thread));
      Arcadia_Value temporary = Arcadia_Map_get(thread, context->backendSymbolInfos, Arcadia_Value_makeObjectReferenceValue(constantSymbol));
      Arcadia_MILC_Backend_EnumerationConstantSymbolInfo* constantSymbolInfo;
      if (Arcadia_Value_isVoidValue(&temporary)) {
        constantSymbolInfo = Arcadia_MILC_Backend_EnumerationConstantSymbolInfo_create(thread, context, (Arcadia_MILC_Symbol*)constantSymbol);
        Arcadia_Map_set(thread, context->backendSymbolInfos, Arcadia_Value_makeObjectReferenceValue(constantSymbol), Arcadia_Value_makeObjectReferenceValue(constantSymbolInfo), NULL, NULL);
      } else {
        constantSymbolInfo = (Arcadia_MILC_Backend_EnumerationConstantSymbolInfo*)Arcadia_Value_getObjectReferenceValueChecked(thread, temporary, _Arcadia_MILC_Backend_EnumerationConstantSymbolInfo_getType(thread));
      }
      Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "  ");
      Arcadia_StringBuilder_insertBackString(thread, stringBuilder, constantSymbolInfo->cxxName);
      Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ",\n");
      Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
    }
#endif

    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "};");
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  }

  // #endif
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "#endif // ");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, symbolInfo->cxxNameUpperCase);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "_H_INCLUDED");
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, "\n");

  Arcadia_ByteArrayBuilder_clear(thread, byteArrayBuilder);
  Arcadia_ByteArrayBuilder_insertBackBytes(thread, byteArrayBuilder, Arcadia_StringBuilder_getBytes(thread, stringBuilder), Arcadia_StringBuilder_getNumberOfBytes(thread, stringBuilder));
  Arcadia_FileSystem_setFileContents(thread, fileSystem, symbolInfo->cxxHeaderFilePath, byteArrayBuilder);
}

void
Arcadia_MILC_Backend_Implementation_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_Implementation* self,
    Arcadia_MILC_Context* context
  )
{
  // (1) Clear the collection of backend symbol infos.
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)context->backendSymbolInfos);
  // (2) Enter the backend symbol infos.
  onVisitScope(thread, self, context, context->scope);

  Arcadia_List* symbolInfos = Arcadia_Map_getValues(thread, context->backendSymbolInfos);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)symbolInfos); i < n; ++i) {
    Arcadia_MILC_Backend_SymbolInfo* symbolInfo = (Arcadia_MILC_Backend_SymbolInfo*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, symbolInfos, i, _Arcadia_MILC_Backend_SymbolInfo_getType(thread));
    if (symbolInfo->symbol->kind == Arcadia_MILC_SymbolKind_Class || symbolInfo->symbol->kind == Arcadia_MILC_SymbolKind_Enumeration) {
      onWriteSymbolInfo(thread, self, symbolInfo, context);
    }
  }
}
