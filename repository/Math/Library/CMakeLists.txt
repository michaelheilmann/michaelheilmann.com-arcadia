# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
#
# Permission to use, copy, modify, and distribute this software for any
# purpose without fee is hereby granted, provided that this entire notice
# is included in all copies of any software which is or includes a copy
# or modification of this software and in all copies of the supporting
# documentation for such software.
#
# THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
# REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
# OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.20)

set(MyLibraryName ${MyProjectName}.Math)

# Create library.
if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.c.tl)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.h.tl)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.c.tl)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.h.tl)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.tl)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.tl)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.h" PROPERTIES GENERATED 1)

  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.c.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.c"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.env")
  InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.h.tl"
                       "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.h"
                       "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.env")
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.c" PROPERTIES GENERATED 1)
  set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.h" PROPERTIES GENERATED 1)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Configure.h.i)
  list(APPEND ${MyLibraryName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Configure.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.h)

  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)

  list(APPEND ${MyLibraryName}.Libraries Arcadia.Ring2)

  if (${${MyLibraryName}.Compiler.Masm} STREQUAL ${${MyLibraryName}.Compiler.Masm.Ms})
	  if (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X64})
      elseif (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X86})
	  endif()
	  if (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X64})
      elseif (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X86})
	  endif()
  endif()

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Math")

endif()
