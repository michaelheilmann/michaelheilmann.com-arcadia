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

set(MyTestName ${MyProjectName}.Tools.Compiler.Tests.Test1)

# Create test executable.
BeginProduct(${MyTestName} test)

# Configuration files.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Configure.h @ONLY)
list(APPEND ${MyTestName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Configure.h.i)
list(APPEND ${MyTestName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Configure.h)

# Source and header files.
list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Main.c)

# Libraries.
list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.Tools.Compiler.Library ${MyProjectName}.DDL)

EndProduct(${MyTestName})
# Copy assets.
add_custom_command(TARGET ${MyTestName} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${${MyTestName}.WorkingDirectory})
# Adjust working directory.
set(${MyTestName}.WorkingDirectory $<TARGET_FILE_DIR:${MyTestName}>)
set_target_properties(${MyTestName} PROPERTIES FOLDER "Tools/Compiler")
