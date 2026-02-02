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

#include "Arcadia.ADL.Tests.Definitions/Model.h"

#include "Arcadia/ADL/Include.h"

static void
makeMaterial
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions
  )
{
  {
    static const char* DDL =
      "{\n"
      "  type : \"Color\",\n"
      "  name : \"MyGame.Colors.MyBlack\",\n"
      "  red : 0,\n"
      "  green : 0,\n"
      "  blue : 0,\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
  {
    static const char* DDL =
      "{\n"
      "  type : \"Color\",\n"
      "  name : \"MyGame.Colors.MyWhite\",\n"
      "  red : 255,\n"
      "  green : 255,\n"
      "  blue : 255,\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
  {
    static const char* DDL =
      "{\n"
      "  type  : \"PixelBufferOperations.CheckerboardFillOperation\",\n"
      "  name  : \"MyGame.PixelBufferOperations.MyPixelBufferFillOperation\",\n"
      "  checkerWidth : 32,\n"
      "  checkerHeight : 32,\n"
      "  firstCheckerColor : \"MyGame.Colors.MyWhite\",\n"
      "  secondCheckerColor : \"MyGame.Colors.MyBlack\",\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
  {
    static const char* DDL =
      "{\n"
      "  type  : \"PixelBuffer\",\n"
      "  name  : \"MyGame.PixelBuffers.MyPixelBuffer\",\n"
      "  width: 256,\n"
      "  height: 256,\n"
      "  operations : [\n"
      "    \"MyGame.PixelBufferOperations.MyPixelBufferFillOperation\",\n"
      "  ],\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
  {
    static const char* DDL =
      "{\n"
      "  type  : \"Texture\",\n"
      "  name  : \"MyGame.Textures.MyTexture\",\n"
      "  pixelBuffer : \"MyGame.PixelBuffers.MyPixelBuffer\",\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
  {
    static const char* DDL =
      "{\n"
      "  type : \"Material\",\n"
      "  name : \"MyGame.Materials.MyMaterial\",\n"
      "  materialType : \"Blinn-Phong\",/* Allowed Values: 'Blinn-Phong'. */\n"
      "  ambientColorSource : \"Texture\",/* Allowed values: 'Mesh', 'Vertex', or 'Texture'. */\n"
      "  ambientColorTexture : \"MyGame.Textures.MyTexture\",\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
}

static void
makeMesh
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions
  )
{
  {
    static const char *DDL =
      "{\n"
      "  type : \"Mesh\",\n"
      "  name : \"MyGame.Meshes.MyMesh\",\n"
      "  ambientColor : \"MyGame.Colors.MyWhite\",\n"
      "  vertexPositions : [],\n"
      "  vertexAmbientColors : [],\n"
      "  vertexAmbientColorTextureCoordinates: [],\n"
      "}\n"
      ;
    Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  }
}

void
testModelDefinition1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ADL_Context* context = Arcadia_ADL_Context_getOrCreate(thread);
  Arcadia_ADL_Definitions* definitions = Arcadia_ADL_Definitions_create(thread);
  makeMaterial(thread, context, definitions);
  makeMesh(thread, context, definitions);
  static const char *DDL =
    "{\n"
    "  type : \"Model\",\n"
    "  name : \"Models.MyModel\",\n"
    "  mesh : \"MyGame.Meshes.MyMesh\",\n"
    "  material : \"MyGame.Materials.MyMaterial\",\n"
    "}\n"
    ;
  Arcadia_ADL_Context_readFromString(thread, context, definitions, Arcadia_String_createFromCxxString(thread, DDL), Arcadia_BooleanValue_False);
  Arcadia_ADL_Definitions_link(thread, definitions);
}
