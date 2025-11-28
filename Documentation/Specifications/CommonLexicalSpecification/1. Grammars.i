<h1 id="unicode">1. Unicode</h1>
<p>
A program is a sequence of Unicode code points encoded into a sequence of Bytes using an Unicode encoding.
In this version, only UTF-8 NOBOM with sequences of length 1 is supported.
The Unicode encoding of a particular program must be determined by consumers of this specification.
</p>

<h1 id="grammars">2. Grammars</h1>
<p>This section describes context-free grammars used in this specification to define the lexical and syntactical structure of a language.</p>

<h2 id="context-free-grammars">2.1 Context-free grammars</h2>
<p>A context-free grammar consists of a number of production. Each production has an abstract symbol called a non-terminal as its left-hand side, and a sequence of one or more
non-terminal and terminal symbols as its right-hand side. For each grammar, the terminal symbols are drawn from a specified alphabet.</p>

<p>Starting from a sequence consisting of a single distinguished non-terminal, called the goal symbol, a given context-free grammar specifies a language, namely, the set of possible
sequences of terminal smbols that can result from repeatedly replacing any non-terminal in the sequence with a right-hand side of a production for which the non-terminal is the
left-hand side.</p>

<h3 id="lexical-grammars">2.3 Lexical grammars</h3>
<p>The lexical grammar uses the Unicode code points from the Unicode decoding phase as its terminal symbols.
The non-terminals of the lexical grammar start with the prefix <code>Lexical.</code>.
It defines a set of productions, starting from the goal symbol <my-mv>Lexical.Word</my-mv>, that describe how sequences of code points are translated into a word.
</p>

<h3 id="syntactical-grammars">2.4 Syntactical grammars</h3>
<p>The syntactical grammar for the <em>Data Definition Language</em> uses words of the lexical grammar as its terminal symbols.
The non-terminals of the syntactical grammar start with the prefix <code>Syntactical.</code>.
It defines a set of productions, starting from the goal symbol <my-mv>sentence</my-mv>, that describe how sequences of words are translated into a sentence.
</p>

<h3 id="grammar-notation">2.5 Grammar notation</h3>
<p>Productions are written in <code>fixed width</code> fonts.</p>

<p>A production is defined by its left-hand side, followed by a colon <code:</code>, followed by its right-hand side definition. The
left-hand side is the name of the non-terminal defined by the production. Multiple alternating definitions of a production may be
defined. The right-hand side of a production consits of any sequence of terminals and non-terminals. In certain cases the right-hand
side is replaced by a comment describing the right-hand side. This comment is opened by <code>/*</code> and closed by <code>*/</code>.
</p>

<div class="box">
<div class="header">
Example
</div>
<div class="body">
<p>The following production denotes the non-terminal for a digit as used in the definitions of numerals:</p>
<p><code>
Lexical.Digit: /* A single Unicode symbol from the code point range +U0030 to +U0039 */
</code></p>
</div>
</div>

<p>A terminal is a sequence of Unicode symbols. A Unicode symbol is denoted by a shebang <code>#</code> followed by a hexadecimal number denoting its code point.<p>

<div class="box">
<div class="header">
Example
</div>
<div class="body">
<p>The following productions denote the non-terminal for a sign as used in the definitions of numerals:</p>
<p><code>
/* #2b is also known as "PLUS SIGN" */<br/>
Lexical.PlusSign : #2b<br/>
/* #2d is also known as "MINUS SIGN" */<br/>
Lexical.MinusSign : #2d sign : plus_sign<br/>
Lexical.Sign : Lexical.PlusSign | Lexical.MinusSign
</code></p>
</div>
</div>

<p>The syntax <code>{x}</code> on the right-hand side of a production denotes zero or more occurrences of <code>x</code>.</p>

<div class="box">
<div class="header">
Example
</div>
<div class="body">
<p>The following production defines a possibly empty sequence of digits as used in the definitions of numerals:</p>
<p><code>
Lexical.ZeroOrMoreDigits : {Lexical.Digit}
</code></p>
</div>
</div>

<p>The syntax <code>[x]</code> on the right-hand side of a production denotes zero or one occurrences of <code>x</code>.</p>

<div class="box">
<div class="header">Example</div>
<div class="body">
<p>The following productions denotes a possible definition of an integer numeral.
It consists of an optional sign followed by a digit followed by zero or more digits (as defined in the previous example):</p>
<p><code>
Lexical.Integer : [Lexical.Sign] Lexical.Digit Lexical.ZeroOrMoreDigits
</code></p>
</div>
</div>

<p>The empty string is denoted by <code>ε</code>.</p>

<div class="box">
<div class="header">Example</div>
<div class="body">
<p>
The following productions denotes a possibly empty list of integers (with integer as defined in the preceeding example).
Note that this list may include a trailing comma hence the <code>{x}</code> operator cannot be used here.
</p>
<p><code>
Syntactical.IntegerList : integer Syntactical.IntegerListRest<br/>
Syntactical.IntegerList : ε<br/>
<br/>
Syntactical.IntegerListRest : Lexical.Comma Syntactical.Integer Syntactical.IntegerListRest<br/>
Syntactical.IntegerListRest : Lexical.Comma<br/>
Syntactical.IntegerListRest : ε<br/>
<br/>
/* #2c is also known as "COMMA" */<br/>
Lexical.Comma : #2c
</code></p>
</div>
</div>
