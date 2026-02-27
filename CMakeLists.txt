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

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/repository)
  include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/all.cmake)
endif()

set(CPACK_PACKAGE_NAME "Arcadia")

set(CPACK_PACKAGE_VENDOR "Michael Heilmann")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Arcadia executable files")
set(CPACK_PACKAGE_CONTACT "contact@michaelheilmann.com")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://michaelheilmann.com/")

set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(CPACK_INSTRUCTIONSETARCHITECTURE "x64")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(CPACK_INSTRUCTIONSETARCHITECTURE "x86")
endif()

set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CPACK_INSTRUCTIONSETARCHITECTURE})

add_subdirectory(Runtime/ARMS)
add_subdirectory(Runtime/Ring1)
add_subdirectory(Runtime/Ring2)
add_subdirectory(Languages)
add_subdirectory(DDL)
add_subdirectory(DDLS)
add_subdirectory(ADL)
add_subdirectory(VPL)
add_subdirectory(Media)
add_subdirectory(Imaging)

add_subdirectory(Engine/Engine)
add_subdirectory(Engine/UI)
add_subdirectory(Engine/Application)
add_subdirectory(Engine/Audials.Implementation)

add_subdirectory(Documentation)
add_subdirectory(Tools/TemplateEngine)
add_subdirectory(Tools/MaterialGenerator)

add_subdirectory(repository)

include(CPack)
