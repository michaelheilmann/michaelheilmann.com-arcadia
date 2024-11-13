# michaelheilmann.com
The website [michaelheilmann.com](https://michaelheilmann.com) and its contents (including all sources for documentations and programs).

### Repository Contents
This repository contains
- the source code of this website
- the C source code of tools to build the website from its source
- the C source code of support libraries for the tools

### Building under Windows / Visual Studio
- Checkout the repository [https://github.com/michaelheilmann.com](https://github.com/michaelheilmann.com) to a directory on your machine.
- Create a directory called the build directory. That directory must not be the source directory or a subdirectory of the source directory.
- Invoke `cmake <source directory>` where `<source directory>` is the path to the source directory.
- Open the `Arcadia.sln` solution file.

Remarks: This will build the target architecture that is the default of your machine.
To generate the build files for the target architecture x86, change the command to `cmake -A Win32 <source directory>`.
To generate the build files for the target architecture x64, change the command to `cmake -A x64 <source directory>`.

### Build status
[![Build status](https://ci.appveyor.com/api/projects/status/og37g8g7t984xtt2/branch/main?svg=true)](https://ci.appveyor.com/project/michaelheilmann-com/michaelheilmann-com/branch/main)
[![Build status](https://ci.appveyor.com/api/projects/status/og37g8g7t984xtt2/branch/develop?svg=true)](https://ci.appveyor.com/project/michaelheilmann-com/michaelheilmann-com/branch/develop)

### Roadmap
The roadmap (that is, what is was, is, and will be done) is available on [michaelheilmann.com/roadmap](https://michaelheilmann.com/roadmap).
