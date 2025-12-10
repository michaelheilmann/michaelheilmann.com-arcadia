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

set(MyTestFolder MIL/Frontend)
set(MyTestName ${MyProjectName}.MIL.Frontend.Tests.LexicalAnalysis)

if (NOT TARGET ${MyTestName})

  BeginProduct(${MyTestName} test)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Tests/LexicalAnalysis/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/Frontend/Tests/LexicalAnalysis/Configure.h @ONLY)
  list(APPEND ${MyTestName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Tests/LexicalAnalysis/Configure.h.i)
  list(APPEND ${MyTestName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/MIL/Frontend/Tests/LexicalAnalysis/Configure.h)

  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/MIL/Frontend/Tests/LexicalAnalysis/Main.c)

  list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.MIL.Frontend)

  EndProduct(${MyTestName})
  set_target_properties(${MyTestName} PROPERTIES FOLDER ${MyTestFolder})
endif()
