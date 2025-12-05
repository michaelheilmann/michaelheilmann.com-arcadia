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

set(MyExecutableName ${MyProjectName}.Tools.GenerateRyuLookupTables)

if (NOT TARGET ${MyExecutableName})

  BeginProduct(${MyExecutableName} executable)
  
  set(${MyExecutableName}.Windows.ResourceFile ${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Configure.h @ONLY)
  list(APPEND ${MyExecutableName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Configure.h.i)
  list(APPEND ${MyExecutableName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Configure.h)

  list(APPEND ${MyExecutableName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Main.c)

  list(APPEND ${MyExecutableName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/generateReal64Table.c)
  list(APPEND ${MyExecutableName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/generateReal64Table.h)
  list(APPEND ${MyExecutableName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/generateReal32Table.c)
  list(APPEND ${MyExecutableName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/generateReal32Table.h)
  list(APPEND ${MyExecutableName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Common.c)
  list(APPEND ${MyExecutableName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.GenerateRyuLookupTables/Common.h)

  list(APPEND ${MyExecutableName}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.Ring1)

  EndProduct(${MyExecutableName})

  set_target_properties(${MyExecutableName} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--target=\"${CMAKE_CURRENT_BINARY_DIR}\"")

  set_target_properties(${MyExecutableName} PROPERTIES FOLDER "Tools")

endif()
