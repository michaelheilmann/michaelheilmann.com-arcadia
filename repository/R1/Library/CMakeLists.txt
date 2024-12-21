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
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")

# Create library.
if (NOT TARGET ${MyProjectName}.R)
  add_library(${MyProjectName}.R)
  BeginProduct(${MyProjectName}.R)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h @ONLY)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ArmsIntegration.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ArmsIntegration.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ArmsIntegration.private.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ArgumentsValidation.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ArgumentsValidation.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/cstdlib.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/cstdlib.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Atoms.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Atoms.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Boolean.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Boolean.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ByteBuffer.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ByteBuffer.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/clamp.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/clamp.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/CommandLine/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/CommandLine/Include.h)

  list(APPEND ${MyProjectName}.R.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/countLeadingZeroes.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/countLeadingZeroes.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/execute.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/execute.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Constructor.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Constructor.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Procedure.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Procedure.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Method.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Method.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Class.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Class.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Variable.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Variable.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Instruction.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Instruction.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Include.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ThreadState.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ThreadState.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ThreadState.private.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ProcessState.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ProcessState.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ProcessState.private.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code/Constants.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code/Constants.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/FileHandle.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/FileHandle.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/FilePath.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/FilePath.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/FileSystem.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/FileSystem.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ForeignProcedure.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ForeignProcedure.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/getTickCount.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/getTickCount.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/hash.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/hash.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ImmutableByteArray.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ImmutableByteArray.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer16.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer16.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer32.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer32.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer64.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer64.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer8.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Integer8.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/isPowerOfTwo.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/isPowerOfTwo.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/JumpTarget.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/JumpTarget.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/List.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/List.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Map.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Map.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/maximum.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/minimum.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural16.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural16.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural32.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural32.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural64.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural64.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural8.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Natural8.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/nextPowerOfTwoGt.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/nextPowerOfTwoGt.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/nextPowerOfTwoGte.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/nextPowerOfTwoGte.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Object.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Object.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Object.internal.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/ObjectReference.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/R.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/R.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Real32.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Real32.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Real64.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Real64.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Stack.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Stack.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Status.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Status.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Size.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Size.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/String.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/String.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/StringBuffer.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/StringBuffer.h)

  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/swap.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/BigInteger/Include.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/BigInteger/Include.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/BigInteger/add.c.i)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/BigInteger/add.h.i)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/BigInteger/from.c.i)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/BigInteger/from.h.i)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/BooleanToString.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/BooleanToString.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/IntegerToString.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/IntegerToString.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/NaturalToString.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/NaturalToString.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/Include.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/Include.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToBoolean.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToBoolean.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToInteger.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToInteger.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToNatural.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToNatural.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToReal.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToReal.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToVoid.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/StringToVoid.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/VoidToString.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/VoidToString.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Convert/parse.i)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/TypeNames.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/TypeNames.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Types.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Types.h)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Types.internal.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/DynamicArrayUtilities.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/DynamicArrayUtilities.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8Reader.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8Reader.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8ByteBufferReader.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8ByteBufferReader.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8StringReader.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8StringReader.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8Writer.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8Writer.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8ByteBufferWriter.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8ByteBufferWriter.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8/EncodeCodePoints.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Utf8/EncodeCodePoints.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Value.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Value.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Void.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Void.h)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Mil/Configure.h @ONLY)
  list(APPEND ${MyProjectName}.R.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Mil/Configure.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Scanner.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Scanner.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Parser.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Parser.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Ast.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Ast.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Keywords.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Keywords.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/TokenType.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/TokenType.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/StringTable.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/StringTable.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Symbols.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Symbols.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Include.h)

  target_link_libraries(${MyProjectName}.R Arcadia.Arms)

  if (${${MyProjectName}.R.OperatingSystem} STREQUAL ${${MyProjectName}.R.OperatingSystem.Linux})
    target_link_libraries(${MyProjectName}.R m)
  endif()

  set_target_properties(${MyProjectName}.R PROPERTIES FOLDER "R")

  EndProduct(${MyProjectName}.R library)

endif()
