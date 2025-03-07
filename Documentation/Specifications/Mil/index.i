  @{include("./../../Documentation/Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/specifications/mil/index.html'>
  <title>Machine Interface Language</title>
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
    <h2>Interpretation</h2>

    <h3>Register Allocation</h3>
    <p>Assume the following procedure:</p>
    <p><code>
    procedure p
    begin
      $1 := 1
      $2 := 2
      $7 := 3
    end
    </code></p>

    <p>
    The set of used registers of this function is <code>$1</code>, <code>$2</code>, <code>$7</code>.
    The register allocator wil rewrite the function such that the register numbers are consective.
    </p>

        <p><code>
    procedure p
    begin
      $1 := 1
      $2 := 2
      $3 := 3
    end
    </code></p>

    <p>The set of used registers of this procedure after the rewrite is <code>$1</code>, <code>$2</code>, <code>$3</code>.</p>

    <h3>Procedure Prologue and Epilogue</h3>
    p>
    When entering the procedure, the contents of the registers <code>$1</code>, <code>$2</code>, <code>$3</code> are pushed on the stack.
    When leaving the procedure, the contents of the registers <code>$1</code>, <code>$2</code>, <code>$3</code> are restored from the stack.
    </p>
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
