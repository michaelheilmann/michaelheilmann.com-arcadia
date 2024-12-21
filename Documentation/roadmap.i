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
    @{include("./Roadmap/Milestone-Banner_Generator-2.i")}
    @{include("./Roadmap/Milestone-Icon_Generator-2.i")}
    @{include("./Roadmap/Milestone-Arbitrary_Precision_Arithmetic-2.i")}
    @{include("./Roadmap/Milestone-Arbitrary_Precision_Arithmetic-1.i")}
    @{include("./Roadmap/Milestone-Template_Engine-2.i")}
    @{include("./Roadmap/Milestone-Website-5.i")}
    @{include("./Roadmap/Milestone-Runtime-2.i")}
    @{include("./Roadmap/Milestone-Runtime-1.i")}
    @{include("./Roadmap/Milestone-Mil-2.i")}
    <h2>Archive of completed milestones</h2>
    <p>You can review completed milestones in the <a href="https://michaelheilmann.com/roadmap-archive">roadmap archive</a>.</p>
  </main>
  <footer>
    <span style="font-style: italic">Webite maintained by Michael Heilmann. Last modified on 26 December 2024.</span>
  </footer>
</body>
</html>
