<h3 id="void-type">3.1.7. Void Type</h3>
<p>
R provides a void type.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> Arcadia_VoidValue
</code></p>
<p>
The only value of this type is <code>Arcadia_VoidValue_Void</code>.
Arcadia_VoidValue is an unsigned integral type.
</p>

<p><code>
#define Arcadia_VoidValue_Void <my-mv>implementation detail</my-mv>
</code><p>
<p>The single value of the type.</p>

<p><code>
#define Arcadia_VoidValue_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bits of the type.</p>

<p><code>
#define Arcadia_VoidValue_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>Arcadia_VoidValue_NumberOfBits</code> divided by 8.</p>
