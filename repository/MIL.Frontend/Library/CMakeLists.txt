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
set(MyLibraryName ${MyProjectName}.MIL.Frontend)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MILC/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MILC/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MILC/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MILC/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/CompilationTask.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/CompilationTask.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/CompilationFailedException.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/CompilationFailedException.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/EnterPhase.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/EnterPhase.h)
  
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Context.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Context.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/FileType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/FileType.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/Symbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/Symbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/SymbolKind.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/SymbolKind.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/ClassSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/ClassSymbol.h)  
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/ConstructorSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/ConstructorSymbol.h) 
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/EnumerationSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/EnumerationSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/FieldSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/FieldSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/MethodSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/MethodSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/ModuleSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/ModuleSymbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Symbols/ProcedureSymbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Symbols/ProcedureSymbol.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Completer.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Completer.h)
  
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/UnexpectedWordDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/UnexpectedWordDiagnostic.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/SymbolAlreadyDefinedDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/SymbolAlreadyDefinedDiagnostic.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/FileNotFoundDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/FileNotFoundDiagnostic.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/MissingModuleDefinitionDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/MissingModuleDefinitionDiagnostic.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/MultipleModuleDefinitionsDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/MultipleModuleDefinitionsDiagnostic.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/ConfigurationFileInvalidDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/ConfigurationFileInvalidDiagnostic.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/InvalidPathDiagnostic.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/InvalidPathDiagnostic.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Diagnostics/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Diagnostics/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/WordType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/WordType.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/Scanner.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Scanner.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Parser.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Parser.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/Keywords.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/Keywords.h)
  
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Node.h)
  
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/ModuleNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/ModuleNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/CompilationUnitNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/CompilationUnitNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/InstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/InstructionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/StatementNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/StatementNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/OperandNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/OperandNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/IdentifierNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/IdentifierNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Literals/BooleanLiteralNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Literals/BooleanLiteralNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Literals/IntegerLiteralNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Literals/IntegerLiteralNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Literals/RealLiteralNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Literals/RealLiteralNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Literals/StringLiteralNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Literals/StringLiteralNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Literals/VoidLiteralNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Literals/VoidLiteralNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/BinaryInstructionKind.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/BinaryInstructionKind.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/BinaryInstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/BinaryInstructionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/UnaryInstructionKind.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/UnaryInstructionKind.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/UnaryInstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/UnaryInstructionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/InvokeInstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/InvokeInstructionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/JumpInstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/JumpInstructionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/RaiseInstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/RaiseInstructionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/ReturnInstructionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Instructions/ReturnInstructionNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionStatementNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionStatementNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/InstructionStatementNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/InstructionStatementNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Operands/LiteralOperandNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Operands/LiteralOperandNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Operands/RegisterOperandNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Operands/RegisterOperandNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Operands/VariableOperandNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Operands/VariableOperandNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ConstructorDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ConstructorDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ClassDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ClassDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/EnumerationConstantDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/EnumerationConstantDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/EnumerationDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/EnumerationDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/FieldDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/FieldDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/MethodDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/MethodDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ModuleDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ModuleDefinitionNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ProcedureDefinitionNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/Definitions/ProcedureDefinitionNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionStatements/VariableDefinitionStatementNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionStatements/VariableDefinitionStatementNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionStatements/LabelDefinitionStatementNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/MILC/AST/DefinitionStatements/LabelDefinitionStatementNode.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Languages ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "MIL/Frontend")

endif()
