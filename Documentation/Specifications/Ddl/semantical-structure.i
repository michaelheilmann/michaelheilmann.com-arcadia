<h2>Semantical Structure</h2>
<p>
The <em>Data Definition Language</em> knows six basic types
<em>List</em> and <em>Map</em>, which are the so called aggregate types, and
<em>Boolean</em>, <em>Number</em>, <em>String</em>, and <em>Void</em>, which are the so called scalar types.
</p>

<h3>Boolean Type</h3>
<p>
The type <em>Boolean</em> type has two values <em>true</em> and <em>false</em> which are expressed in the language by the words <code>true</code> and <code>false</code>, respectively (as defined in the syntactical grammar). 
</p>

<h3>Number Type</h3>
<p>
The type <em>Number</em> type represents both two's complment integer numbers as well as IEEE754 floating-point numbers (without not-a-number values of infinity values).
The values of type number are expressed in the language by the word <code>number</code> (as defined in the syntactical grammar).

Note that the <code>Data Definition Language</code> does not impose restrictions on the size of the literals or the values.
Implementations, however, may impose restrictions.  
</p>

<h3>String Type</h3>
<p>
The type <em>String</em> type represents UTF-8 strings. <em>String</em> values are expressed in the language by the word <code>string</code> (as defined in the syntactical grammar).
At the end of the lexical translation of a String word, its escape sequences are replaced by the Unicode symbols they are representing. Furthermore, the opening and closing quotes are removed.

Note that the <em>Data Definition Language</em> does not impose restrictions on the size of the literals or the values.
Implementations, however, may impose restrictions. 
</p>

<h3>List Type</h3>
<p>The type <em>List</em> represents lists of values. A value of type <em>List</em> is expressed in the language by the sentence <code>list</code> (as defined in the syntactical grammar).</p>

<p><b>Example</b></p>
<div class="box">
<p><code>
// A list with three numbers 1, 2, and 3.
[ 1, 2, 3 ]
</code></p>
</div>

<h3>Map Type</h3>
<p>The type <em>Map</em> represents maps from names to values. A value of type <em>Map</em> is expressed in the language by the sentence <code<map</code> (as defined in the syntactical grammar).</p>

<p><b>Example</b></p>
<div class="box">
<p><code>
// A map of
// text to 'Hello, World!'
// action to 'Print', and
// fontSize to 12.
{ text : 'Hello World!', action : 'Print', fontSize: 12 } 
</code></p>
</div>

<p> If two name/value pairs from the same name in a map are specified, then last specified name/value pair takes precedence. </p>

<p><b>Example</b></p>
<div class="box">
<p>The following Data Definition Language program defines a Map value that contains two name/value pairs with the same name x. The first name/value pair maps to the value 0 and second name/value pair to the number 1.</p>

<p><code>
{ x : 0, x : 1 }
</code></p>

<p>The effective Map value defined by the program is hence</p>

<p><code>
{ x : 1 }
</code></p>

<p>as name/value pair mapping to the value 0 is specified before the name/value pair mapping to the value 1.</p>
</div>
