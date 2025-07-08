  @{include("./../../Documentation/Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=4'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=4'>
  <link rel='canonical' href='@{siteAddress}/specifications/common-lexical-specification/index.html'>
  <title>Common Lexical Specification</title>
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
    <h1>Common Lexical Specifications</h1>
    <p style="font-style: italic">
    This <em>Common Lexical Specification</em> provides definitions of grammar rules being re-used in multiple language specifications on this website.
    This document consists of three sections: Section 1 defines how programs are encoded on a Byte level. Section 2 provides an introduction into grammars.
    Section 3 provides the full profile lexical grammar. Section 4 provides information on profiles.
    </p>
    
    @{include("Specifications/CommonLexicalSpecification/1. Grammars.i")}
    @{include("Specifications/CommonLexicalSpecification/3. Full Profile Lexical Specification.i")} 
    
  </div>
  <div class="right-column">
    <nav>
      <ul style="list-style: none">
        <li><a href="#unicode">1. Unicode</a></li>
        <li><a href="#grammars">2. Grammars</a></li>
        <li><a href="#context-free-grammars">2.1. Context-free grammars</a></li>
        <li><a href="#lexical-grammars">2.2 Lexical grammars</a></li>
        <li><a href="#syntactical-grammars">2.3. Syntactical grammars</a></li>
        <li><a href="#grammar-notation">2.4. Grammar notation</a></li>
        <li><a href="#full-profile-lexical-specification">3 Full Profile Lexical Specification</a></li>
        <li><a href="#full-profile-lexical-specification-word">3.1 word</a></li>
        <li><a href="#full-profile-lexical-specification-whitespace">3.2 whitespace</a></li>
        <li><a href="#full-profile-lexical-specification-line-terminator">3.3 line terminator</a></li>
        <li><a href="#full-profile-lexical-specification-comment">3.4 comment</a></li>
        <li><a href="#full-profile-lexical-specification-parentheses">3.5 parentheses</a></li>
        <li><a href="#full-profile-lexical-specification-curly-brackets">3.6 curly brackets</a></li>
        <li><a href="#full-profile-lexical-specification-colon">3.7 colon</a></li>
        <li><a href="#full-profile-lexical-specification-comma">3.9 comma</a></li>
        <li><a href="#full-profile-lexical-specification-number-literal">3.10 number literal</a></li>
        <li><a href="#full-profile-lexical-specification-string-literal">3.11 string literal</a></li>
        <li><a href="#full-profile-lexical-specification-boolean-literal">3.12 boolean literal</a></li>
        <li><a href="#full-profile-lexical-specification-void-literal">3.13 void literal</a></li>
        <li><a href="#full-profile-lexical-specification-digit">3.14 decimal digit</a></li>
        <li><a href="#full-profile-lexical-specification-digit">3.15 hexadecimal digit</a></li>
        <li><a href="#full-profile-lexical-specification-alphanumeric">3.16 alphanumeric</a></li>
      </ul>
    </nav>
  </div>   
  </main>
  <footer>
    <div class="left-column"></div>
    <div class="center-column"></div>
    <div class="right-column"></div>
    <span style="font-style: italic">Webite maintained by Michael Heilmann. Last modified on 09 July 2025.</span>
    </div>
  </footer>
</body>
</html>
