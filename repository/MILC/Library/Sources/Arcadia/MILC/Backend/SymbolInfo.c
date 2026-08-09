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

#include "Arcadia/MILC/Backend/SymbolInfo.h"

#include "Arcadia/MILC/Include.h"
#include "Arcadia/MILC/AST/Include.h"
#include <assert.h>

static Arcadia_String*
nameToPathString
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

static Arcadia_String*
nameToCxxName
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

static Arcadia_FilePath*
makeCxxSourceFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_FilePath* cxxFilesPath
  );

static Arcadia_FilePath*
makeCxxHeaderFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_FilePath* cxxFilesPath
  );

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfoDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
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

Arcadia_defineObjectType(u8"Arcadia.MILC.Backend.SymbolInfo", Arcadia_MILC_Backend_SymbolInfo,
                         u8"Arcadia.Object", Arcadia_Object,
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
nameToCxxName
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

static Arcadia_FilePath*
makeCxxSourceFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_FilePath* cxxFilesPath
  )
{
  Arcadia_StringBuilder* stringBuilder = Arcadia_StringBuilder_create(thread);
  Arcadia_FilePath* cxxFilePath = Arcadia_FilePath_clone(thread, cxxFilesPath);
  Arcadia_FilePath_append(thread, cxxFilePath, Arcadia_FilePath_parseGeneric(thread, nameToPathString(thread, ((Arcadia_MILC_Symbol*)symbol)->name)));
  Arcadia_String* fileName = Arcadia_List_getObjectReferenceValueAt(thread, cxxFilePath->fileNames, Arcadia_Collection_getSize(thread, (Arcadia_Collection*)cxxFilePath->fileNames) - 1);
  Arcadia_List_removeBack(thread, cxxFilePath->fileNames, 1);
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, fileName);
  if (symbol->kind != Arcadia_MILC_SymbolKind_Enumeration) {
    // Currently a hack as we are merely able to produce proper ".c" files for enumerations.
    // All other types emit "c.g" in order to avoid overwriting the ".c" files with broken contents.
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ".c.g");
  } else {
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ".c");
  }
  Arcadia_List_insertBackObjectReferenceValue(thread, cxxFilePath->fileNames, (Arcadia_Object*)Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuilder)));
  return cxxFilePath;
}

static Arcadia_FilePath*
makeCxxHeaderFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_FilePath* cxxFilesPath
  )
{
  Arcadia_StringBuilder* stringBuilder = Arcadia_StringBuilder_create(thread);
  Arcadia_FilePath* cxxFilePath = Arcadia_FilePath_clone(thread, cxxFilesPath);
  Arcadia_FilePath_append(thread, cxxFilePath, Arcadia_FilePath_parseGeneric(thread, nameToPathString(thread, ((Arcadia_MILC_Symbol*)symbol)->name)));
  Arcadia_String* fileName = Arcadia_List_getObjectReferenceValueAt(thread, cxxFilePath->fileNames, Arcadia_Collection_getSize(thread, (Arcadia_Collection*)cxxFilePath->fileNames) - 1);
  Arcadia_List_removeBack(thread, cxxFilePath->fileNames, 1);
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, fileName);
  if (symbol->kind != Arcadia_MILC_SymbolKind_Enumeration) {
    // Currently a hack as we are merely able to produce proper ".h" files for enumerations.
    // All other types emit "h.g" in order to avoid overwriting the ".h" files with broken contents.
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ".h.g");
  } else {
    Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, ".h");
  }
  Arcadia_List_insertBackObjectReferenceValue(thread, cxxFilePath->fileNames, (Arcadia_Object*)Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuilder)));
  return cxxFilePath;
}

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Backend_SymbolInfo);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
 
  self->symbol = (Arcadia_MILC_Symbol*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_Symbol_getType(thread));
  self->moduleDirectoryPath = NULL;
  self->cxxFilesPath = NULL;
  self->cxxSourceFilePath = NULL;
  self->cxxHeaderFilePath = NULL;
  self->cxxName = nameToCxxName(thread, self->symbol->name);
  self->cxxNameUpperCase = nameToCxxUpperCaseName(thread, self->symbol->name);
  
  Arcadia_MILC_Symbol* enclosingSymbol = ((Arcadia_MILC_Symbol*)self->symbol)->enclosing;
  if (enclosingSymbol) {
    Arcadia_MILC_ModuleSymbol* enclosingModuleSymbol = (Arcadia_MILC_ModuleSymbol*)enclosingSymbol;
    Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = ((Arcadia_MILC_AST_DefinitionNode*)enclosingModuleSymbol->moduleDefinitionNode)->compilationUnitNode;
    Arcadia_MILC_AST_ModuleNode* moduleNode = compilationUnitNode->moduleNode;

    self->moduleDirectoryPath = moduleNode->moduleDirectoryPath;
    Arcadia_FilePath* cxxFilesPath = Arcadia_FilePath_clone(thread, self->moduleDirectoryPath);
    Arcadia_FilePath_append(thread, cxxFilesPath, Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, "Library/Sources")));
    self->cxxFilesPath =  cxxFilesPath;
    self->cxxSourceFilePath = makeCxxSourceFilePath(thread, (Arcadia_MILC_Symbol*)self->symbol, cxxFilesPath);
    self->cxxHeaderFilePath = makeCxxHeaderFilePath(thread, (Arcadia_MILC_Symbol*)self->symbol, cxxFilesPath);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_Backend_SymbolInfo);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfoDispatch* self
  )
{/*Intentionally empty.*/}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{
  if (self->symbol) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->symbol);
  }

  if (self->cxxName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cxxName);
  }
  if (self->cxxNameUpperCase) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cxxNameUpperCase);
  }

  if (self->moduleDirectoryPath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->moduleDirectoryPath);
  }
  if (self->cxxFilesPath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cxxFilesPath);
  }
  if (self->cxxSourceFilePath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cxxSourceFilePath);
  }
  if (self->cxxHeaderFilePath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cxxHeaderFilePath);
  }
}

