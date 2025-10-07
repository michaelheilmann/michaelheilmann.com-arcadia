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

add_subdirectory(Machine)
add_subdirectory(MIL.AST)
add_subdirectory(MIL.Frontend)

add_subdirectory(Integrations)

add_subdirectory(Engine.Demo)

add_subdirectory(Tools.ConcatenateFiles)
add_subdirectory(Tools.CompareFiles)
add_subdirectory(Tools.Compiler)

add_subdirectory(Visuals.Implementation)
add_subdirectory(Audials.Implementation)

add_subdirectory(Tools.IconGenerator)
add_subdirectory(Tools.BannerGenerator)
add_subdirectory(Tools.BitmapFontGenerator)
add_subdirectory(Tools.RyuLookupTablesGenerator)
