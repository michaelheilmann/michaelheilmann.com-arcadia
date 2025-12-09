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
  --base-color: rgb(219, 212, 205);
  --background-color: color-mix(in srgb, var(--base-color) 20%, white 100%);
  --border-color: color-mix(in srgb, var(--base-color) 100%, white 20%);

  padding-bottom: 8px;
  padding-top: 8px;
  padding-left: 8px;
  padding-right: 8px;

  margin-top: 1rem;
  margin-bottom: 1rem;

  border-width: 1.75px;
  border-style: solid;
  border-radius: 4px;

  border-color: var(--border-color);
  background-color: var(--background-color);
}

div.box.todo {
  --todo-base-color: rgb(234, 136, 145);
  --todo-background-color: color-mix(in srgb, var(--todo-base-color) 20%, white 100%);
  --todo-border-color: color-mix(in srgb, var(--todo-base-color) 100%, white 20%);

  padding-bottom: 8px;
  padding-top: 8px;
  padding-left: 8px;
  padding-right: 8px;

  margin-top: 1rem;
  margin-bottom: 1rem;

  border-width: 1.75px;
  border-style: solid;
  border-radius: 4px;

  border-color: var(--todo-border-color);
  background-color: var(--todo-background-color);
}

div.box > div.header
{/*Intentionally empty.*/}

div.box > div.body
{/*Intentionally empty.*/}

div.box code {
  /*background-color: rgb(215, 210, 203);*/
}
