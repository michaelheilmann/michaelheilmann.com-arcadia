  @{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/error.html'>
  <title>Something went wrong ...</title>
</head>
<body class="my-error-page-1">
  <!-- flex-direction: row ~ from left to right -->
  <header>
  <div>
  <a href="@{siteAddress}/">Home</a>
  </div>
  </header>
  <main style='flex-grow: 1; display: flex; flex-direction: row;'>
  <div style='padding-left: 2rem; padding-top: 2rem;'>Something went wrong ...</div>
  </main>
  <!-- flex-direction: row ~ from left to right*/ -->
  <footer style='flex-grow: 0; display: flex; flex-direction: row;'>
  </footer>
</body>
</html>
