<h4 id="r-string">String</h4>
<p>
<code>R_String</code> represents an Unicode string encoded as UTF-8-NO-BOM.
This type is allocated on the heap and values of this type are referenced by <code>R_String</code> pointers.
A <code>R_String</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_String</code> value can be safely cast into a <code>R_String</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-create-pn">R_String_create_pn</h5>
<p><code>
R_String* R_String_create_pn(R_ImmutableByteArray* immutableByteArray)
</code></p>

<p>Create a string from an immutable Byte array.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>immutableByteArray</td><td>A pointer to an immutable Byte array</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the string.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>immutableByteArray</code> is a null pointer.</td></tr>
  <tr><td>R_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-create">R_String_create</h5>
<p><code>
R_String* R_String_create_pn(R_Value value)
</code></p>

<p>
Create a string from a value.
</p>

<p>
The specified value may contain a R_ByteBuffer object.
In that case, the string is created from the Bytes of the Byte buffer object.
A <code>R_Status_EncodingInvalid</code> is raised if the Byte sequence of that <code>R_ByteBuffer</code> object is not a UTF8 Byte sequence.
</p>

<p>
The specified value may contain a R_String object.
In that case, the string is created from the R_String object.
</p>

<p>
The specified value may contain a R_StringBuffer object.
In that case, the string is created from the R_StringBuffer object.
</p>

<p>
The specified value may contain a R_ImmutableByteArray object.
In that case, the string is created from the R_ImmutableByteArray object.
</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>value        </td><td>The value.</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the string. </p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td>The value does not contain either a <code>R_ByteBuffer</code> object, a <code>R_String</code> object, or a <code>R_StringBuffer</code> object.</td>
  </tr>
  <tr>
    <td>R_Status_EncodingInvalid    </td>
    <td>The value contains a <code>R_ByteBuffer</code> object. However, the Byte sequence of that <code>R_ByteBuffer</code> object is not a UTF8 Byte sequence.</td>
  </tr>
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
<h5 id="r-string-getnumberofbytes">getNumberOfBytes</h5>
<p><code>
R_SizeValue R_String_getNumberOfBytes(R_String const* self)
</code></p>

<p>Get the size, in Bytes, of this string.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size, in Bytes, of this string.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-getbyteat">getByteAt</h5>
<p><code>
R_Natural8Value R_String_getByteAt(R_String const* self, R_SizeValue index)
</code></p>

<p>Get the Byte value at the specified index.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
  <tr><td>R_SizeValue index</td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size, in Bytes, of this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The Byte value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tointeger8">toInteger8</h5>
<p><code>
R_Integer8Value R_String_toInteger8(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that integer literal into an <code>R_Integer8Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an integer literal or the number represented by the integer literal cannot be represented a value of type <code>R_Integer8Value</code>.</td>
  </tr>
</table>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tointeger16">toInteger16</h5>
<p><code>
R_Integer16Value R_String_toInteger16(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that integer literal into an <code>R_Integer16Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an integer literal or the number represented by the integer literal cannot be represented a value of type <code>R_Integer16Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tointeger32">toInteger32</h5>
<p><code>
R_Integer32Value R_String_toInteger32(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that integer literal into an <code>R_Integer32Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an integer literal or the number represented by the integer literal cannot be represented a value of type <code>R_Integer32Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tointeger64">toInteger64</h5>
<p><code>
R_Integer64Value R_String_toInteger64(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that integer literal into an <code>R_Integer64Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an integer literal or the number represented by the integer literal cannot be represented a value of type <code>R_Integer64Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tonatural8">toNatural8</h5>
<p><code>
R_Natural8Value R_String_toNatural8(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal natural literal and convert the number represented by that natural literal into an <code>R_Natural8Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an natural literal or the number represented by the natural literal cannot be represented a value of type <code>R_Natural8Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tonatural16">toNatural16</h5>
<p><code>
R_Natural16Value R_String_toNatural16(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal natural literal and convert the number represented by that natural literal into an <code>R_Natural16Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an natural literal or the number represented by the natural literal cannot be represented a value of type <code>R_Natural16Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tonatural32">toNatural32</h5>
<p><code>
R_Natural32Value R_String_toNatural16(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal natural literal and convert the number represented by that natural literal into an <code>R_Natural32Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an natural literal or the number represented by the natural literal cannot be represented a value of type <code>R_Natural32Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-string-tonatural64">toNatural64</h5>
<p><code>
R_Natural64Value R_String_toNatural16(R_String const* self)
</code></p>

<p>Interprete the symbols of this string as decimal natural literal and convert the number represented by that natural literal into an <code>R_Natural64Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>R_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>R_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as an natural literal or the number represented by the natural literal cannot be represented a value of type <code>R_Natural64Value</code>.</td>
  </tr>
</table>
