  @{include("./../../Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/data-definition-language/index.html'>
  <title>Data Definition Language</title>
  <style>
  @{include("./../specification.css.i")}
  my-sem, my-syn, my-lex {
    font-family: my-code-font, monospace;
  }
  my-syn::after {
    content: "<sub>syn/sub>"
  }
  my-sem {
    font-style: italic;
    font-family: my-default-font;
  }
  my-sem::after {
    content: "<sub>sem</sub>"
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
    <h2 id="introduction">1 Introduction</h2>
    <p>This document is the specification of the <em>Data Definition Language</em>.
    Programs of this language are sets of UTF8 files of this language and describe structured data for the purpose of for exchanging that data between entities (humans and machines alike).
    The language provides scalar types (boolean type, number type, string type, and void type)  as well as aggregate types (map values and list values).
    </p>

    <p>
    The language is insipired by JSON (see <a href="https://www.ecma-international.org/publications-and-standards/standards/ecma-404/">ECMA-404 The JSON interchange syntax, 2nd edition, December 2017</a> for more information).
    A conversion between JSON and DDL is possible without the loss of data.
    </p>

    @{include("./lexical-specification.i")}
    @{include("./syntactical-specification.i")}
    @{include("./semantical-specification.i")}

  </div>
  <div class="right-column">
   <nav>
      <ul style="list-style: none">
        <li><a href="#introduction">1 Introduction</a></li>
        <li><a href="#lexical-specification">2 Lexical Specification</a></li>
        <li><a href="#syntactical-specification">3 Syntactical Specification</a></li>
        <li><a href="#semantical-specification">4 Semantical Specification</a></li>
      </ul>
    </nav>
  </div>
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
