<h3 id="schema-type">3.6 Schema type</h3>
<p>A value of type \(\textit{Schema}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) value.
   The map contains three entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{Schema}\right)\) where \(\texttt{Schema}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{name}, v\right)\) where \(v\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{definition}, w\right)\) where \(w\) is a value of type \(\textit{Value}_{\textit{DDLS}}\).</li>
</ul>

<p>The translation function is hence given by</p>
\[
\sigma
\left(
  [\left(\texttt{kind},\texttt{Schema}\right),
   \left(\texttt{name}, v\right),
   \left(\texttt{definition}, w\right)]
\right)
=
\left(v,\sigma\left(w\right)\right)
\]

<p>Given a schema value \( w = (x,y) \) with name \(x\) and definition \(y\) we write
   \(w.\textit{name}\) to denote \(x) and \(w.\textit{definition}\) to denote \(y\).</p>