  <h3>Natural Type</h3>
  <p>
  R provides natural number types.
  </p>
  <p><code>
  typedef <my-mv>implementation detail</my-mv> R_Natural<my-mv>Suffix</my-mv>Value
  </code></p>
  <p>
  where <my-mv>Suffix</my-mv> denotes the number of Bits of the integer and can be one of
  <code>8</code>, <code>16</code>, <code>32</code>, or <code>64</code>.
  </p>

  <p><code>
  #define R_Natural<my-mv>Suffix</my-mv>Value_NumberOfBits <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the number of Bits of the type. The value is always equal to the value of the respective <my-mv>Suffix</my-mv>.</p>

  <p><code>
  #define R_Integer<my-mv>Suffix</my-mv>Value_NumberOfBytes <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the number of Bytes of the type which is usually <code>R_Integer<my-mv>Suffix</my-mv>Value_NumberOfBits</code> divided by 8.</p>

  <p><code>
  #define R_Natural<my-mv>Suffix</my-mv>Value_Minimum <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the least value (in terms of its magnitude) representable by a the <code>R_Natural<my-mv>Suffix</my-mv>Value</code> type.
  The following table denotes the value of the constant for the respective <code><my-mv>Suffix</my-mv></code>
  </p>
  <table>
  <tr><td><my-mv>Suffix</my-mv></td><td>Value</td></tr>
  <tr><td>8                    </td><td>0</td></tr>
  <tr><td>16                   </td><td>0</td></tr>
  <tr><td>32                   </td><td>0</td></tr>
  <tr><td>64                   </td><td>0</td></tr>
  </table>

  <p><code>
  #define R_Natural<my-mv>Suffix</my-mv>Value_Maximum <my-mv>implementation detail</my-mv>
  </code><p>
  <p>denotes the greatest value (in terms of its magnitude) representable by a the <code>R_Natural<span>Suffix</span>Value</code> type.
  The following table denotes the value of the constant for the respective <code><span>Suffix</span></code>
  </p>
  <table>
  <tr><td><code><span>Constant</span></code></td><td>Value</td></tr>
  <tr><td>8                                  </td><td>255</td></tr>
  <tr><td>16                                 </td><td>65535</td></tr>
  <tr><td>32                                 </td><td>4294967295</td></tr>
  <tr><td>64                                 </td><td>18446744073709551615</td></tr>
  </table>
