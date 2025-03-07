<h4 id="Arcadia_Stack">Stack</h4>
<p>
<code>Arcadia_Stack</code> represents a stack of <code>Arcadia_Value</code> objects.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_Stack</code> pointers.
A <code>Arcadia_Stack</code> pointer can be safely cast into a <code>Arcadia_ObjectReferenceValue</code> values.
An <code>Arcadia_ObjectReferenceValue</code> pointing to a <code>Arcadia_Stack</code> value can be safely cast into a <code>Arcadia_Stack</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_Stack_create">Arcadia_Stack_create</h5>
<p><code>
Arcadia_Stack*
Arcadia_Stack_create
  (
    Arcadia_Thread* thread
  )
</code></p>

<p>Create a stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the <code>R_Stack</code> value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_Stack_clear">Arcadia_Stack_clear</h5>
<p><code>
void
Arcadia_Stack_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
</code></p>

<p>Clear this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Stack* self</td><td>A pointer to this stack.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_Stack_getSize">Arcadia_Stack_getSize</h5>
<p><code>
Arcadia_SizeValue
Arcadia_Stack_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Stack const* self
  )
</code></p>

<p>Get the size of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Stack* self</td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this stack.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_Stack_isEmpty">Arcadia_Stack_isEmpty</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_Stack_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
</code></p>

<p>Get if this stack is empty.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Stack* self</td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p><code>Arcadia_BooleanValue_True</code> if this stack is empty. <code>Arcadia_BooleanValue_False</code> otherwise.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_Stack_peek">Arcadia_Stack_peek</h5>
<p><code>
Arcadia_Value
Arcadia_Stack_peek
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
</code></p>

<p>Peek at the value on top of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Stack self </td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The value.</p>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_Stack_pop">Arcadia_Stack_pop</h5>
<p><code>
Arcadia_Value
Arcadia_Stack_pop
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
</code></p>

<p>Pop the value from the top of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Stack* self                     </td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_Stack_push">Arcadia_Stack_push</h5>
<p><code>
void
Arcadia_Stack_push
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self,
    Arcadia_Value value
  )
</code></p>

<p>Push a value on the top of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Stack* self            </td><td>A pointer to this stack.</td></tr>
  <tr><td>Arcadia_Value value            </td><td>The value to push.</td></tr>
</table>
