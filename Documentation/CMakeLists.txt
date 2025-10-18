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

# Build "index.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/index.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/index.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
# Build "error.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/error.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/error.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
# Build "news.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/news.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/news.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
# Build "index.css".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/index.css.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/assets/index.css"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
# Build "reset.css".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/reset.css.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/assets/reset.css"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
# Build "cxx-docs.css".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/cxx-doc.css.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/assets/cxx-doc.css"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

add_custom_target(${MyProjectName}.Website.BuildDocs ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/index.html"
                                                                 "${REPOSITORY_SOURCE_DIR}/../.build/error.html"
                                                                 "${REPOSITORY_SOURCE_DIR}/../.build/news.html"
                                                                 "${REPOSITORY_SOURCE_DIR}/../.build/assets/index.css"
                                                                 "${REPOSITORY_SOURCE_DIR}/../.build/assets/reset.css"
                                                                 "${REPOSITORY_SOURCE_DIR}/../.build/assets/cxx-doc.css")
set_target_properties(${MyProjectName}.Website.BuildDocs PROPERTIES FOLDER "Website")

# Build "roadmap.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/roadmap.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/roadmap.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
add_custom_target(Website.RoadmapPage ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/roadmap.html")
set_target_properties(Website.RoadmapPage PROPERTIES FOLDER "Website")

# Build "roadmap-archive.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/roadmap-archive.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/roadmap-archive.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
add_custom_target(Website.RoadmapArchivePage ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/roadmap-archive.html")
set_target_properties(Website.RoadmapArchivePage PROPERTIES FOLDER "Website")

# Build "specifications/data-definition-language/index.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Specifications/DataDefinitionLanguage/index.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/specifications/data-definition-language/index.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
add_custom_target(Website.Specifications.DataDefinitionLanguage ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/specifications/data-definition-language/index.html")
set_target_properties(Website.Specifications.DataDefinitionLanguage PROPERTIES FOLDER "Website")

# Build "specifications/common-lexical-specification/index.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Specifications/CommonLexicalSpecification/index.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/specifications/common-lexical-specification/index.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
add_custom_target(Website.Specifications.CommonLexicalSpecification ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/specifications/common-lexical-specification/index.html")
set_target_properties(Website.Specifications.CommonLexicalSpecification PROPERTIES FOLDER "Website")

# Build "Specifications/MIL/index.html".
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Specifications/MIL/index.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/specifications/mil/index.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
add_custom_target(Website.Specifications.Mil ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/specifications/mil/index.html")
set_target_properties(Website.Specifications.Mil PROPERTIES FOLDER "Website")
