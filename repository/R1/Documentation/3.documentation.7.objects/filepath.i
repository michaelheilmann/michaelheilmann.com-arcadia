<h4 id="r-filepath">File Path</h4>
<p>
<code>R_FilePath</code> represents a file path.
This type is allocated on the heap and values of this type are referenced by <code>R_FilePath</code> pointers.
A <code>R_FilePath</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_FilePath</code> value can be safely cast into a <code>R_FilePath</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filepath-create">create</h5>

<p><code>
R_FilePath* R_Path_create()
</code></p>

<p>Create the empty file path.</p>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filepath-parsewindowsfilepath">parseWindowsFilePath</h5>
<p><code>
R_FilePath* R_FilePath_parseWindowsFilePath(void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Parse a file path in the Windows format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filepath-parseunixfilepath">parseUnixFilePath</h5>
<p><code>
R_FilePath* R_FilePath_parseUnixFilePath(void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Parse a file path in the Unix format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filepath-parsenativefilepath">parseNativeFilePath</h5>
<p><code>
R_FilePath* R_FilePath_parseNativeFilePath(void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Parse a file path in the native format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filepath-tonative">toNative</h5>
<p><code>
R_String* R_FilePath_toNative(R_FilePath* self)
</code></p>

<p>Convert a file path to the native format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>self</td><td>A pointer to this file path.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the string.</p>
