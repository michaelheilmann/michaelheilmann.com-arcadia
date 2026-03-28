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
set(MyLibraryName ${MyProjectName}.DDL)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDL/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDL/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDL/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDL/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDL/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Writer/Unparser.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Writer/Unparser.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Reader/DefaultReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Reader/DefaultReader.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Reader/Keywords.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Reader/Keywords.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Reader/Parser.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Reader/Parser.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Reader/Scanner.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Reader/Scanner.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Reader/WordType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Reader/WordType.h)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Reader/WordType.i)

  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/Node.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/BooleanNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/BooleanNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/ListNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/ListNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/MapNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/MapNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/MapEntryNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/MapEntryNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/NameNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/NameNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/NodeType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/NodeType.h)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/NodeType.i)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/NumberNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/NumberNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/StringNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/StringNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/DDL/Nodes/VoidNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/Nodes/VoidNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/DDL/SemanticalAnalysis.c)
  OnHeaderFile(${MyLibraryName} Arcadia/DDL/SemanticalAnalysis.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Languages ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "DDL")

endif()
