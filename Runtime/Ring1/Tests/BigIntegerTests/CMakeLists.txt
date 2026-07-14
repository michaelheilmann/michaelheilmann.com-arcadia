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

set(this ${MyProjectName}.Ring1.Tests.BigIntegerTests)

# Create test executable.
BeginProduct(${this} test)

OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Additive.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Additive.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/And.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/And.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Main.c)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Multiplicative.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Multiplicative.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Or.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Or.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/PowersOf.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/PowersOf.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/QuotientRemainder.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/QuotientRemainder.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Relational.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Relational.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/SetInteger.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/SetInteger.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Shift.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/Shift.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/TwosComplement.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/TwosComplement.h)
OnSourceFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/DecimalString.c)
OnHeaderFile(${this} Arcadia.Ring1.Tests.BigIntegerTests/DecimalString.h)

OnModuleDependency(${this} ${MyProjectName}.Ring1 PRIVATE)

EndProduct(${this})
set_target_properties(${this} PROPERTIES FOLDER "Ring1")
