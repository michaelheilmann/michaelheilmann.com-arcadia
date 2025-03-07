<h4 id="Arcadia_String">Arcadia_String</h4>
<p>
<code>Arcadia_String</code> represents an Unicode string encoded as UTF-8-NO-BOM.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_String</code> pointers.
A <code>Arcadia_String</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>R_String</code> value can be safely cast into a <code>R_String</code> pointer.
</p>

<p>Arcadia_String derives fro Arcadia_Object and overrides the following methods:</p>
<ul>
  <li>Arcadia_Object_equalTo</li>
  <li>Arcadia_Object_hash</li>
  <li>Arcadia_Object_notEqualTo</li>
</ul>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_create_pn">Arcadia_String_create_pn</h5>
<p><code>
Arcadia_String*
Arcadia_String_create_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArray* immutableByteArray
  )
</code></p>

<p>Create a string from an immutable Byte array.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_ImmutableByteBuffer* immutableByteArray</td><td>A pointer to the <code>Arcadia_ImmutableByteArray</code> object</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the <code>Arcadia_String</code> object.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>immutableByteArray</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_create">Arcadia_String_create</h5>
<p><code>
Arcadia_String*
Arcadia_String_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  )
</code></p>

<p>
Create a string from a value.
</p>

<p>The following values are accepted:</p>

<p>
The specified value may contain a <code>Arcadia_ByteBuffer</code> object.
In that case, the string is created from the Bytes of the Byte buffer object.
A <code>Arcadia_Status_EncodingInvalid</code> is raised if the Byte sequence of that <code>Arcada_ByteBuffer</code> object is not a UTF8 Byte sequence.
</p>

<p>
The specified value may contain a <code>Arcadia_String</code> object.
In that case, the string is created from the <code>Arcadia_String</code> object.
</p>

<p>
The specified value may contain a <code>Arcadia_StringBuffer</code> object.
In that case, the string is created from the <code>Arcadia_StringBuffer</code> object.
</p>

<p>
The specified value may contain a <code>Arcadia_ImmutableByteArray</code> object.
In that case, the string is created from the <code>Arcadia_ImmutableByteArray</code> object.
A <code>Arcadia_Status_EncodingInvalid</code> is raised if the Byte sequence of that <code>Arcada_ImmutableByteArray</code> object is not a UTF8 Byte sequence.
</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Value value     </td><td>The value.</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the string. </p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td>The value is not of type <code>Arcadia_ByteBuffer</code>, <code>Arcadia_String</code>, <code>Arcadia_StringBuffer</code>, or <code>Arcadia_ImmutableByteArray</code>.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_EncodingInvalid</td>
    <td>
    The value is a <code>Arcadia_ByteBuffer</code> or <code>Arcadia_ImmutableByteArray</code>.
    However, the Byte sequence of that <code>Arcadia_ByteBuffer</code> or <code>Arcadia_ImmutableByteArray</code> object is not a UTF8 Byte sequence.
    </td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_String_endsWith_pn">Arcadia_String_endsWith_pn</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_String_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Get if a sequence of Bytes is a suffix of this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self                    </td><td>A pointer to this string.</td></tr>
  <tr><td>void const* bytes                       </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes         </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a suffix of this string's sequence of Bytes.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_String_startsWith_pn">Arcadia_String_startsWith_pn</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_String_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Get if a sequence of Bytes is a prefix of this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self                    </td><td>A pointer to this string.</td></tr>
  <tr><td>void const* bytes                       </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes         </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a prefix of this string's sequence of Bytes.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_isEqualTo_pn">Arcadia_String_isEqualTo_pn</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_String_isEqualTo_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
</code></p>

<p>Get if a sequence of Bytes is this string's sequence of Bytes.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self                   </td><td>A pointer to this string.</td></tr>
  <tr><td>void const* bytes                      </td><td>A pointer to an array of <code>n</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes        </td><td>The number of Bytes in the array pointed to by <code>p</code>.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>
