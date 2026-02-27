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

cmake_minimum_required(VERSION 4.1.3)

set(MyModule ${MyProjectName}.Engine.UI)

if (NOT TARGET ${MyModule})

  BeginProduct(${MyModule} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/UI/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Configure.h.i)
  OnConfigurationFile(${MyModule} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/UI/Configure.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Include.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Event.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Event.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Node.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/WidgetEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/WidgetEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/WidgetNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/WidgetNode.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Events/WidgetPositionChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Events/WidgetPositionChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Events/WidgetSizeChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Events/WidgetSizeChangedEvent.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Nodes/CanvasNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Nodes/CanvasNode.h)

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Math ${MyProjectName}.Engine)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Engine")

endif()
