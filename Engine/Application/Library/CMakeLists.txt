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

set(this ${MyProjectName}.Application)

if (NOT TARGET ${this})

  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Application/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Application/Configure.h.i)

  OnSourceFile(${this} Arcadia/Application/Include.c)
  OnHeaderFile(${this} Arcadia/Application/Include.h)
  OnSourceFile(${this} Arcadia/Application/Application.c)
  OnHeaderFile(${this} Arcadia/Application/Application.h)

  OnModuleDependency(${this} ${MyProjectName}.Engine)
  OnModuleDependency(${this} ${MyProjectName}.PixelBufferIO)
  OnModuleDependency(${this} ${MyProjectName}.Math)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Engine")

endif()
