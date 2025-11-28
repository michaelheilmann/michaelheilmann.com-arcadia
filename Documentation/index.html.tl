@{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='@{siteAddress}/assets/reset.css?v=1'>
  <link rel='stylesheet' href='@{siteAddress}/assets/index.css?v=1'>
  <link rel='canonical' href='@{siteAddress}/'>
  <title>Michael Heilmann's Arcadia</title>
  <style>
  div.topic {
    margin-left: 8px;
  }
  div.topic:first-child {
    margin-left: 0px;
  }
  div.topic > div.body > ul {
    list-style: none;
  }
  div.topic > div.body > ul > li {
    margin-left: 2rem;
    display: block;
    line-height: 1rem;
  }
  div.topic > div.body > ul > li > a {
    text-decoration: none;
    font-size: small;
  }
  div.topic > div.body > ul > li > div {
    display: inline;
    font-size: small;
  }

  footer > div > div {
    line-height: 1rem;
  }

  footer > div > div > a {
    text-decoration: none;
    font-size: small;
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
          <div class="body">
            <ul>
              <li>
                <a href='@{siteAddress}/Arcadia/ARMS'>Arcadia ARMS</a>
              </li>
              <li>
                <a href='@{siteAddress}/Arcadia/Ring1'>Arcadia Ring1</a>
              </li>
              <li>
                <a href='@{siteAddress}/Arcadia/Ring2'>Arcadia Ring2</a>
              </li>
              <li>
                <a href='@{siteAddress}/Arcadia/Visuals'>Arcadia Visuals</a>
              </li>
              <li>
                <a href='@{siteAddress}/Arcadia/TemplateEngine'>Arcadia Template Engine</a>
              </li>
            </ul>
          </div>
        </div>

        <div class="topic">
          <div class="header">
            <span>Specifications</span>
          </div>
          <div class="body">
            <ul>
              <li>
                <a href='@{siteAddress}/specifications/common-lexical-specification'>Common Lexical Specification</a>
              </li>
              <li>
                <a href='@{siteAddress}/specifications/data-definition-language'>Data Definition Language</a>
              </li>
              <li>
                <div>Data Definition Language Schema (coming soon)</div>
              </li>
            </ul>
          </div>
        </div>

        <div class="topic">
          <div class="header">
            <span>Organizational</span>
          </div>
          <div class="body">
            <ul>
              <li>
                <a href='@{siteAddress}/roadmap'>Roadmap</a>
              </li>
            </ul>
          </div>
        </div>

      </div>
    </div>

    <div></div>

    <div></div>
  </main>
  <footer>
    <div class="left-column">
    </div>
    <div class="center-column">
     </div>
    <div class="right-column" style="display: flex; flex-direction: column">
      <div><a href='mailto:contact@@michaelheilmann.com'>contact@@michaelheilmann.com</a></div>
      <div><a href="@{siteAddress}/imprint">Imprint</a></div>
      <div><a href="@{siteAddress}/data-protection-statement">Data Protection Statement</a></div>
    </div>
  </footer>
</body>
</html>
