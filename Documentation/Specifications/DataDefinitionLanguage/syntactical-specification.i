<h2 id="syntactical-specification">3 Syntactical Specification</h2>
<p>The syntactical grammar describes the translation of the words into sentences. The goal non-terminal of the syntactical grammar is the sentence <code>syn:Sentence</code> symbol.</p>

<p>The words <code>lex:Whitespace</code> and <code>lex:LineTerminator</code> are removed from the sequence of words before the translation to sentences is performed.</p>

<p>The goal sentence <code>syn:Sentence</code> is defined by</p>

<div class="box">
<p><code>
syn:Sentence : syn:Value 
</code></p>
</div>

<p>The sentence <code>syn:Value</code> is defined by</p>

<div class="box">
<p><code>
syn:Value : syn:Map<br/>
syn:Value : syn:List<br/>
syn:Value : syn:String<br/>
syn:Value : syn:Number<br/>
syn:Value : syn:Boolean<br/>
syn:Value : sny:Void
</code></p>
</div>

<p>The sentence <code>syn:String</code> is defined by</p>
<div class="box">
<p><code>
syn:String : lex:String
</code></p>

<p>The sentence <code>syn:Number</code> is defined by</p>
<div class="box">
<p><code>
syn:Number : lex:Number
</code></p>

<p>The sentence <code>syn:Boolean</code> is defined by</p>
<div class="box">
<p><code>
syn:Boolean : lex:Boolean
</code></p>

<p>The sentence <code>syn:Void</code> is defined by</p>
<div class="box">
<p><code>
syn:Void : lex:Void 
</code></p>

<p>The sentence <code>syn:Map</code> is defined by</p> 

<div class="box">
<p><code>
syn:Map : lex:LeftCurlyBracket<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;syn:MapBody<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lex:RightCurlyBracket<br/>
<br/>
syn:MapBody : syn:MapBodyElement syn:MapBodyRest<br/>
syn:MapBody : ε<br/>
<br/>
syn:MapBodyRest : lex:Comma syn:MapBodyElement syn:MapBodyRest <br/>
syn:MapBodyRest : lex:Comma<br/>
syn:MapBodyRest : ε<br/>
syn:MapBodyElement : lex:Name lex:Colon syn:Value
</code></p>
</div>

<p>The sentence <code>syn:List</code> is defined by</p>

<div class="box">
<p><code>
syn:List : lex:LeftSquareBracket<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;syn:ListBody<br/>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;lex:RightSquareBracket<br/>
<br/>
syn:ListBody : syn:ListBodyElement syn:ListBodyRest<br/>
syn:ListBody : ε<br/>
<br/>
syn:ListBodyRest : lex:Comma syn:ListBodyElement syn:ListBodyRest<br/>
syn:ListBodyRest : lex:Comma<br/>
syn:ListBodyRest : ε<br/>
<br/>
syn:ListBodyElement : syn:Value 
</code></p>
</div>
