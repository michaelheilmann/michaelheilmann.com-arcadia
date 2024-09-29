<h4 id="r-clamp">R_clamp</h4>
<p>Clamp a value to a range.</p>
<p><code>
<my-mv>Type</my-mv> R_clamp<my-mv>Suffix</my-mv>(<my-mv>Type</my-mv> value, <my-mv>Type</my-mv> lower, <my-mv>Type</my-mv> upper)
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td><td><my-mv>Type</my-mv></td></tr>
<tr><td><code>Integer8Value</code>  </td><td><code>R_Integer8Value</code></td></tr>
<tr><td><code>Integer16Value</code> </td><td><code>R_Integer16Value</code></td></tr>
<tr><td><code>Integer32Value</code> </td><td><code>R_Integer32Value</code></td></tr>
<tr><td><code>Integer64Value</code> </td><td><code>R_Integer64Value</code></td></tr>
<tr><td><code>Natural8Value</code>  </td><td><code>R_Natural8Value</code></td></tr>
<tr><td><code>Natural16Value</code> </td><td><code>R_Natural16Value</code></td></tr>
<tr><td><code>Natural32Value</code> </td><td><code>R_Natural32Value</code></td></tr>
<tr><td><code>Natural64Value</code> </td><td><code>R_Natural64Value</code></td></tr>
<tr><td><code>SizeValue</code>      </td><td><code>R_SizeValue</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td><my-mv>Type</my-mv> value</td><td>The value to clamp.</td></tr>
  <tr><td><my-mv>Type</my-mv> lower</td><td>The lower bound (inclusive).</td></tr>
  <tr><td><my-mv>Type</my-mv> upper</td><td>The upper bound (inclusive).</td></tr>
</table>

<p>This function returns the value <code>value</code> clamped to the range <code>[lower, upper]</code>.</p>

<h5><b>Errors</b></h5>
<table>
  <tr><td>R_Status_ArgumentValueInvalid</td><td><code>lower &gt; upper</code></td></tr>
  <tr><td>R_Status_EncodingInvalid     </td><td>The sequence of Bytes does not represented a UTF-8-NO-BOM string.</td></tr>
</table>

<h5>Return value</h5>
<p>The value <code>value</code> clamped to the range <code>[lower, upper]</code>.</p>
