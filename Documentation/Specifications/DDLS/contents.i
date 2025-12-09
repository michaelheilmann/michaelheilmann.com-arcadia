<h2 id="introduction">1 Introduction</h2>

<p>
This document is the specification of the <em>Data Definition Language Schema</em>, or <em>DDLS</em> for short.
DDLS is a declarative language for defining the structure and constraints for data described by a <a href="@{siteAddress}/specifications/data-definition-language">DDL</a>  programs.
</p>

<p>
<em>DDLS</em> programs and <em>DDL</em> programs are inputs to <em>DDLS validators</em>.
<em>DDLS validators</em> are tools which validate an input DDL program against an input DDLS Schema program.
These tools can be standalone or integrated into libraries and executables.
</p>

<h2 id="notations">Notations</h2>

<p>This specification uses the semantical form of the DDL as defined
   <a href="@{siteAddress}/specifications/data-definition-language/#semantical-specification">here</a>.</p>

<p>Given a DDL value \(x\), we denote the type of that value by \(\textit{type}(x)\).</p>

<p>
The following DDLS types exist:

The \(\textit{Any}_{\textit{DDLS}}\) type,
the scalar types
\(\textit{Boolean}_{\textit{DDLS}}\),
\(\textit{Number}_{\textit{DDLS}}\),
\(\textit{String}_{\textit{DDLS}}\), and
\(\textit{Void}_{\textit{DDLS}}\),
the aggregate types
\(\textit{List}_{\textit{DDLS}}\), and
\(\textit{Map}_{\textit{DDLS}}\),
as well as the schema reference type
\(\textit{SchemaReference}_{\textit{DDLS}}\).
</p>

The \(\textit{Value}_{\textit{DDLS}}\) type is defined as the union of the above types
\[\begin{aligned}
\textit{Value}_{\textit{DDLS}} =&\;\textit{Any}_{\textit{DDLS}}\\
                            \cup&\;\textit{Boolean}_{\textit{DDLS}}\\
                            \cup&\;\textit{List}_{\textit{DDLS}}\\
                            \cup&\;\textit{Map}_{\textit{DDLS}}\\
                            \cup&\;\textit{Number}_{\textit{DDLS}}\\

                            \cup&\;\textit{SchemaReference}_{\textit{DDLS}}\\
                            \cup&\;\textit{Void}_{\textit{DDLS}}\\
\end{aligned}\]

<p>
Furthermore, there exist a schema type \(\textit{Schema}_{\textit{DDLS}}\) and a map entry type \(\textit{MapEntry}_{\textit{DDLS}}\).
</p>
                            

<p>Given a DDLS value \(x\), we denote the type of that value by \(\textit{type}(x)\).</p>

<h2 id="semantics">3 Semantics</h2>

<p>DDLS programs are a restriction on DDL programs; that is, every DDLS program is a DDL program but not vice versa.
   The DDLS semantics are defined by a translation function \(\sigma\) of DDL values to DDLS values.</p>

\[
\sigma : \textit{Name} \cup \textit{Value}
         \rightarrow \textit{Error} \cup \textit{Value}_{\textit{DDLS}}
\]

@{include("./any-type.i")}
@{include("./boolean-type.i")}
@{include("./list-type.i")}
@{include("./map-type.i")}
@{include("./number-type.i")}
@{include("./schema-type.i")}
@{include("./schema-reference-type.i")}
@{include("./string-type.i")}
@{include("./void-type.i")}

<h2 id="validation">4 Validation</h2>
<p>
A <em>validation context</em> \(\langle \textit{schemas}, \textit{startSchemaName} \rangle\)
consists of a list \(\textit{schemas}\) if \(\textit{Schema}_{\textit{DDLS}}\) values    and
name \(\textit{startSchemaName}\) of type \(\textit{String}\).
</p>

<p>
The validation function maps from a validation context and a DDL node to a result:
</p>
\[
\text{validate} : \textit{Context} \times \textit{Node}_{\textit{DDL}} \rightarrow \textit{Result}
\]
<p>with</p>
\[
\textit{Result} = \textit{Errors} \cup \{ \textit{Success} \}
\]

