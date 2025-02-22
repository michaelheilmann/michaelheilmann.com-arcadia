<h4 id="Arcadia_ByteBuffer">Arcadia_ByteBuffer</h4>
<p>
<code>Arcadia_ByteBuffer</code> represents a mutable sequence of Bytes.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_ByteBuffer</code> pointers.
A <code>Arcadia_ByteBuffer</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_ByteBuffer</code> value can be safely cast into a <code>R_ByteBuffer</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_create">Arcadia_ByteBuffer_create</h5>

<p><code>
Arcadia_ByteBuffer*
Arcadia_ByteBuffer_create
  (
    Arcadia_Process* process
  )
</code></p>

<p>Create a Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_AllocationFailed</td><td>An allocation failed.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>A pointer to the Byte buffer.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_clear">Arcadia_ByteBuffer_clear</h5>
<p><code>
void
Arcadia_ByteBuffer_clear
  (
    Arcadia_ByteBuffer* self
  )
</code></p>

<p>Set the number of elements of this Byte buffer to zero.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_ByteBuffer_endsWith_pn">Arcadia_ByteBuffer_endsWith_pn</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_ByteBuffer_endsWith_pn
  (
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Get if a sequence of Bytes is a suffix of this Byte buffer's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes                       </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes         </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a suffix of this byte buffer's sequence of Bytes.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_ByteBuffer_startsWith_pn">Arcadia_ByteBuffer_startsWith_pn</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_ByteBuffer_startsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Get if a sequence of Bytes is a prefix of this Byte buffer's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes                       </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes         </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a prefix of this byte buffer's sequence of Bytes.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_ByteBuffer_isEqualTo_pn">Arcadia_isEqualTo_pn</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo_pn
  (
    Arcadia_Process* process,
    R_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Get if a sequence of Bytes is this Byte buffer's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes                       </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes         </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is this byte buffer's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_append_pn">Arcadia_ByteBuffer_append_pn</h5>
<p><code>
void
Arcadia_ByteBuffer_append_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Append Bytes to this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadoa_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* bytes                       </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes         </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_AllocationFailed    </td><td>An allocation failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_prepend_pn">Arcadia_ByteBuffer_prepend_pn</h5>
<p><code>
void
Arcadia_ByteBuffer_prepend_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    void const* p,
    Arcadia_SizeValue n
  )
</code></p>

<p>Prepend Bytes to this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>void const* p                           </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue n                     </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_AllocationFailed    </td><td>An allocation failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_insert_pn">Arcadia_ByteBuffer_insert_pn</h5>
<p><code>
void
Arcadia_ByteBuffer_insert_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    Arcadia_SizeValue index,
    void const* p,
    Arcadia_SizeValue n
  )
</code></p>

<p>Insert Bytes into this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>Arcadia_SizeValue index                 </td><td>The index at which to insert the Bytes. Must be within the bounds of <code>[0,n)</code> where <code>n</code> is the size of this Byte buffer.</td></tr>
  <tr><td>void const* p                           </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue n                     </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer. </td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_AllocationFailed    </td><td>An allocation failed.                </td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_isEqualTo">Arcadia_ByteBuffer_isEqualTo</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    Arcadia_ByteBuffer const* other
  )
</code></p>

<p>Compare this Byte buffer with another Byte buffer for equality.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer const* self </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>Arcadia_ByteBuffer const* other</td><td>A pointer to the other Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if this Byte buffer is equal to the other Byte buffer.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_getSize">Arcadia_ByteBuffer_getSize</h5>
<p><code>
Arcadia_SizeValue
Arcadia_ByteBuffer_getSize
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self
  )
</code></p>

<p>Get the size of this Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this Byte buffer.</p>

<h6><b>Remarks</b></h6>
<p> The size of a Byte buffer is the length of the Byte sequence it contains.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_getAt">Arcadia_ByteBuffer_getat</h5>
<p><code>
Arcadia_Natural8Value
Arcadia_ByteBuffer_getAt
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    Arcadia_SizeValue index
  )
</code></p>

<p>Get the Byte value at the specified index.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>Arcadia_SizeValue index</td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size of this Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The Byte value.</p>

<h6><b>Remarks</b></h6>
<p> The size of a Byte buffer is the length of the Byte sequence it contains.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_isEmpty">Arcadia_ByteBuffer_isEmpty</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_ByteBuffer_isEmpty
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self
  )
</code></p>

<p>Get if this Byte buffer is empty.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self</td><td>A pointer to this Byte buffer.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p><code>R_BooleanValue_True</code> if this Byte buffer is empty. <code>R_BooleanValue_False</code> otherwise.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_ByteBuffer_swap">Arcadia_ByteBuffer_swap</h5>
<p><code>
void
Arcadia_ByteBuffer_swap
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    Arcadia_ByteBuffer* other
  )
</code></p>

<p>Swap the contents of this Byte buffer with the contents of another Byte buffer.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to this Byte buffer.</td></tr>
  <tr><td>Arcadia_ByteBuffer* self                </td><td>A pointer to the other Byte buffer.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>other</code> is a null pointer.</td></tr>
</table>
