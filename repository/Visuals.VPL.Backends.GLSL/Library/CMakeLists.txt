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

# Create library.
set(MyLibraryName ${MyProjectName}.Visuals.VPL.Backends.GLSL)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Configure.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/ConstantBlock.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/ConstantBlock.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Field.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Field.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Include.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Include.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Program.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/Program.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/VariableScalar.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Backends/GLSL/VariableScalar.h)
  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Ring2 ${MyProjectName}.Ring1 ${MyProjectName}.ARMS)

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Engine")

endif()
