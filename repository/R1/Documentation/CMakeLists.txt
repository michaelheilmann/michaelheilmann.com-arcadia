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
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" "path to the ARMS1 source directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Sources" "path to the R1 source directory")
FetchProduct(${MyProjectName}.ConcatenateFiles "${REPOSITORY_SOURCE_DIR}/Tools.ConcatenateFiles/Tool/Sources" "path to the Tools.ConcatenateFiles source directory")
FetchProduct(${MyProjectName}.TemplateEngineLibrary "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Library/sources" "path to the Tools.TemplateEngine Library source directory")
FetchProduct(${MyProjectName}.TemplateEngine "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Tool/Sources" "path to the Tools.TemplateEngine Tool source directory")

# Build the documentation.
set(DOCUMENT_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/repository/R1/index.html")
add_custom_command(OUTPUT ${DOCUMENT_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/index.i ${DOCUMENT_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/index.i => ${DOCUMENT_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${CMAKE_CURRENT_SOURCE_DIR}/index.i)

add_custom_target(${MyProjectName}.R.BuildDocs ALL DEPENDS ${DOCUMENT_TARGET_FILE})

set_target_properties(${MyProjectName}.R.BuildDocs PROPERTIES FOLDER "R")
