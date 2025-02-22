<h3 id="Arcadia_ForeignProcedureValue">3.1.2. Arcadia_ForeignProcedureValue</h3>
<p>
Arcadia Ring 1 provides the <scode>Arcadia_ForeignProcedureValue</code> type.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> Arcadia_ForeignProcedureValue;
</code></p>
<p>
which is a pointer to a function adhering to the calling conventions for C functions of the runtime.
</p>

<p>
A valid value of the <code>Arcadia_ForeignProcedureValue</code> is the null value
</p>
<p><code>
#define Arcadia_ForeignProcedureValue_Null <my-mv>implementation detail</my-mv>
</code></p>

<p><code>
#define Arcadia_ForeignProcedureValue_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bits of the type.</p>

<p><code>
#define Arcadia_ForeignProcedureValue_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>Arcadia_ForeignProcedureValue_NumberOfBits</code> divided by 8.</p>
