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
set(this ${MyProjectName}.Languages)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Languages/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Languages/Configure.h.i)

  OnSourceFile(${this} Arcadia/Languages/Include.c)
  OnHeaderFile(${this} Arcadia/Languages/Include.h)
  OnSourceFile(${this} Arcadia/Languages/StringTable.c)
  OnHeaderFile(${this} Arcadia/Languages/StringTable.h)
  OnSourceFile(${this} Arcadia/Languages/EncodingErrorException.c)
  OnHeaderFile(${this} Arcadia/Languages/EncodingErrorException.h)
  OnSourceFile(${this} Arcadia/Languages/LexicalErrorException.c)
  OnHeaderFile(${this} Arcadia/Languages/LexicalErrorException.h)
  OnSourceFile(${this} Arcadia/Languages/SyntacticalErrorException.c)
  OnHeaderFile(${this} Arcadia/Languages/SyntacticalErrorException.h)
  OnSourceFile(${this} Arcadia/Languages/Scanner.c)
  OnHeaderFile(${this} Arcadia/Languages/Scanner.h)
  OnSourceFile(${this} Arcadia/Languages/Scope.c)
  OnHeaderFile(${this} Arcadia/Languages/Scope.h)
  OnSourceFile(${this} Arcadia/Languages/Diagnostic.c)
  OnHeaderFile(${this} Arcadia/Languages/Diagnostic.h)
  OnSourceFile(${this} Arcadia/Languages/DiagnosticsOld.c)
  OnHeaderFile(${this} Arcadia/Languages/DiagnosticsOld.h)
  OnSourceFile(${this} Arcadia/Languages/Diagnostics.c)
  OnHeaderFile(${this} Arcadia/Languages/Diagnostics.h)
  OnSourceFile(${this} Arcadia/Languages/DiagnosticType.c)
  OnHeaderFile(${this} Arcadia/Languages/DiagnosticType.h)
  OnSourceFile(${this} Arcadia/Languages/Parser.c)
  OnHeaderFile(${this} Arcadia/Languages/Parser.h)
  OnSourceFile(${this} Arcadia/Languages/mangleName.c)
  OnHeaderFile(${this} Arcadia/Languages/mangleName.h)

  OnModuleDependency(${this} ${MyProjectName}.Collections)
  OnModuleDependency(${this} ${MyProjectName}.Logging)
  OnModuleDependency(${this} ${MyProjectName}.FileSystem)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  EndProduct(${this})
  set_target_properties(${this} PROPERTIES FOLDER "Languages")

endif()
