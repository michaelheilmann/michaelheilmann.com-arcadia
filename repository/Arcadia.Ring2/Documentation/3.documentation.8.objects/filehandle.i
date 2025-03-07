<h4 id="Arcadia_FileHandle">Arcadia_FileHandle</h4>
<p>
<code>Arcadia_FileHandle</code> represents a operating system file handle.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_FileHandle</code> pointers.
A <code>Arcadia_FileHandle</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_FileHandle</code> value can be safely cast into a <code>Arcadia_FileHandle</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FileHandle_create">Arcadia_FileHandle_create</h5>

<p><code>
Arcadia_FileHandle*
Arcadia_FileHandle_create
  (
    Arcadia_Thread* thread,
    Arcadia_FileSystem* fileSystem
  )
</code></p>

<p>Create a file handle. The file handle is closed.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_FileSystem* self</td><td>A pointer to the backing <code>Arcadia_FileSystem</code> object.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the file handle.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FileHandle_close">Arcadia_FileHandle_close</h5>
<p><code>
void
Arcadia_FileHandle_close
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self
  )
</code></p>

<p>Close this file handle.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_FileHandle* self</td><td>A pointer to this file handle.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_FileHandle_openForReading">Arcadia_FileHandle_openForReading</h5>
<p><code>
void
Arcadia_FileHandle_openForReading
  (
    Arcadia_Thread* thread,
    Arcadia_FileHandle* self,
    Arcadia_FilePath* path
  )
</code></p>

<p>Open a file for reading. If the file is open, it is closed before trying to re-open it.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_FileHandle* self</td><td>A pointer to this file handle.</td></tr>
  <tr><td>Arcadia_FilePath* path  </td><td>The file path of the file to read from.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid     </td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid     </td><td><code>path</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_FileSystemOperationFailed</td><td>Opening the file failed.            </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-openforwriting">openForWriting</h5>
<p><code>
void R_FileHandle_openForWriting(R_FileHandle* self, R_FilePath* path)
</code></p>

<p>Open a file for writing. If the file is open, it is closed before trying to re-open it.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle* self</td><td>A pointer to this file handle.</td></tr>
  <tr><td>R_FilePath* path  </td><td>The file path of the file to write to.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>path</code> is a null pointer.</td></tr>
  <tr><td>R_Status_FileSystemOperationFailed</td><td>Opening the file failed.            </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-isclosed">isClosed</h5>
<p><code>
R_BooleanValue R_FileHandle_isClosed(R_FileHandle const* self)
</code></p>

<p>Get if this file handle is closed.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle const* self </td><td>A pointer to this file handle.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-isopened">isOpened</h5>
<p><code>
R_BooleanValue R_FileHandle_isOpened(R_FileHandle const* self)
</code></p>

<p>Get if this file handle is opened.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle const* self </td><td>A pointer to this file handle.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-isopenedforreading">isOpenedForReading</h5>
<p><code>
R_BooleanValue R_FileHandle_isOpenedForReading(R_FileHandle const* self)
</code></p>

<p>Get if this file handle is opened for reading.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle const* self </td><td>A pointer to this file handle.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-isopenedforwriting">isOpenedForWriting</h5>
<p><code>
R_BooleanValue R_FileHandle_isOpenedForWriting(R_FileHandle const* self)
</code></p>

<p>Get if this file handle is opened for writing.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle const* self </td><td>A pointer to this file handle.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-write">write</h5>
<p><code>
void R_FileHandle_write(R_FileHandle* self, void const* p, R_SizeValue bytesToWrite)
</code></p>

<p>Write Bytes to this file handle.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle* self       </td><td>A pointer to this file handle.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>bytesToWrite</code> Bytes.</td></tr>
  <tr><td>R_SizeValue bytesToWrite </td><td>The number of Bytes in the array pointed to by <code>bytes</code>.</td></tr>
  <tr><td>R_SizeValue* bytesWritten</td><td>A pointer to a <code>R_SizeValue</code> variable.</td></tr>
</table>

<h6><b>Success</b></h6>
<p>
On success <code>*bytesWritten</code> is assigned the actual number of Bytes written.
</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_OperationInvalid         </td><td>The file is not opened for writing.</td></tr>
  <tr><td>R_Status_FileSystemOperationFailed</td><td>Writing failed.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-filehandle-read">read</h5>
<p><code>
void R_FileHandle_read(R_FileHandle* self, void const* bytes, R_SizeValue bytesToRead, R_SizeValue* bytesRead)
</code></p>

<p>Read Bytes from this file handle.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_FileHandle* self      </td><td>A pointer to this file handle.</td></tr>
  <tr><td>void const* bytes       </td><td>A pointer to an array of <code>bytesToWrite</code> Bytes.</td></tr>
  <tr><td>R_SizeValue bytesToRead </td><td>The number of Bytes to read from the the array pointed to by <code>bytes</code>.</td></tr>
  <tr><td>R_SizeValue* bytesRead  </td><td>A pointer to a <code>R_SizeValue</code> variable.</td></tr>
</table>

<h6><b>Success</b></h6>
<p>
On success <code>*bytesRead</code> is assigned the actual number of Bytes read.
The number of Bytes read is 0 if the end of the file was reached.
</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_ArgumentValueInvalid     </td><td><code>bytesRead</code> is a null pointer.</td></tr>
  <tr><td>R_Status_OperationInvalid         </td><td>The file is not opened for writing.</td></tr>
  <tr><td>R_Status_FileSystemOperationFailed</td><td>Writing failed.</td></tr>
</table>
