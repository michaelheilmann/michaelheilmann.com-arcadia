<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity object">

  <h1 id="Arcadia_Visuals_KeyboardKeyEvent">
  [MIL] Arcadia.Visuals.KeyboardKeyEvent
  </h1>

  <my-signature><code>
  class Arcadia.Visuals.KeyboardKeyEvent extends Arcadia.Visuals.Event { ... }
  </code></my-signature>

  <my-summary>
  A keyboard key event.
  </my-summary>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_Visuals_KeyboardKeyEvent_construct">
  [MIL] Arcadia.Visuals.KeyboardKeyEvent.construct
  </h1>

  <my-signature><code>
    void<br>
    Arcadia.Visuals.KeyboardKeyEvent.construct<br>
    &nbsp;&nbsp;(<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Natural64 timestamp,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Visuals.KeyboardKeyAction action,<br>
    &nbsp;&nbsp;&nbsp;&nbsp;Arcadia.Visuals.KeyboardKey key<br>
    &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Construct this keyboard key event.
  </my-summary>

  <section class="cxx parameters">

    <h1>Parameters</h1>

    <div>
      <div>Arcadia.Natural64 timestamp</div>
      <div>The timestamp of this event.</div>
    </div>

    <div>
      <div>Arcadia.Visuals.KeyboardKeyAction action</div>
      <div>The keyboard key action.</div>
    </div>

    <div>
      <div>Arcadia.Visuals.KeyboardKey key</div>
      <div>The keyboard key.</div>
    </div>

  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

<section class="cxx entity method">

  <h1 id="Arcadia_Visuals_KeyboardKeyEvent_getAction">
  [MIL] Arcadia.Visuals.KeyboardKeyEvent.getAction
  </h1>

  <my-signature><code>
    void<br>
    Arcadia.Visuals.KeyboardKeyAction<br>
    Arcadia.Visuals.KeyboardKeyEvent.getAction<br>
    &nbsp;&nbsp;(<br>
    &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the keyboard key action of this keyboard key event.
  </my-summary>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The keyboard key action.</p>
  </section>

</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->



<section class="cxx entity method">

  <h1 id="Arcadia_Visuals_KeyboardKeyEvent_getKey">
  [MIL] Arcadia.Visuals.KeyboardKeyEvent.getKey
  </h1>

  <my-signature><code>
    void<br>
    Arcadia.Visuals.KeyboardKey<br>
    Arcadia.Visuals.KeyboardKeyEvent.getKey<br>
    &nbsp;&nbsp;(<br>
    &nbsp;&nbsp;)
  </code></my-signature>

  <my-summary>
  Get the keyboard key of this keyboard key event.
  </my-summary>

  <section class="cxx return-value">
    <h1>Return value</h1>
    <p>The keyboard key.</p>
  </section>


</section>

<!-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ -->

