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

# Last modified: 2024-12-29

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
FetchProduct(${MyProjectName}.Mil "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the MIL library directory")

set(MyTestName ${MyProjectName}.R.Tests.Execute)

# Create test executable.
BeginProduct(${MyTestName} test)

list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Main.c)

list(APPEND ${MyTestName}.Libraries ${MyProjectName}.Mil ${MyProjectName}.Arms)

EndProduct(${MyTestName})
set_target_properties(${MyTestName} PROPERTIES FOLDER "R")
