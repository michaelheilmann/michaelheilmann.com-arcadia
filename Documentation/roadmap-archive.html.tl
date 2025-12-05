  @{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/roadmap-archive.html'>
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
    <h1>Roadmap Archive</h1>
    @{include("./Roadmap/Archive/Milestone-Arbitrary_Precision_Arithmetic-2.i")}
    @{include("./Roadmap/Archive/Milestone-Arbitrary_Precision_Arithmetic-1.i")}
    @{include("./Roadmap/Archive/Milestone-MIL-1.i")}
    @{include("./Roadmap/Archive/Milestone-Banner_Generator-2.i")}
    @{include("./Roadmap/Archive/Milestone-Banner_Generator-1.i")}
    @{include("./Roadmap/Archive/Milestone-Icon_Generator-2.i")}
    @{include("./Roadmap/Archive/Milestone-Icon_Generator-1.i")}
    @{include("./Roadmap/Archive/Milestone-Template_Engine-2.i")}
    @{include("./Roadmap/Archive/Milestone-Template_Engine-1.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring1-3.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring1-2.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring1-1.i")}
    @{include("./Roadmap/Archive/Milestone-Website-6.i")}
    @{include("./Roadmap/Archive/Milestone-Website-5.i")}
    @{include("./Roadmap/Archive/Milestone-Website-4.i")}
    @{include("./Roadmap/Archive/Milestone-Website-3.i")}
    @{include("./Roadmap/Archive/Milestone-Website-2.i")}
    @{include("./Roadmap/Archive/Milestone-Website-1.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring2-4.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring2-3.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring2-2.i")}
    @{include("./Roadmap/Archive/Milestone-Arcadia.Ring2-1.i")}
  </div>
  <div class="right-column"></div>
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
