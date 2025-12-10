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

# This script downloads the prebuilt dependencies from the releases of `https://github.com/michaelheilmann/michaelheilmann.com-dependencies`.

# The source URL prefix.
$urlPrefix="https://github.com/michaelheilmann/michaelheilmann.com-dependencies/releases/download/michaelheilmann.com-dependencies-v1.0.62"

# The target file prefix.
$target = "C:/arcadia-dependencies"

New-Item -ItemType Directory -Force -Path $target

foreach ($architecture in @('x64', 'x86')) {
  $url="$urlPrefix/dependencies-$architecture.zip"
  Write-Host "downloading $url to $target/dependencies-$architecture.zip"
  Invoke-WebRequest -UseBasicParsing $url -OutFile $target/dependencies-$architecture.zip -ErrorAction Stop
  Expand-Archive -LiteralPath $target/dependencies-$architecture.zip -DestinationPath $target/$architecture
}
