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

macro(BeginFileCopy target)

  if(NOT ${ARGC} EQUAL 1)
    message(FATAL_ERROR "BeginFileCopy: invalid number of arguments")
  endif()
  
  # Initialize the stack if it is not initialized.
  if (NOT g_fileCopyTargets)
    set(g_fileCopyTargets "")
  endif()
  
  # Push the file copy target on the stack of file copy targets.
  list(APPEND g_fileCopyTargets ${target}) 
  
  # Dual list of source and target files to copy.
  set(${target}.copyFiles.sources "")
  set(${target}.copyFiles.targets "")

endmacro()

macro(EndFileCopy)

  if(NOT ${ARGC} EQUAL 0)
    message(FATAL_ERROR "EndFileCopy: invalid number of arguments")
  endif()
  
  list(GET g_fileCopyTargets -1 target)

  list(LENGTH ${target}.copyFiles.sources l)
  math(EXPR l "${l} - 1")
  
  if (l GREATER -1)
    foreach (i RANGE ${l})
      list(GET ${target}.copyFiles.sources ${i} sourceFile)
      list(GET ${target}.copyFiles.targets ${i} targetFile)

      message(STATUS " - ${target} copy file `${sourceFile}` to `${targetFile}")
      
      # Add custom command and custom target.
      string(RANDOM LENGTH 64 randomLength)
      string(UUID generatedTarget NAMESPACE "15340915-a7be-4950-9d26-b789c0eaf106" NAME ${randomLength} TYPE SHA1)
      set(generatedTarget file-copy-${generatedTarget})
      get_filename_component(targetFileDirectory ${targetFile} DIRECTORY) 
      add_custom_command(OUTPUT ${targetFile}
                         COMMAND ${CMAKE_COMMAND} -E make_directory ${targetFileDirectory}
                         COMMAND ${CMAKE_COMMAND} -E copy ${sourceFile} ${targetFile}
                         COMMAND ${CMAKE_COMMAND} -E touch ${targetFile}
                         DEPENDS ${sourceFile}
                         VERBATIM
                         COMMENT "copy file `${sourceFile}` to `${targetFile}`")
      add_custom_target(${generatedTarget} DEPENDS ${targetFile})
      # Add the custom target to the enclosing target. 
      add_dependencies(${target} ${generatedTarget})
      if (${target}.folder)
        set_target_properties(${generatedTarget} PROPERTIES FOLDER ${${target}.folder})
        set_target_properties(${target} PROPERTIES FOLDER ${${target}.folder})
      endif()
    endforeach()
  endif()
  
  list(POP_BACK g_fileCopyTargets)

endmacro()
