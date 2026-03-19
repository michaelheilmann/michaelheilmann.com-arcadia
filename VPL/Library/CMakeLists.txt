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

set(MyLibraryName ${MyProjectName}.VPL)

if (NOT TARGET ${MyLibraryName})

  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/VPL/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/VPL/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/BuiltinType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/BuiltinType.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Constant.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Constant.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/ConstantKind.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/ConstantKind.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/ConstantRecord.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/ConstantRecord.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/ConstantScalar.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/ConstantScalar.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Procedure.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Procedure.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Program.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Program.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Stage.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Stage.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Symbol.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Symbol.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/VariableScalar.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/VariableScalar.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Symbols/Variable.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Symbols/Variable.h)

  OnSourceFile(${MyLibraryName} Arcadia/VPL/SemanticalAnalysis.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/SemanticalAnalysis.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/ModifiersUtilities.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/ModifiersUtilities.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/ResolvePhase.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/ResolvePhase.h)

  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/BinaryExprNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/BinaryExprNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/CallExprNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/CallExprNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/ConstantRecordDefnNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/ConstantRecordDefnNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/ProcedureDefnNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/ProcedureDefnNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/NameExprNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/NameExprNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/Node.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/NodeFactory.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/NodeFactory.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/NodeVisitor.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/NodeVisitor.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/NumberExprNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/NumberExprNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/ProgramDefnNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/ProgramDefnNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Tree/VariableDefnNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Tree/VariableDefnNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/VPL/GLSL/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/GLSL/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/VPL/GLSL/Transpiler.c)
  OnHeaderFile(${MyLibraryName} Arcadia/VPL/GLSL/Transpiler.h)
  
  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Math ${MyProjectName}.Languages)
  list(APPEND ${MyLibraryName}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DDL)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "VPL")

endif()
