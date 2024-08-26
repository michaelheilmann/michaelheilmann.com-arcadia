# A non-portable powershell script to build index.html.
# We will replace this by in-house tools soon.
$files = @("documentation/header.i")
$files += @("documentation/1.files.i")
$files += @("documentation/2.further-references.i")
$files += @("documentation/3.documentation.i",
            "documentation/3.documentation.1.types-and-values.1.boolean.i",
            "documentation/3.documentation.1.types-and-values.2.integer.i",
            "documentation/3.documentation.1.types-and-values.3.natural.i",
            "documentation/3.documentation.1.types-and-values.4.size.i",
            "documentation/3.documentation.1.types-and-values.5.void.i",
            "documentation/3.documentation.1.types-and-values.6.objectreference.i"
            "documentation/3.documentation.2.value.i"
            "documentation/3.documentation.3.status-codes.i",
            "documentation/3.documentation.4.status-variable.i"
            "documentation/3.documentation.5.jumps-and-jump-targets.i",
            "documentation/3.documentation.6.numeric-functions.i",
            "documentation/3.documentation.6.numeric-functions/1.clamp.i",
            "documentation/3.documentation.6.numeric-functions/2.countLeadingZeroes.i",
            "documentation/3.documentation.6.numeric-functions/3.maximum.i",
            "documentation/3.documentation.6.numeric-functions/4.minimum.i")
$files += @("documentation/3.documentation.7.objects.i",
            "documentation/3.documentation.7.objects/bytebuffer.i")
$files += @("documentation/footer.i")
Get-Content -Path $files | Set-Content "index.html"
