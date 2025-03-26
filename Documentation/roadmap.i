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
    <div class="left-column"></div>
    <div class="center-column">
    <h1>Roadmap</h1>
    @{include("./Roadmap/Milestone-Template_Engine-2.i")}
    @{include("./Roadmap/Milestone-Arcadia.Ring1-3.i")}
    @{include("./Roadmap/Milestone-Arcadia.Ring1-2.i")}
    @{include("./Roadmap/Milestone-Arcadia.Ring1-1.i")}
    @{include("./Roadmap/Milestone-Arcadia.Ring2-2.i")}
    @{include("./Roadmap/Milestone-Arcadia.Ring2-1.i")}
    @{include("./Roadmap/Milestone-Mil-2.i")}
    @{include("./Roadmap/Milestone-Cicd-1.i")}
    @{include("./Roadmap/Milestone-Website-9.i")}
    @{include("./Roadmap/Milestone-Website-8.i")}
    @{include("./Roadmap/Milestone-Website-7.i")}
    <h2>Archive of completed milestones</h2>
    <p>You can review completed milestones in the <a href="https://michaelheilmann.com/roadmap-archive">roadmap archive</a>.</p>
  </div>
  <div class="right-column"></div>
  </main>
  <footer>
    <div class="left-column"></div>
    <div class="center-column"></div>
    <div class="right-column"></div>
    <span style="font-style: italic">Webite maintained by Michael Heilmann. Last modified on 22 Feburary 2025.</span>
    </div>
  </footer>
</body>
</html>
