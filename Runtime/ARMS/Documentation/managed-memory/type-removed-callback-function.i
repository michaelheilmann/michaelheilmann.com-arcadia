<h4>Type removed callback function</h4>
<p>
A type removed function is a function of the signature <code>void Arms_TypeRemovedCallbackFunction(void* context, Arms_Natural8 const* name, Arms_Size nameLength)</code>.
The type removed callback function is supplied to a type when that type is created.
The function is invoked when the type is removed (for example, when <code>Arms_shutdown</code> is invoked).
The first argument is the context as supplied to the <code>Arms_addType</code>.
The second argument is an array of Bytes (the name of the type) and the third argument the length of that array.
</p>

<p>
<code>
struct File {<br>
&nbsp;...;<br>
};<br>
...<br>
static bool g_registered = false;
...<br>
void File_typeRemoved(void* context, Arms_Natural8 const* name, Arms_Size nameLength) {<br>
&nbsp;g_registered = false;<br>
}<br>
...<br>
int main(int argc, char**argv) {<br>
&nbsp;Arms_startup();<br>
&nbsp;if (!g_registered) {<br>
&nbsp;&nbsp;Arms_addType("File", strlen("File"), NULL, &typeRemovedCallback, NULL, NULL);<br>
&nbsp;&nbsp;g_registered = true;<br>
&nbsp;}</br>
&nbsp;Arms_shutdown();<br>
&nbsp;return EXIT_SUCCESS;<br>
}
</code>
</p>
<p>Note that types can be created with a null pointer for the finalize function.</p>
