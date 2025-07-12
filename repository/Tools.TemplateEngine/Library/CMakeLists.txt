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

set(MyLibraryName ${MyProjectName}.Tools.TemplateEngineLibrary)

if (NOT TARGET ${MyLibraryName})

  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Tools/TemplateEngine/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/Configure.h.i)
  list(APPEND ${MyLibraryName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Tools/TemplateEngine/Configure.h)

  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/Context.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/Context.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/FileContext.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/FileContext.h)
  list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/Ast.c)
  list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/TemplateEngine/Ast.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Machine ${MyProjectName}.Arms)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Tools/TemplateEngine")

endif()
