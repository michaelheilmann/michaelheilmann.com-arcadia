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

cmake_minimum_required(VERSION 3.20)

set(MyLibraryName ${MyProjectName}.Tools.TemplateEngine.Library)

if (NOT TARGET ${MyLibraryName})

  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Configure.h)

  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Ast.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Ast.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Context.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Context.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Environment.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Environment.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/FileContext.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/FileContext.h)
  OnSourceFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Library.c)
  OnHeaderFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Library.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.MIL.AST ${MyProjectName}.DDL ${MyProjectName}.Ring2 ${MyProjectName}.Ring1 ${MyProjectName}.ARMS)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Tools/TemplateEngine")

endif()
