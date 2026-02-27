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

cmake_minimum_required(VERSION 4.1.3)

set(MyModule ${MyProjectName}.VPL)

if (NOT TARGET ${MyModule})

  BeginProduct(${MyModule} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/VPL/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/VPL/Configure.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/Constant.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/Constant.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantKind.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantKind.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantRecord.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantRecord.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantScalar.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantScalar.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/BuiltinType.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/BuiltinType.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantRecordField.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/ConstantRecordField.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/Scalar.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Symbols/Scalar.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/SemanticalAnalysis.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/SemanticalAnalysis.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Program.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Program.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/BinaryExprNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/BinaryExprNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/ConstantRecord.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/ConstantRecord.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/ConstantRecordField.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/ConstantRecordField.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/Include.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Tree/Node.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/Include.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/GLSL/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/GLSL/Include.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/GLSL/Transpiler.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/VPL/GLSL/Transpiler.h)
  
  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Math ${MyProjectName}.Languages)
  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DDL)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "VPL")

endif()
