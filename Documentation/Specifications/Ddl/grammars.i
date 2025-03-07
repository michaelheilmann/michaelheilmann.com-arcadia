<h2>Grammars</h3>
<p>This section describes context-free grammars used in this specification to define the lexical and syntactical structure of a <em>Data Definition Language</em> program.</p>

<h3>Context-free grammars</h3>
<p>A context-free grammar consists of a number of production. Each production has an abstract symbol called a non-terminal as its left-hand side, and a sequence of one or more
non-terminal and terminal symbols as its right-hand side. For each grammar, the terminal symbols are drawn from a specified alphabet.</p>

<p>Starting from a sequence consisting of a single distinguished non-terminal, called the goal symbol, a given context-free grammar specifies a language, namely, the set of possible
sequences of terminal smbols that can result from repeatedly replacing any non-terminal in the sequence with a right-hand side of a production for which the non-terminal is the
left-hand side.</p>

<h3>Encoding</h3>
<p>
The <em>Data Definition Language</em> programs are encoded as UTF-8 NOBOM.
Furthermore, only UTF8 sequences of length 1 are support in this version of the <em>Data Definition Language</em>.
</p>

<h3>Lexical grammars</h3>
<p>The lexical grammar for the <em>Data Definition Language</em> uses Unicode code points as its terminal symbols.
It defines a set of productions, starting from the goal symbol <my-mv>word</my-mv>, that describe how sequences of code points are translated into a word.
</p>

<h3>Syntactical grammars</h3>
<p>The syntactical grammar for the <em>Data Definition Language</em> uses words of the lexical grammar as its terminal symbols.
It defines a set of productions, starting from the goal symbol <my-mv>sentence</my-mv>, that describe how sequences of words are translated into a sentence.
</p>

<h3>Grammar notation</h3>
<p>Productions are written in <code>fixed width</code> fonts.</p>

<p>A production is defined by its left-hand side, followed by a colon <code:</code>, followed by its right-hand side definition. The left-hand side is the name of the non-terminal defined
by the production.</p>

<p>Multiple alternating definitions of a production may be defined.</p>

<p>The right-hand side of a production consits of any sequence of terminals and non-terminals.</p>

<p>In certain cases the right-hand side is replaced by a comment describing the right-hand side. This comment is opened by <code>/*</code> and closed by <code>*/</code>.

<div class="box">
<p>Example</p>
<p>The following production denotes the non-terminal for a digit as used in the definitions of numerals:</p>
<p><code>
digit: /* A single Unicode symbol from the code point range +U0030 to +U0039 */    
</code></p>
</div>

<p>A terminal is a sequence of Unicode symbols. A Unicode symbol is denoted by a shebang <code>#</code> followed by a hexadecimal number denoting its code point.<p>

<div class="box">
<p>Example</p>
<p>The following productions denote the non-terminal for a sign as used in the definitions of numerals:</p>
<p><code>
/* #2b is also known as "PLUS SIGN" */<br/>
plus_sign : #2b<br/>
/* #2d is also known as "MINUS SIGN" */<br/>
minus_sign : #2d sign : plus_sign<br/>
sign : minus_sign  
</code></p>
</div>

<p>The syntax <code>{x}</code> on the right-hand side of a production denotes zero or more occurrences of <code>x</code>.</p> 

<div class="box">
<p>Example</p>
<p>The following production defines a possibly empty sequence of digits as used in the definitions of numerals:</p>
<p><code>
zero-or-more-digits : {digit} 
</code></p>
</div>

<p>The syntax <code>[x]</code> on the right-hand side of a production denotes zero or one occurrences of <code>x</code>.</p>

<div class="box">
<p>Example</p>
<p>The following productions denotes a possible definition of an integer numeral.
It consists of an optional sign followed by a digit followed by zero-or-more-digits as defined in the preceeding examples):</p>
<p><code>
integer : [sign] digit zero-or-more-digits 
</code></p>
</div>

<p>The empty string is denoted by <code>ε</code>.</p>

<div class="box">
<p>Example</p>
<p>
The following productions denotes a possibly empty list of integers (with integer as defined in the preceeding example).
Note that this list may include a trailing comma.
</p>
<p><code>
integer-list : integer integer-list-rest<br/>
integer-list : ε<br/>
<br/>
integer-list-rest : comma integer integer-list-rest<br/>
integer-list-rest : comma<br/>
integer-list-rest : ε<br/>
<br/>  
/* #2c is also known as "COMMA" */<br/>
comma : #2c 
</code></p>
</div>    
