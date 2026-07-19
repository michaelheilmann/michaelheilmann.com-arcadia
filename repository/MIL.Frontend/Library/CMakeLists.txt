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
set(this ${MyProjectName}.MIL.Frontend)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MILC/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MILC/Configure.h.i)

  OnSourceFile(${this} Arcadia/MILC/Include.c)
  OnHeaderFile(${this} Arcadia/MILC/Include.h)

  OnSourceFile(${this} Arcadia/MILC/CompilationTask.c)
  OnHeaderFile(${this} Arcadia/MILC/CompilationTask.h)
  OnSourceFile(${this} Arcadia/MILC/CompilationFailedException.c)
  OnHeaderFile(${this} Arcadia/MILC/CompilationFailedException.h)

  OnSourceFile(${this} Arcadia/MILC/EnterPhase.c)
  OnHeaderFile(${this} Arcadia/MILC/EnterPhase.h)
  OnSourceFile(${this} Arcadia/MILC/MemberEnterPhase.c)
  OnHeaderFile(${this} Arcadia/MILC/MemberEnterPhase.h)
  
  OnSourceFile(${this} Arcadia/MILC/Context.c)
  OnHeaderFile(${this} Arcadia/MILC/Context.h)

  OnSourceFile(${this} Arcadia/MILC/FileType.c)
  OnHeaderFile(${this} Arcadia/MILC/FileType.h)

  OnSourceFile(${this} Arcadia/MILC/Symbols/Include.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/Include.h)

  OnSourceFile(${this} Arcadia/MILC/Symbols/Symbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/Symbol.h)
  OnSourceFile(${this} Arcadia/MILC/Symbols/SymbolKind.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/SymbolKind.h)

  OnSourceFile(${this} Arcadia/MILC/Symbols/ClassSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/ClassSymbol.h)  
  OnSourceFile(${this} Arcadia/MILC/Symbols/ConstructorSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/ConstructorSymbol.h) 
  OnSourceFile(${this} Arcadia/MILC/Symbols/EnumerationSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/EnumerationSymbol.h)
  OnSourceFile(${this} Arcadia/MILC/Symbols/FieldSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/FieldSymbol.h)
  OnSourceFile(${this} Arcadia/MILC/Symbols/MethodSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/MethodSymbol.h)
  OnSourceFile(${this} Arcadia/MILC/Symbols/ModuleSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/ModuleSymbol.h)
  OnSourceFile(${this} Arcadia/MILC/Symbols/ProcedureSymbol.c)
  OnHeaderFile(${this} Arcadia/MILC/Symbols/ProcedureSymbol.h)

  OnSourceFile(${this} Arcadia/MILC/Enter/Completer.c)
  OnHeaderFile(${this} Arcadia/MILC/Enter/Completer.h)
  OnSourceFile(${this} Arcadia/MILC/Enter/ClassCompleter.c)
  OnHeaderFile(${this} Arcadia/MILC/Enter/ClassCompleter.h)
  OnSourceFile(${this} Arcadia/MILC/Enter/EnumerationCompleter.c)
  OnHeaderFile(${this} Arcadia/MILC/Enter/EnumerationCompleter.h)
  
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/UnexpectedWordDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/UnexpectedWordDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/SymbolAlreadyDefinedDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/SymbolAlreadyDefinedDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/FileNotFoundDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/FileNotFoundDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/MissingModuleDefinitionDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/MissingModuleDefinitionDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/MultipleModuleDefinitionsDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/MultipleModuleDefinitionsDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/ConfigurationFileInvalidDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/ConfigurationFileInvalidDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/InvalidPathDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/InvalidPathDiagnostic.h)
  OnSourceFile(${this} Arcadia/MILC/Diagnostics/UnexpectedSymbolDiagnostic.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/UnexpectedSymbolDiagnostic.h)

  OnSourceFile(${this} Arcadia/MILC/Diagnostics/Include.c)
  OnHeaderFile(${this} Arcadia/MILC/Diagnostics/Include.h)

  OnSourceFile(${this} Arcadia/MILC/WordType.c)
  OnHeaderFile(${this} Arcadia/MILC/WordType.h)

  OnSourceFile(${this} Arcadia/MILC/Scanner.c)
  OnHeaderFile(${this} Arcadia/MILC/Scanner.h)
  OnSourceFile(${this} Arcadia/MILC/Parser.c)
  OnHeaderFile(${this} Arcadia/MILC/Parser.h)
  OnSourceFile(${this} Arcadia/MILC/Keywords.c)
  OnHeaderFile(${this} Arcadia/MILC/Keywords.h)
  
  OnSourceFile(${this} Arcadia/MILC/AST/Include.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Include.h)

  OnSourceFile(${this} Arcadia/MILC/AST/Visitor.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Visitor.h)

  OnSourceFile(${this} Arcadia/MILC/AST/Node.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Node.h)
  
  OnSourceFile(${this} Arcadia/MILC/AST/ModuleNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/ModuleNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/CompilationUnitNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/CompilationUnitNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/InstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/InstructionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/StatementNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/StatementNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/OperandNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/OperandNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/DefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/DefinitionNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/IdentifierNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/IdentifierNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/Literals/BooleanLiteralNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Literals/BooleanLiteralNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Literals/IntegerLiteralNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Literals/IntegerLiteralNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Literals/RealLiteralNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Literals/RealLiteralNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Literals/StringLiteralNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Literals/StringLiteralNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Literals/VoidLiteralNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Literals/VoidLiteralNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/BinaryInstructionKind.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/BinaryInstructionKind.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/BinaryInstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/BinaryInstructionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/UnaryInstructionKind.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/UnaryInstructionKind.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/UnaryInstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/UnaryInstructionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/InvokeInstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/InvokeInstructionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/JumpInstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/JumpInstructionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/RaiseInstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/RaiseInstructionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Instructions/ReturnInstructionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Instructions/ReturnInstructionNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/DefinitionStatementNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/DefinitionStatementNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/InstructionStatementNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/InstructionStatementNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/Operands/LiteralOperandNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Operands/LiteralOperandNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Operands/RegisterOperandNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Operands/RegisterOperandNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Operands/VariableOperandNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Operands/VariableOperandNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/ConstructorDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/ConstructorDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/ClassDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/ClassDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/EnumerationConstantDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/EnumerationConstantDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/EnumerationDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/EnumerationDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/FieldDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/FieldDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/MethodDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/MethodDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/ModuleDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/ModuleDefinitionNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/Definitions/ProcedureDefinitionNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/Definitions/ProcedureDefinitionNode.h)

  OnSourceFile(${this} Arcadia/MILC/AST/DefinitionStatements/VariableDefinitionStatementNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/DefinitionStatements/VariableDefinitionStatementNode.h)
  OnSourceFile(${this} Arcadia/MILC/AST/DefinitionStatements/LabelDefinitionStatementNode.c)
  OnHeaderFile(${this} Arcadia/MILC/AST/DefinitionStatements/LabelDefinitionStatementNode.h)

  OnModuleDependency(${this} ${MyProjectName}.Languages)
  OnModuleDependency(${this} ${MyProjectName}.Logging)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  EndProduct(${this})
  set_target_properties(${this} PROPERTIES FOLDER "MIL/Frontend")

endif()
