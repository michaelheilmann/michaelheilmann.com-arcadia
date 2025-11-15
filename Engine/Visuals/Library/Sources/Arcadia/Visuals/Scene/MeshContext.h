// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_VISUALS_SCENE_MESHCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_SCENE_MESHCONTEXT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Math/Include.h"
typedef struct Arcadia_Visuals_BackendContext Arcadia_Visuals_BackendContext;

// This represents state common to all meshes.
// It is set by a) the viewport and b) the camera and passed to each mesh.
// It contains an up-to-date constant buffer which a mesh shall bind to the "viewer" block.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Scene.MeshContext", Arcadia_Visuals_Scene_MeshContext,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Scene_MeshContext {
  Arcadia_Object parent;
  
  void (*setBackendContext)(Arcadia_Thread*, Arcadia_Visuals_Scene_MeshContext*, Arcadia_Visuals_BackendContext*);
  void (*render)(Arcadia_Thread*, Arcadia_Visuals_Scene_MeshContext*);
  
  struct {
    // Default is 193.
    float red;
    // Default is 216.
    float green;
    // Default is 195.
    float blue;
    // Default is 255.
    float alpha;
  } viewportClearColor;
  
  /// The default value is 1.
  float viewportClearDepth;
  
  /// The relative viewport rectangle.
  /// The default value is 0, 0, 1, 1.
  struct {
    Arcadia_Real32Value left, bottom, right, top;
  } relativeViewportRectangle;
  
  /// The size of the canvas.
  /// The default value is 320 x 240.
  struct {
    Arcadia_Real32Value width, height;
  } canvasSize;
  
  /// The view matrix.
  /// The default value is the identity matrix.
  Arcadia_Math_Matrix4Real32* viewToProjectionMatrix;

  /// The projection matrix.
  /// The default value is the identity matrix.
  Arcadia_Math_Matrix4Real32* worldToViewMatrix;
};

void
Arcadia_Visuals_Scene_MeshContext_setBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self,
    Arcadia_Visuals_BackendContext* backendContext
  );

void
Arcadia_Visuals_Scene_MeshContext_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshContext* self
  );

#endif // ARCADIA_VISUALS_SCENE_MESHCONTEXT_H_INCLUDED
