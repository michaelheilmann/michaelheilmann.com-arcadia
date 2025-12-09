<h3 id="map-type">3.4 Map type</h3>
<p>A value of type \(\textit{Map}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) value.
   The map contains two entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{Map}\right)\) where \(\texttt{Map}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{entries}, w\right)\) where \(w\) is \(\textit{List}\) value with elements of type \(\textit{MapEntry}_{\textit{DDLS}}\).</li>
</ul>

<p>The translation function is hence given by</p>
\[
\sigma
\left(
  [\left(\texttt{kind},\texttt{Map}\right),
   \left(\texttt{entries}, w\right)]
\right)
=
\begin{cases}
\left(\sigma\left(w\right)\right) &\text{if }\sigma(w) \not\in \textit{Error} \text{,}\\
\sigma(w)                         &\text{otherwise.}
\end{cases}
\]
with
\[
\left(\sigma(w)\right)=
\begin{cases}
\left([\sigma(x)] \circ \sigma(v)\right) & \text{if } w = [x] \circ v \text{ and } \sigma(x) \not\in \textit{Error}\text{,}\\
\sigma(x)                                & \text{if } w = [x] \circ v \text{ and } \sigma(x)     \in \textit{Error}\text{,}\\
\left([]                         \right) & \text{if } w = []\text{,}\\     
\end{cases}
\]


<p>A value of type \(\textit{MapEntry}_{\textit{DDLS}}\) are represented by a \(\textit{Map}\) value.
   The map contains three entries.</p>

<ul>
  <li>\(\left(\texttt{kind}, \texttt{MapEntry}\right)\) where \(\texttt{MapEntry}\) is of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{name}, a\right)\) where \(a\) is a value of type \(\textit{String}\).</li>
  <li>\(\left(\texttt{type}, b\right)\) where \(b\) is a value of type \(\textit{Value}_{\textit{DDLS}}\).</li>
</ul>

<p>The translation function for a \(\textit{MapEntry}_{\textit{DDLS}}\) is hence given by</p>
\[
\sigma
\left(
  [\left(\texttt{kind},\texttt{MapEntry}\right),
   \left(\texttt{name}, a\right)
   \left(\texttt{type}, b\right)]
\right)
=
\begin{cases}
\left(a, \sigma\left(b\right)\right) &\text{if }\sigma(b) \not\in \textit{Error} \text{,}\\
\sigma(b)                            &\text{if }\sigma(b) \in \textit{Error} \text{,}\\
\textit{Error}                       &\text{otherwise.}
\end{cases}
\]