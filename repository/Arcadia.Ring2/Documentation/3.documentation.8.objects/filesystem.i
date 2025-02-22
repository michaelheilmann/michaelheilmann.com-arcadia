<h4 id="Arcadia_FileSystem">Arcadia_FileSystem</h4>
<p>
<code>Arcadia_FileSystem</code> provides access to the file system.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_FileSystem</code> pointers.
A <code>Arcadia_FileSystem</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_FileSystem</code> value can be safely cast into a <code>Arcadia_FileSystem</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FileSystem_create">Arcadia_FileSystem_create</h5>
<p><code>
Arcadia_FileSystem*
Arcadia_FileSystem_create
  (
    Arcadia_Process* process
  )
</code></p>

<p>Create a file system.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_AllocationFailed</td><td>An allocation failed.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_FileSystem_getFileContents">Arcadia_FileSystem_getFileContents</h5>
<p><code>
Arcadia_ByteBuffer*
Arcadia_FileSystem_getFileContents
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
</code></p>

<p>Get the contents of a file.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td><a href="#">Arcadia_FileSystem</a>* self</td><td>A pointer to this <code>Arcadia_FileSystem</code> object.</td></tr>
  <tr><td><a href="#">Arcadia_FilePath</a>* path</td><td>The file path of the file.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
A pointer to a <code>Arcadia_ByteBuffer</code> object with the file contents.
</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Status_ArgumentValueInvalid</a>     </td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td><a href="#">Arcadia_Status_ArgumentValueInvalid</a>     </td><td><code>path</code> is a null pointer.</td></tr>
  <tr><td><a href="#">Arcadia_Status_FileSystemOperationFailed</a></td><td>Opening the file failed.            </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_FileSystem_setFileContents">Arcadia_FileSystem_setFileContents</h5>
<p><code>
void
Arcadia_FileSystem_setFileContents
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path,
    Arcadia_ByteBuffer* contents
  )
</code></p>

<p>Get if a sequence of Bytes is a prefix of this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td><a href="#">Arcadia_FileSystem</a>* self</td><td>A pointer to this <code>Arcadia_FileSystem</code> object.</td></tr>
  <tr><td>Arcadia_FilePath* path</td><td>The file path of the file.</td></tr>
  <tr><td>Arcadia_ByteBuffer* contents</td><td>A poiner to the Byte buffer with the file contents.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>sekf</code> is a null pointer.    </td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>path</code> is a null pointer.    </td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>contents</code> is a null pointer.</td></tr>
  <tr><td>R_Status_FileSystemOperationFailed </td><td>Opening the file failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_FileSystem_regularFileExists">Arcadia_FileSystem_regularFileExists</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_FileSystem_regularFileExists
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
</code></p>

<p>Get if a file exists and is a regular file.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td><a href="#">Arcadia_FileSystem</a>* self</td><td>A pointer to this <code>Arcadia_FileSystem</code> object.</td></tr>
  <tr><td>Arcadia_FilePath* path</td><td>The file path of the file.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the file exists and is a regular file.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid     </td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid     </td><td><code>path</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_FileSystem_directoryFileExists">Arcadia_FileSystem_directoryFileExists</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_FileSystem_directoryFileExists
  (
    Arcadia_Process* process,
    Arcadia_FileSystem* self,
    Arcadia_FilePath* path
  )
</code></p>

<p>Get if a file exists and is a directory file.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td><a href="#">Arcadia_FileSystem</a>* self</td><td>A pointer to this <code>Arcadia_FileSystem</code> object.</td></tr>
  <tr><td>Arcadia_FilePath* path</td><td>The file path of the file.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the file exists and is a directory file.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>path</code> is a null pointer.</td></tr>
</table>
