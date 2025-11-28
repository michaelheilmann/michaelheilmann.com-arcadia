  @{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=3'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=3'>
  <link rel='canonical' href='@{siteAddress}/news.html'>
  <title>Data Protection Statement<</title>
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
    <h1>Data Protection Statement</h1>
    <p>
    With the following Privacy Policy, I would like to inform you about the types of your personal data (hereinafter also referred to simply as "data") that I process, for what purposes,
    and to what extent. This Privacy Policy applies to all processing of personal data carried out by me, both in the context of providing my services and in particular on our websites,
    in mobile applications, and within external online presences, such as our social media profiles (hereinafter collectively referred to as the "online offering”).
    </p>
    @{include("./DataProtectionStatement/Controller.i")}
    @{include("./DataProtectionStatement/OverviewOfProcessingActivities.i")}
    @{include("./DataProtectionStatement/RelevantLegalBases.i")}
    @{include("./DataProtectionStatement/RightsOfDataSubjects.i")}
    @{include("./DataProtectionStatement/DefinitionsOfTerms.i")}
  </div>
  <div class="right-column"></div>
  </main>
  <footer>
    <div class="left-column"></div>
    <div class="center-column">

    </div>
    <div class="right-column">
      <div>Website maintained by @{siteAuthor}.</div>
      <div>Last modified on @{dayOfMonth()} @{monthName()} @{year()}.</div>
    </div>
  </footer>
</body>
</html>
