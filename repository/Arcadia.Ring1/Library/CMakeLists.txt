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

# Last modified: 2025-01-01

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

set(MyLibrary ${MyProjectName}.Ring1)

# Create library.
if (NOT TARGET ${MyLibrary})
  add_library(${MyLibrary})
  BeginProduct(${MyLibrary})

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h @ONLY)
  list(APPEND ${MyLibrary}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Utf8ToIeee754/Include.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Utf8ToIeee754/Include.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/apreal10.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/apreal10.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/apint10.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/apint10.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/ieee754.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/ieee754.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/tables.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Support/tables.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeAdd.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeAdd.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeMultiply.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeMultiply.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.private.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.private.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/makeBitmask.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/makeBitmask.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Boolean.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Boolean.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/clamp.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/clamp.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/countLeadingZeroes.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/countLeadingZeroes.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/_declareScalarType.h)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/_defineScalarType.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Diagnostics.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Diagnostics.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ForeignProcedure.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ForeignProcedure.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getTickCount.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getTickCount.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/hash.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/hash.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableByteArray.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableByteArray.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBoolean.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBoolean.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromInteger.c)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromInteger.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromNatural.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromNatural.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromVoid.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromVoid.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/type.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h)
  
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer16.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer16.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer32.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer32.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer64.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer64.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer8.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer8.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/isPowerOfTwo.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/isPowerOfTwo.h)

  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/maximum.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/maximum.h)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/minimum.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/minimum.h)
 
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural16.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural16.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural32.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural32.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural64.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural64.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural8.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural8.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/nextPowerOfTwoGreaterThan.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/nextPowerOfTwoGreaterThan.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/nextPowerOfTwoGreaterThanOrEqualTo.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/nextPowerOfTwoGreaterThanOrEqualTo.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/NoReturn.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/NoReturn.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Object.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Object.h)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Object.internal.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ObjectReference.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ObjectReference.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Process.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Process.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Process1.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Process1.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real32.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real32.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real64.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real64.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Size.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Size.h)
  
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Stack.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Stack.h)
  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Stack.private.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Stack.private.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StaticAssert.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StaticAssert.h)
  
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/swap.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/swap.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Tests.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Tests.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/TypeNameParser.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/TypeNameParser.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.h)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.private.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.private.h)

  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Utf8.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Utf8.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Void.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Void.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Include.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Include.h)

  list(APPEND ${MyLibrary}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Value.c)
  list(APPEND ${MyLibrary}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Value.h)

  target_link_libraries(${MyLibrary} Arcadia.Arms)

  if (${${MyLibrary}.OperatingSystem} STREQUAL ${${MyLibrary}.OperatingSystem.Linux})
    target_link_libraries(${MyLibrary} m)
  endif()

  set_target_properties(${MyLibrary} PROPERTIES FOLDER "Arcadia")

  EndProduct(${MyLibrary} library)

endif()
