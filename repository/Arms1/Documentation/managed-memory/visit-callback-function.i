<h4>Visit callback function</h4>
<p>
A visit function is a function of the signature <code>void Arms_VisitCallbackFunction(void *object)</code>.
The visit callback function is supplied to a type when that type is created and is passed a pointer to
objects of that type (or any other type where it supplied to). The visit function shall invoke
<code>void Arms_visit(void* object)</code> on any object directly reachable from the specified object.
In the following example, <code>File_visit</code> is implemented to visit the field <code>fn</code>
of struct <code>File</code> if it was not null.
</p>
<p>
<code>
struct File {<br>
&nbsp;void* fn;<br>
&nbsp;...<br>
};<br>
...<br>
void File_visit(File* file) {<br>
&nbsp;if (file->fn) {<br>
&nbsp;&nbsp;Arms_visit(file->fn);<br>
&nbsp;&nbsp;file->fn = NULL;<br>
&nbsp;}<br>
}<br>
...<br>
int main(int argc, char**argv) {<br>
&nbsp;Arms_startup();<br>
&nbsp;Arms_registerType("File", strlen("File"), &visitFile, NULL);<br>
&nbsp;struct File* file;<br>
&nbsp;Arms_allocate(&file, "File", strlen("File"), sizeof(struct File));<br>
&nbsp;file->fn = NULL;<br>
&nbsp;Arms_lock(file);<br>
&nbsp;Arms_RunStatistics statistics = { .destroyed = 0 };<br>
&nbsp;Arms_run(&statistics);<br>
&nbsp;Arms_shutdown();<br>
&nbsp;return EXIT_SUCCESS;<br>
}
</code>
</p> 
<p>Note that types can be created with a null pointer for the visit function.</p>
