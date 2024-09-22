# michaelheilmann.com
The website [michaelheilmann.com](https://michaelheilmann.com) and its contents (including all sources for documentations and programs).

### Repository Contents
This repository contains
- the source code of this website
- the C source code of tools to build the website from its source
- the C source code of support libraries for the tools

### Roadmap
- **Milestone 5: Maintain roadmap on website**: Percentage done: 0% @ Week 1 October 2024
The roadmap shall be maintained on the website.

- **Milestone 4: Tooling for generating icons and banners (Windows only) | Tools.BannerGenerator**: Percentage done: 100% @ Week 4 September 2024
Certain operating systems (in particular Windows) require banners for application installers.
We require a tool to generate those.
\
The banner generator generates a "PNG" file.
As parameters, it takes the width and the height of the banner and the path of the "PNG" file.
The generated "PNG" file is an opaque black banner.

- **Milestone 3: Tooling for generating icons (Windows only) | Tools.IconGenerator**: Percentage done: 100% @ Week 3 September 2024
Certain operating systems (in particular Windows) require Icons for application windows and application installers.
We require a tool to generate those.
\
The icon generator generates an "ICO" file.
As parameter, it takes the path of the "ICO" file.
The generated "ICO" file contains opaque black black icons of the sizes 8x8, 16x16, 24x24, 32x32, 48x48, 64x64, 96x96, 128x128, and 256x256.

- **Milestone 2: Tooling for building the website | Tools.TemplateEngine**: Percentage done: 100% @ Week 2 September 2024
The source code of the website consists of multiple `.t` files. A tool called *Tools.TemplateEngine* shall be created in this milestone. The tool reads `.t` files and creates the output `.html`  files.
\
The tool shall work as follows: It receives the filename of one `.t` file and the filename of the target `.html` file. It will *parse* the `.t` file to create the target `.html` file. *parsing* means that the contents of the `.t` file are written to the target file unlesss directives are encountered. The directives are not written to the target file. Instead, they are interpreted. There are two kinds of directives:
  - `@@` directive results in `@` in being written to the target file. 
  - `@include(<filename>)` *parses* the file specified by `<filename>`.
\
Recursive include directives yield an error.
The parser must support UTF-8-NO-BOM encoding.

- **Milestone 1: Improve tooling to build the website | Tools.Concatenate**: Percentage done: 100% @ Week 1 September 2024
The source code of the website consists of multiple `.t` files. A tool called *Tools.Concatenate* shall be created in this milestone. The tool reads the  `.t` files and creates the output `.html` files.
\
The tool shall work as follows: It receives the filename of a one or more `.t` files and the filename of the target  `.html` file. It will then concatenate the Bytes of the `.t` files (in the order they were specified) and write the Bytes to the `.html` file. 
