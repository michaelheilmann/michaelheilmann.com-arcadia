# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-12-30

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

set(MyModule Module.Audials)

if (NOT TARGET ${MyModule})
  BeginProduct(${MyModule})

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
    FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the R1 library directory")

    add_library(${MyModule})

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Audials/Configure.h @ONLY)

    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Include.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Include.h)
    list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Audials/Configure.h)

    target_link_libraries(${MyModule} Arcadia.R Arcadia.Arms)

    EndProduct(${MyModule} library)

  endif()

endif()
