<main>
  <h1>Michael Heilmann's Automatic Resource Management System Mark 1</h1>
  <p>
  This is the documentation for Michael  Heilmann's Automatic Resource Management System Mark 1,
  henceforth ARMS1. ARMS1 is a precise stop the world garbage collector to be used for programs
  written in C. ARMS1 is available at <a href="@{siteAddress}/repository/arms1">michaelheilmann.com/repository/arms1</a>. 
  <h2>Files</h2>
  <p>
  You can find the sources of ARMS1 in my GitHub repository <a href="https://github.com/michaelheilmann/michaelheilmann.com">https://github.com/michaelheilmann/michaelheilmann.com</a>.
  The subdirectory of Arms1 in the repository is here <a href="https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1">https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1</a>.</p>

  <ul>
    <li>The (sources of the) library resides in the directory
    <a href="https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1/Sources">https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1/Sources</a>
    </li>
    <li>The (sources of) demos reside in the directory
    <a href="https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1/Demos">https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1/Demos</a>
    </li>
    <li>The (sources of this very documentation you are reading) documentation reside in the directory
    <a href="https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms1/Documentation">https://github.com/michaelheilmann/michaelheilmann.com/tree/main/repository/Arms/Documentation</a>
    </li>
  </ul>
  <p>You can compile and run these under various platforms (including but not restricted to Windows, Linux, and many more),
  however, we currently only officially support Windows. To build and run all these, simply checkout the repository to the
  and outside of the repository directory create a build folder.
  Invoke from the the build folder</p>
  <p><code>
  cmake <my-mv>path-to-repository-directory</my-mv>
  </code></p>

  <h2>How a ARMS1 works</h2>
  <p>
  ARMS1 allows for the creation of objects and maintains a set of these created objects called the <em>universe</em> \(U\).
  When an object \(x\) is created, a type \(a\) is associated with that object.
  That type \(a\) provides means to ARMS1 to determine the objects reachable from that object \(x\) and to properly destroy the object \(x\).
  To determine which objects are to be retained and are to be destroyed, ARMS1 starts from a subset of the universe called the <em>root set</em> \(R \subseteq U\) and visits all objects transitively reachable from \(R\).
  The reachable objects are called <em>live objects</em> \(L \subseteq U\).
  All other objects are called <em>dead objects</em> \(D\). \(L\) and \(D\) are disjoint and partition the universe in such that \(U = L \cup D\)
  (also note that \(R \subseteq L\) and \(R \cap D = \emptyset\)).
  ARMS1 removes all dead objects \(D\) from the universe \(U\) such that \(U@@new = U@@old - D\) and destroys them.
  </p>
  <h2>Starting up and shutting down</h2>
  <p>To use the services of ARMS1, a user must acquire an handle to ARMS1. The user acquires a handle by a succesfull call to <code>Arms_Status Arms_startup()</code>.
  This function returns <code>Arms_Status_Success</code> to indicate success and returns status code different from <code>Arms_Status_Success</code> on failure.
  The following table lists the possible values returned in case of failure</p>
  <table>
    <tr><td>Value                                    </td><td>Description               </td></tr>
    <tr><td><code>Arms_Status_AllocationFailed</code></td><td>an allocation failed      </td></tr>
    <tr><td><code>Arms_Status_OperationInvalid</code></td><td>there are too many handles</td></tr>
  </table>
  <p>A user may acquire more than one handle.</p>
  <p>
  If the user no longer requires the services of ARMS1, a user must relinquish the acquired handles.
  The user relinquishes a handle by a successful call to <code>Arms_Status Arms_shutdown()</code>.
  This function returns <code>Arms_Status_Success</code> to indicate success and returns status code different from <code>Arms_Status_Success</code> on failure.
  The following table lists the possible values returned in case of failure</p>
  <table>
    <tr><td>Value                                    </td><td>Description               </td></tr>
    <tr><td><code>Arms_Status_OperationInvalid</code></td><td>if there are objects in \(U\). This is usually the result of illicit usage of ARMS1.</td></tr>
    <tr><td><code>Arms_Status_OperationInvalid</code></td><td>if the last handle was already relinquished. This is usually the result of illicit usage of ARMS1</td></tr>
  </table>
  
  <p><b>Warning:</b>
  Using the services of ARMS1 without a handle is undefined behavior.
  </p>
  
  <h2>Creating types</h2>
  <p>The user adds a type to the ARMS1 by invoking <code>Arms_Status Arms_registerType(char const* name, size_t nameLength, 
  Arms_TypeRemovedCallbackFunction* typeRemoved, Arms_VisitCallbackFunction *visit, Arms_FinalizeCallbackFunction* finalize)</code>. The first argument <code>name</code> is
  a pointer to an array of <code>nameLength</code> Bytes denoting the type name. No two types of the same name can be
  registered and this function fails with <code>Arms_Status_TypeExists</code> if an attempt is made to do so. <code>visit</code>
  must point to a <code>Arms_VisitCallbackFunction</code> or must be a null pointer. <code>finalize</code> must point to a
  <code>Arms_FinalizeCallbackFunction</code> or must be a null pointer. <code>typeRemoved</code> must point to a <code>Arms_TypeRemovedCallbackFunction</code>
  or must be a null pointer. If this function fails it returns a value different from <code>Arms_Status_Success</code>. The following table lists the possible values returned in case of failure
  </p>
  <table>
    <tr><td>Value</td><td>Description</td></tr>
    <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>pObject</code> is a null pointer</td></tr>
    <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>name</code> is a null pointer</td></tr>
    <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>nameLength</code> exceeds limits</td></tr>
    <tr><td><code>Arms_Status_ArgumentInvalid</code></td><td><code>size</code> exceeds limits</td></tr>
    <tr><td><code>Arms_Status_AllocationFailed</code></td><td>an allocation failed</td></tr>
  </table>
  
  @{include("type-removed-callback-function.i")}
  @{include("visit-callback-function.i")}
  @{include("finalize-callback-function.i")}

  <h2>Creating objects</h2>
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
  
  <h2>Freeing resources</h2>
  <p>To relinqish resources, the user invokes <code>Arms_Status Arms_run()</code> which destroys dead objects \(D\) such that the new universe
  only contains live objects, in other terms \(U@@new = U@@old - D\) or equivalently \(U@@new = L\) holds.</p>
  
  <p><code>Arms_run</code> always succeeds.</p>
  
  <h2>Locks</h2>
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
@{include("unmanaged-memory.i")}
</main>
