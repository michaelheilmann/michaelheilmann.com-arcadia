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

# Last modified: 2024-09-16

cmake_minimum_required(VERSION 3.29)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" "path to the ARMS1 source directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Sources" "path to the R1 source directory")
FetchProduct(${MyProjectName}.Concatenate "${REPOSITORY_SOURCE_DIR}/Tools.Concatenate/Tool/Sources" "path to the Tools.Concatenate source directory")
FetchProduct(${MyProjectName}.TemplateEngineLibrary "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Library/sources" "path to the Tools.TemplateEngine Library source directory")
FetchProduct(${MyProjectName}.TemplateEngine "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Tool/Sources" "path to the Tools.TemplateEngine Tool source directory")




# Build the documentation.
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../index.html
                   COMMAND $<TARGET_FILE:Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/main.i ${CMAKE_CURRENT_SOURCE_DIR}/../index.html
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/main.i => ${CMAKE_CURRENT_SOURCE_DIR}/../index.html"
                   DEPENDS Tools.TemplateEngine ${CMAKE_CURRENT_SOURCE_DIR}/main.i)

add_custom_target(${MyProjectName}.Arms.BuildDocs ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../index.html)

set_target_properties(${MyProjectName}.Arms.BuildDocs PROPERTIES FOLDER "Arms")
