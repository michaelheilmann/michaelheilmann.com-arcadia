# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

cmake_minimum_required(VERSION 3.20)

FetchProduct(${MyProjectName}.Ring2 "${REPOSITORY_SOURCE_DIR}/Ring2/Library" "path to the Ring 2 library directory")

set(MyTestName ${MyProjectName}.Ring2.Tests.Utf8)

# Create test executable.
BeginProduct(${MyTestName} test)

list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring2.Tests.Utf8/Main.c)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring2.Tests.Utf8/readWrite.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring2.Tests.Utf8/readWrite.h)
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring2.Tests.Utf8/read.c)
list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring2.Tests.Utf8/read.h)

list(APPEND ${MyTestName}.Libraries ${MyProjectName}.Ring2 ${MyProjectName}.Arms)

EndProduct(${MyTestName})

set_target_properties(${MyTestName} PROPERTIES FOLDER "Ring2")
