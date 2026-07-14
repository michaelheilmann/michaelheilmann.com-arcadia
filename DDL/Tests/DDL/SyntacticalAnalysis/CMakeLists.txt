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

set(MyTestFolder DDL)
set(this ${MyProjectName}.DDL.Tests.SyntacticalAnalysis)

if (NOT TARGET ${this})

  BeginProduct(${this} test)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/DDL/Tests/SyntacticalAnalysis/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/DDL/Tests/SyntacticalAnalysis/Configure.h.i)

  OnSourceFile(${this} Arcadia/DDL/Tests/SyntacticalAnalysis/Main.c)

  OnAssetsDirectory(${this} ${CMAKE_CURRENT_SOURCE_DIR}/Assets)

  OnModuleDependency(${this} ${MyProjectName}.DDL PRIVATE)

  EndProduct(${this})
  target_include_directories(${this} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources ${CMAKE_CURRENT_BINARY_DIR}/Sources)
  set_target_properties(${this} PROPERTIES FOLDER ${MyTestFolder})

  CopyProductAssets(${this} ${MyTestFolder} ${CMAKE_CURRENT_BINARY_DIR}/Assets)

endif()
