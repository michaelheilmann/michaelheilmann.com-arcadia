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
set(MyLibraryName ${MyProjectName}.DDLS)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDLS/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDLS/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Syntactical/DefaultReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Syntactical/DefaultReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/AnySymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/AnySymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/ChoiceSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/ChoiceSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/ListSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/ListSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/MapSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/MapSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/MapEntrySymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/MapEntrySymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/ScalarSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/ScalarSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/SchemaSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/SchemaSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/SchemaReferenceSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/SchemaReferenceSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/Scope.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/Scope.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/Symbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/Symbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Symbols/SymbolReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Symbols/SymbolReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Implementation/Diagnostics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Implementation/Diagnostics.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Implementation/ValidationContext.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Implementation/ValidationContext.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Extensions.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Extensions.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/AnyNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/AnyNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/ChoiceNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/ChoiceNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/ListNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/ListNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/MapNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/MapNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/Node.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/ScalarNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/ScalarNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/SchemaNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/SchemaNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDLS/Nodes/SchemaReferenceNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDLS/Nodes/SchemaReferenceNode.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.DDL ${MyProjectName}.Languages ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "DDLS")

endif()
