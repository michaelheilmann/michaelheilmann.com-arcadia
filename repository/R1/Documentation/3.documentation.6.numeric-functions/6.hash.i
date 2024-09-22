<h4 id="r-hash">R_hash</h4>
<p>Return the hash of a value.</p>
<p><code>
R_SizeValue R_hash<my-mv>Suffix</my-mv>(<my-mv>Type</my-mv> x)
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
<tr><td><code>VoidValue</code>      </td><td><code>R_VoidValue</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td><my-mv>Type</my-mv> x</td><td>The value.</td></tr>
</table>

<h5>Return value</h5>
<p>Return hash of  <code>x</code>.</p>
