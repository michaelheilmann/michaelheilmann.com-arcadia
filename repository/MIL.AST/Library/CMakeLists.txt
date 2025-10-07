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
set(MyLibraryName ${MyProjectName}.MIL.AST)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/AST/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Configure.h.i)
  list(APPEND ${MyLibraryName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/AST/Configure.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Include.h)
  
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Node.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Node.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/BinaryInstructionKind.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/BinaryInstructionKind.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/UnaryInstructionKind.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/UnaryInstructionKind.h)
  
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/BooleanLiteralNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/BooleanLiteralNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/IntegerLiteralNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/IntegerLiteralNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/RealLiteralNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/RealLiteralNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/StringLiteralNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/StringLiteralNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/VoidLiteralNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Literals/VoidLiteralNode.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/InstructionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/InstructionNode.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/StatementNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/StatementNode.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/OperandNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/OperandNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/LiteralOperandNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/LiteralOperandNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/RegisterOperandNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/RegisterOperandNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/VariableOperandNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Operands/VariableOperandNode.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/ConstructorDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/ConstructorDefinitionNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/ClassDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/ClassDefinitionNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/EnumerationConstantDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/EnumerationConstantDefinitionNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/EnumerationDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/EnumerationDefinitionNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/FieldDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/FieldDefinitionNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/MethodDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/MethodDefinitionNode.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/ProcedureDefinitionNode.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/AST/Definitions/ProcedureDefinitionNode.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Ring2 ${MyProjectName}.Ring1 ${MyProjectName}.Arms)

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "MIL/AST")

endif()
