<h4 id="Arcadia_Real*Value_getBits">Arcadia_Real*Value_getBits</h4>
<p>Get the bits of a Real value.</p>
<p><code>
Arcadia_Natural<my-mv>Bits</my-mv>
Arcadia_Real<my-mv>Bits</my-mv>Value_getBits
  (
    Arcadia_Thread* thread,
    Arcadia_Real<my-mv>Bits</my-mv>Value self
  )
</code></p>
<p>The following table lists the value of <my-mv>Bits</my-mv> for which functions are defined</p>

<table>
<tr><td><my-mv>Bits</my-mv></td></tr>
<tr><td><code>32</code></td></tr>
<tr><td><code>64</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td>Arcadia_Real<my-mv>Bits</my-mv> self</td><td>The Real value.</td></tr>
</table>

<h5>Return value</h5>
<p>Return the bits of the Real value as a Natural value.</p>
