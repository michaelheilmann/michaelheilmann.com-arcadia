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

cmake_minimum_required(VERSION 4.1.3)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/repository)
  include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/all.cmake)
endif()

add_subdirectory(Runtime/ARMS)
add_subdirectory(Runtime/Ring1)
add_subdirectory(Runtime/Ring2)
add_subdirectory(Languages)
add_subdirectory(DDL)
add_subdirectory(DDLS)
add_subdirectory(Engine/Engine)
add_subdirectory(Engine/Imaging)
add_subdirectory(Engine/Audials)
add_subdirectory(Engine/Visuals)
add_subdirectory(Documentation)
add_subdirectory(Tools/TemplateEngine)
add_subdirectory(repository)
