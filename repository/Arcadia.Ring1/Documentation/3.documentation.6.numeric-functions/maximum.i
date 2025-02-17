<h4 id="arcadia-maximum">Arcadia_maximum</h4>
<p>Return the maximum of two values.</p>
<p><code>
<my-mv>Type</my-mv>
Arcadia_maximum<my-mv>Suffix</my-mv>
  (
    Arcadia_Process* process,
    <my-mv>Type</my-mv> x,
    <my-mv>Type</my-mv> y
  )
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td> <td><my-mv>Type</my-mv></td></tr>
<tr><td><code>Integer8Value</code></td><td><code>Arcadia_Integer8Value</code></td></tr>
<tr><td><code>Integer16Value</code></td><td><code>Arcadia_Integer16Value</code></td></tr>
<tr><td><code>Integer32Value</code></td><td><code>Arcadia_Integer32Value</code></td></tr>
<tr><td><code>Integer64Value</code></td><td><code>Arcadia_Integer64Value</code></td></tr>
<tr><td><code>Natural8Value</code></td><td><code>Arcadia_Natural8Value</code></td></tr>
<tr><td><code>Natural16Value</code></td><td><code>Arcadia_Natural16Value</code></td></tr>
<tr><td><code>Natural32Value</code></td><td><code>Arcadia_Natural32Value</code></td></tr>
<tr><td><code>Natural64Value</code></td><td><code>Arcadia_Natural64Value</code></td></tr>
<tr><td><code>SizeValue</code></td><td><code>Arcadia_SizeValue</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Process* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td><my-mv>Type</my-mv> x</td><td>The first value.</td></tr>
  <tr><td><my-mv>Type</my-mv> y</td><td>The second value.</td></tr>
</table>

<h5>Return value</h5>
<p>Return the maximum of <code>x</code> and <code>y</code>.</p>
