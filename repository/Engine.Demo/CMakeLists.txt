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

set(MyDemoName ${MyProjectName}.Engine.Demo)

if (NOT TARGET ${MyDemoName})
  #message(STATUS "${MyDemoName}: ${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled = ${${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled}")
  set(${MyDemoName}.Enabled FALSE)

  # This demo requires at least one rendering backend.
  if (${${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled})
    set(${MyDemoName}.Enabled TRUE)
  endif()
  if (${${MyProjectName}.Visuals.Implementation.Direct3D12.Enabled})
    set(${MyDemoName}.Enabled TRUE)
  endif()
  if (${${MyProjectName}.Visuals.Implementation.Vulkan.Enabled})
    set(${MyDemoName}.Enabled TRUE)
  endif()

  if (${${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled})
	
  BeginProduct(${MyDemoName} executable)

  set(${MyDemoName}.Windows.ResourceFile ${CMAKE_CURRENT_SOURCE_DIR}/Arcadia.Engine.Demo.rc)

	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Demo/Configure.h @ONLY)
  list(APPEND ${MyDemoName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configure.h.i)
  list(APPEND ${MyDemoName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Demo/Configure.h)

  list(APPEND ${MyDemoName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Main.c)

  list(APPEND ${MyDemoName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Audials.c)
  list(APPEND ${MyDemoName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Audials.h)

  list(APPEND ${MyDemoName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Visuals.c)
  list(APPEND ${MyDemoName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Visuals.h)

  list(APPEND ${MyDemoName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configuration.c)
  list(APPEND ${MyDemoName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configuration.h)

  list(APPEND ${MyDemoName}.PrivateLibraries ${MyProjectName}.DDL ${MyProjectName}.Audials.Implementation ${MyProjectName}.Visuals.Implementation)

  EndProduct(${MyDemoName})
  
  endif()
endif()
