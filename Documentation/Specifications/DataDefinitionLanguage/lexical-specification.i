<h2 id="lexical-specification">2 Lexical Specification</h2>
<p>The lexical specification of the <em>Data Definition Language</em> is based on the <em>Common Lexical Specification</em>
(see <a href="@{siteAddress}/specifications/common-lexical-specification">@{siteAddress}/specifications/common-lexical-specification</a> for more information).
The Data Definition Language lexical specification profile is obtained by adjusting the definition of the 
<code>Lexical.Word</code> of the <Full lexical specification profile:</p>

<div class="box">
<div class="body">
<p><code>
Lexical.Word : Lexical.Boolean<br/>
Lexical.Word : Lexical.Number<br/>
Lexical.Word : Lexical.String<br/>
Lexical.Word : Lexical.Void<br/>
Lexical.Word : Lexical.Name<br/>
Lexical.Word : Lexical.LeftCurlyBracket<br/>
Lexical.Word : Lexical.RightCurlyBracket<br/>
Lexical.Word : Lexical.LeftSquareBracket<br/>
Lexical.Word : Lexical.RightSquareBracket<br/>
Lexical.Word : Lexical.Comma<br/>
/*whitespace, newline, and comment are not considered the syntactical grammar*/
Lexical.Word : Lexical.Whitespace<br/>
Lexical.Word : Lexical.Newline<br/>
Lexical.Word : Lexical.Comment<br/>
</code></p>
</div>
</div>
