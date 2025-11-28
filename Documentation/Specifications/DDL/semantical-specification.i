<h2 id="semantical-specification">4 Semantical Specification</h2>
<p>
The <em>Data Definition Language</em> language describes structured data in terms of <em>typed values</em>.
That is, each <em>sentence</em> of the <em>syntactical specification</em> translates to <em>values</em> each of which has <em>type</em>.
The <em>Data Definition Language</em> knows six basic types
<my-sem>sem:List</my-sem> and <my-sem>sem:Map</my-sem>, which are the so called aggregate types, and
<my-sem>sem:Boolean</my-sem>, <my-sem>sem:Number</my-sem>, <my-sem>sem:String</my-sem>, and <my-sem>sem:Void</my-sem>, which are the so called scalar types.
There exists a special type <my-sem>sem:Name</my-sem>.
</p>

<h3>4.1 Boolean Type</h3>
<p>
The type <my-sem>Boolean</my-sem> type has two values <my-sem>sem:true</my-sem> and <my-sem>sem:false</my-sem> which are expressed in the language by the words
<my-syn>true</my-syn> and <my-syn>false</my-syn>, respectively (as defined in the syntactical grammar).
</p>

<h3>4.2 List Type</h3>
<p>
The type <my-sem>sem:List := [sem:Value]</my-sem> represents lists of values of type <my-sem>Value</my-sem>.
A value of type <my-sem>sem:List<</my-sem> is expressed in the language by the sentence <my-syn>syn:List</my-syn> (as defined in the syntactical grammar).
The i-th <my-syn>syn:ListBodyElement</my-syn> is the i-th value in the list.
</p>

<p><b>Example</b></p>
<div class="box">
<p><code>
// A list with three numbers 1, 2, and 3.<br>
[ 1, 2, 3 ]
</code></p>
</div>

<h3>4.3 Map Type</h3>
<p>
The type <my-sem>sem:Map := [sem:MapElement]</my-sem> represents a list of map elements.
The values of type map expressed in the language by the sentence <my-sy>map</my-syn>.
The i-th <my-syn>syn:MapBodyElement</my-syn> is the it-h <my-sem>sem:MapElement</my-sem> in the list.
</p>

<p>
A <my-sem>sem:MapElement</my-sem> is a tuple of which the first element is a value of the special type <my-sem>sem:Name</my-sem> and of which the second element is a value <my-sem>Value</my-sem> value.
The <my-syn>syn:Name</my-syn> of the <my-syn>syn:MapBodyElement</my-syn> represents the first element of the tuple and <my-syn>syn:Value</my-syn> represents the second element of the tupel.
</p>

<p><b>Example</b></p>
<div class="box">
<p><code>
// A map of<br>
// text to 'Hello, World!'<br>
// action to 'Print', and<br>
// fontSize to 12.<br>
{ text : 'Hello World!', action : 'Print', fontSize: 12 }
</code></p>
</div>

<p>If two map entries of the same <my-sem>sem:Name</my-sem> occur in the same map, this is an error.</p>

<p><b>Example</b></p>
<div class="box">
<p>
The following Data Definition Language program defines a <my-sem>sem:Map</my-sem> value that contains two map entries with the same name <my-lex>lex:x</my-syn>.
The first name/value pair maps to the value <my-lex>lex:'0'</my-syn> and second name/value pair to the number <my-syn>lex:'1'</my-syn>.
</p>

<p><code>
{ x : 0, x : 1 }
</code></p>

<p>
This is a semantical error.
</p>

</div>

<h3>4.4 Number Type</h3>
<p>
The type <my-sem>sem:Number</my-sem> type represents both two's complment integer numbers as well as IEEE754 floating-point numbers (without not-a-number values of infinity values).
The values of type number are expressed in the language by the word <my-syn>sem:Number</my-syn> (as defined in the syntactical grammar).

Note that the <code>Data Definition Language</code> does not impose restrictions on the size of the literals or the values.
Implementations, however, may impose restrictions.
</p>

<h3>4.5 String Type</h3>
<p>
The type <my-sem>sem:String</my-sem> type represents UTF-8 strings. <my-sem>sem:String</my-sem> values are expressed in the language by the word <my-syn>syn:String</my-syn> (as defined in the syntactical grammar).
At the end of the syntactical translation of a <my-syn>syn:String</my-syn> word, its escape sequences are replaced by the Unicode symbols they are representing. Furthermore, the opening and closing quotes are removed.

Note that the <em>Data Definition Language</em> does not impose restrictions on the size of the literals or the values.
Implementations, however, may impose restrictions.
</p>

<h3>4.6 Value Type</h3>
<p>
The type <my-sem>sem:Value</my-sem> type is the union type of the types <my-sem>sem:Boolean</my-sem>, <my-sem>sem:List</my-sem>, <my-sem>sem:Map</my-sem>, <my-sem>sem:Number</my-sem>, <my-sem>sem:String</my-sem>, <my-sem>sem:Void</my-sem>.
</p>

<h3>4.7 Void Type</h3>
<p>
The type <my-sem>sem:Void</my-sem> type has a single values <my-sem>void</my-sem> which is expressed in the language by the word <my-sym>sym: Void</my-sym> (as defined in the syntactical grammar).
</p>
