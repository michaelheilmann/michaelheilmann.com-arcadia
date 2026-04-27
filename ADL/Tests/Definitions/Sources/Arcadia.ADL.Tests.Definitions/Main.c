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

#include "Arcadia.ADL.Tests.Definitions/Audials/SampleBuffer.h"

#include "Arcadia.ADL.Tests.Definitions/Visuals/Color.h"
#include "Arcadia.ADL.Tests.Definitions/Visuals/Material.h"
#include "Arcadia.ADL.Tests.Definitions/Visuals/Mesh.h"
#include "Arcadia.ADL.Tests.Definitions/Visuals/Model.h"
#include "Arcadia.ADL.Tests.Definitions/Visuals/PixelBuffer.h"
#include "Arcadia.ADL.Tests.Definitions/Visuals/Texture.h"

#include "Arcadia.ADL.Tests.Definitions/DSP/Constant.h"
#include "Arcadia.ADL.Tests.Definitions/DSP/SawtoothWave.h"
#include "Arcadia.ADL.Tests.Definitions/DSP/SineWave.h"
#include "Arcadia.ADL.Tests.Definitions/DSP/WhiteNoise.h"

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Audials_SampleBufferDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_ColorDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_ColorDefinitionTest2)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_PixelBufferDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_PixelBufferDefinitionTest2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_PixelBufferDefinitionTest3)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_TextureDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_MaterialDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_MaterialDefinitionTest2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_MaterialDefinitionTest3)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_MeshDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_Visuals_ModelDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_DSP_ConstantDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_DSP_SawtoothWaveDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_DSP_SineWaveDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_DSP_SineWaveDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&Arcadia_ADL_Tests_DSP_WhiteNoiseDefinitionTest1)) {
    return EXIT_FAILURE;
  }
  //
  return EXIT_SUCCESS;
}
