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

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms/Library" "path to the Arcadia ARMS library directory")
FetchProduct(${MyProjectName}.Machine "${REPOSITORY_SOURCE_DIR}/Machine/Library" "path to the Machine library directory")
FetchProduct(${MyProjectName}.ConcatenateFiles "${REPOSITORY_SOURCE_DIR}/Tools.ConcatenateFiles/Tool/Sources" "path to the Tools.ConcatenateFiles source directory")
FetchProduct(${MyProjectName}.TemplateEngineLibrary "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Library/Sources" "path to the Tools.TemplateEngine Library source directory")
FetchProduct(${MyProjectName}.TemplateEngine "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Tool/Sources" "path to the Tools.TemplateEngine Tool source directory")

# Build the documentation.
set(DOCUMENT_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/Arcadia/Arms/index.html")
add_custom_command(OUTPUT ${DOCUMENT_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/index.i ${DOCUMENT_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/index.i => ${DOCUMENT_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${CMAKE_CURRENT_SOURCE_DIR}/index.i)

add_custom_target(${MyProjectName}.Arms.BuildDocs ALL DEPENDS ${DOCUMENT_TARGET_FILE})

set_target_properties(${MyProjectName}.Arms.BuildDocs PROPERTIES FOLDER "Arcadia.Arms")
