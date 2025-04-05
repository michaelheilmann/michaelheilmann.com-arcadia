# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-09-22

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
FetchProduct(${MyProjectName}.Machine "${REPOSITORY_SOURCE_DIR}/Arcadia.Machine/Library" "path to the Arcadia Machine library directory")

set(MyTestFolder ${MyProjectName}.Machine)
set(MyTestName ${MyProjectName}.Machine.Tests.SemanticalAnalysis)

if (NOT TARGET ${MyTestName})
  BeginProduct(${MyTestName} test)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/Configure.h @ONLY)

  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/Main.c)
  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/EnterPass.c)
  list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/EnterPass.h)
  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/StatementsContext.c)
  list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/StatementsContext.h)
  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/Pass.c)
  list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/Pass.h)
  list(APPEND ${MyTestName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Mil/Tests/SemanticalAnalysis/Configure.h)

  list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.Machine ${MyProjectName}.Arms)

  EndProduct(${MyTestName})
  target_include_directories(${MyTestName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  set_target_properties(${MyTestName} PROPERTIES FOLDER ${MyTestFolder})

  CopyProductAssets(${MyTestName}.CopyAssets ${MyTestFolder} ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets)
  add_dependencies(${MyTestName} ${MyTestName}.CopyAssets)
endif()
