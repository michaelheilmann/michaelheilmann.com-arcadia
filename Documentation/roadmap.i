  @{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/roadmap.html'>
  <title>Roadmap</title>
</head>
<body class="my-content-page-1">
  <header>
  <div>
  <a href="@{siteAddress}/">Home</a>
  </div>
  </header>
  <main>
    <h1>Roadmap</h1>
    @{include("./Roadmap/Milestone2.2.i")}
    @{include("./Roadmap/Milestone10.i")}
    @{include("./Roadmap/Milestone9.i")}
    @{include("./Roadmap/Milestone8.i")}
    <h2>Archive of completed milestones</h2>
    <p>You can review completed milestones in the <a href="https://michaelheilmann.com/roadmap-archive">roadmap archive</a>.</p>
  </main>
  <footer>
    <span style="font-style: italic">Webite maintained by Michael Heilmann. Last modified on 20 October 2024.</span>
  </footer>
</body>
</html>
