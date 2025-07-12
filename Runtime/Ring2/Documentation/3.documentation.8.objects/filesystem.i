<section class="cxx entity object">
<h1 id="Arcadia_FileSystem">Arcadia_FileSystem</h1>
<p><code>Arcadia_FileSystem</code> extends <code>Arcadia_Object</code>.</p>
<p><code>Arcadia_FileSystem</code> provides access to the file system.</p>
</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FileSystem_create">Arcadia_FileSystem_create</h1>

  <my-signature><code>
  Arcadia_FileSystem*<br>
  Arcadia_FileSystem_create<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Create a file system.
  </my-summary>

  <section clas="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_AllocationFailed</div>
      <div>An allocation failed.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FileSystem_getFileContents">Arcadia_FileSystem_getFileContents</h1>

  <my-signature><code>
  Arcadia_ByteBuffer*<br>
  Arcadia_FileSystem_getFileContents<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FileSystem* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FilePath* path<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the contents of a file.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_FileSystem</a>* self</div>
      <div>A pointer to this <code>Arcadia_FileSystem</code> object.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_FilePath</a>* path</div>
      <div>The file path of the file.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    A pointer to a <code>Arcadia_ByteBuffer</code> object with the file contents.
    </p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div><a href="#">Arcadia_Status_ArgumentValueInvalid</a></div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_Status_ArgumentValueInvalid</a></div>
      <div><code>path</code> is a null pointer.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_Status_FileSystemOperationFailed</a></div>
      <div>Opening the file failed.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FileSystem_setFileContents">Arcadia_FileSystem_setFileContents</h1>

  <my-signature><code>
  void<br>
  Arcadia_FileSystem_setFileContents<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FileSystem* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FilePath* path,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* contents<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a sequence of Bytes is a prefix of this string's sequence of Bytes.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_FileSystem</a>* self</div>
      <div>A pointer to this <code>Arcadia_FileSystem</code> object.</div>
    </div>
    <div>
      <div>Arcadia_FilePath* path</div>
      <div>The file path of the file.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* contents</div>
      <div>A poiner to the Byte buffer with the file contents.</div>
    </div>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>sekf</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>path</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>contents</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_FileSystemOperationFailed</div>
      <div>Opening the file failed.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FileSystem_regularFileExists">Arcadia_FileSystem_regularFileExists</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_FileSystem_regularFileExists<br>
  &nbsp;&nbsp;(
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FileSystem* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FilePath* path<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a file exists and is a regular file.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_FileSystem</a>* self</div>
      <div>A pointer to this <code>Arcadia_FileSystem</code> object.</div>
    </div>
    <div>
      <div>Arcadia_FilePath* path</div>
      <div>The file path of the file.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    <code>Arcadia_BooleanValue_True</code> if the file exists and is a regular file.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</td><td><code>path</code> is a null pointer.</td></tr>
  </section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FileSystem_directoryFileExists">Arcadia_FileSystem_directoryFileExists</h1>

  <my-summary><code>
  Arcadia_BooleanValue<br>
  Arcadia_FileSystem_directoryFileExists<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FileSystem* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FilePath* path<br>
  &nbsp;&nbsp;)
  </code></my-summary>

  <my-summary>
  Get if a file exists and is a directory file.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div><a href="#">Arcadia_FileSystem</a>* self</div>
      <div>A pointer to this <code>Arcadia_FileSystem</code> object.</div>
    </div>
    <div>
      <div>Arcadia_FilePath* path</div>
      <div>The file path of the file.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    <code>Arcadia_BooleanValue_True</code> if the file exists and is a directory file.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>path</code> is a null pointer.</div>
    </div>
  </section>

</section>
