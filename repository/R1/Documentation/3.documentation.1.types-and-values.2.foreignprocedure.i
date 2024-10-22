<h3 id="foreignprocedure-type">Foreign Procedure Type</h3>
<p>
R provides the <scode>R_ForeignProcedureValue</code> type.
</p>
<p><code>
typedef <my-mv>implementation detail</my-mv> R_ForeignProcedureValue;
</code></p>
<p>
which is a pointer to a function adhering to the calling conventions for C functions of the runtime.
</p>

<p>
A valid value of the <code>R_ForeignProcedureValue</code> is the null value
</p>
<p><code>
#define R_ForeignProcedureValue_Null <my-mv>implementation detail</my-mv>
</code></p>

<p><code>
#define R_ForeignProcedureValue_NumberOfBits <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bits of the type.</p>

<p><code>
#define R_ForeignProcedureValue_NumberOfBytes <my-mv>implementation detail</my-mv>
</code><p>
<p>denotes the number of Bytes of the type which is usually <code>R_ForeignProcedureValue_NumberOfBits</code> divided by 8.</p>
