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
set(this ${MyProjectName}.Logging)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Logging/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Logging/Configure.h.i)

  OnSourceFile(${this} Arcadia/Logging/Include.c)
  OnHeaderFile(${this} Arcadia/Logging/Include.h)
  OnSourceFile(${this} Arcadia/Logging/ConsoleLog.c)
  OnHeaderFile(${this} Arcadia/Logging/ConsoleLog.h)
  OnSourceFile(${this} Arcadia/Logging/FileLog.c)
  OnHeaderFile(${this} Arcadia/Logging/FileLog.h)

  OnModuleDependency(${this} ${MyProjectName}.FileSystem)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  set(${this}.Install TRUE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Runtime/Logging")

endif()
