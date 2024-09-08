# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-09-09

cmake_minimum_required(VERSION 3.29)

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

if (NOT TARGET ${MyProjectName}.Arms)
  set(Arms1-Source-Dir "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" CACHE STRING "path to the ARMS1 source directory")
  get_filename_component(Arms1-Source-Dir "${Arms1-Source-Dir}"
                         REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  message(STATUS "fetching ${Arms1-Source-Dir}")
  FetchContent_Declare(arms1 SOURCE_DIR ${Arms1-Source-Dir})
  FetchContent_MakeAvailable(arms1)
endif()

if (NOT TARGET ${MyProjectName}.R)
  set(R1-Source-Dir "${REPOSITORY_SOURCE_DIR}/R1/Sources" CACHE STRING "path to the R1 source directory")
  get_filename_component(R1-Source-Dir "${R1-Source-Dir}"
                         REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  FetchContent_Declare(r1 SOURCE_DIR ${R1-Source-Dir})
  FetchContent_MakeAvailable(r1)
endif()  

set(MyTestName ${MyProjectName}.R.Tests.List)

# Create test executable.
add_executable(${MyTestName})
BeginProduct(${MyTestName})

add_test(NAME ${MyTestName} COMMAND ${MyTestName} WORKING_DIRECTORY $<TARGET_FILE_DIR:${MyTestName}>)

list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Main.c)

target_link_libraries(${MyTestName} ${MyProjectName}.R ${MyProjectName}.Arms)
EndProduct(${MyTestName} executable)
