<h3 id="integer-types">3.1.3. Integer Types</h3>
<p>
R provides a two's complement integer number types.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> Arcadia_Integer<my-mv>Suffix</my-mv>Value
</code></p>
<p>
where <my-mv>Suffix</my-mv> denotes the number of Bits of the two's complement integer and can be one of
<code>8</code>, <code>16</code>, <code>32</code>, or <code>64</code>.
</p>

<p>The macros in this section all include the <my-mv>Suffix</my-mv> metavariable and are defined for the
values <code>8</code>, <code>16</code>, <code>32</code>, and <code>64</code> of that meta variable.</p>

<p><code>
#define Arcadia_Integer<my-mv>Suffix</my-mv>Value_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bits of the type. The value is always equal to the value of the respective <my-mv>Suffix</my-mv>.</p>

<p><code>
#define Arcadia_Integer<my-mv>Suffix</my-mv>Value_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>Arcadia_Integer<my-mv>Suffix</my-mv>Value_NumberOfBits</code> divided by 8.</p>

<p><code>
#define Arcadia_Integer<my-mv>Suffix</my-mv>Value_Minimum <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the least value (in terms of its magnitude) representable by a the <code>Arcadia_Integer<my-mv>Suffix</my-mv>Value</code> type.
The following table denotes the value of the constant for the respective <my-mv>Suffix</my-mv>
</p>
<table>
<tr><td><my-mv>Suffix</my-mv></td><td>Value</td></tr>
<tr><td>8                    </td><td>-128</td></tr>
<tr><td>16                   </td><td>-32768</td></tr>
<tr><td>32                   </td><td>-2147483648</td></tr>
<tr><td>64                   </td><td>-9223372036854775808</td></tr>
</table>

<p><code>
#define Arcadia_Integer<my-mv>Suffix</my-mv>Value_Maximum <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the greatest value (in terms of its magnitude) representable by a the <code>Arcadia_Integer<my-mv>Suffix</my-mv>Value</code> type.
The following table denotes the value of the constant for the respective <my-mv>Suffix</my-mv>
</p>
<table>
<tr><td><my-mv>Suffix</my-mv></td><td>Value</td></tr>
<tr><td>8                    </td><td>127</td></tr>
<tr><td>16                   </td><td>32767</td></tr>
<tr><td>32                   </td><td>2147483647</td></tr>
<tr><td>64                   </td><td>9223372036854775807</td></tr>
</table>

<p><code>
#define Arcadia_Integer<my-mv>Suffix</my-mv>Value_Literal(x) <my-mv>implementation detail</my-mv>
</code><p>
<p>is used to write a literal of the type <code>Arcadia_Integer<my-mv>Suffix</my-mv></code> in C source code.
The following table denotes  the expansions of the macro:
</p>
<table>
<tr><td><my-mv>Suffix</my-mv></td><td>Value</td></tr>
<tr><td>8                    </td><td>x</td></tr>
<tr><td>16                   </td><td>x</td></tr>
<tr><td>32                   </td><td>x</td></tr>
<tr><td>64                   </td><td>x##LL</td></tr>
</table>
