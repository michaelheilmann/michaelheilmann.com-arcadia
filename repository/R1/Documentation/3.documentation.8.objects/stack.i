<h4 id="r-stack">Stack</h4>
<p>
<code>R_Stack</code> represents a stack of <code>R_Value</code> objects.
This type is allocated on the heap and values of this type are referenced by <code>R_Stack</code> pointers.
A <code>R_Stack</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_Stack</code> value can be safely cast into a <code>R_Stack</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-stack-create">R_Stack_create</h5>
<p><code>
R_Stack* R_Stack_create()
</code></p>

<p>Create a stack.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>bytes</code> is a null pointer.</td></tr>
  <tr><td>R_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the <code>R_Stack</code> value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-stack-clear">clear</h5>
<p><code>
void R_Stack_clear(R_Stack* self)
</code></p>

<p>Clear this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_Stack* self</td><td>A pointer to this stack.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-stack-getsize">getSize</h5>
<p><code>
R_SizeValue R_Stack_getSize(R_Stack const* self)
</code></p>

<p>Get the size of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_Stack* self</td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this stack.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-stack-isempty">isEmpty</h5>
<p><code>
R_BooleanValue R_Stack_isEmpty(R_Stack* self)
</code></p>

<p>Get if this stack is empty.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_Stack* self</td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p><code>R_BooleanValue_True</code> if this stack is empty. <code>R_BooleanValue_False</code> otherwise.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-stack-peek">peek</h5>
<p><code>
R_Value R_Stack_peek(R_Stack* self)
</code></p>

<p>Peek at the value on top of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_Stack self </td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The value.</p>


<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-stack-pop">pop</h5>
<p><code>
R_Value R_Stack_pop(R_Stack* self)
</code></p>

<p>Pop the value from the top of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_Stack self </td><td>A pointer to this stack.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-stack-push">push</h5>
<p><code>
void R_Stack_push(R_Stack* self, R_Value value)
</code></p>

<p>Push a value on the top of this stack.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_Stack* self            </td><td>A pointer to this stack.</td></tr>
  <tr><td>R_Value value            </td><td>The value to push.</td></tr>
</table>
