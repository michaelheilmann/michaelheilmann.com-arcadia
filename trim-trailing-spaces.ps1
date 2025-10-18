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

# This script removes trailing whitespaces from the following file types
# - *.c
# - *.h
# - *.i
# - *.te
# - *.mil

# CMakeLists.txt
Get-ChildItem -Path ./repository -Recurse -ErrorAction SilentlyContinue -Force -Filter CMakeLists.txt |
  Foreach-Object {
    (Get-Content -Path $_.FullName | foreach {$_ -replace '\s+$', ''}) | Set-Content -Path $_.FullName
  }
  
# *.c, *.h, and *.i
Get-ChildItem -Path ./repository -Recurse -ErrorAction SilentlyContinue -Force -Include *.c, *.h, *.i. |
  Foreach-Object {
    (Get-Content -Path $_.FullName | foreach {$_ -replace '\s+$', ''}) | Set-Content -Path $_.FullName
  }

# *.tl and *.mil
Get-ChildItem -Path ./repository -Recurse -ErrorAction SilentlyContinue -Force -Include *.tl, *.mil |
  Foreach-Object {
    (Get-Content -Path $_.FullName | foreach {$_ -replace '\s+$', ''}) | Set-Content -Path $_.FullName
  }
