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

cmake_minimum_required(VERSION 4.1.3)

set(MyTool ${MyProjectName}.Tools.Compiler)

if (NOT TARGET ${MyTool})

  BeginProduct(${MyTool} executable)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Compiler/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Compiler/Configure.h @ONLY)
  list(APPEND ${MyTool}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Compiler/Configure.h.i)
  list(APPEND ${MyTool}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Compiler/Configure.h)

  list(APPEND ${MyTool}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Compiler/Main.c)

  list(APPEND ${MyTool}.PrivateLibraries ${MyProjectName}.MIL.Frontend ${MyProjectName}.MIL.AST)

  EndProduct(${MyTool})

  set_target_properties(${MyTool} PROPERTIES FOLDER "Tools/Compiler")

endif()
