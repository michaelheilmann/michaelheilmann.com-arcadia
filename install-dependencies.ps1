# The source URL prefix.
$urlPrefix="https://github.com/michaelheilmann/michaelheilmann.com-dependencies/releases/download/michaelheilmann.com-dependencies-v1.0.29"

# The target file prefix.
$target = "C:/arcadia-dependencies"

# The packages.
$packages =
  @(
    "my-freetype",
    "my-libpng",
    "my-zlib",
    "my-openal",
    "my-opengl"
  );
  
New-Item -ItemType Directory -Force -Path $target

foreach ($configuration in @('debug', 'release', 'minsizerel', 'relwithdebinfo')) {
  foreach ($architecture in @('x64', 'x86')) {
    foreach ($package in $packages) {
      $url="$urlPrefix/$package-$configuration-$architecture.zip"
      Write-Host "downloading $url to $target/$package-$configuration-$architecture.zip"
      Invoke-WebRequest -UseBasicParsing $url -OutFile $target/$package-$configuration-$architecture.zip -ErrorAction Stop
      Expand-Archive -LiteralPath $target/$package-$configuration-$architecture.zip -DestinationPath $target/$package-$configuration-$architecture 
    }
  }
}
