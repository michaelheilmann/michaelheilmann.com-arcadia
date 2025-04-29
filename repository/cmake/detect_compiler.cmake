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

# Last modified: 2025-04-26

# SUMMARY
# Define an enumeration of MASM compilers and detect the MASM compiler.
#
# DETAIL
# Define an enumeration of MASM compilers and detect the MASM compiler.
# The detailed steps are:
# a) The numeration constants ${target}.Compiler.Masm.(Unknown|Ms) are defined.
#    Each constant is a string of an unique name identifying a C compiler.
# b) The constant ${target}.Compiler.Masm is set to the {target}.Compiler.Masm.* values denoting the detected Masm compiler.
#
# PARAM target The target.
macro(DetectCompilerMasm target)
   # An unknown MASM compiler.
  set(${target}.Compiler.Masm.Unknown 0)
  set(${${target}.Compiler.Masm.Unknown}.Help "<unknown MASM compiler>")

  # MASM.
  set(${target}.Compiler.Masm.Ms 1)
  set(${${target}.Compiler.Masm.Ms}.Help "MASM")

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}.Compiler.Masm)
    set(${target}.Compiler.Masm ${${target}.Compiler.Masm.Unknown})
    set(${target}.Configuration.Compiler.Masm ${${target}.Configuration.Compiler.Masm.Unknown})
  endif()

  # Perform detection.
  if (CMAKE_ASM_MASM_COMPILER)
    enable_language(ASM_MASM)
    set(${target}.Compiler.Masm ${${target}.Compiler.Masm.Ms})
    set(${target}.Configuration.Compiler.Masm ${${target}.Compiler.Masm.Ms})
  endif()
  message( STATUS " - ${target} MASM compiler: ${${${target}.Compiler.Masm}.Help}")
endmacro()

# SUMMARY
# Define an enumeration of C compilers and detect the C compiler.
#
# DETAIL
# Define an enumeration of C compilers and detect the C compiler.
# The detailed steps are:
# a) The enumeration constants ${target}.Compiler.C.(Unknown|Clang|Msvc|Gcc) are defined.
#    Each constant is a string of an unique name identifying a C compiler.
# b) The constant ${target}.Compiler.C is set to the {target}.Compiler.C.* values denoting the detected C compiler.
#
# PARAM target The target.
macro(DetectCompilerC target)
  # An unknown C compiler.
  set(${target}.Compiler.C.Unknown 0)
  set(${${target}.Compiler.C.Unknown}.Help "<unknown C compiler>")

  # CLANG.
  set(${target}.Compiler.C.Clang 1)
  set(${${target}.Compiler.C.Clang}.Help "CLANG")

  # GCC.
  set(${target}.Compiler.C.Gcc 2)
  set(${${target}.Compiler.C.Gcc}.Help "GCC")

  # MSVC.
  set(${target}.Compiler.C.Msvc 3)
  set(${${target}.Compiler.C.Msvc}.Help "MSVC")

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}.Compiler.C)
    set(${target}.Compiler.C ${${target}.Compiler.C.Unknown})
    set(${target}.Configuration.Compiler.C ${${target}.Compiler.C.Unknown})
  endif()

  # Perform detection.
  if (CMAKE_C_COMPILER)
    if (CMAKE_C_COMPILER_ID)
      if (CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
        set(${target}.Compiler.C ${${target}.Compiler.C.Clang})
        set(${target}.Configuration.Compiler.C ${${target}.Compiler.C.Clang})
      endif()
      if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        set(${target}.Compiler.C ${${target}.Compiler.C.Clang})
        set(${target}.Configuration.Compiler.C ${${target}.Compiler.C.Clang})
      endif()
      if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(${target}.Compiler.C ${${target}.Compiler.C.Gcc})
        set(${target}.Configuration.Compiler.C ${${target}.Compiler.C.Gcc})
      endif()
      if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        set(${target}.Compiler.C ${${target}.Compiler.C.Msvc})
        set(${target}.Configuration.Compiler.C ${${target}.Compiler.C.Msvc})
      endif()
    endif()
  endif()
  message( STATUS " - ${target} C compiler: ${${${target}.Compiler.C}.Help}")
endmacro()
