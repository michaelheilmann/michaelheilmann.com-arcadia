<section class="cxx entity object">
<h1 id="Arcadia_ByteBuffer">Arcadia_ByteBuffer</h1>
<p>
<code>Arcadia_ByteBuffer</code> represents a mutable sequence of Bytes.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_ByteBuffer</code> pointers.
A <code>Arcadia_ByteBuffer</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_ByteBuffer</code> value can be safely cast into a <code>Arcadia_ByteBuffer</code> pointer.
</p>
</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_create">Arcadia_ByteBuffer_create</h1>

  <my-signature><code>
  Arcadia_ByteBuffer*<br>
  Arcadia_ByteBuffer_create<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Create a Byte buffer.
  </my-summary>

  <section class="cxx parameters">
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
  
  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>A pointer to the Byte buffer.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">
  
  <h1 id="Arcadia_ByteBuffer_clear">Arcadia_ByteBuffer_clear</h1>

  <my-signature><code>
  void<br>
  Arcadia_ByteBuffer_clear<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Set the number of elements of this Byte buffer to zero.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_endsWith_pn">Arcadia_ByteBuffer_endsWith_pn</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_ByteBuffer_endsWith_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a sequence of Bytes is a suffix of this Byte buffer's sequence of Bytes.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>void const* bytes</div>
      <div>A pointer to an array of <code>n</code> Bytes.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>p</code>.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    <code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a suffix of this byte buffer's sequence of Bytes.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_startsWith_pn">Arcadia_ByteBuffer_startsWith_pn</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_ByteBuffer_startsWith_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a sequence of Bytes is a prefix of this Byte buffer's sequence of Bytes.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>void const* bytes</div>
      <div>A pointer to an array of <code>n</code> Bytes.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>p</code>.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    <code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a prefix of this byte buffer's sequence of Bytes.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_isEqualTo_pn">Arcadia_isEqualTo_pn</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_ByteBuffer_isEqualTo_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a sequence of Bytes is this Byte buffer's sequence of Bytes.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>void const* bytes</div>
      <div>A pointer to an array of <code>n</code> Bytes.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>p</code>.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    <code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is this byte buffer's sequence of Bytes.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_append_pn">Arcadia_ByteBuffer_append_pn</h1>

  <my-signature><code>
  void<br>
  Arcadia_ByteBuffer_append_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Append Bytes to this Byte buffer.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>void const* bytes</div>
      <div>A pointer to an array of <code>n</code> Bytes.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue numberOfBytes</div>
      <div>The number of Bytes in the array pointed to by <code>p</code>.</div>
    </div>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>bytes</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_AllocationFailed</div>
      <div>An allocation failed.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">
  
  <h1 id="Arcadia_ByteBuffer_prepend_pn">Arcadia_ByteBuffer_prepend_pn</h1>

  <my-signature><code>
  void<br>
  Arcadia_ByteBuffer_prepend_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* p,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue n<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Prepend Bytes to this Byte buffer.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>void const* p</div>
      <div>A pointer to an array of <code>n</code> Bytes.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue n</div>
      <div>The number of Bytes in the array pointed to by <code>p</code>.</div>
    </div>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>bytes</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_AllocationFailed</div>
      <div>An allocation failed.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_insert_pn">Arcadia_ByteBuffer_insert_pn</h1>

  <my-signature><code>
  void<br>
  Arcadia_ByteBuffer_insert_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue index,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* p,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue n<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Insert Bytes into this Byte buffer.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue index</div>
      <div>The index at which to insert the Bytes. Must be within the bounds of <code>[0,n)</code> where <code>n</code> is the size of this Byte buffer.</div>
    </div>
    <div>
      <div>void const* p</div>
      <div>A pointer to an array of <code>n</code> Bytes.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue n</div>
      <div>The number of Bytes in the array pointed to by <code>p</code>.</div>
    </div>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>bytes</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_AllocationFailed</div>
      <div>An allocation failed.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_isEqualTo">Arcadia_ByteBuffer_isEqualTo</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_ByteBuffer_isEqualTo<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer const* other<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Compare this Byte buffer with another Byte buffer for equality.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer const* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer const* other</div>
      <div>A pointer to the other Byte buffer.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>
    <code>Arcadia_BooleanValue_True</code> if this Byte buffer is equal to the other Byte buffer.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_getSize">Arcadia_ByteBuffer_getSize</h1>

  <my-signature><code>
  Arcadia_SizeValue<br>
  Arcadia_ByteBuffer_getSize<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the size of this Byte buffer.
  Remarks: The size of a Byte buffer is the length of the Byte sequence it contains.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The size of this Byte buffer.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_getAt">Arcadia_ByteBuffer_getAt</h1>

  <my-signature><code>
  Arcadia_Natural8Value<br>
  Arcadia_ByteBuffer_getAt<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue index<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the Byte value at the specified index.
  Remarks: The size of a Byte buffer is the length of the Byte sequence it contains.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue index</div>
      <div>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size of this Byte buffer.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The Byte value.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_isEmpty">Arcadia_ByteBuffer_isEmpty</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_ByteBuffer_isEmpty<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>Get if this Byte buffer is empty.</my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p><code>Arcadia_BooleanValue_True</code> if this Byte buffer is empty. <code>Arcadia_BooleanValue_False</code> otherwise.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_ByteBuffer_swap">Arcadia_ByteBuffer_swap</h1>

  <my-signature><code>
  void<br>
  Arcadia_ByteBuffer_swap<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ByteBuffer* other<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>Swap the contents of this Byte buffer with the contents of another Byte buffer.</my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to this Byte buffer.</div>
    </div>
    <div>
      <div>Arcadia_ByteBuffer* self</div>
      <div>A pointer to the other Byte buffer.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ArgumentValueInvalid</div>
      <div><code>other</code> is a null pointer.</div>
    </div>
  </section>

</section>
