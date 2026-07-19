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

set(this ${MyProjectName}.Engine.UI)

if (NOT TARGET ${this})

  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/UI/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/UI/Configure.h.i)

  OnSourceFile(${this} Arcadia/Engine/UI/Include.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Include.h)

  OnSourceFile(${this} Arcadia/Engine/UI/Event.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Event.h)
  OnSourceFile(${this} Arcadia/Engine/UI/Node.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Node.h)

  OnSourceFile(${this} Arcadia/Engine/UI/WidgetEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/WidgetEvent.h)
  OnSourceFile(${this} Arcadia/Engine/UI/WidgetNode.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/WidgetNode.h)

  OnSourceFile(${this} Arcadia/Engine/UI/Events/WidgetPositionChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Events/WidgetPositionChangedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/UI/Events/WidgetSizeChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Events/WidgetSizeChangedEvent.h)

  OnSourceFile(${this} Arcadia/Engine/UI/Nodes/CanvasNode.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Nodes/CanvasNode.h)
  OnSourceFile(${this} Arcadia/Engine/UI/Nodes/PanelNode.c)
  OnHeaderFile(${this} Arcadia/Engine/UI/Nodes/PanelNode.h)

  OnModuleDependency(${this} ${MyProjectName}.Math)
  OnModuleDependency(${this} ${MyProjectName}.Engine)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Engine")

endif()
