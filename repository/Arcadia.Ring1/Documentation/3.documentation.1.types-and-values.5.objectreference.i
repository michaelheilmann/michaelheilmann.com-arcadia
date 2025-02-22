<h3 id="Arcadia_ObjectReferenceValue">3.1.5. Arcadia_ObjectReferenceValue</h3>
<p>
Arcadia Ring 1 provides a ObjectReference type.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> Arcadia_ObjectReferenceValue
</code></p>
<p>
The <code>Arcadia_ObjectReferenceValue</code> type is a pointer.
</p>

<p>
A valid value of the <code>Arcadia_ObjectReferenceValue</code> is the null reference
</p>
<p><code>
#define Arcadia_ObjectReferenceValue_Null <my-mv>implementation detail</my-mv>
</code></p>

<p><code>
#define Arcadia_ObjectReferenceValue_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bits of the type.</p>

<p><code>
#define Arcadia_ObjectReferenceValue_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>Arcadia_ObjectReferenceValue_NumberOfBits</code> divided by 8.</p>
