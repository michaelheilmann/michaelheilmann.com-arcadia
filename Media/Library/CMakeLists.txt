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

set(MyModule ${MyProjectName}.Media)

if (NOT TARGET ${MyModule})
  BeginProduct(${MyModule} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Media/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Media/Configure.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Include.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBuffer.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBuffer.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelFormat.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelFormat.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBufferOperation.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBufferOperation.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBufferOperations/CheckerboardFill.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBufferOperations/CheckerboardFill.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBufferOperations/Fill.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/PixelBufferOperations/Fill.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBuffer.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBuffer.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleFormat.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleFormat.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBufferOperation.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBufferOperation.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBufferOperations/SineWave.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBufferOperations/SineWave.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBufferOperations/WhiteNoise.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/SampleBufferOperations/WhiteNoise.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Quantization.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Quantization.h)

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.ADL)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Media")

endif()
