@{include("./../../../../Documentation/Commons/header-common.i")}
<link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
<link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
<link rel='canonical' href='@{siteAddress}/repository/R1/'>
<title>Michael Heilmann's Runtime Mark 1</title>
<script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@@3.2.2/es5/tex-mml-chtml.min.js"></script>
<style>
  /* variable */
  my-v {
    font-family: my-code-font;
    font-size: 0.9rem;
  }

  /* meta variable */
  my-mv {
    display: inline;
    font-family: my-code-font;
    font-size: 0.9rem;
  }
  my-mv::before {
    content: "<";
  }
  my-mv::after {
    content: ">";
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
  <h1>Michael Heilmann's Runtime Mark 1</h1>
  <p>
  This is the documentation for Michael  Heilmann's Runtime Mark 1,
  henceforth R1. R1 facilitates the creation of C programs - in particular interpreters - that are portable,
  maintainable, as well as safe. R1 is available at <a href="@{siteAddress}/repository/R1">michaelheilmann.com/repository/R1</a>.
