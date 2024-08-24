  <h3>Void Type</h3>
  <p>
  R provides a void type.
  </p>
  <p><code>
  typedef <my-mv>implementation detail</my-mv> R_VoidValue
  </code></p>
  <p>
  The only value of this type is <code>R_VoidValue_Void</code>.
  R_VoidValue is an unsigned integral type.
  </p>
  
  <p><code>
  #define R_VoidValue_Void <my-mv>implementation detail</my-mv>
  </code><p>
  <p>The single value of the type.</p>

  <p><code>
  #define R_VoidValue_NumberOfBits <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the number of Bits of the type.</p>

  <p><code>
  #define R_VoidValue_NumberOfBytes <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the number of Bytes of the type which is usually <code>R_VoidValue_NumberOfBits</code> divided by 8.</p>
