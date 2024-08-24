# A non-portable powershell script to build index.html.
# We will replace this by in-house tools soon.
$files = @("documentation/header.i", "documentation/main.i", "documentation/unmanaged-memory.i", "documentation/footer.i")
Get-Content -Path $files | Set-Content "index.html"
