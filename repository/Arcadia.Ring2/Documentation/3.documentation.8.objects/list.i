<h4 id="r-list">List</h4>
<p>
<code>R_List</code> represents a list of <code>R_Value</code> objects.
This type is allocated on the heap and values of this type are referenced by <code>R_List</code> pointers.
A <code>R_List</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_List</code> value can be safely cast into a <code>R_List</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-list-create">R_List_create</h5>
<p><code>
R_List* R_List_create()
</code></p>

<p>Create a list.</p>

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

<h6><b>Return value</b></h6>
<p>A pointer to the <code>R_List</code> value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-list-append">append</h5>
<p><code>
void R_List_append(R_List* self, R_Value value)
</code></p>

<p>Append a <code>R_Value</code> to a list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self           </td><td>A pointer to this list.</td></tr>
  <tr><td>R_Value value          </td><td>The value to append.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-list-clear">clear</h5>
<p><code>
void R_List_clear(R_List* self)
</code></p>

<p>Clear this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self</td><td>A pointer to this list.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-list-getat">getAt</h5>
<p><code>
R_Value R_List_getAt(R_List* self, R_SizeValue index)
</code></p>

<p>Get the value at the specifie index in this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self</td><td>A pointer to this list.</td></tr>
  <tr><td>R_SizeValue index</td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size of this list.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-list-getsize">getSize</h5>
<p><code>
R_SizeValue R_List_getSize(R_List const* self)
</code></p>

<p>Get the size of this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self</td><td>A pointer to this list.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this list.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-list-insertat">insert</h5>
<p><code>
void R_List_insertAt(R_List* self, R_SizeValue index, R_Value value)
</code></p>

<p>Compare this string with another string for equality.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self      </td><td>A pointer to this list.</td></tr>
  <tr><td>R_SizeValue index </td><td>The index at which to insert the value. Must be within the bounds of <code>[0,n]</code> where <code>n</code> is the size of thie list.</td></tr>
  <tr><td>R_Value value     </td><td>The value to insert.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-list-isempty">isEmpty</h5>
<p><code>
R_BooleanValue R_List_isEmpty(R_List* self)
</code></p>

<p>Get if this list is empty.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self</td><td>A pointer to this list.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p><code>R_BooleanValue_True</code> if this list is empty. <code>R_BooleanValue_False</code> otherwise.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="r-list-prepend">prepend</h5>
<p><code>
void R_List_prepend(R_List* self, R_Value value)
</code></p>

<p>Get if a sequence of Bytes is a prefix of this string's sequence of Bytes.</p>

<p>Prepend a <code>R_Value</code> to a list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self           </td><td>A pointer to this list.</td></tr>
  <tr><td>R_Value value          </td><td>The value to prepend.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="r-list-remove">remove</h5>
<p><code>
void R_List_remove(R_List* self, R_SizeValue index, R_SizeValue count)
</code></p>

<p>Remove <code>length</code> elements starting with element at index <code>index</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td>R_List* self</td><td>A pointer to this list.</td></tr>
  <tr><td>R_SizeValue index</td><td>The index of the first element to remove.</td></tr>
  <tr><td>R_SizeValue length</td><td>The number of elements to remove.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>index + count > n</code> where <code>n</code> is the length of the list.</td></tr>
</table>
