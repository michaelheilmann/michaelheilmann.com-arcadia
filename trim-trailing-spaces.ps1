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
# - *.txt
# - *.c
# - *.h
# - *.i
# - *.tl
# - *.mil
function removeWhitespaceAtEndOfLines {
  $forbiddenFolders=@(".git",".vs");
  $allowedExtensions=@(".txt", ".c", ".h", ".i",  ".tl", ".mil");
  $includeByName=@("CMakeLists.txt")
  
  $xl = new-object system.collections.stack;
  $x = Get-Item -Path '.';
  $xl.Push($x);
  
  #Write-Host "worklist size: " $xl.Count;
  
  while ($xl.Count -ne 0) {
    $x = $xl.Pop();
    if ($x.PSIsContainer) {
      # if the item is '.git' or '.vs', skip.
      if ($x.Name -In $forbiddenFolders) {
        #Write-Host "skipping " $x.FullName; 
        continue;
      }
      Get-ChildItem -Path $x.FullName | Foreach-Object {
        #Write-Host "adding " $_.FullName;
        $xl.Push($_);
      }
    } else {
      if ($x.Extension -NotIn $allowedExtensions) {
        #Write-Host "skipping " $x.FullName; 
        continue;
      }
      # if the item is a file, process it.
      Write-Host "processing " $x.FullName;
      (Get-Content -Path $x.FullName | foreach {$_ -replace '\s+$', ''}) | Set-Content -Path $x.FullName
    }
  }
}

removeWhitespaceAtEndOfLines  
