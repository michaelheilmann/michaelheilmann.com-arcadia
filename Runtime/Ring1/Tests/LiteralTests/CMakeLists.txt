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

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms/Library" "path to the ARMS library directory")
FetchProduct(${MyProjectName}.Ring1 "${REPOSITORY_SOURCE_DIR}/Arcadia.Ring1/Library" "path to the Arcadia.Ring1 library directory")

set(MyTestName ${MyProjectName}.Ring1.Tests.LiteralTests)

# Create test executable.
add_executable(${MyTestName})
BeginProduct(${MyTestName})

add_test(NAME ${MyTestName} COMMAND ${MyTestName} WORKING_DIRECTORY $<TARGET_FILE_DIR:${MyTestName}>)

list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Ring1.Tests.LiteralTests/Main.c)

target_link_libraries(${MyTestName} ${MyProjectName}.Ring1 ${MyProjectName}.Arms)

set_target_properties(${MyTestName} PROPERTIES FOLDER "Arcadia")

EndProduct(${MyTestName} executable)
