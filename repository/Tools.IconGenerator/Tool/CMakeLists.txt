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

set(MyTool ${MyProjectName}.Tools.IconGenerator)

if (NOT TARGET ${MyTool})

  BeginProduct(${MyTool} executable)

  OnConfigurationFile(${MyTool} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Tools/IconGenerator/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Tools/IconGenerator/Configure.h.i)

  OnSourceFile(${MyTool} Tools/IconGenerator/Main.c)

  OnModuleDependency(${MyTool} ${MyProjectName}.PixelBufferIO PRIVATE)
  OnModuleDependency(${MyTool} ${MyProjectName}.Machine PRIVATE)

  EndProduct(${MyTool})

  set_target_properties(${MyTool} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--target=\"\"\"helloworld.ico\"\"\"")

  set_target_properties(${MyTool} PROPERTIES FOLDER "Tools")

endif()
