# Building under Linux

## Installing the dependencies
*michaelheilmann.com* requires
- *make* version 4.3.0 or better
  - Debian: `sudo apt-get install build-essential`
- *gcc* version 11.4.0 or better
  - Debian: `sudo apt-get install gcc`
- *cmake* version 4.1.3 or better
  - Debian: `sudo apt-get install cmake` or compile and install from source code.
- *libpng* version 1.6 or better
  - Debian:`sudo apt-get install libpng-dev`
- Optional: *gdb* version 12.1 or better
  - Debian: `sudo apt-get install gdb`
- Recommended: *X11 development headers and libraries*
  - Debian:
    - `sudo apt-get install libx11-dev`
    - `sudo apt-get install libxrandr-dev`
- Recommended: *OpenGL/GLX development headers and libraries*
  - Debian: `sudo apt-get install libglx-dev`
- Recommended: *OpenAL development headers and libraries*
  - Debian: `sudo apt-get install mesa-common-dev`

## Building the program
The following instructions will perform an out-of-source build. An out-of-source build does not modify the source directory
by storing any build file, intermediate file, or product file in a dedicated build directory outside of the source directory.
An out of source build is the recommended way of building *michaelheilmann.com*.

- Checkout *michaelheilmann.com* [https://github.com/michaelheilmann/michaelheilmann.com](https://github.com/michaelheilmannn/michaelheilmann.com) into a directory in your file system.
  For the remainder of this manual, we call this directory *source directory* and denote it in command-line prompts by the meta variable `<source-directory>`.
- Create a directory outside of the *source directory* in which the build will be performed.
  That directory *must not* reside in the source directory `<source-directory>`.
  For the remainder of this manual, we call this directory *build directory* and denote it in command-line prompts by the meta variable `<build-directory>`.
- Open a console and enter the build directory `<build-directory>`.
- Enter `cmake <source-directory>`.
- The makefiles should have been generated in `<build-directory>`.

*Remarks* The above builds *michaelheilmann.com* without debug information. To build *michaelheilmann.com* with debug information add the parameter `-DCMAKE_BUILD_TYPE="Debug"` to the cmake command.

#### Further Options

- `Arcadia.Arms.Statistics.Enabled`
`TRUE` enables statistics for *Arcadia ARMS*, `FALSE` disables them. Default is `FALSE`.

- `Arcadia.Visuals.Implementation.OpenGL4.Enabled`
`TRUE` enables OpenGL 4 support in *Arcadia Visuals*, `FALSE` disables it. Default is `FALSE`.
\
To enable OpenGL support, add the parameter `-D"Arcadia.Visuals.Implementation.OpenGL4.Enabled"=TRUE` to the cmake command.
To disable OpenGL support, add the parameter `-D"Arcadia.Visuals.Implementation.OpenGL4.Enabled"=FALSE` to the cmake command.

- `Arcadia.Audials.Implementation.OpenAL.Enabled`
`TRUE` enables OpenAL support in *Arcadia Audials*, `FALSE` disables it. Default is `FALSE`.
\
To enable OpenAL support, add the parameter `-D"Arcadia.Audials.Implementation.OpenAL.Enabled"=TRUE` to the cmake command.
To disable OpenAL support, add the parameter `-D"Arcadia.Audials.Implementation.OpenAL.Enabled"=FALSE` to the cmake command.