<h3>4.1 validate</h3>
<p>\(\textit{validate}(\langle \textit{schemas}, \textit{startSchemaName} \rangle, x)\) is defined as follows:</p>
<ul>
  <li>Return a \(\textit{SchemaNotFound}\) error if there is no \(s \in \textit{schemas}, s.\textit{name} = \textit{startSchemaName}\).</li>
  <li>Return a \(\textit{SchemaAlreadySpecified}\) error if there two schemas \(s_i, s_j \in \textit{schemas}\) such that \(i \neq j\) but \(s_i.\textit{name} = s_j.\textit{name}\).</li>
  <li>Otherwise let \(s \in \textit{schemas}\) with \(s.\textit{name} = \textit{startSchemaName}\).</li>

  <li>
    If \(s\) is a \(\textit{SchemaReference}_{\textit{DDLS}}\) type:
    <ul>
      <li>Let \(v = \emptyset\).</li>
      <li>While \(s\) is a \(\textit{SchemaReference}_{\textit{DDLS}}\) type:
        <ul>
          <li>Find \(s' \in \textit{schemas}\) such that \(s'.\textit{name} = s.\textit{name}\). Return a \(\textit{SchemaNotFound}\) error if no such \(s'\) was found.</li>
          <li>Return a <em>CyclicSchema</em> error if \(s' \in v\).</li>
          <li>Let \(s = s'\) and \(v = v \cup \{ s' \}\).</li>
        </ul>
      </li>
      <li>Invoke \(\text{validate}\left(\langle \textit{schemas}, s'.\textit{name} \rangle, x\right)\).</li>
    </ul>
  </li>
  
  <li>If \(x\) is a DDL boolean value:
      <ul>
        <li>If \(s\) is not a value of type \(\textit{Boolean}_{\textit{DDLS}}\): return \(\textit{ValidationError}\).</li>
        <li>Otherwise return \(\textit{Success}\).</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL list value:
      <ul>
        <li>If \(s\) is not a value of type \(\textit{List}_{\textit{DDLS}}\): return \(\textit{ValidationError}\).</li>
        <li>Otherwise: \(\text{listValidation}(\langle \textit{schemas}, \textit{startSchemaName} \rangle, x)\).</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL map value:
      <ul>
        <li>If \(s\) is not a value of type \(\textit{Map}_{\textit{DDLS}}\): return \(\textit{ValidationError}\).</li>
        <li>Otherwise: \(\text{mapValidation}(\langle \textit{schemas}, \textit{startSchemaName} \rangle, x)\).</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL number value:
      <ul>
        <li>If \(s\) is not a value of type \(\textit{Number}_{\textit{DDLS}}\): return \(\textit{ValidationError}\).</li>
        <li>Otherwise return <em>Success</em>.</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL string value:
      <ul>
        <li>If \(s\) is not a value of type \(\textit{String}_{\textit{DDLS}}\): return \(\textit{ValidationError}\)-</li>
        <li>Otherwise return <em>Success</em>.</li>
      </ul>
  </li>
  <li>If \(x\) is a DDL void value:
      <ul>
        <li>If \(s\) is not a value of type \(\textit{Void}_{\textit{DDLS}}\): return \(\textit{ValidationError}\).</li>
        <li>Otherwise return <em>Success</em>.</li>
      </ul>
</ul>

<h3>4.2 validateList</h3>
<p>\(\textit{validateList} : \textit{Context} \times \textit{ListNode}_{\textit{DDL}} \rightarrow \textit{Result}\) validates a DDL list node.</p>
<p>\(\textit{validateList}(\langle \textit{schemas}, \textit{startSchemaName}\rangle, x)\) is defined as follows:</p>

<ul>
  <li>Return a \(\textit{SchemaNotFound}\) error if there is no \(s \in \textit{schemas}, s.\textit{name} = \textit{startSchemaName}\).</li>
  <li>Return a \(\textit{SchemaAlreadySpecified}\) error if there two schemas \(s_i, s_j \in \textit{schemas}\) such that \(i \neq j\) but \(s_i.\textit{name} = s_j.\textit{name}\).</li>
  <li>Otherwise let \(s \in \textit{schemas}\) with \(s.\textit{name} = \textit{startSchemaName}\).</li>
   <li>If \(s\) is no DDLS list type: return \(\textit{ValidationError}\).</li>
</ul>

<p>
\(x.\textit{elements}\) has a list of DDL nodes.
\(s.\textit{element}\) is a DDLS node.
</p>
<p>
\(\textit{validate}(\langle \textit{schemas}, s.\textit{element}.\textit{name} \rangle, x')\) is invoked for each \(x' \in x.\textit{elements}\).
If there is an invocation \(r := \textit{validate}\left(\langle \textit{schemas}, s.\textit{element}.\textit{name} \rangle, x'\right)\) where \(r \neq \textit{Success}\), then return \(r\);
otherwise return \(\textit{Success}\).
</p>

<h3>4.3 validateMap</h3>
<p>\(\textit{validateMap} : \textit{Context} \times \textit{MapNode}_{\textit{DDL}} \rightarrow \textit{Result}\) validates a DDL map node.</p>
<p>\(\textit{validateMap}(\langle \textit{schemas}, \textit{startSchemaName}\rangle, x\) is defined as follows:</p>

<ul>
  <li>Return a \(\textit{SchemaNotFound}\) error if there is no \(s \in \textit{schemas}, s.\textit{name} = \textit{startSchemaName}\).</li>
  <li>Return a \(\textit{SchemaAlreadySpecified}\) error if there two schemas \(s_i, s_j \in \textit{schemas}\) such that \(i \neq j\) but \(s_i.\textit{name} = s_j.\textit{name}\).</li>
  <li>Otherwise let \(s \in \textit{schemas}\) with \(s.\textit{name} = \textit{startSchemaName}\).</li>
  <li>If \(s\) is no DDLS map type: return \(\textit{ValidationError}\).</li>
</ul>

<p>
\(x.\textit{entries}\) is a list of DDL map entry nodes; a map entry node \(x' \in x.\textit{entries}\) consists of a name \(x'.\textit{name}\) and a \(x'.\textit{value}\) which is a DDL node.
\(s.\textit{entries}\) is a list of DDLS map entry nodes; a map entry node \(s' \in s.\textit{entries}\) consists of a name \(s'.\textit{name}\) and a \(s'.\textit{value}\) which is a DDLS node.
</p>

<p>
Return a <em>ValidationError</em> if there exist \(x', x'' \in x.\textit{entries}\) such that \(x' \neq x''\) and \(x'.\textit{name} = x''.\textit{name}\).
That is, the DDL map must not have two map entries with the same name. 
</p>

<p>
Return a <em>ValidationError</em> if there exists \(s' \in s.\textit{entries}\) such that no \(x' \in x.\textit{entries}\) with \(s'.\textit{name} = x'.\textit{name}\).
That is, if a map entry with a certain name was specified in \(s\) then it must be present in \(x\).
</p>

<p>
Return a <em>ValidationError</em> if there exists \(x' \in x.\textit{entries}\) such that no \(s' \in s.\textit{entries}\) with \(x'.\textit{name} = s'.\textit{name}\).
That is, if a map entry with a certain name is present in \(x\) then it must be specified in \(s\).

</p>

<p>
For each \(x' \in x.\textit{entries}\) and for each \(s' \in s.\textit{entries}\)
\(\textit{validate}\left(\langle \textit{schemas}, s'.\textit{value}.\textit{name} \rangle, x'.\textit{value}\right)\) is invoked if \(s'.\textit{name} = x'.\textit{name}\).
If there is an invocation \(r := \textit{validate}\left(\langle \textit{schemas}, s'.\textit{value}.\textit{name} \rangle, x'.\textit{value}\right)\) where \(r \neq \textit{Success}\), then return \(r\);
otherwise return \(\textit{Success}\).
</p>

<h3>4.4 Acceptance and Rejection</h3>
<p>
\(\textit{validate}(S, s, x)\) always terminates.
If no error is raised, then \(x\) was accepted by \(S\) with \(s\).
Otherwise \(x\) was rejected by \(S\) with \(s\).
</p>