<code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is this string's sequence of Bytes.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_getNumberOfBytes">Arcadia_String_getNumberOfBytes</h5>
<p><code>
Arcadia_SizeValue
Arcadia_String_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Get the size, in Bytes, of this string.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size, in Bytes, of this string.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_getByteAt">Arcadia_String_getByteAt</h5>
<p><code>
Arcadia_Natural8Value
Arcadia_String_getByteAt
  (
    Arcadia_String const* self,
    Arcadia_SizeValue index
  )
</code></p>

<p>Get the Byte value at the specified index.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
  <tr><td>Arcadia_SizeValue index</td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size, in Bytes, of this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The Byte value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toBoolean">Arcadia_String_toBoolean</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_String_toBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as boolean literal and convert the boolean represented by that literal into an <code>Arcadia_BooleanValue</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The boolean value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a boolean literal. Valid boolean literals are <code>true</code> and <code>false</code>, both case sensitve.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toInteger16">Arcadia_String_toInteger16</h5>
<p><code>
Arcadia_Integer16Value
Arcadia_String_toInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that integer literal into an <code>Arcadia_Integer16Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal integer literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Integer16Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toInteger32">Arcadia_String_toInteger32</h5>
<p><code>
Arcadia_Integer32Value
Arcadia_String_toInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that literal into an <code>Arcadia_Integer32Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal integer literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Integer32Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toInteger64">Arcadia_String_toInteger64</h5>
<p><code>
Arcadia_Integer64Value
Arcadia_String_toInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that literal into an <code>Arcadia_Integer64Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>R_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal integer literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Integer64Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toInteger8">Arcadia_String_toInteger8</h5>
<p><code>
Arcadia_Integer8Value
Arcadia_String_toInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as decimal integer literal and convert the number represented by that literal into an <code>Arcadia_Integer8Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The integer value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal integer literal or
    the number represented by the integer literal cannot be represented a value of type <code>Arcadia_Integer8Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toNatural16">Arcadia_String_toNatural16</h5>
<p><code>
Arcadia_Natural16Value
Arcadia_Stringg_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural16Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal natural literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural16Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toNatural32">Arcadia_String_toNatural32</h5>
<p><code>
Arcadia_Natural32Value
Arcadia_String_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural32Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal natural literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural32Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toNatural64">Arcadia_String_toNatural64</h5>
<p><code>
Arcadia_Natural64Value
Arcadia_String_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as a decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural64Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal natural literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural64Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toNatural8">Arcadia_String_toNatural8</h5>
<p><code>
Arcadia_Natural8Value
Arcadia_String_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as a decimal natural literal and convert the number represented by that literal into an <code>R_Natural8Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The natural value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal natural literal or
    the number represented by the literal cannot be represented a value of type <code>R_Natural8Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toReal32">Arcadia_String_toReal32</h5>
<p><code>
Arcadia_Real32Value
Arcadia_String_toReal32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as a decimal real literal and convert the number represented by that literal into an <code>Arcadia_Real32Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The <code>Arcadia_Real32Value</code> value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal real literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Real32Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toReal64">Arcadia_String_toReal64</h5>
<p><code>
Arcadia_Real64Value
Arcadia_String_toReal64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as a decimal real literal and convert the number represented by that literal into an <code>Arcadia_Real64Value</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The <code>Arcadia_Real64Value</code> value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a decimal real literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Real64Value</code>.</td>
  </tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_String_toVoid">Arcadia_String_toVoid</h5>
<p><code>
Arcadia_VoidValue
Arcadia_String_toVoid
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  )
</code></p>

<p>Interprete the symbols of this string as a void literal and convert the void value represented by that literal into an <code>R_VoidValue</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The void value.</p>

<h6><b>Errors</b></h6>
<table>
  <tr>
    <td>Arcadia_Status_ArgumentTypeInvalid</td>
    <td><code>self</code> is a null pointer.</td>
  </tr>
  <tr>
    <td>Arcadia_Status_ConversionFailed</td>
    <td>The symbols of this string cannot be interpreted as a void literal. The valid void literal is <code>void</code>, case sensitve.</td>
  </tr>
</table>
