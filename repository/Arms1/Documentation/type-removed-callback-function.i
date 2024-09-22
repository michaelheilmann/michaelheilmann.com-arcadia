<h3>Type removed callback function</h3>
<p>
A type removed function is a function of the signature <code>void Arms_TypeRemovedCallbackFunction(Arms_Natural8 const* name, Arms_Size nameLength)</code>.
The type removed callback function is supplied to a type when that type is created.
The function is invoked when the type is removed (for example, when <code>Arms_shutdown</code> is invoked) and is passed a pointer to an array of Bytes (the name of the type) and the length of that array.
</p>
<p>
<code>
struct File {<br>
&nbsp;...;<br>
};<br>
...<br>
static bool g_registered = false;
...<br>
void File_typeRemoved(Arms_Natural8 const* name, Arms_Size nameLength) {<br>
&nbsp;g_registered = false;<br>
}<br>
...<br>
int main(int argc, char**argv) {<br>
&nbsp;Arms_startup();<br>
&nbsp;if (!g_registered) {<br>
&nbsp;&nbsp;Arms_registerType("File", strlen("File"), &typeRemovedCallback, NULL, NULL);<br>
&nbsp;&nbsp;g_registered = true;<br>  
&nbsp;}</br>
&nbsp;Arms_shutdown();<br>
&nbsp;return EXIT_SUCCESS;<br>
}
</code>
</p> 
<p>Note that types can be created with a null pointer for the finalize function.</p>
