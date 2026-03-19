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
set(MyLibraryName ${MyProjectName}.Ring2)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Ring2/Implementation/Configure.h)


  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Implementation/ByteBuffer.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Implementation/ByteBuffer.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Print/print.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Print/print.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/ArrayList.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/ArrayList.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/ArrayDeque.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/ArrayDeque.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/ArrayStack.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/ArrayStack.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/Collection.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/Collection.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/Deque.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/Deque.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/HashMap.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/HashMap.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/HashSet.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/HashSet.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/ImmutableHashMap.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/ImmutableHashMap.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/ImmutableList.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/ImmutableList.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/ImmutableSet.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/ImmutableSet.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/List.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/List.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/Map.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/Map.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/Set.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/Set.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Collections/Stack.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Collections/Stack.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/CommandLine/CommandLineArgument.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/CommandLine/CommandLineArgument.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/CommandLine/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/CommandLine/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Exceptions/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Exceptions/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Exceptions/Exception.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Exceptions/Exception.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/DirectoryIterator.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/DirectoryIterator.h)
  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Linux/DirectoryIteratorLinux.c)
    OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Linux/DirectoryIteratorLinux.h)
    OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Linux/getHomeFolder.c)
    OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Linux/getHomeFolder.h)
  endif()
  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Windows})
    OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Windows/DirectoryIteratorWindows.c)
    OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Windows/DirectoryIteratorWindows.h)
    OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Windows/getLocalFolder.c)
    OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Windows/getLocalFolder.h)
    OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Windows/getRoamingFolder.c)
    OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Windows/getRoamingFolder.h)
  endif()
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/ExistingFilePolicy.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/ExistingFilePolicy.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileAccessMode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileAccessMode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileHandle.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileHandle.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileHandleExtensions.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileHandleExtensions.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FilePath.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FilePath.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileSystem.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileSystem.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/FileType.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/NonExistingFilePolicy.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/NonExistingFilePolicy.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/DefaultFileSystem.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/DefaultFileSystem.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/DefaultFileHandle.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/DefaultFileHandle.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/getFileType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/getFileType.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/deleteRegularFile.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/deleteRegularFile.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/deleteDirectoryFile.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/FileSystem/Implementation/deleteDirectoryFile.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Implementation/ArgumentsValidation.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Implementation/ArgumentsValidation.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/String.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/String.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/StringExtensions.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/StringExtensions.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/StringBuffer.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/StringBuffer.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8Reader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8Reader.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8ByteBufferReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8ByteBufferReader.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8StringReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8StringReader.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8Writer.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8Writer.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8ByteBufferWriter.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8ByteBufferWriter.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8FileHandleWriter.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Strings/UTF8FileHandleWriter.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Time/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Time/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Time/PointInTime.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Time/PointInTime.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Time/TimeSpecification.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Time/TimeSpecification.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Logging/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Logging/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Logging/Log.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Logging/Log.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Logging/ConsoleLog.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Logging/ConsoleLog.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Logging/FileLog.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Logging/FileLog.h)
  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Logging/LogCategory.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Logging/LogCategory.h)

  OnSourceFile(${MyLibraryName} Arcadia/Ring2/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Ring2/Include.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.Ring1)

  if (${${MyLibraryName}.OperatingSystem} STREQUAL ${${MyLibraryName}.OperatingSystem.Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  set(${MyLibraryName}.Install TRUE)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Ring2")

endif()
