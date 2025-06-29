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
set(${MyProjectName}.Arms.DocFiles)
list(APPEND ${MyProjectName}.Arms.DocFiles "${CMAKE_CURRENT_SOURCE_DIR}/index.html.i")

MyBuildDocs(${MyProjectName} ${MyProjectName}.Arms.BuildDocs "${CMAKE_CURRENT_SOURCE_DIR}" "${REPOSITORY_SOURCE_DIR}/../.build/Arcadia/Arms" "${${MyProjectName}.Arms.DocFiles}")

set_target_properties(${MyProjectName}.Arms.BuildDocs PROPERTIES FOLDER "Arms")
