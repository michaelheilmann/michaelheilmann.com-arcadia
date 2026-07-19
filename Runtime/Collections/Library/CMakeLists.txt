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

# Create library.
set(this ${MyProjectName}.Collections)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Collections/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Collections/Configure.h.i)

  OnSourceFile(${this} Arcadia/Collections/Include.c)
  OnHeaderFile(${this} Arcadia/Collections/Include.h)
  OnSourceFile(${this} Arcadia/Collections/ArrayList.c)
  OnHeaderFile(${this} Arcadia/Collections/ArrayList.h)
  OnSourceFile(${this} Arcadia/Collections/ArrayDeque.c)
  OnHeaderFile(${this} Arcadia/Collections/ArrayDeque.h)
  OnSourceFile(${this} Arcadia/Collections/ArrayStack.c)
  OnHeaderFile(${this} Arcadia/Collections/ArrayStack.h)
  OnSourceFile(${this} Arcadia/Collections/Collection.c)
  OnHeaderFile(${this} Arcadia/Collections/Collection.h)
  OnSourceFile(${this} Arcadia/Collections/Deque.c)
  OnHeaderFile(${this} Arcadia/Collections/Deque.h)
  OnSourceFile(${this} Arcadia/Collections/HashMap.c)
  OnHeaderFile(${this} Arcadia/Collections/HashMap.h)
  OnSourceFile(${this} Arcadia/Collections/HashSet.c)
  OnHeaderFile(${this} Arcadia/Collections/HashSet.h)
  OnSourceFile(${this} Arcadia/Collections/ImmutableHashMap.c)
  OnHeaderFile(${this} Arcadia/Collections/ImmutableHashMap.h)
  OnSourceFile(${this} Arcadia/Collections/ImmutableList.c)
  OnHeaderFile(${this} Arcadia/Collections/ImmutableList.h)
  OnSourceFile(${this} Arcadia/Collections/ImmutableSet.c)
  OnHeaderFile(${this} Arcadia/Collections/ImmutableSet.h)
  OnSourceFile(${this} Arcadia/Collections/List.c)
  OnHeaderFile(${this} Arcadia/Collections/List.h)
  OnSourceFile(${this} Arcadia/Collections/Map.c)
  OnHeaderFile(${this} Arcadia/Collections/Map.h)
  OnSourceFile(${this} Arcadia/Collections/Set.c)
  OnHeaderFile(${this} Arcadia/Collections/Set.h)
  OnSourceFile(${this} Arcadia/Collections/Stack.c)
  OnHeaderFile(${this} Arcadia/Collections/Stack.h)

  OnSourceFile(${this} Arcadia/Collections/Include.c)
  OnHeaderFile(${this} Arcadia/Collections/Include.h)

  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  set(${this}.Install TRUE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Runtime/Collections")

endif()
