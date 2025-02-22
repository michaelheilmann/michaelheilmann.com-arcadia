<h4 id="Arcadia_List">Arcadia_List</h4>
<p>
<code>Arcadia_List</code> represents a list of <code>Arcadia_Value</code> objects.
This type is allocated on the heap and values of this type are referenced by <code>Arcadia_List</code> pointers.
A <code>R_List</code> pointer can be safely cast into a <code>R_ObjectReferenceValue</code> values.
An <code>R_ObjectReferenceValue</code> pointing to a <code>R_List</code> value can be safely cast into a <code>Arcadia_List</code> pointer.
</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_List_create">Arcadia_List_create</h5>
<p><code>
Arcadia_List*
Arcadia_List_create
  (
    Arcadia_Process* process
  )
</code></p>

<p>Create a list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_AllocationFailed</td><td>An allocation failed.</td></tr>
</table>

<h6><b>Return value</b></h6>
<p>A pointer to the <code>Arcadia_List</code> value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_List_append">Arcadia_List_append</h5>
<p><code>
void
Arcadia_List_append
  (
    Arcadia_Process* process,
    Arcadia_List* self,
    Arcadia_Value value
  )
</code></p>

<p>Append a value to this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self                      </td><td>A pointer to this list.</td></tr>
  <tr><td>Arcadia_Value value                     </td><td>The value to append.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_List_clear">Arcadia_List_clear</h5>
<p><code>
void
Arcadia_List_clear
  (
    Arcadia_Process* process,
    Arcadia_List* self
  )
</code></p>

<p>Clear this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self                      </td><td>A pointer to this list.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_List_getAt">Arcadia_List_getAt</h5>
<p><code>
Arcadia_Value
Arcadia_List_getAt
  (
    Arcadia_Process* process,
    Arcadia_List* self,
    Arcadia_SizeValue index
  )
</code></p>

<p>Get the value at the specifie index in this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self                      </td><td>A pointer to this list.</td></tr>
  <tr><td>Arcadia_SizeValue index                 </td><td>The index. Must be within the bounds <code>[0,n)</code> where <code>n</code> is the size of this list.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>index</code> is out of bounds.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The value.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_List_getSize">Arcadia_List_getSize</h5>
<p><code>
Arcadia_SizeValue
Arcadia_List_getSize
  (
    Arcadia_Process* process,
    Arcadia_List const* self
  )
</code></p>

<p>Get the size of this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self</td><td>A pointer to this list.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>index</code> is out of bounds.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p>The size of this list.</p>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_List_insertAt">Arcadia_List_insert</h5>
<p><code>
void
Arcadia_List_insertAt
  (
    Arcadia_Process* process,
    Arcadia_List* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
</code></p>

<p>Insert a value at the specified position in this list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self                      </td><td>A pointer to this list.</td></tr>
  <tr><td>Arcadia_SizeValue index                 </td><td>The index at which to insert the value. Must be within the bounds of <code>[0,n]</code> where <code>n</code> is the size of thie list.</td></tr>
  <tr><td>Arcadia_Value value                      </td><td>The value to insert.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>index</code> is out of bounds.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_List_isEmpty">Arcadia_List_isEmpty</h5>
<p><code>
Arcadia_BooleanValue
Arcadia_List_isEmpty
  (
    Arcadia_Process* process,
    Arcadia_List* self
  )
</code></p>

<p>Get if this list is empty.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self</td><td>A pointer to this list.</td></tr>
</table>

<h6><b>Return Value</b></h6>
<p><code>Arcadia_BooleanValue_True</code> if this list is empty. <code>Arcadia_BooleanValue_False</code> otherwise.</p>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<h5 id="Arcadia_List_prepend">Arcadia_List_prepend</h5>
<p><code>
void
Arcadia_List_prepend
  (
    Arcadia_Process* process,
    Arcadia_List* self,
    Arcadia_Value value
  )
</code></p>

<p>Prepend a value to this list.</p>

<p>Prepend a <code>R_Value</code> to a list.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>R_List* self           </td><td>A pointer to this list.</td></tr>
  <tr><td>R_Value value          </td><td>The value to prepend.</td></tr>
</table>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
<h5 id="Arcadia_List_remove">Arcadia_List_remove</h5>
<p><code>
void
Arcadia_List_remove
  (
    Arcadia_Process* process,
    Arcadia_List* self,
    Arcadia_SizeValue start,
    Arcadia_SizeValue length
  )
</code></p>

<p>Remove <code>length</code> values starting with element at index <code>start</code>.</p>

<h6><b>Parameters</b></h6>
<table>
  <tr><td><a href="#">Arcadia_Process</a>* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>Arcadia_List* self</td><td>A pointer to this list.</td></tr>
  <tr><td>Arcadia_SizeValue start</td><td>The index of the first element to remove.</td></tr>
  <tr><td>Arcadia_SizeValue length</td><td>The number of elements to remove.</td></tr>
</table>

<h6><b>Errors</b></h6>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>self</code> is a null pointer.</td></tr>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>index + length &gt; n</code> where <code>n</code> is the length of the list.</td></tr>
</table>
