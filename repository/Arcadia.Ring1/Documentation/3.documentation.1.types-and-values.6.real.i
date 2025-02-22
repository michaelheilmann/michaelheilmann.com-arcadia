<h3 id="Arcadia_Real*Value">
3.1.6. Arcadia_Real*Value
</h3>
<p>
Arcadia Ring 1 provides IEEE754 real number types.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> Arcadia_Real<my-mv>Suffix</my-mv>Value
</code></p>
<p>
where <my-mv>Suffix</my-mv> denotes the number of Bits of the integer and can be one of
<code>32</code> or <code>64</code>.
</p>

<p>The macros in this section all include the <my-mv>Suffix</my-mv> metavariable and are defined for the
values <code>32</code> and <code>64</code>.</p>

<p><code>
#define Arcadia_Real<my-mv>Suffix</my-mv>Value_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bits of the type. The value is always equal to the value of the respective <my-mv>Suffix</my-mv>.</p>

<p><code>
#define Arcadia_Real<my-mv>Suffix</my-mv>Value_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>Arcadia_Real<my-mv>Suffix</my-mv>Value_NumberOfBits</code> divided by 8.</p>

<p><code>
#define Arcadia_Real<my-mv>Suffix</my-mv>Value_Minimum <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the least value (in terms of its magnitude) representable by a the <code>Arcadia_Real<my-mv>Suffix</my-mv>Value</code> type.
The following table denotes the value of the constant for the respective <code><my-mv>Suffix</my-mv></code>
</p>
<table>
<tr><td><my-mv>Suffix</my-mv></td><td>Value</td></tr>
<tr><td>32                   </td><td><code>-FLT_MAX</code></td></tr>
<tr><td>64                   </td><td><code>-DBL_MAX</code></td></tr>
</table>

<p><code>
#define Arcadia_Real<my-mv>Suffix</my-mv>Value_Maximum <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the greatest value (in terms of its magnitude) representable by a the <code>Arcadia_Real<span>Suffix</span>Value</code> type.
The following table denotes the value of the constant for the respective <code><span>Suffix</span></code>
</p>
<table>
<tr><td><code><span>Constant</span></code></td><td>Value</td></tr>
<tr><td>32                                </td><td><code>+FLT_MAX</code></td></tr>
<tr><td>64                                </td><td><code>+DBL_MAX</code></td></tr>
</table>
