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

FetchProduct(${MyProjectName}.TemplateEngine "${REPOSITORY_SOURCE_DIR}/Tools.TemplateEngine/Tool/Sources" "path to the Template Engine tool source directory")

# Build the documentation.
set(${MyProjectName}.Website.DocFiles "")
list(APPEND ${MyProjectName}.Website.DocFiles "${CMAKE_CURRENT_SOURCE_DIR}/index.html.i")
list(APPEND ${MyProjectName}.Website.DocFiles "${CMAKE_CURRENT_SOURCE_DIR}/error.html.i")
MyBuildDocs(${MyProjectName} ${MyProjectName}.Website.BuildDocs "${CMAKE_CURRENT_SOURCE_DIR}" "${REPOSITORY_SOURCE_DIR}/../.build/" "${${MyProjectName}.Website.DocFiles}")
set_target_properties(${MyProjectName}.Website.BuildDocs PROPERTIES FOLDER "Website")

set(${MyProjectName}.Website.Assets.DocFiles "")
list(APPEND ${MyProjectName}.Website.Assets.DocFiles "${CMAKE_CURRENT_SOURCE_DIR}/index.css.i")
list(APPEND ${MyProjectName}.Website.Assets.DocFiles "${CMAKE_CURRENT_SOURCE_DIR}/reset.css.i")
list(APPEND ${MyProjectName}.Website.Assets.DocFiles "${CMAKE_CURRENT_SOURCE_DIR}/cxx-doc.css.i")
MyBuildDocs(${MyProjectName} ${MyProjectName}.Website.Assets.BuildDocs "${CMAKE_CURRENT_SOURCE_DIR}" "${REPOSITORY_SOURCE_DIR}/../.build/assets/" "${${MyProjectName}.Website.Assets.DocFiles}")
set_target_properties(${MyProjectName}.Website.Assets.BuildDocs PROPERTIES FOLDER "Website")

# Build "roadmap.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i)
file(GLOB_RECURSE DOCUMENTATION_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/Roadmap/*)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/roadmap.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_DEPENDENCIES})
add_custom_target(Website.RoadmapPage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})
set_target_properties(Website.RoadmapPage PROPERTIES FOLDER "Website")

# Build "roadmap-archive.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/roadmap.i)
file(GLOB_RECURSE DOCUMENTATION_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/Roadmap/Archive/*)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/roadmap-archive.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${CMAKE_CURRENT_SOURCE_DIR}/roadmap-archive.i ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${CMAKE_CURRENT_SOURCE_DIR}/roadmap-archive.i => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE})
add_custom_target(Website.RoadmapArchivePage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE} ${DOCUMENTATION_DEPENDENCIES})
set_target_properties(Website.RoadmapArchivePage PROPERTIES FOLDER "Website")

# Build "Specifications/Mil/index.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Specifications/Mil/index.i)
file(GLOB_RECURSE DOCUMENTATION_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/Specifications/Mil/*)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/specifications/mil/index.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_DEPENDENCIES})
add_custom_target(Website.Specifications.Mil ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})
set_target_properties(Website.Specifications.Mil PROPERTIES FOLDER "Website")

# Build "Specifications/Ddl/index.html".
set(DOCUMENTATION_SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Specifications/DataDefinitionLanguage/index.i")
file(GLOB_RECURSE DOCUMENTATION_DEPENDENCIES "${CMAKE_CURRENT_SOURCE_DIR}/Specifications/DataDefinitionLanguage/*")
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/specifications/data-definition-language/index.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_DEPENDENCIES})
add_custom_target(Website.Specifications.DataDefinitionLanguage ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})
set_target_properties(Website.Specifications.DataDefinitionLanguage PROPERTIES FOLDER "Website")

# Build "Specifications/Common-Lexical-Specification/index.html".
set(DOCUMENTATION_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Specifications/CommonLexicalSpecification/index.i)
file(GLOB_RECURSE DOCUMENTATION_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR}/Specifications/CommonLexicalSpecification/*)
set(DOCUMENTATION_TARGET_FILE "${REPOSITORY_SOURCE_DIR}/../.build/specifications/common-lexical-specification/index.html")
add_custom_command(OUTPUT ${DOCUMENTATION_TARGET_FILE}
                   COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "${DOCUMENTATION_SOURCE_FILE} => ${DOCUMENTATION_TARGET_FILE}"
                   DEPENDS ${MyProjectName}.Tools.TemplateEngine ${DOCUMENTATION_SOURCE_FILE} ${DOCUMENTATION_DEPENDENCIES})
add_custom_target(Website.Specifications.CommonLexicalSpecification ALL DEPENDS ${DOCUMENTATION_TARGET_FILE})
set_target_properties(Website.Specifications.CommonLexicalSpecification PROPERTIES FOLDER "Website")
