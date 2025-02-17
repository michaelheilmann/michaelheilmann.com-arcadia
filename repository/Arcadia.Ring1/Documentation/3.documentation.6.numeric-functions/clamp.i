<h4 id="arcadia-clamp">Arcadia_clamp</h4>
<p>Clamp a value to a range.</p>
<p><code>
<my-mv>Type</my-mv>
Arcadia_clamp<my-mv>Suffix</my-mv>
  (
    Arcadia_Process* process,
    <my-mv>Type</my-mv> value,
    <my-mv>Type</my-mv> lower,
    <my-mv>Type</my-mv> upper
  )
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td><td><my-mv>Type</my-mv></td></tr>
<tr><td><code>Integer8Value</code>  </td><td><code>Arcadia_Integer8Value</code></td></tr>
<tr><td><code>Integer16Value</code> </td><td><code>Arcadia_Integer16Value</code></td></tr>
<tr><td><code>Integer32Value</code> </td><td><code>Arcadia_Integer32Value</code></td></tr>
<tr><td><code>Integer64Value</code> </td><td><code>Arcadia_Integer64Value</code></td></tr>
<tr><td><code>Natural8Value</code>  </td><td><code>Arcadia_Natural8Value</code></td></tr>
<tr><td><code>Natural16Value</code> </td><td><code>Arcadia_Natural16Value</code></td></tr>
<tr><td><code>Natural32Value</code> </td><td><code>Arcadia_Natural32Value</code></td></tr>
<tr><td><code>Natural64Value</code> </td><td><code>Arcadia_Natural64Value</code></td></tr>
<tr><td><code>SizeValue</code>      </td><td><code>Arcadia_SizeValue</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Process* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td><my-mv>Type</my-mv> value</td><td>The value to clamp.</td></tr>
  <tr><td><my-mv>Type</my-mv> lower</td><td>The lower bound (inclusive).</td></tr>
  <tr><td><my-mv>Type</my-mv> upper</td><td>The upper bound (inclusive).</td></tr>
</table>

<p>This function returns the value <code>value</code> clamped to the range <code>[lower, upper]</code>.</p>

<h5><b>Errors</b></h5>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>lower &gt; upper</code></td></tr>
  <tr><td>Arcadia_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<h5>Return value</h5>
<p>The value <code>value</code> clamped to the range <code>[lower, upper]</code>.</p>
