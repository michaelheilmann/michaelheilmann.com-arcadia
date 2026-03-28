# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

cmake_minimum_required(VERSION 3.29)

set(MyToolName ${MyProjectName}.DDLS.Validator)

if (NOT TARGET ${MyToolName})

  BeginProduct(${MyToolName} executable)

  set(${MyToolName}.Windows.ResourceFile ${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.DDLS.Validator/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.DDLS.Validator/Configure.h @ONLY)
  list(APPEND ${MyToolName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.DDLS.Validator/Configure.h.i)
  OnConfigurationFile(${MyToolName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.DDLS.Validator/Configure.h)

  OnSourceFile(${MyToolName} Arcadia.DDLS.Validator/Main.c)

  list(APPEND ${MyToolName}.PrivateLibraries ${MyProjectName}.DDLS)

  set(${MyToolName}.Install TRUE)

  EndProduct(${MyToolName})

  set_target_properties(${MyToolName} PROPERTIES FOLDER "DDLS")

endif()
