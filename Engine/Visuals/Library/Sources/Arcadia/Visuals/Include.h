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

#if !defined(ARCADIA_VISUALS_INCLUDE_H_INCLUDED)
#define ARCADIA_VISUALS_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_VISUALS_PRIVATE")
#undef ARCADIA_VISUALS_PRIVATE
#define ARCADIA_VISUALS_PRIVATE (1)

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Engine/Include.h"
#include "Arcadia/Imaging/Include.h"

#include "Arcadia/Visuals/Backend.h"
#include "Arcadia/Visuals/BackendContext.h"

#include "Arcadia/Visuals/Configuration.h"

#include "Arcadia/Engine/Visuals/Node.h"
#include "Arcadia/Engine/Visuals/NodeFactory.h"

#include "Arcadia/Visuals/Diagnostics.h"

#include "Arcadia/Engine/Visuals/Nodes/CameraNode.h"
#include "Arcadia/Engine/Visuals/Nodes/FrameBufferNode.h"
#include "Arcadia/Engine/Visuals/Nodes/MaterialNode.h"
#include "Arcadia/Engine/Visuals/Nodes/MeshNode.h"
#include "Arcadia/Engine/Visuals/Nodes/PixelBufferNode.h"
#include "Arcadia/Engine/Visuals/Nodes/RenderingContextNode.h"
#include "Arcadia/Engine/Visuals/Nodes/TextureNode.h"
#include "Arcadia/Engine/Visuals/Nodes/ViewportNode.h"

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

#include "Arcadia/Engine/Visuals/CullMode.h"
#include "Arcadia/Visuals/DisplayDevice.h"
#include "Arcadia/Visuals/DisplayMode.h"
#include "Arcadia/Engine/Visuals/TextureAddressMode.h"
#include "Arcadia/Engine/Visuals/TextureFilter.h"
#include "Arcadia/Engine/Visuals/VertexDescriptor.h"
#include "Arcadia/Engine/Visuals/VertexDescriptorBuilder.h"
#include "Arcadia/Engine/Visuals/VertexElementDescriptor.h"
#include "Arcadia/Engine/Visuals/VertexElementSemantics.h"
#include "Arcadia/Engine/Visuals/VertexElementSyntactics.h"
#include "Arcadia/Engine/Visuals/WindingMode.h"

#include "Arcadia/Engine/Visuals/Nodes/RenderScene.h"

#include "Arcadia/Visuals/VPL/ConstantBlock.h"
#include "Arcadia/Visuals/VPL/Field.h"
#include "Arcadia/Visuals/VPL/Scalar.h"
#include "Arcadia/Visuals/VPL/Program.h"
#include "Arcadia/Visuals/VPL/Tree/Include.h"

#undef ARCADIA_VISUALS_PRIVATE
#pragma pop_macro("ARCADIA_VISUALS_PRIVATE")

#endif // ARCADIA_VISUALS_INCLUDE_H_INCLUDED
