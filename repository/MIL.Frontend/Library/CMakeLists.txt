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
set(MyLibraryName ${MyProjectName}.MIL.Frontend)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/Frontend/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Configure.h.i)
  list(APPEND ${MyLibraryName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/Frontend/Configure.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Include.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/Include.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/Ast.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/Ast.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/BinaryExpressionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/BinaryExpressionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/BooleanLiteralOperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/BooleanLiteralOperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ConstructorDefinitionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ConstructorDefinitionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ClassDefinitionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ClassDefinitionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ExpressionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ExpressionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ExpressionStatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ExpressionStatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/IntegerLiteralOperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/IntegerLiteralOperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/InvokeExpressionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/InvokeExpressionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/JumpStatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/JumpStatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/LabelStatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/LabelStatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/LoadExpressionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/LoadExpressionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/MethodDefinitionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/MethodDefinitionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ModuleAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ModuleAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/OperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/OperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ProcedureDefinitionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ProcedureDefinitionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/RaiseStatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/RaiseStatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/RealLiteralOperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/RealLiteralOperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ReturnStatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/ReturnStatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/StatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/StatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/StringLiteralOperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/StringLiteralOperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/UnaryExpressionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/UnaryExpressionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VariableDefinitionAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VariableDefinitionAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VariableDefinitionStatementAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VariableDefinitionStatementAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VoidLiteralOperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VoidLiteralOperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VariableOperandAst.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Asts/VariableOperandAst.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Scanner.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Scanner.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Parser.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Parser.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Keywords.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Keywords.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/TokenType.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/TokenType.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/StringTable.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/StringTable.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Include.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Include.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Ring2 ${MyProjectName}.Ring1 ${MyProjectName}.Arms)

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "MIL/Frontend")

endif()
