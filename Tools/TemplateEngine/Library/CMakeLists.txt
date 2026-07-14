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

set(this ${MyProjectName}.Tools.TemplateEngine.Library)

if (NOT TARGET ${this})

  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Tools.TemplateEngine.Library/Configure.h.i)

  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Scanner/Scanner.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Scanner/Scanner.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Scanner/WordType.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Scanner/WordType.h)

  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Parser/Parser.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Parser/Parser.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Parser/Tree.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Parser/Tree.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Parser/TreeType.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Parser/TreeType.h)

  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Context.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Context.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Environment.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Environment.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/FileContext.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/FileContext.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/Library.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/Library.h)
  OnSourceFile(${this} Arcadia.Tools.TemplateEngine.Library/DependenciesContext.c)
  OnHeaderFile(${this} Arcadia.Tools.TemplateEngine.Library/DependenciesContext.h)

  OnModuleDependency(${this} ${MyProjectName}.DDL)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Tools/TemplateEngine")

endif()
