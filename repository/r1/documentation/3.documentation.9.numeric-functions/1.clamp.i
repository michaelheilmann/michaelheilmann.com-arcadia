<h4>R_clamp</h4>
<p>R provides functions clamping values to a value range.</p>
<p><code>
<my-mv>Type</my-mv> R_clamp_<my-mv>Suffix</my-mv>(<my-mv>Type</my-mv> value, <my-mv>Type</my-mv> lower, <my-mv>Type</my-mv> upper)
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

<p>This function returns the value <code>value</code> clamped to the range <code>[lower, upper]</code>.
If <code>lower &gt; upper</code> then this function sets the status variable to <code>R_Status_ArgumentValueInvalid</code> and jumps.</p>
