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

#include "Arcadia/MIL/Compiler/Context.h"

#include "Arcadia/MIL/Compiler/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  );

static void
Arcadia_MIL_Compiler_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_ContextDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MIL_Compiler_Context_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Compiler.Context", Arcadia_MIL_Compiler_Context,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MIL_Compiler_Context);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->workingDirectoryPath = NULL;
  self->moduleNodes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->log = (Arcadia_Log*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Log_getType(thread));
  self->parser = Arcadia_MIL_Parser_create(thread);
  Arcadia_LeaveConstructor(Arcadia_MIL_Compiler_Context);
}

static void
Arcadia_MIL_Compiler_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_ContextDispatch* self
  )
{/*Intentionally empty.*/}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  )
{
  if (self->log) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->log);
  }
  if (self->workingDirectoryPath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->workingDirectoryPath);
  }
  if (self->moduleNodes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->moduleNodes);
  }
  if (self->parser) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parser);
  }
}

Arcadia_MIL_Compiler_Context*
Arcadia_MIL_Compiler_Context_create
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (log) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)log); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Compiler_Context);
}

#if defined(Verbose)
  #error("`Verbose` already defined")
#endif
#define Verbose (1)

// (1.1) For each module path, create a module node storing that path.
// (1.2) If a module path is relative, make it absolute wrt the specified working directory path.
static void
step1
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  )
{
#if defined(Verbose)
  Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"file paths:\n"));
#endif
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->moduleNodes); i < n; ++i) {
    Arcadia_MIL_AST_ModuleNode* moduleNode = (Arcadia_MIL_AST_ModuleNode*)Arcadia_List_getObjectReferenceValueAt(thread, self->moduleNodes, i);
    Arcadia_FilePath* moduleDirectoryPath = moduleNode->moduleDirectoryPath;
    if (Arcadia_FilePath_isRelative(thread, moduleDirectoryPath)) {
      Arcadia_FilePath* newModuleDirectoryPath = Arcadia_FilePath_clone(thread, self->workingDirectoryPath);
      Arcadia_FilePath_append(thread, newModuleDirectoryPath, moduleDirectoryPath);
      moduleNode->moduleDirectoryPath = newModuleDirectoryPath;
    }
  #if defined(Verbose)
    Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"- "));
    Arcadia_Log_info(thread, self->log, Arcadia_FilePath_toGeneric(thread, moduleNode->moduleDirectoryPath));
    Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"\n"));
  #endif
  }
}

// (2.1) For each module node, parse its `Module.mil` file in a compilation unit node.
//       Add that compilation unit node to the list of compilation unit nodes of that module node.
static void
step2
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->moduleNodes); i < n; ++i) {
    Arcadia_MIL_AST_ModuleNode* moduleNode= (Arcadia_MIL_AST_ModuleNode*)Arcadia_List_getObjectReferenceValueAt(thread, self->moduleNodes, i);
    Arcadia_FilePath* moduleDirectoryPath = moduleNode->moduleDirectoryPath;
    Arcadia_FilePath* moduleFilePath = Arcadia_FilePath_clone(thread, moduleDirectoryPath);
    Arcadia_FilePath_append(thread, moduleFilePath, Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"Module.mil")));
    Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
    if (!Arcadia_FileSystem_regularFileExists(thread, fileSystem, moduleFilePath)) {
      Arcadia_Log_error(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"moduile file `"));
      Arcadia_Log_error(thread, self->log, Arcadia_FilePath_toGeneric(thread, moduleFilePath));
      Arcadia_Log_error(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"` not found"));
    } else {
      Arcadia_String* input = Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(Arcadia_FileSystem_getFileContents(thread, fileSystem, moduleFilePath)));
      Arcadia_MIL_Parser_setInput(thread, self->parser, input);
      Arcadia_MIL_AST_CompilationUnitNode* compilationUnitNode = Arcadia_MIL_Parser_run(thread, self->parser);
      compilationUnitNode->filePath = moduleFilePath;
      Arcadia_MIL_AST_ModuleNode_appendCompilationUnit(thread, moduleNode, compilationUnitNode);
    }
  }
}

