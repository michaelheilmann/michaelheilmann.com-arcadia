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

# This is the canonical method of disabling in-source builds.
if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  message( FATAL_ERROR
           "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
           "Please remove any files from the source directory which this call might have generated (in particular, CMakeCache.txt and CMakeFiles)." )
endif()

include(${CMAKE_CURRENT_LIST_DIR}/configure_warnings_and_errors.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_compiler.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_byte_order.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_instruction_set_architecture.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_operating_system.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/tool-file-copy.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/tools-template-engine.cmake)

enable_testing()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)
include(CheckLanguage)

check_language(C)
if (CMAKE_C_COMPILER)
  enable_language(C)
endif()

check_language(ASM_MASM)
if (CMAKE_ASM_MASM_COMPILER)
  enable_language(ASM_MASM)
endif()

# Begin a product (library, executable, or test).
#
# - if ${type} is `library`, `executable`, or `test`:
#   The following variables are defined
#   - ${target}.SourceFiles      List of C/C++ source files. Initially defined but empty
#   - ${target}.HeaderFiles      List of C/C++ header files. Initially defined but empty
#   - ${target}.AssetFiles       List of asset files. Initially defined but empty
#   - ${target}.InlayFiles       List of inlay files. Initially defined but empty
#   - ${target}.WorkingDirectory for tests and executables only: the working directory. Defaults to ${CMAKE_CURRENT_BINARY_DIR}.
#   - ${target}.Libaries         List of libraries. Initially defined but empty
#   - ${target}.PrivateLibaries  List of libraries only visible from within ${target}. Initially defined but empty
#   - ${target}.Enabled          TRUE if the product should be built. FALSE otherwise. Defaults to TRUE.
#
# - if ${type} is `template`   
macro(BeginProduct target type)
  set(${target}.SourceFiles "")
  set(${target}.HeaderFiles "")
  set(${target}.InlayFiles "")
  set(${target}.ConfigurationTemplateFiles "")
  set(${target}.ConfigurationFiles "")
  set(${target}.AssetFiles "")
  set(${target}.AssemblerFiles "")
  set(${target}.Libraries "")
  set(${target}.PrivateLibraries "")
  set(${target}.IncludeDirectories "")
  set(${target}.Enabled TRUE)
  DetectCompilerC(${target})
  DetectCompilerMasm(${target})
  DetectByteOrder(${target})
  DetectOperatingSystem(${target})
  DetectInstructionSetArchitecture(${target})
  
  BeginFileCopy(${target})

  # Store the product type.
  set(${target}.Type ${type})

endmacro()

# Determine if a string haystack starts with a string needle.
# Return the result in a variable result.
# Usage:
#   string_starts_with(result ${haystack} ${needle})
#   if (${result})
#     ...
#   endif()
function(string_starts_with result haystack needle)
  string(FIND "${haystack}" "${needle}" index)
  if("${index}" EQUAL 0)
    set(${result} 1 PARENT_SCOPE)
  else()
    set(${result} 0 PARENT_SCOPE)
  endif()
endfunction()

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
    
    # Combine all file lists into a single list.
    set (allFiles "")
    foreach (e ${${target}.HeaderFiles})
      list(APPEND allFiles ${e})
    endforeach()
    foreach (e ${${target}.SourceFiles})
      list(APPEND allFiles ${e})
    endforeach()
    foreach (e ${${target}.InlayFiles})
      list(APPEND allFiles ${e})
    endforeach()
    foreach (e ${${target}.ConfigurationTemplateFiles})
      list(APPEND allFiles ${e})
    endforeach()
    foreach (e ${${target}.ConfigurationFiles})
      list(APPEND allFiles ${e})
    endforeach()
    foreach (e ${${target}.AssemblerFiles})
      list(APPEND allFiles ${e})
    endforeach()
    
    # Support for resource files under windows.
    if (${${target}.OperatingSystem} STREQUAL ${${target}.OperatingSystem.Windows} AND ${target}.Windows.ResourceFile)
      list(APPEND allFiles ${${target}.Windows.ResourceFile})
    endif()

    target_sources(${target} PRIVATE ${allFiles})

    # Assign source groups to the files.
    # For this to work, the files must reside in ${CMAKE_CURRENT_SOURCE_DIR} or in ${CMAKE_CURRENT_BINARY_DIR}.  
    foreach (file ${allFiles})
      string_starts_with(result ${file} ${CMAKE_CURRENT_SOURCE_DIR})
      if (${result})
        source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${file})    
      else()
        string_starts_with(result ${file} ${CMAKE_CURRENT_BINARY_DIR})
        if(${result})
          source_group(TREE ${CMAKE_CURRENT_BINARY_DIR} FILES ${file})
        else()
          message(FATAL_ERROR "unknown/unsupported source directory: ${file}")
        endif() 
      endif()
    endforeach()

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

  if( CMAKE_SIZEOF_VOID_P EQUAL 4 AND CMAKE_ASM_MASM_COMPILER)
    set_source_files_properties(${${target}.AssemblerFiles}}
                                PROPERTIES
                                COMPILE_FLAGS "/safeseh")
  endif()
  
  EndFileCopy()

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

# @param target the target to which targetFile becomes a dependency to
# @param sourceFile the source file.
# @param targetFile the target file. to which the target file is a dependency
macro(MyCopyFile target sourceFile targetFile)
  list(APPEND ${target}.copyFiles.sources ${sourceFile})
  list(APPEND ${target}.copyFiles.targets ${targetFile})
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

# Can be used between `BeginProduct` and `EndProduct`.
macro(OnConfigurationFile target file)
  list(APPEND ${target}.ConfigurationFiles ${file})
endmacro()

# Can be used between `BeginProduct` and `EndProduct`.
macro(OnConfigurationTemplateFile target file)
  list(APPEND ${target}.ConfigurationTemplateFiles ${file})
endmacro()

# Can be used between `BeginProduct` and `EndProduct`.
macro(OnSourceFile target file)
  list(APPEND ${target}.SourceFiles ${file})
endmacro()

# Can be used between `BeginProduct` and `EndProduct`.
macro(OnHeaderFile target file)
  list(APPEND ${target}.SourceFiles ${file})
endmacro()