Arcadia_MILC_Backend_SymbolInfo*
Arcadia_MILC_Backend_SymbolInfo_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Backend_SymbolInfo);
  if (context) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)context); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (symbol) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)symbol); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  _Arcadia_EndCreate(Arcadia_MILC_Backend_SymbolInfo); 
}

void
Arcadia_MILC_Backend_SymbolInfo_dump
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self,
    Arcadia_SizeValue indent,
    Arcadia_StringBuilder* target
  )
{ 
  Arcadia_MILC_Symbol* symbol = self->symbol;
  for (Arcadia_SizeValue i = 0, n = indent; i < n; ++i) {
    Arcadia_StringBuilder_insertBackCodePoint(thread, target, ' ');
  }
  Arcadia_StringBuilder_insertBackString(thread, target, Arcadia_MILC_SymbolKind_toString(thread, symbol->kind));
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8" ");
  Arcadia_StringBuilder_insertBackString(thread, target, ((Arcadia_MILC_Symbol*)symbol)->name);
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8"\n");
  //
  for (Arcadia_SizeValue i = 0, n = indent + 2; i < n; ++i) {
    Arcadia_StringBuilder_insertBackCodePoint(thread, target, ' ');
  }
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8"[ modulePath = ");
  Arcadia_StringBuilder_insertBackString(thread, target, self->moduleDirectoryPath ? Arcadia_FilePath_toGeneric(thread, self->moduleDirectoryPath) : Arcadia_String_createFromCxxString(thread, u8"null"));
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8" ]\n");
  //
  for (Arcadia_SizeValue i = 0, n = indent + 2; i < n; ++i) {
    Arcadia_StringBuilder_insertBackCodePoint(thread, target, ' ');
  }
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8"[ cxxFilesPath = ");
  Arcadia_StringBuilder_insertBackString(thread, target, self->cxxFilesPath ? Arcadia_FilePath_toGeneric(thread, self->cxxFilesPath) : Arcadia_String_createFromCxxString(thread, u8"null"));
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8" ]\n");
  //
  for (Arcadia_SizeValue i = 0, n = indent + 2; i < n; ++i) {
    Arcadia_StringBuilder_insertBackCodePoint(thread, target, ' ');
  }
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8"[ cxxSourceFilePath = ");
  Arcadia_StringBuilder_insertBackString(thread, target, self->cxxSourceFilePath ? Arcadia_FilePath_toGeneric(thread, self->cxxSourceFilePath) : Arcadia_String_createFromCxxString(thread, u8"null"));
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8" ]\n");
  //
  for (Arcadia_SizeValue i = 0, n = indent + 2; i < n; ++i) {
    Arcadia_StringBuilder_insertBackCodePoint(thread, target, ' ');
  }
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8"[ cxxHeaderFilePath = ");
  Arcadia_StringBuilder_insertBackString(thread, target, self->cxxHeaderFilePath ? Arcadia_FilePath_toGeneric(thread, self->cxxHeaderFilePath) : Arcadia_String_createFromCxxString(thread, u8"null"));
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8" ]\n");
  //
  for (Arcadia_SizeValue i = 0, n = indent + 2; i < n; ++i) {
    Arcadia_StringBuilder_insertBackCodePoint(thread, target, ' ');
  }
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8"[ cxxName = ");
  Arcadia_StringBuilder_insertBackString(thread, target, self->cxxName);
  Arcadia_StringBuilder_insertBackCxxString(thread, target, u8" ]\n");
}
