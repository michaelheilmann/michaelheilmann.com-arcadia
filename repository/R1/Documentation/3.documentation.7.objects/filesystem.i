<h4 id="r-filesystem">FileSystem</h4>
<p>
<code>R_FileSystem</code> provides access to the file system.
This type is allocated on the heap and values of this type are referenced by <code>R_String</code> pointers.
A <code>R_FileSystem</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_String</code> value can be safely cast into a <code>R_String</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filesystem-create">R_FileSystem_create</h5>
<p><code>
R_FileSystem* R_FileSystem_create()
</code></p>

<p>Create a file system.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_AllocationFailed</td><td>An allocation failed.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-filesystem-getfilecontents">getFileContents</h5>
<p><code>
R_ByteBuffer* R_ByteBuffer_getFileContents(char const *path)
</code></p>

<p>Get the contents of a file.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>char const* path  </td><td>A pointer to a C string denoting the path to the file.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
A pointer to a <code>R_ByteBuffer</code> object with the file contents.
</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>path</code> is a null pointer.</td></tr>
  <tr><td>R_Status_FileSystemOperationFailed</td><td>Opening the file failed.            </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-filesystem-setfilecontents">setFileContents</h5>
<p><code>
void R_FileSystem_setFileContents(char const* path, R_ByteBuffer* contents)
</code></p>

<p>Get if a sequence of Bytes is a prefix of this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>char const* path  </td><td>A pointer to a C string denoting the path to the file.</td></tr>
  <tr><td>R_ByteBuffer const* byteBuffer</td><td>A poiner to the Byte buffer with the file contents.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>path</code> is a null pointer.    </td></tr>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>contents</code> is a null pointer.</td></tr>
  <tr><td>R_Status_FileSystemOperationFailed</td><td>Opening the file failed.                </td></tr>
</table>
