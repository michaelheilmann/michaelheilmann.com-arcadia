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
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

# Create a library.
if (NOT TARGET ${MyProjectName}.Arms)
    add_library(${MyProjectName}.Arms)
    BeginProduct(${MyProjectName}.Arms)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Arms/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Arms/Configure.h @ONLY)

    list(APPEND ${MyProjectName}.Arms.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms.c)
    list(APPEND ${MyProjectName}.Arms.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms.h)
    list(APPEND ${MyProjectName}.Arms.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/MemoryManager.c)
    list(APPEND ${MyProjectName}.Arms.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/MemoryManager.h)
    list(APPEND ${MyProjectName}.Arms.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/MemoryManager.private.c)
    list(APPEND ${MyProjectName}.Arms.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/MemoryManager.private.h)
    list(APPEND ${MyProjectName}.Arms.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/SizeType.c)
    list(APPEND ${MyProjectName}.Arms.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/SizeType.h)
    list(APPEND ${MyProjectName}.Arms.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/DefaultMemoryManager.c)
    list(APPEND ${MyProjectName}.Arms.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/DefaultMemoryManager.h)
    list(APPEND ${MyProjectName}.Arms.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/SlabMemoryManager.c)
    list(APPEND ${MyProjectName}.Arms.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Arms/SlabMemoryManager.h)
    list(APPEND ${MyProjectName}.Arms.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Arms/Configure.h)

    set_target_properties(${MyProjectName}.Arms PROPERTIES FOLDER "Arms")

    EndProduct(${MyProjectName}.Arms library)
endif()
