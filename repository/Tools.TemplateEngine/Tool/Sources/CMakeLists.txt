# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-12-02

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the R1 library directory")
FetchProduct(${MyProjectName}.Tools.TemplateEngineLibrary "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Library" "path to the Tools.TemplateEngineLibrary library directory")

set(MyExecutableName ${MyProjectName}.Tools.TemplateEngine)
if (NOT TARGET ${MyExecutableName})
    add_executable(${MyExecutableName})
    BeginProduct(${MyExecutableName})

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Tools/TemplateEngine/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Tools/TemplateEngine/Configure.h @ONLY)

    list(APPEND ${MyExecutableName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/TemplateEngine/Main.c)
    list(APPEND ${MyExecutableName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Tools/TemplateEngine/Configure.h)

    target_link_libraries(${MyExecutableName} ${MyProjectName}.Tools.TemplateEngineLibrary ${MyProjectName}.R ${MyProjectName}.Arms)

    set_target_properties(${MyExecutableName} PROPERTIES FOLDER "Tools/TemplateEngine")

    EndProduct(${MyExecutableName} executable)
endif()
