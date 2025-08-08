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
  <main>
  <div class="left-column"></div>
  <div class="center-column">
    <div style='padding-left: 2rem; padding-top: 2rem;'>Something went wrong ...</div>
    </div>
  <div class="right-column">
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
