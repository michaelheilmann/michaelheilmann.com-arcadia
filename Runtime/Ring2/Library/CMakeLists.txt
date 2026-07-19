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

# Create library.
set(this ${MyProjectName}.Ring2)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h.i)

  OnSourceFile(${this} Arcadia/Ring2/CommandLine/CommandLineArgument.c)
  OnHeaderFile(${this} Arcadia/Ring2/CommandLine/CommandLineArgument.h)
  OnSourceFile(${this} Arcadia/Ring2/CommandLine/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/CommandLine/Include.h)

  OnSourceFile(${this} Arcadia/Ring2/Exceptions/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Exceptions/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Exceptions/Exception.c)
  OnHeaderFile(${this} Arcadia/Ring2/Exceptions/Exception.h)

  OnSourceFile(${this} Arcadia/Ring2/Implementation/ArgumentsValidation.c)
  OnHeaderFile(${this} Arcadia/Ring2/Implementation/ArgumentsValidation.h)

  OnSourceFile(${this} Arcadia/Ring2/Unicode/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Unicode/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Unicode/Encoder.c)
  OnHeaderFile(${this} Arcadia/Ring2/Unicode/Encoder.h)
  OnSourceFile(${this} Arcadia/Ring2/Unicode/UTF8Encoder.c)
  OnHeaderFile(${this} Arcadia/Ring2/Unicode/UTF8Encoder.h)

  OnSourceFile(${this} Arcadia/Ring2/Strings/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Strings/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Strings/StringExtensions.c)
  OnHeaderFile(${this} Arcadia/Ring2/Strings/StringExtensions.h)

  OnSourceFile(${this} Arcadia/Ring2/Time/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Time/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Time/PointInTime.c)
  OnHeaderFile(${this} Arcadia/Ring2/Time/PointInTime.h)
  OnSourceFile(${this} Arcadia/Ring2/Time/TimeSpecification.c)
  OnHeaderFile(${this} Arcadia/Ring2/Time/TimeSpecification.h)

  OnSourceFile(${this} Arcadia/Ring2/Logging/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Logging/Log.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/Log.h)
  OnSourceFile(${this} Arcadia/Ring2/Logging/LogCategory.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/LogCategory.h)

  OnSourceFile(${this} Arcadia/Ring2/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Include.h)

  OnModuleDependency(${this} ${MyProjectName}.Ring1)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  set(${this}.Install TRUE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Runtime/Ring2")

endif()
