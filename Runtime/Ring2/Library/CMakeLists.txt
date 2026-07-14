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

cmake_minimum_required(VERSION 3.29)

# Create library.
set(this ${MyProjectName}.Ring2)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h.i)

  OnSourceFile(${this} Arcadia/Ring2/Print/print.c)
  OnHeaderFile(${this} Arcadia/Ring2/Print/print.h)

  OnSourceFile(${this} Arcadia/Ring2/Collections/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/ArrayList.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/ArrayList.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/ArrayDeque.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/ArrayDeque.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/ArrayStack.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/ArrayStack.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/Collection.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/Collection.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/Deque.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/Deque.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/HashMap.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/HashMap.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/HashSet.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/HashSet.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/ImmutableList.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/ImmutableList.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/ImmutableSet.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/ImmutableSet.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/List.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/List.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/Map.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/Map.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/Set.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/Set.h)
  OnSourceFile(${this} Arcadia/Ring2/Collections/Stack.c)
  OnHeaderFile(${this} Arcadia/Ring2/Collections/Stack.h)

  OnSourceFile(${this} Arcadia/Ring2/CommandLine/CommandLineArgument.c)
  OnHeaderFile(${this} Arcadia/Ring2/CommandLine/CommandLineArgument.h)
  OnSourceFile(${this} Arcadia/Ring2/CommandLine/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/CommandLine/Include.h)

  OnSourceFile(${this} Arcadia/Ring2/Exceptions/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Exceptions/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Exceptions/Exception.c)
  OnHeaderFile(${this} Arcadia/Ring2/Exceptions/Exception.h)

  OnSourceFile(${this} Arcadia/Ring2/FileSystem/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/DirectoryIterator.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/DirectoryIterator.h)
  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    OnSourceFile(${this} Arcadia/Ring2/FileSystem/Linux/DirectoryIteratorLinux.c)
    OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Linux/DirectoryIteratorLinux.h)
    OnSourceFile(${this} Arcadia/Ring2/FileSystem/Linux/getHomeFolder.c)
    OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Linux/getHomeFolder.h)
  endif()
  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Windows})
    OnSourceFile(${this} Arcadia/Ring2/FileSystem/Windows/DirectoryIteratorWindows.c)
    OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Windows/DirectoryIteratorWindows.h)
    OnSourceFile(${this} Arcadia/Ring2/FileSystem/Windows/getLocalFolder.c)
    OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Windows/getLocalFolder.h)
    OnSourceFile(${this} Arcadia/Ring2/FileSystem/Windows/getRoamingFolder.c)
    OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Windows/getRoamingFolder.h)
  endif()
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/ExistingFilePolicy.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/ExistingFilePolicy.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/FileAccessMode.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/FileAccessMode.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/FileHandle.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/FileHandle.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/FileHandleExtensions.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/FileHandleExtensions.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/FilePath.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/FilePath.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/FileSystem.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/FileSystem.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/FileType.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/FileType.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/NonExistingFilePolicy.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/NonExistingFilePolicy.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/Implementation/DefaultFileSystem.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Implementation/DefaultFileSystem.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/Implementation/DefaultFileHandle.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Implementation/DefaultFileHandle.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/Implementation/getFileType.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Implementation/getFileType.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/Implementation/deleteRegularFile.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Implementation/deleteRegularFile.h)
  OnSourceFile(${this} Arcadia/Ring2/FileSystem/Implementation/deleteDirectoryFile.c)
  OnHeaderFile(${this} Arcadia/Ring2/FileSystem/Implementation/deleteDirectoryFile.h)

  OnSourceFile(${this} Arcadia/Ring2/Implementation/ArgumentsValidation.c)
  OnHeaderFile(${this} Arcadia/Ring2/Implementation/ArgumentsValidation.h)

  OnSourceFile(${this} Arcadia/Ring2/Unicode/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Unicode/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Unicode/Encoder.c)
  OnHeaderFile(${this} Arcadia/Ring2/Unicode/Encoder.h)
  OnSourceFile(${this} Arcadia/Ring2/Unicode/UTF8Encoder.c)
  OnHeaderFile(${this} Arcadia/Ring2/Unicode/UTF8Encoder.h)

  OnSourceFile(${this} Arcadia/Ring2/Strings/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Strings/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Strings/StringExtensions.c)
  OnHeaderFile(${this} Arcadia/Ring2/Strings/StringExtensions.h)

  OnSourceFile(${this} Arcadia/Ring2/Time/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Time/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Time/PointInTime.c)
  OnHeaderFile(${this} Arcadia/Ring2/Time/PointInTime.h)
  OnSourceFile(${this} Arcadia/Ring2/Time/TimeSpecification.c)
  OnHeaderFile(${this} Arcadia/Ring2/Time/TimeSpecification.h)

  OnSourceFile(${this} Arcadia/Ring2/Logging/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/Include.h)
  OnSourceFile(${this} Arcadia/Ring2/Logging/Log.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/Log.h)
  OnSourceFile(${this} Arcadia/Ring2/Logging/ConsoleLog.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/ConsoleLog.h)
  OnSourceFile(${this} Arcadia/Ring2/Logging/FileLog.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/FileLog.h)
  OnSourceFile(${this} Arcadia/Ring2/Logging/LogCategory.c)
  OnHeaderFile(${this} Arcadia/Ring2/Logging/LogCategory.h)

  OnSourceFile(${this} Arcadia/Ring2/Include.c)
  OnHeaderFile(${this} Arcadia/Ring2/Include.h)

  OnModuleDependency(${this} ${MyProjectName}.Ring1)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  set(${this}.Install TRUE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Ring2")

endif()
