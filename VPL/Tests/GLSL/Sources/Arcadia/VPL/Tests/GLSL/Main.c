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

#include "Arcadia/VPL/Include.h"

static void
test1
  (
    Arcadia_Thread* thread
  )
{ 
  Arcadia_VPL_Program* program = Arcadia_VPL_Program_create(thread, Arcadia_VPL_ProgramFlags_MeshAmbientColor);
  Arcadia_VPL_Backends_GLSL_Transpiler* transpiler = Arcadia_VPL_Backends_GLSL_Transpiler_create(thread);
  Arcadia_Map* constantBlockMapping = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

  Arcadia_ByteBuffer* vertexShaderCode = Arcadia_ByteBuffer_create(thread);
  Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader(thread, transpiler, program, constantBlockMapping, vertexShaderCode);

  Arcadia_ByteBuffer* fragmentShaderCode = Arcadia_ByteBuffer_create(thread);
  Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader(thread, transpiler, program, constantBlockMapping, fragmentShaderCode);

  Arcadia_FilePath* vertexShaderPath = Arcadia_FileSystem_getWorkingDirectory(thread, Arcadia_FileSystem_getOrCreate(thread));
  Arcadia_FilePath_append(thread, vertexShaderPath, Arcadia_FilePath_parseGeneric(thread, u8"vertex-shader-mesh-ambient-color.txt", sizeof(u8"vertex-shader-mesh-ambient-color.txt") - 1));
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), vertexShaderPath, vertexShaderCode);

  Arcadia_FilePath* fragmentShaderPath = Arcadia_FileSystem_getWorkingDirectory(thread, Arcadia_FileSystem_getOrCreate(thread));
  Arcadia_FilePath_append(thread, fragmentShaderPath, Arcadia_FilePath_parseGeneric(thread, u8"fragment-shader-mesh-ambient-color.txt", sizeof(u8"fragment-shader-mesh-ambient-color.txt") - 1));
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), fragmentShaderPath, fragmentShaderCode);
}

static void
test2
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_VPL_Program* program = Arcadia_VPL_Program_create(thread, Arcadia_VPL_ProgramFlags_VertexAmbientColor);
  Arcadia_VPL_Backends_GLSL_Transpiler* transpiler = Arcadia_VPL_Backends_GLSL_Transpiler_create(thread);
  Arcadia_Map* constantBlockMapping = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

  Arcadia_ByteBuffer* vertexShaderCode = Arcadia_ByteBuffer_create(thread);
  Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader(thread, transpiler, program, constantBlockMapping, vertexShaderCode);

  Arcadia_ByteBuffer* fragmentShaderCode = Arcadia_ByteBuffer_create(thread);
  Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader(thread, transpiler, program, constantBlockMapping, fragmentShaderCode);

  Arcadia_FilePath* vertexShaderPath = Arcadia_FileSystem_getWorkingDirectory(thread, Arcadia_FileSystem_getOrCreate(thread));
  Arcadia_FilePath_append(thread, vertexShaderPath, Arcadia_FilePath_parseGeneric(thread, u8"vertex-shader-vertex-ambient-color.txt", sizeof(u8"vertex-shader-vertex-ambient-color.txt") - 1));
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), vertexShaderPath, vertexShaderCode);

  Arcadia_FilePath* fragmentShaderPath = Arcadia_FileSystem_getWorkingDirectory(thread, Arcadia_FileSystem_getOrCreate(thread));
  Arcadia_FilePath_append(thread, fragmentShaderPath, Arcadia_FilePath_parseGeneric(thread, u8"fragment-shader-vertex-ambient-color.txt", sizeof(u8"fragment-shader-vertex-ambient-color.txt") - 1));
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), fragmentShaderPath, fragmentShaderCode);
}

static void
test3
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_VPL_Program* program = Arcadia_VPL_Program_create(thread, Arcadia_VPL_ProgramFlags_TextureAmbientColor);
  Arcadia_VPL_Backends_GLSL_Transpiler* transpiler = Arcadia_VPL_Backends_GLSL_Transpiler_create(thread);
  Arcadia_Map* constantBlockMapping = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

  Arcadia_ByteBuffer* vertexShaderCode = Arcadia_ByteBuffer_create(thread);
  Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader(thread, transpiler, program, constantBlockMapping, vertexShaderCode);

  Arcadia_ByteBuffer* fragmentShaderCode = Arcadia_ByteBuffer_create(thread);
  Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader(thread, transpiler, program, constantBlockMapping, fragmentShaderCode);

  Arcadia_FilePath* vertexShaderPath = Arcadia_FileSystem_getWorkingDirectory(thread, Arcadia_FileSystem_getOrCreate(thread));
  Arcadia_FilePath_append(thread, vertexShaderPath, Arcadia_FilePath_parseGeneric(thread, u8"vertex-shader-texture-ambient-color.txt", sizeof(u8"vertex-shader-texture-ambient-color.txt") - 1));
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), vertexShaderPath, vertexShaderCode);

  Arcadia_FilePath* fragmentShaderPath = Arcadia_FileSystem_getWorkingDirectory(thread, Arcadia_FileSystem_getOrCreate(thread));
  Arcadia_FilePath_append(thread, fragmentShaderPath, Arcadia_FilePath_parseGeneric(thread, u8"fragment-shader-texture-ambient-color.txt", sizeof(u8"fragment-shader-texture-ambient-color.txt") - 1));
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_getOrCreate(thread), fragmentShaderPath, fragmentShaderCode);
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
  if (!Arcadia_Tests_safeExecute(&test2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test3)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
