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
set(MyLibraryName ${MyProjectName}.Languages)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Languages/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Languages/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Languages/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Languages/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/Languages/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/StringTable.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/StringTable.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/EncodingErrorException.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/EncodingErrorException.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/LexicalErrorException.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/LexicalErrorException.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/SyntacticalErrorException.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/SyntacticalErrorException.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/Scanner.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/Scanner.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/Scope.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/Scope.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/Diagnostics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/Diagnostics.h)
  OnSourceFile(${MyLibraryName} Arcadia/Languages/mangleName.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Languages/mangleName.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Languages")

endif()
