<h3 id="ddls-schema-reference-type">3.7 Schema Reference type</h3>


<p>A value of type \(\textit{SchemaReference}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) value.
   The map contains two entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{SchemaReference}\right)\) where \(\texttt{Schema}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{name}, v\right)\) where \(v\) is of type \(\textit{String}\).</li>
</ul>

<p>The translation function is hence given by</p>
\[
\sigma
\left(
  [\left(\texttt{kind},\texttt{Schema}\right),
   \left(\texttt{name}, v\right)]
\right)
=
\left(v,\sigma\left(w\right)\right)
\]
