<section class="cxx entity object">
<h1 id="Arcadia_FilePath">Arcadia_FilePath</h1>
<p>
<code>Arcadia_FilePath</code> represents a file path.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_FilePath</code> pointers.
A <code>Arcadia_FilePath</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_FilePath</code> value can be safely cast into a <code>Arcadia_FilePath</code> pointer.
</p>
</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">
  
  <h1 id="Arcadia_FilePath_create">create</h1>

  <my-signature><code>
  Arcadia_FilePath*<br>
  Arcadia_FilePath_create<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Create the empty file path.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
  </section>
  
  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>A pointer to the file path.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FilePath_parseWindows">Arcadia_FilePath_parseWindows</h1>

  <my-signature><code>
  Arcadia_FilePath*<br>
  Arcadia_FilePath_parseWindows<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Parse a file path in the Windows format.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>bytes</div>
      <div>A pointer to an array of <code>numberOfBytes</code> Bytes.</div>
    </div>
    <div>
      <div>numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>A pointer to the file path.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FilePath_parseUnix">Arcadi_FilePath_parseUnix</h1>

  <my-signature><code>
  Arcadia_FilePath*<br>
  Arcadia_FilePath_parseUnix<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Parse a file path in the Unix format.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>bytes</div>
      <div>A pointer to an array of <code>numberOfBytes</code> Bytes.</div>
    </div>
    <div>
      <div>numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>A pointer to the file path.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_FilePath-parseNative">Arcadia_FilePath_parseNative</h1>

  <my-signature><code>
  Arcadia_FilePath*<br>
  Arcadia_FilePath_parseNative<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Parse a file path in the native format.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>bytes</div>
      <div>A pointer to an array of <code>numberOfBytes</code> Bytes.</div>
    </div>
    <div>
      <div>numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>bytes</code> Bytes.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>A pointer to the file path.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">
  
  <h1 id="Arcadia_FilePath_toNative">Arcadia_FilePath_toNative</h1>

  <my-signature><code>
  Arcadia_String*<br>
  Arcadia_FilePath_toNative<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_FilePath* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Convert a file path to the native format.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>self</div>
      <div>A pointer to this file path.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>A pointer to the string.</p>
  </section>

</section>
