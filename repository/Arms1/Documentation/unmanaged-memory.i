<h2>Unmanaged Memory</h2>
<p>ARMS1 allows for allocation, reallocation, and deallocation of <em>unmanaged</em> memory.</p>

<h3>Arms_allocateUnmanaged</h3>
<p><code>
Arms_Status Arms_allocateUnmanaged(void** p, size_t n);
</code></p>
<p>
Allocates an unmanaged memory block of size <code>n</code>.
</p>

<p>
<em>If this function succeeds</em>:
A pointer to the beginning of the memory block is stored in <code>*p</code>.
<code>Arms_Status_Success</code> is returned.
</p>

<p>
<em>If this function fails</em>:
The environment is not observably changed.
The function returns one of the status code in the table below.
</p>

<table>
  <tr><td>Status Code</td><td>Description</td></tr>
  <tr><td>Arms_Status_AllocationFailed</td><td>The allocation failed.</td></tr>
  <tr><td>Arms_Status_ArgumentValueInvalid</td><td><code>p</code> is a null pointer.</td></tr>
</table>


<p>Note that <code>n</code> can be 0 as 0 is a valid size for a memory block.</p>


<h3>Arms_reallocateUnmanaged</h3>
<p><code>
Arms_Status Arms_rallocateUnmanaged(void** p, size_t n);
</code></p>

<p>
<em>If this function succeeds</em>:
A pointer to the beginning of the new memory block is stored in <code>*p</code>.
The first <my-mv>k</my-mv> values of the new memory memory block and the old memory block are equal
where <code><my-mv>k</my-mv></code> is <code>min(n, <my-mv>m</my-mv>)</code> where <code>n</code> is the size of the
new memory block and <my-mv>m</my-mv> is the size of the new memory block.
<code>Arms_Status_Success</code> is returned.
</p>

<p>
<em>If this function fails</em>:
The environment is not observably changed.
The function returns one of the status code in the table below.
</p>

<table>
  <tr><td>Status Code</td><td>Description</td></tr>
  <tr><td>Arms_Status_AllocationFailed</td><td>The allocation failed.</td></tr>
  <tr><td>Arms_Status_ArgumentValueInvalid</td><td><code>p</code> is a null pointer.</td></tr>
</table>

<p>Note that <code>n</code> can be 0 as 0 is a valid size for a memory block.</p>

<h3>Arms_deallocateUnmanaged</h3>
<p><code>
Arms_Status Arms_deallocateUnmanaged(void* p);
</code></p>

<p>Deallocates an unmanaged memory block.</p>
<p>
<em>If this function succeeds</em>:
The memory block pointed to by <code>p</code> was deallocated.
</p>

<p>
<em>If this function fails</em>:
The environment is not observably changed.
This function fails only if <code>p</code> is a null pointer. In that case, it returns <code>Arms_Status_ArgumentValueInvalid</code>.
</p>
