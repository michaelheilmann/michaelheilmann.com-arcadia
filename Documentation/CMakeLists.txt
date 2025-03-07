# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-12-29

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../repository)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the R1 library directory")
FetchProduct(${MyProjectName}.ConcatenateFiles "${REPOSITORY_SOURCE_DIR}/Tools.ConcatenateFiles/Tool/Sources" "path to the Tools.ConcatenateFiles source directory")
FetchProduct(${MyProjectName}.TemplateEngineLibrary "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Library/Sources" "path to the Tools.TemplateEngine Library source directory")
FetchProduct(${MyProjectName}.TemplateEngine "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Tool/Sources" "path to the Tools.TemplateEngine Tool source directory")

# Build "index.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/index.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/index.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.IndexPage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "error.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/error.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/error.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.ErrorPage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "roadmap.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/roadmap.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.RoadmapPage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "roadmap-archive.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/roadmap-archive.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/roadmap-archive.i ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/roadmap-archive.i => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.RoadmapArchivePage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "assets/index.css".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/index.css.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/assets/index.css")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.IndexCss ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "assets/reset.css".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/reset.css.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/assets/reset.css")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.ResetCss ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "Specifications/Mil/index.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Specifications/Mil/index.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/specifications/mil/index.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.Specifications.Mil ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})

# Build "Specifications/Ddl/index.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Specifications/Ddl/index.i)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/specifications/ddl/index.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.Specifications.Ddl ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})
