<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity object">

  <h1 id="Arcadia_Visuals_MouseButtonEvent">
  [MIL] Arcadia.Visuals.MouseButtonEvent
  </h1>

  <my-signature><code>
  class Arcadia.Visuals.MouseButtonEvent extends Arcadia.Visuals.Event { ... }
  </code></my-signature>

  <my-summary>
  A mouse button event.
  </my-summary>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<!-- TODO: This should be "mil" scope not "cxx" scope. -->
<section class="cxx entity method">

  <h1 id="Arcadia_Visuals_MouseButtonEvent_construct">
  [MIL] Arcadia.Visuals.MouseButtonEvent.construct
  </h1>

  <my-signature><code>
    void<br>
    Arcadia.Visuals.MouseButtonEvent.construct<br>
    &nbsp;&nbsp;(<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Natural64 timestamp,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Visuals.MouseButtonAction action,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Natural64Value button,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Integer64Value x,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Integer64Value y<br>
    &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Construct this canvas activation state changed event.
  </my-summary>

  <section class="cxx parameters">

    <h1>Parameters</h1>

    <div>
      <div>Arcadia.Natural64 timestamp</div>
      <div>The timestamp of this event.</div>
    </div>

    <div>
      <div>Arcadia.Visuals.MouseButtonAction action</div>
      <div>The mouse button action.</div>
    </div>

    <div>
      <div>Arcadia.Natural64 button</div>
      <div>The zero-based index of the mouse button.</div>
    </div>
    
    <div>
      <div>Arcadia.Integer32 x</div>
      <div>The position along the x-axis of the mouse pointer..</div>
    </div>
    
    <div>
      <div>Arcadia.Integer32 y</div>
      <div>The position along the y-axis of the mouse pointer..</div>
    </div>

  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->
