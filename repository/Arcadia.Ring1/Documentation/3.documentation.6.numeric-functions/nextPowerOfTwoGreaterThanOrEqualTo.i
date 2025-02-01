<h4 id="arcadia-nextpoweroftwogreaterthanorequalto">Arcadia_nextPowerOfTwoGreaterThanOrEqualTo</h4>
<p>R provides functions returning the next power of two greater or equal to a value.</p>
<p><code>
<my-mv>Type</my-mv> Arcadia_nextPowerOfTwoGte<my-mv>Suffix</my-mv>(<my-mv>Type</my-mv> x)
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
  <tr><td><my-mv>Type</my-mv> x</td><td>The value.</td></tr>
</table>

<h5><b>Errors</b></h5>
<table>
  <tr><td>Arcadia_Status_NotExists</td><td>The next power of two greater greater than or equal to <code>x</code> is not representable by the type <my-mv>Type</my-mv></td></tr>
</table>

<h5>Return value</h5>
<p>Return the next power of two greater than or equal to <code>x</code>.</p>
