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

# Create library.
set(MyLibraryName ${MyProjectName}.DDLS)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDLS/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDLS/Configure.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Include.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Include.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Syntactical/DefaultReader.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Syntactical/DefaultReader.h)


  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/SchemaSymbol.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/SchemaSymbol.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/SchemaReferenceSymbol.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/SchemaReferenceSymbol.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/Scope.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/Scope.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/Symbol.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/Symbol.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/ScalarSymbol.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/ScalarSymbol.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/MapSymbol.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/MapSymbol.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/MapEntrySymbol.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/MapEntrySymbol.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/SymbolReader.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Semantical/SymbolReader.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Implementation/Diagnostics.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Implementation/Diagnostics.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Implementation/ValidationContext.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Implementation/ValidationContext.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Extensions.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Extensions.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/Include.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/Include.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/Node.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/Node.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/SchemaNode.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/SchemaNode.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/SchemaReferenceNode.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/SchemaReferenceNode.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/ListNode.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/ListNode.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/MapNode.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/MapNode.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/ScalarNode.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDLS/Nodes/ScalarNode.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.DDL ${MyProjectName}.Languages ${MyProjectName}.Ring2 ${MyProjectName}.Ring1 ${MyProjectName}.ARMS)

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "DDLS")

endif()
