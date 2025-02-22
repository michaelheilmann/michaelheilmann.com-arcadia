<h3 id="Arcadia_SizeValue">3.1.7. Size Type</h3>
<p>
Arcadia Ring 1 provides an alias for builtin <code>size_t</code> type.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> Arcadia_SizeValue
</code></p>

<p><code>
#define Arcadia_SizeValue_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>
denotes the number of Bits of the type.
<b>
This number must one of 32 or 64, otherwise the environment is not supported by <em>Arcadia Ring 1</em>.
This restriction may be relaxed in future versions of <em>Arcadia Ring 1</em>.
</b></p>

<p><code>
#define Arcadia_SizeValue_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>Arcadia_SizeValue_NumberOfBits</code> divided by 8.</p>

<p><code>
#define Arcadia_SizeValue_Minimum <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the least value (in terms of its magnitude) representable by a the <code>Arcadia_Size</code> type.</p>

<p><code>
#define Arcadia_SizeValue_Literal(x) <my-mv>implementation detail</my-mv>
</code><p>
<p>is used to write a literal of type <code>Arcadia_SizeValue</code> in C source code.</p>
