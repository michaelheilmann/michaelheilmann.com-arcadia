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

set(MyLibraryName ${MyProjectName}.Media)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Media/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Media/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Media/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/Media/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/Media/PixelBuffer.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/PixelBuffer.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/PixelFormat.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/PixelFormat.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/PixelBufferOperation.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/PixelBufferOperation.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/PixelBufferOperations/CheckerboardFill.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/PixelBufferOperations/CheckerboardFill.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/PixelBufferOperations/Fill.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/PixelBufferOperations/Fill.h)

  OnSourceFile(${MyLibraryName} Arcadia/Media/SampleBuffer.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/SampleBuffer.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/SampleFormat.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/SampleFormat.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/SampleBufferOperation.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/SampleBufferOperation.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/SampleBufferOperations/SineWave.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/SampleBufferOperations/SineWave.h)
  OnSourceFile(${MyLibraryName} Arcadia/Media/SampleBufferOperations/WhiteNoise.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/SampleBufferOperations/WhiteNoise.h)

  OnSourceFile(${MyLibraryName} Arcadia/Media/Quantization.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Media/Quantization.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.ADL)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Media")

endif()
