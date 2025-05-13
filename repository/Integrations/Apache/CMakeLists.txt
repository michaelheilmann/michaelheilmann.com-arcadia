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

FetchProduct(${MyProjectName}.Machine "${REPOSITORY_SOURCE_DIR}/Machine/Library" "path to the Machine library directory")

set(MyTargetName Integrations.Apache)

# Add executable.
BeginProduct(${MyTargetName} executable)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Integrations/Apache/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Integrations/Apache/Configure.h @ONLY)
list(APPEND ${MyTargetName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Integrations/Apache/Configure.h.i)
list(APPEND ${MyTargetName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Integrations/Apache/Configure.h)

list(APPEND ${MyTargetName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Integrations/Apache/Main.c)

list(APPEND ${MyTargetName}.Libraries ${MyProjectName}.Machine ${MyProjectName}.Arms)

EndProduct(${MyTargetName})
set_target_properties(${MyTargetName} PROPERTIES OUTPUT_NAME "arcadia")
