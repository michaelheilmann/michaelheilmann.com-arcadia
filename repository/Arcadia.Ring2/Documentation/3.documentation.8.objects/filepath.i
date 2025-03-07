<h4 id="Arcadia_FilePath">Arcadia_FilePath</h4>
<p>
<code>Arcadia_FilePath</code> represents a file path.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_FilePath</code> pointers.
A <code>Arcadia_FilePath</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_FilePath</code> value can be safely cast into a <code>Arcadia_FilePath</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filepath-create">create</h5>

<p><code>
Arcadia_FilePath*
Arcadia_FilePath_create
  (
    Arcadia_Thread* thread
  )
</code></p>

<p>Create the empty file path.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FilePath_parseWindows">Arcadia_FilePath_parseWindows</h5>
<p><code>
Arcadia_FilePath*
Arcadia_FilePath_parseWindows
  (
    Arcadia_Thread* thread,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Parse a file path in the Windows format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FilePath_parseUnix">Arcadi_FilePath_parseUnix</h5>
<p><code>
Arcadia_FilePath*
Arcadia_FilePath_parseUnix
  (
    Arcadia_Thread* thread,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Parse a file path in the Unix format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FilePath-parseNative">Arcadia_FilePath_parseNative</h5>
<p><code>
Arcadia_FilePath*
Arcadia_FilePath_parseNative
  (
    Arcadia_Thread* thread,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Parse a file path in the native format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file path.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FilePath_toNative">Arcadia_FilePath_toNative</h5>
<p><code>
Arcadia_String*
Arcadia_FilePath_toNative
  (
    Arcadia_Thread* thread,
    Arcadia_FilePath* self
  )
</code></p>

<p>Convert a file path to the native format.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>self</td><td>A pointer to this file path.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the string.</p>
