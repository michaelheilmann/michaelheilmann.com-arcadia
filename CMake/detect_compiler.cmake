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



# An unknown ASM compiler.
set(Arcadia_Compiler_ASM_Unknown 0)

# The "MASM" ASM compiler.
set(Arcadia_Compiler_ASM_MASM 1)

# The "NASM" ASM compiler.
set(Arcadia_Compiler_ASM_NASM 2)

function(Arcadia_DetectCompilerASM result)
  if (CMAKE_ASM_MASM_COMPILER)
    enable_language(ASM_MASM)
    set(${result} ${Arcadia_Compiler_ASM_MASM} PARENT_SCOPE)
  elseif(CMAKE_ASM_NASM_COMPILER)
    enable_language_(ASM_NASM)
    set(${result} ${Arcadia_Compiler_ASM_NASM} PARENT_SCOPE)
  else()
    set(${result} ${Arcadia_Compiler_ASM_Unknown} PARENT_SCOPE)
  endif()
endfunction()



# An unknown C compiler.
set(Arcadia_Compiler_C_Unknown 0)
#set(${${target}.Compiler.C.Unknown}.Help "<unknown C compiler>")

# The "Clang" C compiler.
set(Arcadia_Compiler_C_Clang 1)

# The "GCC" C compiler.
set(Arcadia_Compiler_C_GCC 2)

# The "MSVC" C compiler.
set(Arcadia_Compiler_C_MSVC 3)

function(Arcadia_DetectCompilerC result)
  if (CMAKE_C_COMPILER)
    if (CMAKE_C_COMPILER_ID)
      if (CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
        set(${result} ${Arcadia_Compiler_C_Clang} PARENT_SCOPE)
      elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        set(${result} ${Arcadia_Compiler_C_Clang} PARENT_SCOPE)
      elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(${result} ${Arcadia_Compiler_C_GCC} PARENT_SCOPE)
      elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        set(${result} ${Arcadia_Compiler_C_MSVC} PARENT_SCOPE)
      else()
        set(${result} ${Arcadia_Compiler_C_Unknown} PARENT_SCOPE)
      endif()
    else()
      set(${result} ${Arcadia_Compiler_C_Unknown} PARENT_SCOPE)
    endif()
  else()
    set(${result} ${Arcadia_Compiler_C_Unknown} PARENT_SCOPE)
  endif()
endfunction()



# SUMMARY
# Define an enumeration of MASM compilers and detect the MASM compiler.
#
# DETAIL
# Define an enumeration of MASM compilers and detect the MASM compiler.
# The detailed steps are:
# a) The numeration constants ${target}_Compiler_ASM_(Unknown|MASM|NAMS) are defined.
#    Each constant is a string of an unique name identifying a C compiler.
# b) The constant ${target}_Compiler_ASM is set to one of the {target}_Compiler_ASM_* values denoting the detected Masm compiler.
#
# PARAM target The target.
macro(DetectCompilerASM target)
   # An unknown ASM compiler.
  set(${target}_Compiler_ASM_Unknown ${Arcadia_Compiler_ASM_Unknown})
  # MASM.
  set(${target}_Compiler_ASM_MASM ${Arcadia_Compiler_ASM_MASM})
  # NASM.
  set(${target}_Compiler_ASM_NASM ${Arcadia_Compiler_ASM_NASM})

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}_Compiler_ASM)
    Arcadia_DetectCompilerASM(${target}_Compiler_ASM)
  endif()

  set(VERBOSE TRUE)
  
  if (VERBOSE) 
    if (${target}_Compiler_ASM STREQUAL ${target}_Compiler_ASM_Unknown)
      message( STATUS " - ${target} ASM compiler: unknown")
    elseif (${target}_Compiler_ASM STREQUAL ${target}_Compiler_ASM_MASM)
      message( STATUS " - ${target} ASM compiler: MASM")
    elseif (${target}_Compiler_ASM STREQUAL ${target}_Compiler_ASM_NASM)
      message( STATUS " - ${target} ASM compiler: NASM")
    else()
      message(FATAL_ERROR "<internal error>") 
    endif()
  endif()

endmacro()

# SUMMARY
# Define an enumeration of C compilers and detect the C compiler.
#
# DETAIL
# Define an enumeration of C compilers and detect the C compiler.
# The detailed steps are:
# a) The enumeration constants ${target}_Compiler_C_(Unknown|Clang|MSVC|GCC) are defined.
#    Each constant is a string of an unique name identifying a C compiler.
# b) The constant ${target}_Compiler_C is set to one of the the {target}_Compiler_C_* values denoting the detected C compiler.
#
# PARAM target The target.
macro(DetectCompilerC target)
  # An unknown C compiler.
  set(${target}_Compiler_C_Unknown ${Arcadia_Compiler_C_Unknown})

  # CLANG.
  set(${target}_Compiler_C_Clang ${Arcadia_Compiler_C_Clang})

  # GCC.
  set(${target}_Compiler_C_GCC ${Arcadia_Compiler_C_GCC})

  # MSVC.
  set(${target}_Compiler_C_MSVC ${Arcadia_Compiler_C_MSVC})

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}_Compiler_C)
    Arcadia_DetectCompilerC(${target}_Compiler_C)
  endif()
  
  set(VERBOSE TRUE)
  
  if (VERBOSE) 
    if (${target}_Compiler_C STREQUAL ${target}_Compiler_C_Unknown)
      message( STATUS " - ${target} C compiler: unknown")
    elseif (${target}_Compiler_C STREQUAL ${target}_Compiler_C_Clang)
      message( STATUS " - ${target} C compiler: Clang")
    elseif (${target}_Compiler_C STREQUAL ${target}_Compiler_C_GCC)
      message( STATUS " - ${target} C compiler: GCC")
    elseif (${target}_Compiler_C STREQUAL ${target}_Compiler_C_MSVC)
      message( STATUS " - ${target} C compiler: MSVC")
    else()
      message(FATAL_ERROR "<internal error>") 
    endif()
  endif()

endmacro()
