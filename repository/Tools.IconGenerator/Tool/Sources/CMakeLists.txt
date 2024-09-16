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

# Last modified: 2024-09-16

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

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" "path to the ARMS1 source directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Sources" "path to the R1 source directory")

add_executable(Tools.IconGenerator)
BeginProduct(Tools.IconGenerator)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Tools/IconGenerator/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Tools/IconGenerator/Configure.h @ONLY)

list(APPEND Tools.IconGenerator.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/IconGenerator/Main.c)
list(APPEND Tools.IconGenerator.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/Tools/IconGenerator/Configure.h)

target_link_libraries(Tools.IconGenerator Tools.Visuals2d Arcadia.R Arcadia.Arms)

EndProduct(Tools.IconGenerator executable)
