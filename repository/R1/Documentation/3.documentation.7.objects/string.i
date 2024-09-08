<h4 id="r-string">String</h4>
<p>
<code>R_String</code> represents an Unicode string encoded as UTF-8-NO-BOM.
This type is allocated on the heap and values of this type are referenced by <code>R_String</code> pointers.
A <code>R_String</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_String</code> value can be safely cast into a <code>R_String</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-create">R_String_create</h5>
<p><code>
R_String* R_String_create(void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Create a string from a sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>bytes        </td><td>A pointer to an array of Bytes.</td></tr>
  <tr><td>numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>bytes</code>.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-string-endswith-pn">endsWith_pn</h5>
<p><code>
R_BooleanValue R_String_endsWith_pn(R_String const* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Get if a sequence of Bytes is a suffix of this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self           </td><td>A pointer to this string.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is a suffix of this string's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-string-startswith-pn">startsWith_pn</h5>
<p><code>
R_BooleanValue R_String_startsWith_pn(R_String const* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Get if a sequence of Bytes is a prefix of this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self           </td><td>A pointer to this string.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is a prefix of this string's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-isequalto">isEqualTo</h5>
<p><code>
R_BooleanValue R_String_isEqualTo(R_String const* self, R_String const* other)
</code></p>

<p>Compare this string with another string for equality.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String const* self </td><td>A pointer to this string.</td></tr>
  <tr><td>R_String const* other</td><td>A pointer to the other string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if this string is equal to the other string.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-isequalto_pn">isEqualTo_pn</h5>
<p><code>
R_BooleanValue R_String_isEqualTo_pn(R_String const* self, void const* bytes, R_SizeValue numberOfBytes)
</code></p>

<p>Get if a sequence of Bytes is this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self           </td><td>A pointer to this string.</td></tr>
  <tr><td>void const* bytes        </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>R_SizeValue numberOfBytes</td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>R_BooleanValue_True</code> if the sequence of Bytes is this string's sequence of Bytes.
<code>R_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-getsize">getSize</h5>
<p><code>
R_SizeValue R_String_getSize(R_String const* self)
</code></p>

<p>Get the size of this string.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this string.</p>

<h6><b>Remarks</b></h6>
<p> The size of a string is the length of the Byte sequence it contains.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-getat">getat</h5>
<p><code>
R_Natural8Value R_String_getAt(R_String const* self, R_SizeValue index)
</code></p>

<p>Get the Byte value at the specified index.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
  <tr><td>R_SizeValue index</td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size of this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The Byte value.</p>

<h6><b>Remarks</b></h6>
<p> The size of a string is the length of the Byte sequence it contains.</p>
