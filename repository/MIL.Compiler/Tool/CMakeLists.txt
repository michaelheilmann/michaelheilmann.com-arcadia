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

set(MyTool ${MyProjectName}.MIL.Compiler)

if (NOT TARGET ${MyTool})

  BeginProduct(${MyTool} executable)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Compiler/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/Compiler/Configure.h @ONLY)
  list(APPEND ${MyTool}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Compiler/Configure.h.i)
  OnConfigurationFile(${MyTool} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/Compiler/Configure.h)

  OnSourceFile(${MyTool} Arcadia/MIL/Compiler/Main.c)
  OnSourceFile(${MyTool} Arcadia/MIL/Compiler/HelpSystem.c)
  OnHeaderFile(${MyTool} Arcadia/MIL/Compiler/HelpSystem.h)

  list(APPEND ${MyTool}.PrivateLibraries ${MyProjectName}.DDL ${MyProjectName}.DDLS ${MyProjectName}.MIL.Compiler.Library ${MyProjectName}.MIL.Frontend ${MyProjectName}.MIL.AST)

  EndProduct(${MyTool})

  set(COMMAND_LINE "--mil2mil --configuration=\\\"${CMAKE_CURRENT_SOURCE_DIR}/../../../Modules.mil\\\"")
  set_target_properties(${MyTool} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${COMMAND_LINE}")
  set_target_properties(${MyTool} PROPERTIES FOLDER "MIL")

endif()
