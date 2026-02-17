// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

#if !defined(ARCADIA_ENGINE_VISUALS_INCLUDE2_H_INCLUDED)
#define ARCADIA_ENGINE_VISUALS_INCLUDE2_H_INCLUDED

#include "Arcadia/Engine/Visuals/Backend.h"
#include "Arcadia/Engine/Visuals/BackendContext.h"

#include "Arcadia/Engine/Visuals/Configuration.h"

#include "Arcadia/Engine/Visuals/CullMode.h"

#include "Arcadia/Engine/Visuals/DepthCompareFunction.h"

#include "Arcadia/Engine/Visuals/FillMode.h"

#include "Arcadia/Engine/Visuals/Icon.h"

#include "Arcadia/Engine/Visuals/Node.h"
#include "Arcadia/Engine/Visuals/NodeFactory.h"
#include "Arcadia/Engine/Visuals/Nodes/CameraNode.h"
#include "Arcadia/Engine/Visuals/Nodes/EnterPassNode.h"
#include "Arcadia/Engine/Visuals/Nodes/FrameBufferNode.h"
#include "Arcadia/Engine/Visuals/Nodes/MaterialNode.h"
#include "Arcadia/Engine/Visuals/Nodes/MeshNode.h"
#include "Arcadia/Engine/Visuals/Nodes/ModelNode.h"
#include "Arcadia/Engine/Visuals/Nodes/PixelBufferNode.h"
#include "Arcadia/Engine/Visuals/Nodes/RenderScene.h"
#include "Arcadia/Engine/Visuals/Nodes/TextureNode.h"
#include "Arcadia/Engine/Visuals/Nodes/ViewportNode.h"

#include "Arcadia/Engine/Visuals/TextureAddressMode.h"
#include "Arcadia/Engine/Visuals/TextureFilter.h"

#include "Arcadia/Engine/Visuals/VertexDescriptor.h"
#include "Arcadia/Engine/Visuals/VertexDescriptorBuilder.h"
#include "Arcadia/Engine/Visuals/VertexElementDescriptor.h"
#include "Arcadia/Engine/Visuals/VertexElementSemantics.h"
#include "Arcadia/Engine/Visuals/VertexElementSyntactics.h"
#include "Arcadia/Engine/Visuals/VPL/ConstantBlock.h"
#include "Arcadia/Engine/Visuals/VPL/Field.h"
#include "Arcadia/Engine/Visuals/VPL/Scalar.h"
#include "Arcadia/Engine/Visuals/VPL/Program.h"
#include "Arcadia/Engine/Visuals/VPL/Tree/Include.h"

#include "Arcadia/Engine/Visuals/WindingMode.h"

#include "Arcadia/Engine/Visuals/Window.h"
#include "Arcadia/Engine/Visuals/WindowBackend.h"

//{
// 
#include "Arcadia/Engine/Visuals/Diagnostics.h"

#include "Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.h"

#include "Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.h"
#include "Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.h"
#include "Arcadia/Engine/Visuals/Events/CanvasEvent.h"
#include "Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.h"
#include "Arcadia/Engine/Visuals/Events/WindowClosedEvent.h"
#include "Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.h"
#include "Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.h"

#include "Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.h"
#include "Arcadia/Engine/Visuals/Events/MouseButtonEvent.h"
#include "Arcadia/Engine/Visuals/Events/MousePointerEvent.h"

#include "Arcadia/Engine/Visuals/DisplayDevice.h"
#include "Arcadia/Engine/Visuals/DisplayMode.h"
//}

#endif // ARCADIA_ENGINE_VISUALS_INCLUDE2_H_INCLUDED
