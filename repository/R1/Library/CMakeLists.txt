# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-12-29

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

# Create library.
if (NOT TARGET ${MyProjectName}.R)
  BeginProduct(${MyProjectName}.R)

  FetchProduct(${MyProjectName}.Arms  "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
  FetchProduct(${MyProjectName}.Ring1 "${REPOSITORY_SOURCE_DIR}/Arcadia.Ring1/Library" "path to the Arcadia.Ring1 library directory")
  FetchProduct(${MyProjectName}.Ring2 "${REPOSITORY_SOURCE_DIR}/Arcadia.Ring2/Library" "path to the Arcadia.Ring2 library directory")

  add_library(${MyProjectName}.R)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h @ONLY)

  list(APPEND ${MyProjectName}.R.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/execute.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/execute.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Constructor.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Constructor.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Procedure.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Procedure.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Method.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Method.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Class.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Class.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Variable.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Variable.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Instruction.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Instruction.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Include.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ThreadState.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ThreadState.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ThreadState.private.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ProcessState.c)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ProcessState.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/ProcessState.private.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code/Constants.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Interpreter/Code/Constants.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Include.h)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Mil/Configure.h @ONLY)
  list(APPEND ${MyProjectName}.R.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Mil/Configure.h)

  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Ast.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Ast.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/Ast.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/Ast.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/BinaryExpressionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/BinaryExpressionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/BooleanLiteralOperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/BooleanLiteralOperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ConstructorDefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ConstructorDefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ClassDefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ClassDefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ClassMemberDefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ClassMemberDefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/DefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/DefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ExpressionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ExpressionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ExpressionStatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ExpressionStatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/IntegerLiteralOperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/IntegerLiteralOperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/InvokeExpressionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/InvokeExpressionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/JumpStatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/JumpStatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/LabelStatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/LabelStatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/LoadExpressionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/LoadExpressionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/MethodDefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/MethodDefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ModuleAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ModuleAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/OperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/OperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ProcedureDefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ProcedureDefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/RaiseStatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/RaiseStatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/RealLiteralOperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/RealLiteralOperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ReturnStatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/ReturnStatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/StatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/StatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/StringLiteralOperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/StringLiteralOperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/UnaryExpressionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/UnaryExpressionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VariableDefinitionAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VariableDefinitionAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VariableDefinitionStatementAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VariableDefinitionStatementAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VoidLiteralOperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VoidLiteralOperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VariableOperandAst.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Asts/VariableOperandAst.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Scanner.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Scanner.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Parser.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Parser.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Keywords.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Keywords.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/TokenType.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/TokenType.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/StringTable.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/StringTable.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Symbols.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Symbols.h)
  list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Include.c)
  list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/R/Mil/Include.h)

  target_link_libraries(${MyProjectName}.R Arcadia.Ring2 Arcadia.Ring1 Arcadia.Arms)

  if (${${MyProjectName}.R.OperatingSystem} STREQUAL ${${MyProjectName}.R.OperatingSystem.Linux})
    target_link_libraries(${MyProjectName}.R m)
  endif()

  set_target_properties(${MyProjectName}.R PROPERTIES FOLDER "R")

  EndProduct(${MyProjectName}.R library)

endif()
