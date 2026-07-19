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

# Create a library.
set(this ${MyProjectName}.ARMS)
if (NOT TARGET ${this})

  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/ARMS/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/ARMS/Configure.h.i)

  OnSourceFile(${this} Arcadia/ARMS/Include.c)
  OnHeaderFile(${this} Arcadia/ARMS/Include.h)
  OnSourceFile(${this} Arcadia/ARMS/ARMS.c)
  OnHeaderFile(${this} Arcadia/ARMS/ARMS.h)
  OnSourceFile(${this} Arcadia/ARMS/MemoryManager.c)
  OnHeaderFile(${this} Arcadia/ARMS/MemoryManager.h)
  OnSourceFile(${this} Arcadia/ARMS/SizeType.c)
  OnHeaderFile(${this} Arcadia/ARMS/SizeType.h)
  OnSourceFile(${this} Arcadia/ARMS/Natural8Type.c)
  OnHeaderFile(${this} Arcadia/ARMS/Natural8Type.h)
  OnSourceFile(${this} Arcadia/ARMS/StatusType.c)
  OnHeaderFile(${this} Arcadia/ARMS/StatusType.h)
  OnSourceFile(${this} Arcadia/ARMS/TypeName.c)
  OnHeaderFile(${this} Arcadia/ARMS/TypeName.h)
  OnSourceFile(${this} Arcadia/ARMS/NotifyDestroy.c)
  OnHeaderFile(${this} Arcadia/ARMS/NotifyDestroy.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/MemoryManager.private.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/MemoryManager.private.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/DefaultMemoryManager.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/DefaultMemoryManager.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/SlabMemoryManager.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/SlabMemoryManager.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/Common.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/Common.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/Statistics.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/Statistics.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/Tag.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/Tag.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/TypeName.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/TypeName.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/ReferenceCounter.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/ReferenceCounter.h)
  OnSourceFile(${this} Arcadia/ARMS/Internal/NotifyDestroy.c)
  OnHeaderFile(${this} Arcadia/ARMS/Internal/NotifyDestroy.h)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  set(${this}.Install TRUE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Runtime/ARMS")

endif()
