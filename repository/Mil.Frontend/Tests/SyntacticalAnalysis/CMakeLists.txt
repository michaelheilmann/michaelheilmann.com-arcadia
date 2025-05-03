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

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms/Library" "path to the ARMS library directory")
FetchProduct(${MyProjectName}.Mil.Frontend "${REPOSITORY_SOURCE_DIR}/Mil.Frontend/Library" "path to the MIL frontend library directory")

set(MyTestFolder ${MyProjectName}.Mil.Frontend)
set(MyTestName ${MyProjectName}.Mil.Frontend.Tests.SyntacticalAnalysis)

if (NOT TARGET ${MyTestName})
  BeginProduct(${MyTestName} test)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SyntacticalAnalysis/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SyntacticalAnalysis/Configure.h @ONLY)
  list(APPEND ${MyTestName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SyntacticalAnalysis/Configure.h.i)
  list(APPEND ${MyTestName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SyntacticalAnalysis/Configure.h)

  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SyntacticalAnalysis/Main.c)

  list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.Mil.Frontend ${MyProjectName}.Arms)

  EndProduct(${MyTestName})
  target_include_directories(${MyTestName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources ${CMAKE_CURRENT_BINARY_DIR}/Sources)
  set_target_properties(${MyTestName} PROPERTIES FOLDER ${MyTestFolder})

  CopyProductAssets(${MyTestName}.CopyAssets ${MyTestFolder} ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets)
  add_dependencies(${MyTestName} ${MyTestName}.CopyAssets)
endif()
