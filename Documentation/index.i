@{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=1'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=1'>
  <link rel='canonical' href='@{siteAddress}/'>
  <title>Michael Heilmann Contact Information</title>
  <style>
  div.topic {
    margin-left: 8px;
  }
  div.topic:first-child {
    margin-left: 0px;
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
            <span>Software</span>
          </div>
          <div class="body" style="display: flex; flex-direction: row;">
            <a href = '@{siteAddress}/repository/Arms1'>ARMS</a>
            <a href = '@{siteAddress}/repository/Arcadia.Ring1'>Arcadia Ring1</a>
            <a href = '@{siteAddress}/repository/Arcadia.Ring2'>Arcadia Ring2</a>
            <a href = '@{siteAddress}/repository/R1'>R1</a>
          </div>
        </div>
        
        <div class="topic">
          <div class="header">
            <span>Specifications</span>
          </div>
          <div class="body" style="display: flex; flex-direction: row;">
            <a href = '@{siteAddress}/specifications/common-lexical-specification'>Common Lexical Specification</a>
          </div>
          <div class="body" style="display: flex; flex-direction: row;">
            <a href = '@{siteAddress}/specifications/data-definition-language'>Data Definition Language</a>
          </div>
        </div>
        
        <div class="topic">
          <div class="header">
            <span>Organizational</span>
          </div>
          <div class="body" style="display: flex; flex-direction: row;">
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
