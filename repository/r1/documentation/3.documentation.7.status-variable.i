  <h3>Status Variable</h3>
  <p>R provides a global status variable.</p>

  <p><code>
  R_Status
  R_getStatus
    (
    );
  </code></p>
  <p>gets the value of the status variable. The initial value of the status variable is <code>R_Status_Success</code>.</p>

  <p><code>
  void
  R_setStatus
    (
      R_Status status
    );
  </code></p>
  <p>sets the value of the status variable to the value <code>status</code>.</p>
