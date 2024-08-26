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

# Last modified: 2024-08-29

# SUMMARY
# Configure warnings and errors for a static libraries, module libraries, and executables.
# 
# DETAIL
# Configure warnings and errors for a static libraries, module libraries, and executables.
# For GCC:  Turn several warnings into errors.
# For MSVC: Turn several warnings into errors.
#
# PARAM target The target.
macro(ConfigureWarningsAndErrors target)
  if (NOT DEFINED ${target}.Compiler.C)
    message(FATAL_ERROR "please execute DetectCompiler before ConfigureWarningsAndErrors")
  endif()
  if (${${target}.Compiler.C} EQUAL ${${target}.Compiler.C.Gcc})
    target_compile_options(${target} BEFORE PRIVATE "-Werror=implicit-function-declaration")
  endif()

  if(${${target}.Compiler.C} EQUAL ${${target}.Compiler.C.Msvc})
    set(${target}.compile_options "")
    # C4090:  'opertion' : different 'modifier' qualifiers
    list(APPEND ${target}.compile_options "/we4090")
    # C4133: 'function' incompatible types - from 'type1' to 'type2'
    list(APPEND ${target}.compile_options "/we4133")
    # C4020_ 'function': too many actual parameters
    list(APPEND ${target}.compile_options "/we4020")
    # C4013: 'function': undefined; assuming extern returning int
    list(APPEND ${target}.compile_options "/we4013")
    # C4024: 'function': different types for formal and actual parameter 'number'
    list(APPEND ${target}.compile_options "/we4024")
    # C4716: 'function' must return a value
    list(APPEND ${target}.compile_options "/we4716")
    # C4013: 'function' undefined; assuming extern returning int
    list(APPEND ${target}.compile_options "/we4013")
    # C4028: formal parameter 'number' different from declaration
    list(APPEND ${target}.compile_options "/we4028")

    # The quotes around "${${target}.compile_options}" concatenate the list elements to a single string separated by semicolons.
    set_source_files_properties(${${target}.SourceFiles} PROPERTIES COMPILE_OPTIONS "${${target}.compile_options}")
    set_source_files_properties(${${target}.HeaderFiles} PROPERTIES COMPILE_OPTIONS "${${target}.compile_options}")

  endif()

endmacro()
