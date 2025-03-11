<h4 id="Arcadia_quotientRemainder*">Arcadia_quotientRemainder*</h4>
<p>Return the number of significand Bits of the binary representation of a value.</p>
<p><code>
void
Arcadia_quotientRemainder<my-mv>Suffix</my-mv>
  (
    Arcadia_Thread* thread,
    <my-mv>Type</my-mv> dividend,
    <my-mv>Type</my-mv> divisor,
    <my-mv>Type</my-mv>* quotient,
    <my-mv>Type</my-mv>* remainder
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

<p>
This function computes the quotient <code><my-mv>q</my-mv> = dividend / divisor</code> and the remainder <code><my-mv>r</my-mv> = dividend - (q * divisor)</code>.
The quotient is stored in <code>*quotient</code> and the divisor is stored in <code>*remainder</code>.
</p>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Thread* thread</td><td>A pointer to the <code>Arcadia_Thread</code> object.</td></tr>
  <tr><td><my-mv>Type</my-mv> dividend</td><td>The dividend.</td></tr>
  <tr><td><my-mv>Type</my-mv> divisor</td><td>The divisor.</td></tr>
  <tr><td><my-mv>Type</my-mv> quotient</td><td>Variable to store the quotient in.</td></tr>
  <tr><td><my-mv>Type</my-mv> remainder</td><td>Variable to store the remainder in.</td></tr>
</table>

<h5><b>Errors</b></h5>
<table>
  <tr><td>Arcadia_Status_ArgumentValueInvalid</td><td><code>quotient</code> or <code>remainder</code> is zero.<td></tr>
  <tr><td>Arcadia_Status_DivisionByZero</td><td>The divisor is zero.<td></tr>
</table>
