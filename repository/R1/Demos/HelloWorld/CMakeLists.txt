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
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the R1 library directory")

add_executable(${MyProjectName}.R.HelloWorldDemo)
BeginProduct(${MyProjectName}.R.HelloWorldDemo)

# Create configuration file.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Configure.h @ONLY)

list(APPEND ${MyProjectName}.R.HelloWorldDemo.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Configure.h)
list(APPEND ${MyProjectName}.R.HelloWorldDemo.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Main.c)
                                                                            
target_link_libraries(${MyProjectName}.R.HelloWorldDemo Arcadia.R Arcadia.Arms)

set_target_properties(${MyProjectName}.R.HelloWorldDemo PROPERTIES FOLDER "R")

EndProduct(${MyProjectName}.R.HelloWorldDemo executable)