/// Recursively search `Library/Sources` for `*.mil` files.
/// @param moduleNode The module node.
/// @param list The list to add the files to.
static inline void
enumerateFiles
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self,
    Arcadia_MIL_AST_ModuleNode* moduleNode,
    Arcadia_List* files
  )
{
  // Stack to add discovered directories to.
  Arcadia_Stack* stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);

  // Compute the absolute path to `Library/Sources`.
  Arcadia_FilePath* sourceDirectoryPath = Arcadia_FilePath_clone(thread, moduleNode->moduleDirectoryPath);
  Arcadia_FilePath_append(thread, sourceDirectoryPath, Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"Library/Sources")));
  // Compute the `..` and `.` paths.
  Arcadia_FilePath* dot = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8".")),
                  * dotdot = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8".."));

  Arcadia_Stack_pushObjectReferenceValue(thread, stack, sourceDirectoryPath);

  while (!Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)stack)) {
    Arcadia_FilePath* directoryFilePath = (Arcadia_FilePath*)Arcadia_Stack_getObjectReferenceValue(thread, stack, 0);
    Arcadia_Stack_pop(thread, stack);

    Arcadia_DirectoryIterator* directoryIterator = Arcadia_FileSystem_createDirectoryIterator(thread, fileSystem, directoryFilePath);
    while (Arcadia_DirectoryIterator_hasValue(thread, directoryIterator)) {
      Arcadia_FilePath* elementPath = Arcadia_DirectoryIterator_getValue(thread, directoryIterator);
      if (Arcadia_FilePath_isEqualTo(thread, elementPath, dot) || Arcadia_FilePath_isEqualTo(thread, elementPath, dotdot)) {
        // Skip those.
      } else {
        Arcadia_FilePath* nextElementPath = Arcadia_FilePath_clone(thread, directoryFilePath);
        Arcadia_FilePath_append(thread, nextElementPath, elementPath);
        elementPath = nextElementPath;
        if (Arcadia_FileSystem_directoryFileExists(thread, fileSystem, elementPath)) {
          Arcadia_Stack_pushObjectReferenceValue(thread, stack, (Arcadia_Object*)elementPath);
        } else if (Arcadia_FileSystem_regularFileExists(thread, fileSystem, elementPath)) {
        #if defined(Verbose) && 0
          Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"discovered regular file `"));
          Arcadia_Log_info(thread, self->log, Arcadia_FilePath_toGeneric(thread, elementPath));
          Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"`\n"));
        #endif
          Arcadia_List_insertBackObjectReferenceValue(thread, files, (Arcadia_Object*)elementPath);
        }
      }
      Arcadia_DirectoryIterator_nextValue(thread, directoryIterator);
    }
  }
}

// (3) For each module node:
// (3.1) search its `Library/Sources` directory and its child directories `*.mil` files.
// (3.2) For each discovered `*.mil` file, parse that file into a compilation unit node.
// (3.3) Add that compilation unit node to the list of compilation unit nodes of that module node.
static void
step3
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self
  )
{
  Arcadia_Value milExtension = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8".mil"));
  Arcadia_List* files = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->moduleNodes); i < n; ++i) {
    Arcadia_Collection_clear(thread, (Arcadia_Collection*)files);
    Arcadia_MIL_AST_ModuleNode* moduleNode = (Arcadia_MIL_AST_ModuleNode*)Arcadia_List_getObjectReferenceValueAt(thread, self->moduleNodes, i);
    enumerateFiles(thread, self, moduleNode, files);
  #if defined(Verbose)
    Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"module `"));
    Arcadia_Log_info(thread, self->log, Arcadia_FilePath_toGeneric(thread, moduleNode->moduleDirectoryPath));
    Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"` files:\n"));
  #endif
    for (Arcadia_SizeValue j = 0, m = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)files); j < m; ++j) {
      Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueAt(thread, files, j);
      Arcadia_String* extension = Arcadia_FilePath_getExtension(thread, filePath);
      if (extension && Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)extension, &milExtension)) {
      #if defined(Verbose)
        Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8" - `"));
        Arcadia_Log_info(thread, self->log, Arcadia_FilePath_toGeneric(thread, filePath));
        Arcadia_Log_info(thread, self->log, Arcadia_String_createFromCxxString(thread, u8"`\n"));
      #endif
      }
    } 
  }
}

void
Arcadia_MIL_Compiler_Context_run
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Compiler_Context* self,
    Arcadia_FilePath* workingDirectoryPath,
    Arcadia_List* moduleDirectoryPaths
  )
{
  self->workingDirectoryPath = workingDirectoryPath;
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)self->moduleNodes);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)moduleDirectoryPaths); i < n; ++i) {
    // Get the module directory path from the list.
    Arcadia_FilePath* moduleDirectoryPath = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueAt(thread, moduleDirectoryPaths, i);
    // Create a module from it.
    Arcadia_MIL_AST_ModuleNode* moduleNode = Arcadia_MIL_AST_ModuleNode_create(thread);
    // Add the module to the list of modules.
    moduleNode->moduleDirectoryPath = Arcadia_FilePath_clone(thread, moduleDirectoryPath);
    Arcadia_List_insertBackObjectReferenceValue(thread, self->moduleNodes, moduleNode);
  }
  // (1)
  step1(thread, self);
  // (2)
  step2(thread, self);
  // (3)
  step3(thread, self);
}

#undef Verbose
