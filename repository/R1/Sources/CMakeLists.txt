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

cmake_minimum_required(VERSION 3.29)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" "path to the ARMS1 source directory")

# Create library.
if (NOT TARGET ${MyProjectName}.R)
  add_library(${MyProjectName}.R)
  BeginProduct(${MyProjectName}.R)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/R/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/R/Configure.h @ONLY)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ArmsIntegration.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ArmsIntegration.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Atoms.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Atoms.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Boolean.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ByteBuffer.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ByteBuffer.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/clamp.h)
  
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/CommandLine/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/CommandLine/Include.h)

  list(APPEND ${MyProjectName}.R.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/R/Configure.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/countLeadingZeroes.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/countLeadingZeroes.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/FileHandle.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/FileHandle.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/FilePath.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/FilePath.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/FileSystem.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/FileSystem.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ForeignFunctionReference.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/getTickCount.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/getTickCount.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/hash.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/hash.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Integer16.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Integer32.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Integer64.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Integer8.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/isPowerOfTwo.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/isPowerOfTwo.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/JumpTarget.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/JumpTarget.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/List.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/List.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/maximum.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/minimum.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Natural16.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Natural32.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Natural64.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Natural8.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/nextPowerOfTwoGt.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/nextPowerOfTwoGt.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/nextPowerOfTwoGte.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/nextPowerOfTwoGte.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Object.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Object.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Object.internal.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ObjectReference.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Real32.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Real64.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Stack.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Stack.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Status.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Status.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Size.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/String.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/String.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/StringBuffer.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/StringBuffer.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/swap.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ToNumber/Include.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/ToNumber/Include.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/TypeNames.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/TypeNames.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Types.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Types.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Types.internal.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8Reader.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8Reader.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8ByteBufferReader.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8ByteBufferReader.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8StringReader.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8StringReader.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8Writer.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8Writer.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8ByteBufferWriter.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8ByteBufferWriter.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8/EncodeCodePoints.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Utf8/EncodeCodePoints.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Value.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Value.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/R/Void.h)

  target_link_libraries(${MyProjectName}.R Arcadia.Arms)

  set_target_properties(${MyProjectName}.R PROPERTIES FOLDER "R")

  EndProduct(${MyProjectName}.R library)

endif()
