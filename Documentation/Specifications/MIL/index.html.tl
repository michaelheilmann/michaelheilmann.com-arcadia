  @{include("./../../Documentation/Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/mil/index.html'>
  <title>Machine Interface Language</title>
  <style>
  my-lhs {
    display: block;
  }
  my-rhs {
    display: block;
    margin-left: 1rem;
  }
  
  </style>
</head>
<body class="my-content-page-1">
  <header>
  <div>
  <a href="@{siteAddress}/">Home</a>
  </div>
  </header>
  <main>
    <div class="left-column"></div>
    <div class="center-column">
    <h1>Machine Interface Language</h1>
    <h2>Grammar</h2>
    <h3>Module</h3>
    <p>A module consists of zero or more class, enumeration, and procedure definitions.</p>
    <p><code>
    module : definition*<br>
    definition : classDefinition<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
               | procedureDefinition
    </code></p>
        
    <h3 id="class-definition">Class Definition</h3>
    <p><code>
    classDefinition : 'class' name ('extends' name)? classBody<br>
    procedureBody : '{' classMemberDefinition '}'<br>
    classMemberDefinition : constructorDefinition<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                          | methodDefinition<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                          | fieldDefinition
    </code></p>
    
    <h3 id="constructor-definition">Constructor Definition</h3>
    <p><code>
    constructorDefinition : 'constructor' ('native' string)? constructorParameters<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                          | 'constructor' constructorParameters constructorBody<br>
    constructorBody : '{' statements '}'
    </code></p>
    
    <h3 id="method-definition">Method Definition</h3>
    <p><code>
    methodDefinition : 'method' ('native' string)? name methodParameters<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                     | 'method' methodParameters methodBody<br>
    methodBody : '{' statements '}'
    </code></p>
    
    <h3 id="procedure-definition">Procedure Definition</h3>
    <p><code>
    procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                        | 'procedure' 'entry'? name procedureParameters procedureBody<br>
    procedureBody : '{' statements '}'
    </code></p>
    

    <h3 id="instruction-statement">Instruction Statement</h3>
    <p>An instruction statement is an instruction.</p>
    <p><code>
    instructionStatement : instruction
    </code></p>
    
    <h3 id="definition-statement">Definition Statement</h3>
    <p>A definition statement is a variable definition statement or a label definition statement.</p>
    <p><code>
    definitionStatement : variableDefinitionStatement<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                        | labelDefinitionStatement
    </code></p>
    
    <h3 id="label-definition-statement">Label Definition Statement</h3>
    <p>A label definition statement is a name followed by a colon.</p>
    <p><code>
    labelDefinitionStatement : name ':'
    </code></p>
    
    <h3 id="variable-definition-statement">Variable Definition Statement</h3>
    <p>A variable definition statement is the variable keyword followed by the name of the variable.</p>
    <p><code>
    variableDefinitionStatement : 'variable' name
    </code></p>
  </div>
  <div class="right-column"></div>   
  </main>
  <footer>
    <div class="left-column"></div>
    <div class="center-column"></div>
    <div class="right-column">
      <div>Website maintained by @{siteAuthor}.</div>
      <div>Last modified on @{dayOfMonth()} @{monthName()} @{year()}.</div>
    </div>
  </footer>
</body>
</html>
