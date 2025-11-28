# Building under Windows 11/Visual Studio Community 2022

## Installing the dependencies
*michaelheilmann.com* requires
- *Microsoft Visual Studio Community 2022* version 17.9.2 or better.
  *Microsoft Visual Studio Community 2022* is available at [https://visualstudio.microsoft.com/vs/community/](https://visualstudio.microsoft.com/vs/community/).
- *Kitware CMake* version 3.29.6 or better.
  *Kitware CMake* is available at [https://cmake.org/](https://cmake.org/).
- *PowerShell*

## Integrating external libraries
*Arcadia.Ring1*, *Arcadia.Ring2*, *Arcadia.Mil* and many other parts have minimal external dependencies which are provided by the operating systems.
There are interesting modules related to audials, visuals, haptics, etc. which - nowadays - require the integration of certain external libraries.
These dependencies include "OpenAL", "OpenGL", "libpng", "freetype", and "zlib".

To facilitate building and integrating these dependencies under *Windows*, the PowerShell script
[https://github.com/michaelheilmann/michaelheilmann.com/blob/main/install-dependencies.ps1](https://github.com/michaelheilmann/michaelheilmann.com/blob/main/install-dependencies.ps1)
which downloads precompiled dependencies and installs them to `C:\arcadia-dependencies`.

The dependencies are downloaded from the [releases](https://github.com/michaelheilmann/michaelheilmann.com-dependencies/releases) of
[https://github.com/michaelheilmann/michaelheilmann.com-dependencies](https://github.com/michaelheilmann/michaelheilmann.com-dependencies).

Under Linux, of course, such ordeals are not necessary.

## Building the program
The following instructions will perform an out-of-source build. An out-of-source build does not modify the source directory
by storing any build file, intermediate file, or product file in a dedicated build directory outside of the source directory.
An out of source build is the recommended way of building *michaelheilmann.com*.

- Checkout *michaelheilmann.com* [https://github.com/michaelheilmann/michaelheilmann.com](https://github.com/michaelheilmann/michaelheilmann.com) into a directory in your file system.
  For the remainder of this manual, we call this directory *source directory* and denote it in command-line prompts by the meta variable `<source-directory>`.
- Create a directory outside of the *source directory* in which the build will be performed.
  That directory *must not* reside in the source directory `<source-directory>`.
  For the remainder of this manual, we call this directory *build directory* and denote it in command-line prompts by the meta variable `<build-directory>`.
- Open a console and enter the build directory `<build-directory>`.
- Enter `cmake <source-directory>`.
- The Visual Studio Community 2022 solution file `Arcadia.sln` should have been generated in `<build-directory>`.

#### Adding support for non-default instruction set architecture
By default, the cmake command to generate the build files will create those files for the default instruction set architecture based on the machine your are building on
which is either x64 or x86 for Windows. You can explicitly select one of these two instruction set architectures by adding parameters to the cmake command:
- To generate the build files for the target architecture x86, add the parameter `-A Win32` to the cmake command.
- To generate the build files for the target architecture x64, add the parameter `-A x64` to the cmake command.

#### Further Options

- `Arcadia.Arms.Statistics.Enabled`
`TRUE` enables statistics for *Arcadia ARMS*, `FALSE` disables them. Default is `FALSE`.

- `Arcadia.Visuals.Implementation.OpenGL4.Enabled`
`TRUE` enables OpenGL 4 support in *Arcadia Visuals*, `FALSE` disables it. Default is `FALSE`.
\
To enable OpenGL 4 support, add the parameter `-D"Arcadia.Visuals.Implementation.OpenGL4.Enabled"=TRUE` to the cmake command.
To disable OpenGL 4 support, add the parameter `-D"Arcadia.Visuals.Implementation.OpenGL4.Enabled"=FALSE` to the cmake command.
\
*Important*: Ensure that the dependencies are installed by executing the script [/install-dependencies.ps1](/install-dependencies.ps1).

- `Arcadia.Audials.Implementation.OpenAL.Enabled`
`TRUE` enables OpenAL support in *Arcadia Audials*, `FALSE` disables it. Default is `FALSE`.
\
To enable OpenAL support, add the parameter `-D"Arcadia.Audials.Implementation.OpenAL.Enabled"=TRUE` to the cmake command.
To disable OpenAL support, add the parameter `-D"Arcadia.Audials.Implementation.OpenAL.Enabled"=FALSE` to the cmake command.
\
*Important*: Ensure that the dependencies are installed by executing the script [/install-dependencies.ps1](/install-dependencies.ps1).
