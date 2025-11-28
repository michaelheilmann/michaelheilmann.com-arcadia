/* the left-hand side of a grammar rule */
my-lhs {
  display: block;
}

/* the right-hand side of a grammar rule */
my-rhs {
  display: block;
  margin-left: 1rem;
}

/* A box used to surround out of text contents e.g., theorems, lemmas, examples, etc. */
div.box {
  padding-bottom: 8px;
  padding-top: 8px;
  padding-left: 8px;
  padding-right: 8px;

  margin-top: 1rem;
  margin-bottom: 1rem;

  background-color: rgb(215, 210, 203);
}

div.box > div.header
{/*Intentionally empty.*/}

div.box > div.body
{/*Intentionally empty.*/}

div.box code {
  background-color: rgb(215, 210, 203);
}
