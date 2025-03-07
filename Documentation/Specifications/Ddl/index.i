  @{include("./../../Documentation/Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/ddl/index.html'>
  <title>Data Definition Language</title>
  <style>
  .box {
    padding-bottom: 8px;
    padding-top: 8px;
    padding-left: 8xp;
    padding-right: 8px;
    background-color: rgb(215, 210, 203);
  }
  div.box code {
    background-color: rgb(215, 210, 203);
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
    <h1>Data Definition Language</h1>
    <h2>Introduction</h2>
    <p>This document is the specification of the <em>Data Definition Language</em>.
    Programs of this language describe data as text for the purpose of storing and exchanging that data between entities (humans and machines alike).
    For the purpose of describing such data, the language offers built-in data types consisting of scalar values (boolean values, number values, string values, and void values)
    as well as aggregate values (map values and list values).
    </p>
    
    <p>
    The language is insipired by JSON (see <a href="https://www.ecma-international.org/publications-and-standards/standards/ecma-404/">ECMA-404 The JSON interchange syntax, 2nd edition, December 2017</a> for more information).
    A conversion between JSON and DDL is possible without the loss of data.
    </p>

    @{include("./Specifications/Ddl/grammars.i")}
    @{include("./Specifications/Ddl/lexical-structure.i")}
    @{include("./Specifications/Ddl/syntactical-structure.i")}
    @{include("./Specifications/Ddl/semantical-structure.i")}
   
  </div>
  <div class="right-column"></div>   
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
