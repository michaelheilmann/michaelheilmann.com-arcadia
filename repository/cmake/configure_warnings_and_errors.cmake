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

# Last modified: 2024-12-07

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
    set(${target}.CompileOptions "")
    # C4090:  'opertion' : different 'modifier' qualifiers
    list(APPEND ${target}.CompileOptions "/we4090")
    # C4133: 'function' incompatible types - from 'type1' to 'type2'
    list(APPEND ${target}.CompileOptions "/we4133")
    # C4020_ 'function': too many actual parameters
    list(APPEND ${target}.CompileOptions "/we4020")
    # C4013: 'function': undefined; assuming extern returning int
    list(APPEND ${target}.CompileOptions "/we4013")
    # C4024: 'function': different types for formal and actual parameter 'number'
    list(APPEND ${target}.CompileOptions "/we4024")
    # C4716: 'function' must return a value
    list(APPEND ${target}.CompileOptions "/we4716")
    # C4013: 'function' undefined; assuming extern returning int
    list(APPEND ${target}.CompileOptions "/we4013")
    # C4028: formal parameter 'number' different from declaration
    list(APPEND ${target}.CompileOptions "/we4028")

    # C4189: 'identifier' : local variable is initialized but not referenced
    list(APPEND ${target}.CompileOptions "/we4189")
    
    # C4113: 'identifier1' differs in parameter lists from 'identifier2'
    list(APPEND ${target}.CompileOptions "/we4113")
    
    # C4002: 'function' : pointer mismatch for actual parameter 'number'
    list(APPEND ${target}.CompileOptions "/we4002")
    
    # C4047: 'operator' : 'identifier1' differs in levels of indirection from 'identifier2'
    list(APPEND ${target}.CompileOptions "/we4047")
    
    # C4029: declared formal parameter list different from definition
    list(APPEND ${target}.CompileOptions "/we4029")

    # The quotes around "${${target}.CompileOptions}" concatenate the list elements to a single string separated by semicolons.
    set_source_files_properties(${${target}.SourceFiles} PROPERTIES COMPILE_OPTIONS "${${target}.CompileOptions}")
    set_source_files_properties(${${target}.HeaderFiles} PROPERTIES COMPILE_OPTIONS "${${target}.CompileOptions}")

    # warning level 4
    target_compile_options(${target} PRIVATE /W1)

  endif()

endmacro()
