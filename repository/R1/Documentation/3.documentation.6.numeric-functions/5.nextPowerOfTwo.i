<h4>R_nextPowerOfTwo</h4>
<p>R provides functions returning the next power of two greater than a value.</p>
<p><code>
<my-mv>Type</my-mv> R_nextPowerOfTwo_<my-mv>Suffix</my-mv>(<my-mv>Type</my-mv> x)
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td><td><my-mv>Type</my-mv></td></tr>
<tr><td><code>i8</code>      </td><td><code>R_Integer8Value</code></td></tr>
<tr><td><code>i16</code>     </td><td><code>R_Integer16Value</code></td></tr>
<tr><td><code>i32</code>     </td><td><code>R_Integer32Value</code></td></tr>
<tr><td><code>i64</code>     </td><td><code>R_Integer64Value</code></td></tr>
<tr><td><code>n8</code>      </td><td><code>R_Natural8Value</code></td></tr>
<tr><td><code>n16</code>     </td><td><code>R_Natural16Value</code></td></tr>
<tr><td><code>n32</code>     </td><td><code>R_Natural32Value</code></td></tr>
<tr><td><code>n64</code>     </td><td><code>R_Natural64Value</code></td></tr>
<tr><td><code>sz</code>      </td><td><code>R_Size</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td><my-mv>Type</my-mv> x</td><td>The value.</td></tr>
</table>

<h5><b>Errors</b></h5>
<table>
  <tr><td>R_Status_NotExists</td><td>The next power of two greater than <code>x</code> is not representable by the type <my-mv>Type</my-mv></td></tr>
</table>

<h5>Return value</h5>
<p>Return the next power of two greater than <code>x</code>.</p>
