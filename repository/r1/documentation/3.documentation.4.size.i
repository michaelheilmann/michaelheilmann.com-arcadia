  <h3>Size Type</h3>
  <p>
  R provides an alias for builtin <code>size_t</code> type.
  </p>
  <p><code>
  typedef <my-mv>implementation detail</my-mv> R_SizeValue
  </code></p>

  <p><code>
  #define R_SizeValue_NumberOfBits <my-mv>implementation detail</my-mv>
  </code><p>
  <p>
  denotes the number of Bits of the type.
  <b>
  This number must one of 32 or 64, otherwise the environment is not supported by R.
  This restriction may be relaxed in future versions of R.
  </b></p>

  <p><code>
  #define R_SizeValue_NumberOfBytes <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the number of Bytes of the type which is usually <code>R_SizeValue_NumberOfBits</code> divided by 8.</p>

  <p><code>
  #define R_SizeValue_Minimum <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the least value (in terms of its magnitude) representable by a the <code>R_Size</code> type.</p>
