  <h2>3. Starting up and shutting down</h2>
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
