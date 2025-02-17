<h4 id="arcadia-isutf8">Arcadia_isUtf8</h4>
<p>Get if a sequence of Bytes is an UTF-8 sequence of Bytes and count its number of symbols.</p>
<p><code>
Arcadia_BooleanValue
Arcadia_isUtf8
  (
    Arcadia_Process* process,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  )
</code></p>

<h5>Parameters</h5>
<table>
  <tr><td>Arcadia_Process* process</td><td>A pointer to the <code>Arcadia_Process</code> object.</td></tr>
  <tr><td>const void* bytes</td><td>A pointer to an array of <code>numberOfBytes</code> Bytes.</td></tr>
  <tr><td>Arcadia_SizeValue numberOfBytes</td><td>The number of Bytes in the array of Bytes pointed to by <code>bytes</code>.</td></tr>
  <tr><td>Arcadia_SizeValue* numberOfSymbols</td><td>
  The number of Bytes in the array of Bytes pointed to by <code>bytes</code>.
  If this function terminates and this pointer is not null, the variable is assigned the number of symbols decoded successfully so far.
  </td></tr>
</table>

<h5>Return value</h5>
<p>
<code>Arcadia_BooleanValue_True</code> if the sequence of <code>numberOfBytes</code> Bytes pointed to by <code>bytes</code> is an UTF-8 sequence of Bytes.
<code>Arcadia_BooleanValue_False</code> otherwise.
</p>
