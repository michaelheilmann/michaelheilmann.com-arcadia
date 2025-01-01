<h2>3. Managed Memory</h2>

<h3>3.1 Creating types</h3>
<p>The user adds a type to the ARMS1 by invoking <code>Arms_Status Arms_addType(const char* name, size_t nameLength, 
void* context, Arms_TypeRemovedCallbackFunction* typeRemoved, Arms_VisitCallbackFunction *visit, Arms_FinalizeCallbackFunction* finalize)</code>. The first argument <code>name</code> is
a pointer to an array of <code>nameLength</code> Bytes denoting the type name. No two types of the same name can be
registered and this function fails with <code>Arms_Status_TypeExists</code> if an attempt is made to do so. <code>visit</code>
must point to a <code>Arms_VisitCallbackFunction</code> or must be a null pointer. <code>finalize</code> must point to a
<code>Arms_FinalizeCallbackFunction</code> or must be a null pointer. <code>typeRemoved</code> must point to a <code>Arms_TypeRemovedCallbackFunction</code>
or must be a null pointer. <code>context</code> is an opaque pointer which is passed to the type removed callback function,
the visit callback function, and the finalize callback function. If <code>Arms_addType</code> fails it returns a value different from
<code>Arms_Status_Success</code>. The following table lists the possible values returned in case of failure
</p>
<table>
  <tr><td>Value</td><td>Description</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>pObject</code> is a null pointer</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>name</code> is a null pointer</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>nameLength</code> exceeds limits</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>size</code> exceeds limits</td></tr>
  <tr><td><code>Arms_Status_AllocationFailed</code></td><td>an allocation failed</td></tr>
</table>

@{include("managed-memory/type-removed-callback-function.i")}
@{include("managed-memory/visit-callback-function.i")}
@{include("managed-memory/finalize-callback-function.i")}

<h3>3.2 Creating objects</h3>
<p>
To create an object, the user of ARMS1 creates an object by invoking <code>Arms_Status Arms_allocate(void** pObject,
char const* name, size_t nameLength, size_t size)</code>. <code>name</code> is a pointer to an array of <code>nameLength</code> Bytes
denoting the type name of the type to be assigned to object. <code>size</code> denotes the size, in Bytes, of the object to allocated
(0 is a valid size). If this function is invoked successfully, the <code>*pObject</code> is assigned a pointer to an object of the
specified size. The contents of the Bytes are unspecified. The object is assigned the type of the specified name. 
If this function fails it returns a value different from  <code>Arms_Status_Success</code>.
The following table lists the possible values returned in case of failure
</p>
<table>
  <tr><td>Value</td><td>Description</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>pObject</code> is a null pointer</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>name</code> is a null pointer</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>nameLength</code> exceeds limits</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>size</code> exceeds limits</td></tr>
  <tr><td><code>Arms_Status_TypeNotExists</code></td><td>the type does not exist</td></tr>
  <tr><td><code>Arms_Status_AllocationFailed</code></td><td>an allocation failed</td></tr>
</table>

<h3>3.3 Freeing resources</h3>
<p>To relinqish resources, the user invokes <code>Arms_Status Arms_run()</code> which destroys dead objects \(D\) such that the new universe
only contains live objects, in other terms \(U@@new = U@@old - D\) or equivalently \(U@@new = L\) holds.</p>

<p><code>Arms_run</code> always succeeds.</p>

<h3>3.4 Locks</h3>
<p>
A locked object \(x\) is element of the root set \(R\).
Hence this object and all objects reachable from this object are live.
</p>

<p>
To add a lock to an object, the user invokes <code>Arms_Status Arms_lock(void* object)</code>.
If this function is invoked successfully, the lock count of the object pointed to by <code>object</code>
was incremented by one. The initial lock count of an object is 0. A lock count of 0 means an object is not locked.
If this function fails it returns a value different from  <code>Arms_Status_Success</code>.
The following table lists the possible values returned in case of failure
<table>
  <tr><td>Value</td><td>Description</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>object</code> is a null pointer</td></tr>
  <tr><td><code>Arms_Status_OperationInvalid</code></td><td>the lock would overflow</td></tr>
  <tr><td><code>Arms_Status_AllocationFailed</code></td><td>an allocation failed</td></tr>
</table>

<p>
To remove a lock from an object, the user invokes <code>Arms_Status Arms_unlock(void* object)</code>.
If this function is invoked successfully, the lock count of the object pointed to by <code>object</code>
was decremented by one. If this function fails it returns a value different from  <code>Arms_Status_Success</code>.
The following table lists the possible values returned in case of failure
<table>
  <tr><td>Value</td><td>Description</td></tr>
  <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>object</code> is a null pointer</td></tr>
  <tr><td><code>Arms_Status_OperationInvalid</code></td><td>the lock count would underflow</td></tr>
</table>
