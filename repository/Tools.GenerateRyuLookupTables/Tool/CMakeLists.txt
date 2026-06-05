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

set(this ${MyProjectName}.Tools.GenerateRyuLookupTables)

if (NOT TARGET ${this})

  BeginProduct(${this} executable)

  set(${this}.Windows.ResourceFile ${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Configure.h.i)

  OnSourceFile(${this} Arcadia.Tools.GenerateRyuLookupTables/Main.c)

  OnSourceFile(${this} Arcadia.Tools.GenerateRyuLookupTables/generateReal64Table.c)
  OnHeaderFile(${this} Arcadia.Tools.GenerateRyuLookupTables/generateReal64Table.h)
  OnSourceFile(${this} Arcadia.Tools.GenerateRyuLookupTables/generateReal32Table.c)
  OnHeaderFile(${this} Arcadia.Tools.GenerateRyuLookupTables/generateReal32Table.h)
  OnSourceFile(${this} Arcadia.Tools.GenerateRyuLookupTables/Common.c)
  OnHeaderFile(${this} Arcadia.Tools.GenerateRyuLookupTables/Common.h)

  OnModuleDependency(${this} ${MyProjectName}.Ring2 PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.Ring1 PRIVATE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--target=\"\"\"${CMAKE_CURRENT_BINARY_DIR}\"\"\"")

  set_target_properties(${this} PROPERTIES FOLDER "Tools")

endif()
