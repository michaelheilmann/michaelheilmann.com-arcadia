<h4 id="arcadia-safeadd">Arcadia_safeAdd</h4>
<p>Get the sum of two values.</p>
<p><code>
void Arcadia_safeAdd<my-mv>Suffix</my-mv>(<my-mv>Type<my-mv> augend, <my-mv>Type<my->mv> addend, <my-mv>Type</my-mv>* sumHigh, <my-mv>Type</my-mv>* sumLow)
</code></p>
<p>The following table lists the combinations of <my-mv>Type</my-mv> and <my-mv>Suffix</my-mv> for which the above functions are defined</p>

<table>
<tr><td><my-mv>Suffix</my-mv></td>      <td><my-mv>Type</my-mv></td></tr>
<tr><td><code>Natural16Value</code></td><td><code>Arcadia_Natural16Value</code></td></tr>
<tr><td><code>Natural32Value</code></td><td><code>Arcadia_Natural32Value</code></td></tr>
<tr><td><code>Natural64Value</code></td><td><code>Arcadia_Natural64Value</code></td></tr>
<tr><td><code>Natural8Value</code></td> <td><code>Arcadia_Natural8Value</code></td></tr>
<tr><td><code>SizeValue</code></td>     <td><code>Arcadia_SizeValue</code></td></tr>
</table>

<h5>Parameters</h5>
<table>
  <tr><td><my-mv>Type</my-mv> augend</td>  <td>The augend value.</td></tr>
  <tr><td><my-mv>Type</my-mv> addend</td>  <td>The addend value.</td></tr>
  <tr><td><my-mv>Type</my-mv>* sumHigh</td><td>A pointer to a variable. The variable is assigned the high bits of the result.</td></tr>
  <tr><td><my-mv>Type</my-mv>* sumLow</td> <td>A pointer to a variable. The variable is assigned the low bits of the result.</td></tr>
</table>
