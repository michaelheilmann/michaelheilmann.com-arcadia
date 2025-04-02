  @{include("./../../Documentation/Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/ddl/index.html'>
  <title>Data Definition Language</title>
  <style>
  @{include("./Specifications/specification.css.i")} 
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
    <h1>Data Definition Language</h1>
    <h2 id="introduction">1. Introduction</h2>
    <p>This document is the specification of the <em>Data Definition Language</em>.
    Programs of this language are sets of UTF8 files of this language and describe structured data for the purpose of for exchanging that data between entities (humans and machines alike).
    The language provides scalar types (boolean type, number type, string type, and void type)  as well as aggregate types (map values and list values).
    </p>
    
    <p>
    The language is insipired by JSON (see <a href="https://www.ecma-international.org/publications-and-standards/standards/ecma-404/">ECMA-404 The JSON interchange syntax, 2nd edition, December 2017</a> for more information).
    A conversion between JSON and DDL is possible without the loss of data.
    </p>

    @{include("./Specifications/DataDefinitionLanguage/lexical-specification.i")}
    @{include("./Specifications/DataDefinitionLanguage/syntactical-specification.i")}
    @{include("./Specifications/DataDefinitionLanguage/semantical-specification.i")}
   
  </div>
  <div class="right-column">
   <nav>
      <ul style="list-style: none">
        <li><a href="#introduction">1. Introduction</a></li>
        <li><a href="#lexical-specification">2. Lexical Specification</a></li>
        <li><a href="#syntactical-specification">3. Syntactical Specification</a></li>
        <li><a href="#semantical-specification">4. Semantical Specification</a></li>
      </ul>
    </nav>
  </div>   
  </main>
  <footer>
    <div class="left-column"></div>
    <div class="center-column"></div>
    <div class="right-column"></div>
    <span style="font-style: italic">Webite maintained by Michael Heilmann. Last modified on 25 Feburary 2025.</span>
    </div>
  </footer>
</body>
</html>
