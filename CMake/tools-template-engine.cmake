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

# Invoke the template engine with the following arguments.
# - `--source="${sourceFile}"`
# - `--target="${targetFile}"`
# - `--environment="${environmentFile}"`
#
# Furthermore
# - `${target}` is a target to which `${targetFile}` is added as a dependency to.
# - `${folder}` is only used in Visual Studio and can be left unspecified.
#    It is stored in `${target}.folder`. If specified then it will add generated vcxproj files in that folder in the IDE.

macro(BeginTemplateEngine target folder)

  if(NOT ${ARGC} EQUAL 2)
    message(FATAL_ERROR "BeginTemplateEngine: invalid number of arguments")
  endif()
  
  # Initialize the stack if it is not initialized.
  if (NOT g_templateEngineTargets)
    set(g_templateEngineTargets "")
  endif()
  
  # Push the file copy target on the stack of file copy targets.
  list(APPEND g_templateEngineTargets ${target})
  
  # File copy support.
  BeginFileCopy(${target})
  
  # Triples source, target, and environment files.
  set(${target}.templateEngine.sources "")
  set(${target}.templateEngine.targets "")
  set(${target}.templateEngine.environments "")
      
  # Store the target folder.
  set(${target}.folder ${folder})

endmacro()

macro(EndTemplateEngine)

  if(NOT ${ARGC} EQUAL 0)
    message(FATAL_ERROR "EndTemplatEngine: invalid number of arguments")
  endif()

  list(GET g_templateEngineTargets -1 target)
  
  list(LENGTH ${target}.templateEngine.sources l)
  math(EXPR l "${l} - 1")
  
  
  add_custom_target(${target})
  
  if (l GREATER -1)
    foreach (i RANGE ${l})
      list(GET ${target}.templateEngine.sources ${i} sourceFile)
      list(GET ${target}.templateEngine.targets ${i} targetFile)
      list(GET ${target}.templateEngine.environments ${i} environmentFile)

      #message(STATUS " - ${target} copy file `${sourceFile}` to `${targetFile}")
      
      # Add custom command and custom target.
      add_custom_command(OUTPUT ${targetFile}
                         COMMAND $<TARGET_FILE:${MyProjectName}.Tools.TemplateEngine> --source="${sourceFile}" --target="${targetFile}" --environment="${environmentFile}"
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                         VERBATIM
                         COMMENT "${sourceFile} / ${environmentFile} => ${targetFile}"
                         DEPENDS ${MyProjectName}.Tools.TemplateEngine ${sourceFile} ${environmentFile})
      set_source_files_properties(${targetFile} PROPERTIES GENERATED 1)
      string(RANDOM LENGTH 64 randomLength)
      string(UUID generatedTarget NAMESPACE "15340915-a7be-4950-9d26-b789c0eaf106" NAME ${randomLength} TYPE SHA1)
      set(generatedTarget template-engine-${generatedTarget})
      
      add_custom_target(${generatedTarget} DEPENDS ${targetFile})
      # Add the custom target to the enclosing target.
      add_dependencies(${target} ${generatedTarget})
      # Set the folder.
      if (${target}.folder)
        set_target_properties(${generatedTarget} PROPERTIES FOLDER ${${target}.folder})
        set_target_properties(${target} PROPERTIES FOLDER ${${target}.folder})
      endif()
    endforeach()
  endif()

  EndFileCopy()
  
  list(POP_BACK g_templateEngineTargets)

endmacro()

macro(OnTemplateEngine sourceFile targetFile environmentFile)

  if(NOT ${ARGC} EQUAL 3)
    message(FATAL_ERROR "OnTemplateEngine: invalid number of arguments")
  endif()

  list(GET g_templateEngineTargets -1 target)
  
  
  list(APPEND ${target}.templateEngine.sources ${sourceFile})
  list(APPEND ${target}.templateEngine.targets ${targetFile})
  list(APPEND ${target}.templateEngine.environments ${environmentFile})

endmacro()
