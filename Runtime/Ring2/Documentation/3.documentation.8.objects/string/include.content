<section class="cxx entity object">
<h1 id="Arcadia_String">Arcadia_String</h1>
<p>
<code>Arcadia_String</code> represents an Unicode string encoded as UTF-8-NO-BOM.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_String</code> pointers.
A <code>Arcadia_String</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_String</code> value can be safely cast into a <code>Arcadia_String</code> pointer.
</p>

<p>Arcadia_String derives fro Arcadia_Object and overrides the following methods:</p>
<ul>
  <li>Arcadia_Object_equalTo</li>
  <li>Arcadia_Object_hash</li>
  <li>Arcadia_Object_notEqualTo</li>
</ul>
</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_create_pn">
    Arcadia_String_create_pn
  </h1>

  <my-signature><code>
    Arcadia_String*<br>
    Arcadia_String_create_pn<br>
    &nbsp;&nbsp;(<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_ImmutableByteArray* immutableByteArray<br>
    &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
    Create a string from an immutable Byte array.
  </my-summary>

  <section class="cxx parameters">

    <h1>Parameters</h1>

    <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
    <tr><td>Arcadia_ImmutableByteBuffer* immutableByteArray</td><td>A pointer to the <code>Arcadia_ImmutableByteArray</code> object</td></tr>

  </section>

  <section class="cxx return-value">

    <h1>Return value</h1>
    <p>A pointer to the <code>Arcadia_String</code> object.</p>

  </section>

  <section class="cxx errors">

    <h1>Errors</h1>

    <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>immutableByteArray</code> is a null pointer.</td></tr>
    <tr><td>Arcadia_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>

  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<section class="cxx entity method">

  <h1 id="Arcadia_String_create">
    Arcadia_String_create
  </h1>

  <my-signature><code>
    Arcadia_String*<br>
    Arcadia_String_create<br>
    &nbsp;&nbsp;(<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Value value<br>
    &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>

    <p>Create a string from a value.</p>

    <p>The following values are accepted:</p>

    <p>
    The specified value may contain a <code>Arcadia_ByteBuffer</code> object.
    In that case, the string is created from the Bytes of the Byte buffer object.
    A <code>Arcadia_Status_EncodingInvalid</code> is raised if the Byte sequence of that <code>Arcada_ByteBuffer</code> object is not a UTF8 Byte sequence.
    </p>

    <p>
    The specified value may contain a <code>Arcadia_ImmutableByteArray</code> object.
    In that case, the string is created from the <code>Arcadia_ImmutableByteArray</code> object.
    A <code>Arcadia_Status_EncodingInvalid</code> is raised if the Byte sequence of that <code>Arcada_ImmutableByteArray</code> object is not a UTF8 Byte sequence.
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
    The specified value may contain a <code>Arcadia_ImmutableUtf8String</code> object.
    In that case, the string is created from the <code>Arcadia_ImmutableUtf8String</code> object.
    </p>

  </my-summary>

  <section class="cxx parameters">

    <h1>Parameters</h1>

    <div>
      <div>
        <a href="#">Arcadia_Thread</a>* thread
      </div>
      <div>
        A pointer to the <code>Arcadia_Thread</code> object.
      </div>
    </div>
    <div>
      <div>Arcadia_Value value</div>
      <div>The value.</div>
    </div>

  </section>

  <section class="cxx return-value">

    <h1>Return value</h1>
    <p>A pointer to the string.</p>

  </section>

  <section class="cxx errors">

    <h1>Errors</h1>

    <div>
      <div>
        Arcadia_Status_ArgumentTypeInvalid
      </div>
      <div>
        The value is not of type <code>Arcadia_ByteBuffer</code>, <code>Arcadia_String</code>, <code>Arcadia_StringBuffer</code>, or <code>Arcadia_ImmutableByteArray</code>.
      </div>
    </div>
    <div>
      <div>
        Arcadia_Status_EncodingInvalid
      </div>
      <div>
        The value is a <code>Arcadia_ByteBuffer</code> or <code>Arcadia_ImmutableByteArray</code>.
        However, the Byte sequence of that <code>Arcadia_ByteBuffer</code> or <code>Arcadia_ImmutableByteArray</code> object is not a UTF8 Byte sequence.
      </div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_endsWith_pn">Arcadia_String_endsWith_pn</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_String_endsWith_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a sequence of Bytes is a suffix of this string's sequence of Bytes.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
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
    <h1>Return value</my-return-value>
    <p>
    <code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a suffix of this string's sequence of Bytes.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_startsWith_pn">Arcadia_String_startsWith_pn</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_String_startsWith_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
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
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
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
    <code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is a prefix of this string's sequence of Bytes.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_isEqualTo_pn">Arcadia_String_isEqualTo_pn</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_String_isEqualTo_pn<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;void const* bytes,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue numberOfBytes<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get if a sequence of Bytes is this string's sequence of Bytes.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
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
    <code>Arcadia_BooleanValue_True</code> if the sequence of Bytes is this string's sequence of Bytes.
    <code>Arcadia_BooleanValue_False</code> otherwise.
    </p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_getNumberOfBytes">Arcadia_String_getNumberOfBytes</h1>

  <my-signature><code>
  Arcadia_SizeValue<br>
  Arcadia_String_getNumberOfBytes<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the size, in Bytes, of this string.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The size, in Bytes, of this string.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_getByteAt">Arcadia_String_getByteAt</h1>

  <my-signature><code>
  Arcadia_Natural8Value<br>
  Arcadia_String_getByteAt<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_SizeValue index<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the Byte value at the specified index.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
    <div>
      <div>Arcadia_SizeValue index</div>
      <div>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size, in Bytes, of this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The Byte value.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toBoolean">Arcadia_String_toBoolean</h1>

  <my-signature><code>
  Arcadia_BooleanValue<br>
  Arcadia_String_toBoolean<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as boolean literal and convert the boolean represented by that literal into an <code>Arcadia_BooleanValue</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The boolean value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <tr>
      <td>Arcadia_Status_ArgumentTypeInvalid</td>
      <td><code>self</code> is a null pointer.</td>
    </tr>
    <tr>
      <td>Arcadia_Status_ConversionFailed</td>
      <td>The symbols of this string cannot be interpreted as a boolean literal. Valid boolean literals are <code>true</code> and <code>false</code>, both case sensitve.</td>
    </tr>
  </<section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toInteger16">Arcadia_String_toInteger16</h1>

  <my-signature><code>
  Arcadia_Integer16Value<br>
  Arcadia_String_toInteger16<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as decimal integer literal and convert the number represented by that integer literal into an <code>Arcadia_Integer16Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
    <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The integer value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal integer literal or
      the number represented by the literal cannot be represented a value of type <code>Arcadia_Integer16Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toInteger32">Arcadia_String_toInteger32</h1>

  <my-signature><code>
  Arcadia_Integer32Value<br>
  Arcadia_String_toInteger32<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as decimal integer literal and convert the number represented by that literal into an <code>Arcadia_Integer32Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The integer value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal integer literal or
      the number represented by the literal cannot be represented a value of type <code>
      Arcadia_Integer32Value</code>.
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toInteger64">Arcadia_String_toInteger64</h1>

  <my-signature><code>
  Arcadia_Integer64Value<br>
  Arcadia_String_toInteger64<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as decimal integer literal and convert the number represented by that literal into an <code>Arcadia_Integer64Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The integer value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal integer literal or
           the number represented by the literal cannot be represented a value of type <code>
           Arcadia_Integer64Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toInteger8">Arcadia_String_toInteger8</h1>

  <my-signature><code>
  Arcadia_Integer8Value<br>
  Arcadia_String_toInteger8<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as decimal integer literal and convert the number represented by that literal into an <code>Arcadia_Integer8Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
    <div>
      <div>Arcadia_String* self</div><div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The integer value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</dov>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal integer literal or
      the number represented by the integer literal cannot be represented a value of type <code>Arcadia_Integer8Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toNatural16">Arcadia_String_toNatural16</h1>

  <my-signature><code>
  Arcadia_Natural16Value<br>
  Arcadia_Stringg_toNatural16<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural16Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The natural value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</td>
      <div>The symbols of this string cannot be interpreted as a decimal natural literal or
      the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural16Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toNatural32">Arcadia_String_toNatural32</h1>

  <my-signature><code>
  Arcadia_Natural32Value<br>
  Arcadia_String_toNatural32<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural32Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
    <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The natural value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal natural literal or
      the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural32Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toNatural64">Arcadia_String_toNatural64</h1>

  <my-signature><code>
  Arcadia_Natural64Value<br>
  Arcadia_String_toNatural64<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as a decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural64Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The natural value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
    <div>Arcadia_Status_ArgumentTypeInvalid</div>
    <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
    <div>Arcadia_Status_ConversionFailed</td>
    <div>The symbols of this string cannot be interpreted as a decimal natural literal or
    the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural64Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toNatural8">Arcadia_String_toNatural8</h1>

  <my-signature><code>
  Arcadia_Natural8Value<br>
  Arcadia_String_toNatural8<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as a decimal natural literal and convert the number represented by that literal into an <code>Arcadia_Natural8Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The natural value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</td>
      <div>The symbols of this string cannot be interpreted as a decimal natural literal or
      the number represented by the literal cannot be represented a value of type <code>Arcadia_Natural8Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toReal32">Arcadia_String_toReal32</h1>

  <my-signature><code>
  Arcadia_Real32Value<br>
  Arcadia_String_toReal32<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as a decimal real literal and convert the number represented by that literal into an <code>Arcadia_Real32Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The <code>Arcadia_Real32Value</code> value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal real literal or
      the number represented by the literal cannot be represented a value of type <code>Arcadia_Real32Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toReal64">Arcadia_String_toReal64</h1>

  <my-signature><code>
  Arcadia_Real64Value<br>
  Arcadia_String_toReal64<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as a decimal real literal and convert the number represented by that literal into an <code>Arcadia_Real64Value</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <div>
      <div><a href="#">Arcadia_Thread</a>* thread</div>
      <div>A pointer to the <code>Arcadia_Thread</code> object.</div>
    </div>
    <div>
      <div>Arcadia_String* self</div>
      <div>A pointer to this string.</div>
    </div>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The <code>Arcadia_Real64Value</code> value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a decimal real literal or
      the number represented by the literal cannot be represented a value of type <code>Arcadia_Real64Value</code>.</div>
    </div>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_String_toVoid">Arcadia_String_toVoid</h1>

  <my-signature><code>
  Arcadia_VoidValue<br>
  Arcadia_String_toVoid<br>
  &nbsp;&nbsp;(<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_Thread* thread,<br>
  &nbsp;&nbsp;&nbsp;&nbsp;Arcadia_String const* self<br>
  &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Interprete the symbols of this string as a void literal and convert the void value represented by that literal into an <code>Arcadia_VoidValue</code>.
  </my-summary>

  <section class="cxx parameters">
    <h1>Parameters</h1>
    <tr><td><a href="#">Arcadia_Thread</a>* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
    <tr><td>Arcadia_String* self</td><td>A pointer to this string.</td></tr>
  </section>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The void value.</p>
  </section>

  <section class="cxx errors">
    <h1>Errors</h1>
    <div>
      <div>Arcadia_Status_ArgumentTypeInvalid</div>
      <div><code>self</code> is a null pointer.</div>
    </div>
    <div>
      <div>Arcadia_Status_ConversionFailed</div>
      <div>The symbols of this string cannot be interpreted as a void literal. The valid void literal is <code>void</code>, case sensitve.</div>
    </div>
  </section>

</section>
