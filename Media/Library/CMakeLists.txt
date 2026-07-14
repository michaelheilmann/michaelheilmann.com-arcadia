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

set(this ${MyProjectName}.Media)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Media/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Configure.h.i)

  OnSourceFile(${this} Arcadia/Media/Include.c)
  OnHeaderFile(${this} Arcadia/Media/Include.h)

  OnSourceFile(${this} Arcadia/Media/PixelBuffer.c)
  OnHeaderFile(${this} Arcadia/Media/PixelBuffer.h)
  OnSourceFile(${this} Arcadia/Media/PixelFormat.c)
  OnHeaderFile(${this} Arcadia/Media/PixelFormat.h)
  OnSourceFile(${this} Arcadia/Media/PixelBufferOperation.c)
  OnHeaderFile(${this} Arcadia/Media/PixelBufferOperation.h)
  OnSourceFile(${this} Arcadia/Media/PixelBufferOperations/CheckerboardFill.c)
  OnHeaderFile(${this} Arcadia/Media/PixelBufferOperations/CheckerboardFill.h)
  OnSourceFile(${this} Arcadia/Media/PixelBufferOperations/Fill.c)
  OnHeaderFile(${this} Arcadia/Media/PixelBufferOperations/Fill.h)

  OnSourceFile(${this} Arcadia/Media/SampleBuffer.c)
  OnHeaderFile(${this} Arcadia/Media/SampleBuffer.h)
  OnSourceFile(${this} Arcadia/Media/SampleFormat.c)
  OnHeaderFile(${this} Arcadia/Media/SampleFormat.h)
  OnSourceFile(${this} Arcadia/Media/DSP.c)
  OnHeaderFile(${this} Arcadia/Media/DSP.h)
  OnSourceFile(${this} Arcadia/Media/DSP/SineWave.c)
  OnHeaderFile(${this} Arcadia/Media/DSP/SineWave.h)
  OnSourceFile(${this} Arcadia/Media/DSP/WhiteNoise.c)
  OnHeaderFile(${this} Arcadia/Media/DSP/WhiteNoise.h)

  OnSourceFile(${this} Arcadia/Media/Quantization.c)
  OnHeaderFile(${this} Arcadia/Media/Quantization.h)

  OnSourceFile(${this} Arcadia/Media/VertexBuffer.c)
  OnHeaderFile(${this} Arcadia/Media/VertexBuffer.h)

  OnSourceFile(${this} Arcadia/Media/VertexDescriptorBuilder.c)
  OnHeaderFile(${this} Arcadia/Media/VertexDescriptorBuilder.h)

  OnSourceFile(${this} Arcadia/Media/VertexDescriptor.c)
  OnHeaderFile(${this} Arcadia/Media/VertexDescriptor.h)
  OnSourceFile(${this} Arcadia/Media/VertexDescriptor.module.c)
  OnHeaderFile(${this} Arcadia/Media/VertexDescriptor.module.h)

  OnSourceFile(${this} Arcadia/Media/VertexElementDescriptor.c)
  OnHeaderFile(${this} Arcadia/Media/VertexElementDescriptor.h)

  OnSourceFile(${this} Arcadia/Media/VertexElementSemantics.c)
  OnHeaderFile(${this} Arcadia/Media/VertexElementSemantics.h)
  OnSourceFile(${this} Arcadia/Media/VertexElementSyntactics.c)
  OnHeaderFile(${this} Arcadia/Media/VertexElementSyntactics.h)

  list(APPEND ${this}.Libraries ${MyProjectName}.ADL)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Media")

endif()
