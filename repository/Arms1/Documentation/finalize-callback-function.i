<h3>Finalize callback function</h3>
<p>
A finalize function is a function of the signature <code>void Arms_FinalizeCallbackFunction(void *object)</code>.
The finalize callback function is supplied to a type when that type is created and is passed a pointer to
objects of that type (or any other type where it supplied to). The finalize function shall perform cleanup
of unmanaged resources like unmanaged memory, file handles, etc. In the following example, <code>File_finalize</code>
is implemented to invoke `fclose` on the field <code>fd</code> of struct <code>File</code> if it was not null.
</p>
<p>
<code>
struct File {<br>
&nbsp;FILE* fd;<br>
};<br>
...<br>
void File_finalize(File* file) {<br>
&nbsp;if (file->fd) {<br>
&nbsp;&nbsp;fclose(file->fd);<br>
&nbsp;&nbsp;file->fd = NULL;<br>
&nbsp;}<br>
}<br>
...<br>
int main(int argc, char**argv) {<br>
&nbsp;Arms_startup();<br>
&nbsp;Arms_registerType("File", strlen("File"), NULL, NULL, &finalizeFile);<br>
&nbsp;struct File* file;<br>
&nbsp;Arms_allocate(&file, "File", strlen("File"), sizeof(struct File));<br>
&nbsp;file->fd = fopen(...);<br>
&nbsp;Arms_RunStatistics statistics = { .destroyed = 0 };<br>
&nbsp;Arms_run(&statistics);<br>
&nbsp;Arms_shutdown();<br>
&nbsp;return EXIT_SUCCESS;<br>
}
</code>
</p> 
<p>Note that types can be created with a null pointer for the finalize function.</p>
