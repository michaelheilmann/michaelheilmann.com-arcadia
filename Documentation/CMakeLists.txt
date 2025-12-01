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

BeginTemplateEngine(${MyProjectName}.Website.Generate "Website")

  # Build "index.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/index.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/index.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "error.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/error.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/error.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "news.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/news.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/news.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "index.css".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/index.css.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assets/index.css"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "reset.css".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/reset.css.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assets/reset.css"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "cxx-docs.css".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/cxx-doc.css.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/assets/cxx-doc.css"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "roadmap.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/roadmap.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/roadmap.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "roadmap-archive.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/roadmap-archive.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/roadmap-archive.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "imprint.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/imprint.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/imprint.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "data-protection-statement.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/data-protection-statement.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/data-protection-statement.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "specifications/common-lexical-specification/index.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Specifications/CommonLexicalSpecification/index.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/specifications/common-lexical-specification/index.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

  # Build "Specifications/MIL/index.html".
  OnTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/Specifications/MIL/index.html.tl"
                   "${REPOSITORY_SOURCE_DIR}/../.build/specifications/mil/index.html"
                   "${CMAKE_CURRENT_SOURCE_DIR}/website.env")

EndTemplateEngine()

add_subdirectory(Specifications/DDL)
