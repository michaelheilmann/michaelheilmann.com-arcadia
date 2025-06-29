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

cmake_minimum_required(VERSION 3.20)

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms/Library" "path to the ARMS library directory")

set(MyLibraryName ${MyProjectName}.Ring1)

# Create library.
if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h.i)
  list(APPEND ${MyLibraryName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/add.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/add.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/and.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/and.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/BigInteger.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/BigInteger.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/divide.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/divide.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/compareByMagnitudeTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/compareByMagnitudeTo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/compareTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/compareTo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/equalTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/equalTo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/fromDecimalString.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/fromDecimalString.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/fromTwosComplement.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/fromTwosComplement.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/getBitLength.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/getBitLength.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/greaterThan.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/greaterThan.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/greaterThanOrEqualTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/greaterThanOrEqualTo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/getHigh64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/getHigh64.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/lowerThan.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/lowerThan.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/lowerThanOrEqualTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/lowerThanOrEqualTo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/multiply.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/multiply.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/notEqualTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/notEqualTo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/or.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/or.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setNatural.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setNatural.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setInteger.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setInteger.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/shiftLeft.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/shiftLeft.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/shiftRight.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/shiftRight.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/subtract.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/subtract.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toDecimalString.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toDecimalString.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toNatural.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toNatural.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toInteger.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toInteger.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toTwosComplement.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/BigInteger/toTwosComplement.h)

  # >> String to number

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToInteger/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToInteger/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToNatural/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToNatural/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/toReal64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/toReal64.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/toReal32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/toReal32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Lemire.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Lemire.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Gay.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Gay.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Clinger.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Clinger.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Result.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StringToReal/Result.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Include.h)

  ## << String to number

  ## >> Number to string

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Include.h)
  #list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Common.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Common.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Real32ToString.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Real32ToString.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Real64ToString.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/Real64ToString.h)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/BigTablesReal64.i)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/SmallTablesReal64.i)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/RealToString/TablesReal32.i)

  ## << Number to string

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Arrays.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeAdd.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeAdd.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeMultiply.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/safeMultiply.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.private.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Atoms.private.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/makeBitmask.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/makeBitmask.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Boolean.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Boolean.h)

  # Numerics >>

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/ceil.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/ceil.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/clamp.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/clamp.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/cos.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/cos.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/countLeadingZeroes.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/countLeadingZeroes.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/countSignificandBits.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/countSignificandBits.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/countTrailingZeroes.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/countTrailingZeroes.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/floor.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/floor.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/hash.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/hash.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/Include.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/isPowerOfTwo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/isPowerOfTwo.h)

  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/maximum.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/maximum.h)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/minimum.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/minimum.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThan.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThan.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThanOrEqualTo.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThanOrEqualTo.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/quotientRemainder.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/quotientRemainder.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/sin.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/sin.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/isDivisibleByPowerOfFive.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Numerics/isDivisibleByPowerOfFive.h)

  # << Numerics

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/_declareScalarType.h)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/_defineScalarType.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Diagnostics.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Diagnostics.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Enumeration.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Enumeration.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ForeignProcedure.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ForeignProcedure.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getNumberOfCores.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getNumberOfCores.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getPageSize.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getPageSize.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getTickCount.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/getTickCount.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableByteArray.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableByteArray.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBoolean.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBoolean.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromInteger.c)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromInteger.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromNatural.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromNatural.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromSize.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromSize.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromVoid.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/fromVoid.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/type.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toReal.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toReal.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer16.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer16.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer64.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer8.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Integer8.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural16.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural16.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural64.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural8.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Natural8.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/NoReturn.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/NoReturn.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/Likely.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/Likely.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/ThreadLocal.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/ThreadLocal.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/Unlikely.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Annotations/Unlikely.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Object.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Object.h)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Object.internal.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ObjectReference.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ObjectReference.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Process.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Process.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ProcessExtensions.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/ProcessExtensions.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real32.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real32.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real32_getBits.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real32_getBits.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real64.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real64.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real64_getBits.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Real64_getBits.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Size.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Size.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StaticAssert.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/StaticAssert.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Status.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Status.h)

  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/swap.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/swap.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Tests.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Tests.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Thread.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Thread.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Thread.private.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Thread.private.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/TypeNameParser.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/TypeNameParser.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.h)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.private.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Types.private.h)

  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Unicode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Unicode.h)

  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/NumberLiteral.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/NumberLiteral.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Void.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Void.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Include.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Value.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Value.h)


  list(APPEND ${MyLibraryName}.Libraries Arcadia.Arms)

  if (${${MyLibraryName}.Compiler.Masm} STREQUAL ${${MyLibraryName}.Compiler.Masm.Ms})
	  if (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X64})
      elseif (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X86})
	  endif()
	  if (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X64})
      elseif (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X86})
	  endif()
  endif()

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Ring1")

endif()
