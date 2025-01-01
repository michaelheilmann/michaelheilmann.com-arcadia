  <h3>3.5. Jumps and Jump Targets</h3>
  <p>R provides non-local jumps by allowing to save and restore the C program state.</p>

  <p><code>
  typedef <my-mv>implementation detail</my-mv> R_JumpTarget;
  </code></p>
  <p>is a type of which its values are stack allocated.</p>

  <p><code>
  void R_pushJumpTarget(R_JumpTarget* jumpTarget);
  </code></p>
  <p>
  Push a jump target on top of the jump target stack.
  Initially, the jump target stack is empty.
  </p>

  <p><code>
  void R_popJumpTarget();
  </code></p>
  <p>
  Pop the jump target on top of the jump target stack.
  The jump target stack must not be empty.
  </p>

  <p><code>
  void R_jump();
  </code></p>
  <p>
  Jump to the jump target on top of the jump target stack.
  The jump target stack must not be empty.
  </p>
  
  <p><code>
  #define R_JumpTarget_save(jumpTarget) <my-mv>implementation detail</my-mv>
  </code></p>
  <p>Macro to save the current C program state into a jump target.</p>
  
  <p>The canonical way of using <code>R_pushJumpTarget</code>, <code>R_popJumpTarget</code>, and
  <code>R_jump</code> is the following.</p>
  <p><code>
  R_pushJumpTarget(&jumpTarget);<br>
  if (R_JumpTarget_save(&jumpTarget)) {<br>
    &nbsp;<my-mv>(1)</my-mv><br>
    &nbsp;R_popJumpTarget();<my-mv>(2)</my-mv><br>
  } else {<br>
    &nbsp;R_popJumpTarget();<my-mv>(3)</my-mv><br>
    &nbsp;<my-mv>(4)</my-mv><br>
  }<br>
  <my-mv>(5)</my-mv>
  </code></p>
  <p>
  The    if-branch is always entered at first as the <code>R_JumpTarget_save()</code>       at
  its first invocation returns logically true. If the program at <my-mv>(1)</my-mv> does   not
  jump to the jump target (using <code>R_jump()</code>),  then <code>R_popJumpTarget();<my-mv>
  (2)</my-mv></code> and <my-mv>(5)</my-mv> are executed. If the program at <my-mv>(1)</my-mv>
  jumps to the jump target, then <code>R_JumpTarget_save()</code> is re-evaluated and  returns
  logically false and <code>R_popJumpTarget();<my-mv>(2)</my-mv></code> and <my-mv>(4)</my-mv>
  is executed.
  </p>
  
  <p>One usage example is the implementation of the <code>R_safeExecute</code> function.</p> 
  <p><code>
  void R_safeExecute(void (*f)()) {<br>
  &nbsp;R_JumpTarget jumpTarget;<br>
  &nbsp;R_pushJumpTarget(&jumpTarget);<br>
  &nbsp;if (R_JumpTarget_save(&jumpTarget)) {<br>
  &nbsp;&nbsp;f();<br>
  &nbsp;&nbsp;R_popJumpTarget();<br>
  &nbsp;}<br>
  }
  </code></p>
