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

set(MyTestName ${MyProjectName}.Ring1.Tests.BigIntegerTests)

# Create test executable.
BeginProduct(${MyTestName} test)

list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Additive.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Additive.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/And.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/And.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Main.c)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Multiplicative.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Multiplicative.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Or.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Or.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/PowersOf.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/PowersOf.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/QuotientRemainder.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/QuotientRemainder.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Relational.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Relational.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/SetInteger.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/SetInteger.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Shift.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/Shift.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/TwosComplement.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/TwosComplement.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/DecimalString.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.BigIntegerTests/DecimalString.h)

list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.Ring1)

EndProduct(${MyTestName})
set_target_properties(${MyTestName} PROPERTIES FOLDER "Ring1")
