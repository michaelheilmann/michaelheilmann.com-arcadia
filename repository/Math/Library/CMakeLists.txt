# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

cmake_minimum_required(VERSION 4.1.3)

set(MyLibraryName ${MyProjectName}.Math)

# Create library.
if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.c.te)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.h.te)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.c.te)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.h.te)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.te)
  list (APPEND ${MyLibraryName}.TemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.te)

  BeginTemplateEngine(${MyLibraryName}.GenerateFiles "Math")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.env")

    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.c.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.c"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.env")
    OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color.h.te"
                     "${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.h"
                     "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.env")

  EndTemplateEngine()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Configure.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real32.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Color4Real64.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real32.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector3Real64.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real32.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Vector4Real64.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real32.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Math/Implementation/Matrix4Real64.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setOrthographicProjection.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setOrthographicProjection.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setPerspectiveProjection.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setPerspectiveProjection.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setRotationX.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setRotationX.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setRotationY.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setRotationY.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setRotationZ.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setRotationZ.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setScaling.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setScaling.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setTranslation.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/setTranslation.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/trigonometry.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Implementation/trigonometry.h)

  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Math/Include.h)

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
  # @todo This is hackish, fixme.
  add_dependencies(${MyLibraryName} ${MyLibraryName}.GenerateFiles)
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Math")

endif()
