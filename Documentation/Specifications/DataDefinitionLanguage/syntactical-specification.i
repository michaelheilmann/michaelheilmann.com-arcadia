<h2 id="syntactical-specification">3 Syntactical Specification</h2>
<p>The syntactical grammar describes the translation of the words into sentences. The goal non-terminal of the syntactical grammar is the sentence <code>sentence</code> symbol.</p>

<p>The words <code>whitespace</code> and <code>line_terminator</code> are removed from the sequence of words before the translation to sentences is performed.</p>

<p>The goal sentence <code>sentence</code> is defined by</p>

<div class="box">
<p><code>
sentence : value 
</code></p>
</div>

<p>The sentence <code>value</code> is defined by</p>

<div class="box">
<p><code>
value : map<br/>
value : list<br/>
value : lexical:string<br/>
value : lexical:number<br/>
value : lexical:boolean<br/>
value : lexical:void 
</code></p>
</div>

<p>The sentence <code<map</code> is defined by</p> 

<div class="box">
<p><code>
map : lexical:left_curly_bracket<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;map_body<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lexical:right_curly_bracket<br/>
<br/>
map_body : map_body_element map_body_rest<br/>
map_body : ε<br/>
<br/>
map_body_rest : lexical:comma map_body_element map_body_rest<br/>
map_body_rest : lexical:comma<br/>
map_body_rest : ε<br/>
map_body_element : lexical:name lexical:colon value
</code></p>
</div>

<p>The sentence <code>list</code> is defined by</p>

<div class="box">
<p><code>
list : lexical:left_square_bracket<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;list_body<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lexical:right_square_bracket<br/>
<br/>
list_body : list_body_element list_body_rest<br/>
list_body : ε<br/>
<br/>
list_body_rest : lexical:comma list_body_element list_body_rest<br/>
list_body_rest : lexical:comma<br/>
list_body_rest : ε<br/>
<br/>
list_body_element : value 
</code></p>
</div>
