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

include(${CMAKE_CURRENT_LIST_DIR}/configure_warnings_and_errors.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_compiler.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_instruction_set_architecture.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_operating_system.cmake)

# Begin a product (library, executable, or test).
# The following variables are defined
# - ${target}.SourceFiles      List of C/C++ source files
# - ${target}.HeaderFiles      List of C/C++ header files
# - ${target}.AssetFiles       List of asset files
# - ${target}.WorkingDirectory for tests and executables only: the working directory. Defaults to ${CMAKE_CURRENT_BINARY_DIR}.
# - ${target}.Libaries         List of libraries
# - ${target}.PrivateLibaries  List of libraries only visible from within ${target}
# - ${target}.Enabled          TRUE if the product should be built. FALSE otherwise. Defaults to TRUE.
#   The files are all copied (without their folder) to the binary output directories.
macro(BeginProduct target type)
  set(${target}.SourceFiles "")
  set(${target}.HeaderFiles "")
  set(${target}.ConfigurationFiles "")
  set(${target}.AssetFiles "")
  set(${target}.Libraries "")
  set(${target}.PrivateLibraries "")
  set(${target}.IncludeDirectories "")
  set(${target}.Enabled TRUE)
  DetectCompilerC(${target})
  DetectOperatingSystem(${target})
  DetectInstructionSetArchitecture(${target})

  # Store the product type.
  set(${target}.Type ${type})

endmacro()

macro(EndProduct target)
  if (${${target}.Enabled})
    if (${${target}.Type} STREQUAL library)
      add_library(${target})
    elseif (${${target}.Type} STREQUAL executable)
      set(${target}.WorkingDirectory ${CMAKE_CURRENT_BINARY_DIR})
      add_executable(${target})
    elseif (${${target}.Type} STREQUAL test)
      set(${target}.WorkingDirectory ${CMAKE_CURRENT_BINARY_DIR})
      add_executable(${target})
    else()
      message(FATAL_ERROR "unknown/unsupported product type")
    endif()

    ConfigureWarningsAndErrors(${target})

    target_sources(${target} PRIVATE ${${target}.ConfigurationFiles} ${${target}.SourceFiles} ${${target}.HeaderFiles})

    source_group(TREE ${CMAKE_CURRENT_BINARY_DIR} FILES ${${target}.ConfigurationFiles})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${target}.HeaderFiles})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${${target}.SourceFiles})

    set_property(TARGET ${target} PROPERTY C_STANDARD 17)
    
    target_link_libraries(${target} PRIVATE ${${target}.PrivateLibraries})
    target_link_libraries(${target} PUBLIC ${${target}.Libraries})

    if (${${target}.Type} STREQUAL library)

      target_include_directories(${target} PRIVATE ${${target}.IncludeDirectories})
      target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
      target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/Sources)

    elseif (${${target}.Type} STREQUAL executable)

      target_include_directories(${target} PRIVATE ${${target}.IncludeDirectories})
      target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
      target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Sources)

      set_property(TARGET ${target} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${${target}.WorkingDirectory})

    elseif (${${target}.Type} STREQUAL test)
    
      target_include_directories(${target} PRIVATE ${${target}.IncludeDirectories})
      target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources)
      target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Sources)
      
      # Possible alternative is `add_test(NAME ${target} COMMAND ${target} WORKING_DIRECTORY $<TARGET_FILE_DIR:${target}>)`.
      add_test(NAME ${target} COMMAND ${target} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
      set_property(TARGET ${target} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${${target}.WorkingDirectory})
      
      # `add_test` must already have been invoked for `set_test_properties` to be successful.
      set_tests_properties(${target} PROPERTIES WORKING_DIRECTORY ${${target}.WorkingDirectory})
    
    else()
      message(FATAL_ERROR "unknown/unsupported product type")
    endif()
  endif()

endmacro()

macro(FetchProduct target directory help)
  if (NOT TARGET ${target})
      set(__${target}.SourceDir "${directory}" CACHE STRING ${help})
      get_filename_component(__${target}.SourceDir "${__${target}.SourceDir}"
                              REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
      #message(STATUS "fetching ${__${target}.SourceDir}")
      FetchContent_Declare(__${target} SOURCE_DIR ${__${target}.SourceDir})
      FetchContent_MakeAvailable(__${target})
  endif()
endmacro()

macro(CopyProductAssets target folder sourceDirectory targetDirectory)
 #message(STATUS "=> target directory ${targetDirectory}")
 file(GLOB_RECURSE sourceFiles RELATIVE ${sourceDirectory} "${sourceDirectory}/*")
 set(targetFiles "")
 foreach (sourceFile ${sourceFiles})
   set(targetFile ${sourceFile})
   #message(STATUS "=> source file: ${sourceDirectory}/${sourceFile}")
   #message(STATUS "=> target file: ${targetDirectory}/${targetFile}")
   get_filename_component(targetFileDirectory ${targetDirectory}/${targetFile} DIRECTORY)
   #message(STATUS "=> target file directory: ${targetFileDirectory}")
   add_custom_command(OUTPUT ${targetDirectory}/${targetFile}
                      COMMAND ${CMAKE_COMMAND} -E make_directory ${targetFileDirectory}
                      COMMAND ${CMAKE_COMMAND} -E copy ${sourceDirectory}/${sourceFile} ${targetDirectory}/${targetFile}
                      COMMAND ${CMAKE_COMMAND} -E touch ${targetDirectory}/${targetFile}
                      DEPENDS ${sourceDirectory}/${sourceFile}
                      VERBATIM
                      COMMENT "copy file `${sourceDirectory}/${sourceFile}` to `${targetDirectory}/${targetFile}`")
   list(APPEND targetFiles "${targetFileDirectory}" "${targetDirectory}/${targetFile}")
 endforeach()

 add_custom_target(${target} ALL DEPENDS ${targetFiles})
 set_target_properties(${target} PROPERTIES FOLDER ${folder})

endmacro()
