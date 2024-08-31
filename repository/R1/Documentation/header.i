<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Michael Heilmann's Runtime Mark 1</title>
    <link rel="canonical" href="https://michaelheilmann.com/repository/r1/" />
    <link rel="icon" type="image/x-icon" href="https://michaelheilmann.com/assets/favicon/512x512.svg">
    <link rel="mask-icon" href="https://michaelheilmann.com/assets/favicon/safari-mask-icon-512x512.svg" color="#000000"> <!-- Safari crap. Single color with transparent background. -->
    <link rel="apple-touch-icon" href="https://michaelheilmann.com/assets/favicon/apple-touch-icon-180x180.png" > <!-- iOS crap. 180 * 180px. color attribute is obsolete. -->
    <style>
    body {
      margin: 16px;
    }

    /* variable */
    my-v {
      display: inline;
      font-family: monospace;
    }

    /* meta variable */
    my-mv {
      display: inline;
      font-family: monospace;
    }
    my-mv::before {
      content: "<";
    }
    my-mv::after {
      content: ">";
    }

    /* meta variable */
    .meta {
      font-family: monospace;
    }
    .meta::before {
      content: "<";
    }
    .meta::after {
      content: ">";
    }
    </style>
    <script id="MathJax-script" async src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js"></script>
  </head>
  <body>
  <h1>Michael Heilmann's Runtime Mark 1</h1>
  <p>
  This is the documentation for Michael  Heilmann's Runtime Mark 1,
  henceforth R1. R1 facilates the creation of C programs - in particular interpreters - that are portable,
  maintainable, as well as safe. R1 is available at <a href="https://michaelheilmann.com/repository/r1">michaelheilmann.com/repository/r1</a>.
