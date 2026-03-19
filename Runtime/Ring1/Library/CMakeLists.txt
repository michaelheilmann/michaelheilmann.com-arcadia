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

cmake_minimum_required(VERSION 3.29)

set(MyLibraryName ${MyProjectName}.Ring1)

# Create library.
if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring1/Implementation/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/add.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/add.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/and.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/and.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/BigInteger.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/BigInteger.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/divide.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/divide.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/compareByMagnitudeTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/compareByMagnitudeTo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/compareTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/compareTo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/equalTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/equalTo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/fromDecimalString.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/fromDecimalString.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/fromTwosComplement.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/fromTwosComplement.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/getBitLength.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/getBitLength.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/greaterThan.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/greaterThan.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/greaterThanOrEqualTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/greaterThanOrEqualTo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/getHigh64.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/getHigh64.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/lowerThan.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/lowerThan.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/lowerThanOrEqualTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/lowerThanOrEqualTo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/multiply.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/multiply.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/notEqualTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/notEqualTo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/or.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/or.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setNatural.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setNatural.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setInteger.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setInteger.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setPowerOfFive.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setPowerOfTen.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/shiftLeft.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/shiftLeft.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/shiftRight.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/shiftRight.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/subtract.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/subtract.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toDecimalString.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toDecimalString.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toNatural.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toNatural.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toInteger.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toInteger.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toTwosComplement.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BigInteger/toTwosComplement.h)

    # >> Signals

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Signal.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Signal.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Slot.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Slot.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Internal.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Signals/Internal.h)

  # << Signals

  # >> String to number

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToInteger/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToInteger/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToNatural/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToNatural/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/toReal64.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/toReal64.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/toReal32.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/toReal32.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Lemire.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Lemire.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Gay.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Gay.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Clinger.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Clinger.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Result.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StringToReal/Result.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Include.h)

  ## << String to number

  ## >> Number to string

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Include.h)
  OnInlayFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Common.i)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Real32ToString.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Real32ToString.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Real64ToString.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/Real64ToString.h)
  OnInlayFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/BigTablesReal64.i)
  OnInlayFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/SmallTablesReal64.i)
  OnInlayFile(${MyLibraryName} Arcadia/Ring1/Implementation/RealToString/TablesReal32.i)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/BooleanToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/BooleanToString/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/IntegerToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/IntegerToString/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/NaturalToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/NaturalToString/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/SizeToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/SizeToString/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/VoidToString/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/VoidToString/Include.h)

  ## << Number to string

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Arrays.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Arrays.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Arrays.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Arrays.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/safeAdd.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/safeAdd.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/safeMultiply.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/safeMultiply.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Atoms.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Atoms.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Atoms.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Atoms.module.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/makeBitmask.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/makeBitmask.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Boolean.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Boolean.h)

  # Numerics >>

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/ceil.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/ceil.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/clamp.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/clamp.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/cos.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/cos.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/countLeadingZeroes.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/countLeadingZeroes.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/countSignificandBits.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/countSignificandBits.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/countTrailingZeroes.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/countTrailingZeroes.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/floor.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/floor.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/hash.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/hash.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/isPowerOfTwo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/isPowerOfTwo.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/maximum.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/maximum.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/minimum.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/minimum.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThan.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThan.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThanOrEqualTo.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/nextPowerOfTwoGreaterThanOrEqualTo.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/quotientRemainder.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/quotientRemainder.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/sin.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/sin.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/sqrt.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/sqrt.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/tan.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/tan.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/isDivisibleByPowerOfFive.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Numerics/isDivisibleByPowerOfFive.h)

  # << Numerics

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/_declareScalarType.h)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/_defineScalarType.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Diagnostics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Diagnostics.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Enumeration.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Enumeration.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ForeignProcedure.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ForeignProcedure.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/getNumberOfCores.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/getNumberOfCores.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/getPageSize.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/getPageSize.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/getTickCount.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/getTickCount.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableByteArray.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableByteArray.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/fromBytes.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/hash.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/NumeralParser.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/type.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/type.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toBoolean.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toInteger.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toNatural.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toReal.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toReal.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toSize.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toSize.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ImmutableUtf8String/toVoid.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer16.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer16.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer32.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer32.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer64.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer64.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer8.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Integer8.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural16.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural16.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural32.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural32.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural64.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural64.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural8.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Natural8.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/NoReturn.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/NoReturn.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/Likely.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/Likely.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/ThreadLocal.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/ThreadLocal.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/Unlikely.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Annotations/Unlikely.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Object.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Object.h)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Object.internal.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ObjectReference.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ObjectReference.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Process.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Process.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ProcessExtensions.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ProcessExtensions.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real32.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real32.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real32_getBits.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real32_getBits.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real32_isFinite.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real32_isFinite.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real64.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real64.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real64_getBits.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real64_getBits.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real64_isFinite.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Real64_isFinite.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Size.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Size.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/StaticAssert.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/StaticAssert.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Status.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Status.h)

  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/swap.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/swap.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Tests.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Tests.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Thread.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Thread.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Thread.private.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Thread.private.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/ThreadExtensions.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/ThreadExtensions.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeNameParser.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeNameParser.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Types.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Types.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Types.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Types.module.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Unicode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Unicode.h)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Unicode/Unicode.h)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Unicode/Utf8.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/NumberLiteral.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/NumberLiteral.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Void.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Void.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Value.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Value.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/WeakReference.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/WeakReference.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Memory.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Memory.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Names.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Names.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Names.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Names.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/TypeKind.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/TypeKind.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Type.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/Type.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/TypeNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/TypeNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/EnumerationTypeNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/EnumerationTypeNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/InterfaceTypeNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/InterfaceTypeNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/InternalTypeNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/InternalTypeNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/ObjectTypeNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/ObjectTypeNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/ScalarTypeNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/TypeSystem/ScalarTypeNode.h)


  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Module.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Concurrency/Mutex.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Concurrency/Mutex.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Concurrency/Condition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Concurrency/Condition.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Concurrency/CompareAndSwap.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Concurrency/CompareAndSwap.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Network/AddressFamily.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Network/AddressFamily.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Network/Protocol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Network/Protocol.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring1/Implementation/Network/SocketType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring1/Implementation/Network/SocketType.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.ARMS)

  if (${${MyLibraryName}.Compiler.Masm} STREQUAL ${${MyLibraryName}.Compiler.Masm.Ms})
	  if (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X64})
      elseif (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X86})
	  endif()
	  if (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X64})
      elseif (${${MyLibraryName}.InstructionSetArchitecture} STREQUAL ${${MyLibraryName}.InstructionSetArchitecture.X86})
	  endif()
  endif()

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})

    # link "math" library
	list(APPEND ${MyLibraryName}.Libraries m)

	# link "pthread" library
	set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
	set(THREADS_PREFER_PTHREAD_FLAG TRUE)
	find_package(Threads REQUIRED)
	list(APPEND ${MyLibraryName}.Libraries Threads::Threads)

  endif()

  set(${MyLibraryName}.Install TRUE)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Ring1")

endif()
