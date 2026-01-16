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

set(MyModule ${MyProjectName}.Visuals)

if (NOT TARGET ${MyModule})

  BeginProduct(${MyModule} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configure.h.i)
  OnConfigurationFile(${MyModule} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Configure.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/CameraNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/CameraNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/FrameBufferNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/FrameBufferNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/Node.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MeshNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MeshNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/ModelNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/ModelNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/PixelBufferNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/PixelBufferNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/RenderingContextNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/RenderingContextNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/ViewportNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/ViewportNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/TextureNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/TextureNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MaterialNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MaterialNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/RenderScene.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/RenderScene.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationQuitRequestedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationQuitRequestedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasActivationStateChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasActivationStateChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasDpiChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasDpiChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasSizeChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasSizeChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKey.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKey.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKey.i)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyAction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyAction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonAction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonAction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerAction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerAction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowClosedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowClosedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowPositionChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowPositionChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowSizeChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowSizeChangedEvent.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Backend.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Backend.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/BackendContext.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/BackendContext.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/SceneNodeFactory.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/SceneNodeFactory.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Diagnostics.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Diagnostics.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/Command.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/Command.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/EmitCommand.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/EmitCommand.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Icon.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Icon.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Window.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Window.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindowBackend.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindowBackend.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configuration.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configuration.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/CullMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/CullMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DepthCompareFunction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DepthCompareFunction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/FillMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/FillMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureAddressMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureAddressMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureFilter.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureFilter.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSemantics.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSemantics.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSyntactics.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSyntactics.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindingMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindingMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexDescriptor.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexDescriptor.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexDescriptor.module.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexDescriptor.module.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexDescriptorBuilder.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexDescriptorBuilder.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementDescriptor.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementDescriptor.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Include.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayDevice.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayDevice.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/ConstantBlock.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/ConstantBlock.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Field.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Field.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Program.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Program.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/VariableScalar.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/VariableScalar.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Tree/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Tree/Include.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Tree/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Tree/Node.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Tree/BinaryExprNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VPL/Tree/BinaryExprNode.h)


  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Math ${MyProjectName}.Engine ${MyProjectName}.Imaging)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Engine")

endif()
