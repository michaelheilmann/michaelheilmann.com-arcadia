@{include("./Commons/header-common.i")}
  <link rel='stylesheet' href='https://michaelheilmann.com/assets/reset.css'>
  <link rel='stylesheet' href='https://michaelheilmann.com/assets/index.css'>
  <link rel='canonical' href='https://michaelheilmann.com/' />
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
    body.my-index-page-1 div.topic div.body > a:first-child()
    {/*Intentionally empty.*/}
  </style>
</head>
<body class="my-index-page-1">
<!-- flex-direction: row ~ from left to right -->
  <header style='flex-grow: 0; display: flex; flex-direction: row;'>
    <div style='flex-grow:0; display: flex; flex-direction: column; padding-left: 2rem; padding-top: 2rem;'>
      <div>michael heilmann</div>
    <div>information system architect</div>
    </div>
      <div style='flex-grow:1;'></div>
    <div style='flex-grow:0;'></div>
  </header>
  <main style='flex-grow: 1; display: flex; flex-direction: row;'>
    <div style='flex-grow:0; padding-left: 2rem; padding-bottom: 2rem;'>
      <div style='display: flex; flex-direction: row'>
        <div class="topic">
          <div class="header">
            <span>Projects</span>
          </div>
          <div class="body" style="display: flex; flex-direction: row;">
            <a href = 'https://michaelheilmann.com/repository/Arms1'>ARMS</a>
            <a href = 'https://michaelheilmann.com/repository/R1'>R</a>
            <a href = 'https://michaelheilmann.com/roadmap'>Roadmap</a>
          </div>
        </div>
      </div>
    </div>

    <div style='flex-grow:1;'></div>

    <div style='flex-grow:0; padding-right: 2rem; padding-bottom: 2rem;'>
    </div>
  </main>
  <!-- flex-direction: row ~ from left to right -->
  <footer style='flex-grow: 0; display: flex; flex-direction: row;'>
    <div style='flex-grow:0; padding-left: 2rem; padding-bottom: 2rem;'>
      <div style='display: flex; flex-direction: row'>

      </div>
    </div>

    <div style='flex-grow:1;'></div>

    <div style='flex-grow:0; padding-right: 2rem; padding-bottom: 2rem;'><a style='font-size: small; text-decoration: none;' href='mailto:contact@@michaelheilmann.com'>contact@@michaelheilmann.com</a></div>
  </footer>
</body>
</html>
