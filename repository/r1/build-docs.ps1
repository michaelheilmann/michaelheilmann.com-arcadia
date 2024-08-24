# A non-portable powershell script to build index.html.
# We will replace this by in-house tools soon.
$files = @("documentation/header.i")
$files += @("documentation/1.files.i")
$files += @("documentation/2.further-references.i")
$files += @("documentation/3.documentation.i",
            "documentation/3.documentation.1.boolean.i",
            "documentation/3.documentation.2.integer.i",
            "documentation/3.documentation.3.natural.i",
            "documentation/3.documentation.4.size.i",
            "documentation/3.documentation.5.void.i",
            "documentation/3.documentation.6.status-codes.i",
            "documentation/3.documentation.7.status-variable.i"
            "documentation/3.documentation.8.jumps-and-jump-targets.i",
            "documentation/3.documentation.9.numeric-functions.i")
$files += @("documentation/footer.i")
Get-Content -Path $files | Set-Content "index.html"
