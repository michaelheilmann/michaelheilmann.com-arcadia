@{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css'>
  <link rel='canonical' href='@{siteAddress}/'>
  <title>Michael Heilmann Contact Information</title>
  <style>
    body.my-index-page-1 div.topic div.header {
      display: inline;
      font-size: small;
      text-decoration: none
    }
    body.my-index-page-1 div.topic div.body {
      display: inline;
    }
    body.my-index-page-1 div.topic div.body > a {
      font-size: small;
      text-decoration: none;
      margin-left: 2rem;
    }
    body.my-index-page-1 header {
      flex-grow: 0;
      display: flex;
      flex-direction: row;
    }
    body.my-index-page-1 main {
      flex-grow: 1;
      display: flex;
      flex-direction: row;
    }
    body.my-index-page-1 footer {
      flex-grow: 0;
      display: flex;
      flex-direction: row;
    }
    body.my-index-page-1 header > div:first-child {
      flex-grow:0;
      display: flex;
      flex-direction: column;
      padding-left: 2rem;
      padding-top: 2rem;
    }
    body.my-index-page-1 header > div:nth-child(2) {
      flex-grow: 1;
    }
    body.my-index-page-1 header > div:last-child {
      flex-grow:0;
      padding-right: 2rem;
      padding-bottom: 2rem;
    }


    body.my-index-page-1 main > div:first-child {
      flex-grow:0;
      padding-left: 2rem;
      padding-bottom: 2rem;
    }
    body.my-index-page-1 main > div:nth-child(2) {
      flex-grow: 1;
    }
    body.my-index-page-1 main > div:last-child {
      flex-grow:0;
      padding-right: 2rem;
      padding-bottom: 2rem;
    }


    body.my-index-page-1 footer > div:first-child {
      flex-grow:0;
      padding-left: 2rem;
      padding-bottom: 2rem;
    }
    body.my-index-page-1 footer > div:nth-child(2) {
      flex-grow: 1;
    }
    body.my-index-page-1 footer > div:last-child {
      flex-grow:0;
      padding-right: 2rem;
      padding-bottom: 2rem;
    }
  </style>
</head>
<body class="my-index-page-1">
  <header>
    <div>
      <div>michael heilmann</div>
      <div>information system architect</div>
    </div>
    <div></div>
    <div></div>
  </header>
  <main>
    <div>
      <div style='display: flex; flex-direction: row'>
        <div class="topic">
          <div class="header">
            <span>Projects</span>
          </div>
          <div class="body" style="display: flex; flex-direction: row;">
            <a href = '@{siteAddress}/repository/Arms1'>ARMS</a>
            <a href = '@{siteAddress}/repository/Arcadia.Ring1'>Arcadia Ring1</a>
            <a href = '@{siteAddress}/repository/R1'>R</a>
            <a href = '@{siteAddress}/roadmap'>Roadmap</a>
          </div>
        </div>
      </div>
    </div>

    <div></div>

    <div></div>
  </main>
  <footer>
    <div></div>
    <div></div>
    <div><a style='font-size: small; text-decoration: none;' href='mailto:contact@@michaelheilmann.com'>contact@@michaelheilmann.com</a></div>
  </footer>
</body>
</html>
