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

cmake_minimum_required(VERSION 3.29)

set(MyLibraryName ${MyProjectName}.Application)

if (NOT TARGET ${MyLibraryName})

  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Application/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Application/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Application/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Application/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/Application/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Application/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Application/Application.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Application/Application.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Engine ${MyProjectName}.PixelBufferIO ${MyProjectName}.Math ${MyProjectName}.Ring2)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Engine")

endif()
