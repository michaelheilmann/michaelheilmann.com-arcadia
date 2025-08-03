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

# Build the documentation.
InvokeTemplateEngine("${CMAKE_CURRENT_SOURCE_DIR}/index.html.tl"
                     "${REPOSITORY_SOURCE_DIR}/../.build/Arcadia/Ring2/index.html"
                     "${CMAKE_CURRENT_SOURCE_DIR}/website.env")
add_custom_target(${MyProjectName}.Ring2.BuildDocs ALL DEPENDS "${REPOSITORY_SOURCE_DIR}/../.build/Arcadia/Ring2/index.html")
set_target_properties(${MyProjectName}.Ring2.BuildDocs PROPERTIES FOLDER "Ring2")
