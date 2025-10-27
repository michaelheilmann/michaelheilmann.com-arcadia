/* Fomatting for the cxx documentation. */

section.cxx.entity
{/*Intentionally empty.*/}




/* We adjust the heading sizes depending on where in the document we reside. */
h1 ~ section.cxx.entity {
  --h1-font-size: var(--h2-font-size);
  --h2-font-size: var(--h3-font-size);
}

h2 ~ section.cxx.entity {
  --h1-font-size: var(--h3-font-size);
  --h2-font-size: var(--h4-font-size);
}

h3 ~ section.cxx.entity {
  --h1-font-size: var(--h4-font-size);
  --h2-font-size: var(--h5-font-size);
}

section.cxx.entity > h1 {
  font-size: var(--h1-font-size);
}

section.cxx.entity > h2 {
  font-size: var(--h2-font-size);
}

section.cxx.enumeration-elements > h1,
section.cxx.errors > h1,
section.cxx.parameters > h1,
section.cxx.remarks > h1,
section.cxx.return-value > h1,
section.cxx.success-condition > h1
{
  font-size: var(--h2-font-size);
}




/* Separate the entity by a margin and by a border. */
section.cxx.entity {
  border-top-width: 8px;
  border-top-color: lightgray;
  border-top-style: solid;
  margin-top: 4rem;
}



/* We do not display any content. */
section.cxx-entity > h1::before {
  content: '';
}

section.cxx-entity > h2::before {
  content: '';
}

/* display of remarks, parameter lists, error lists, and enumeration element lists. */
section.cxx.enumeration-elements > div
section.cxx.errors > div,
section.cxx.parameters > div,
section.cxx.remarks > div
{
  border-bottom-width: 2px;
  border-bottom-style: solid;
  border-bottom-color: lightgray;

  & div:nth-child(1) {
    margin-top: 1rem;
    margin-bottom: 1rem;
  }
  & div:nth-child(2) {
    margin-top: 1rem;
    margin-bottom: 1rem;
  }
}

/* 2nd child because the first child is the headline. */
section.cxx.enumeration-elements > div:nth-child(2)
section.cxx.errors > div:nth-child(2),
section.cxx.parameters > div:nth-child(2),
section.cxx.remarks > div:nth-child(2)
{
  border-top-width: 2px;
  border-top-style: solid;
  border-top-color: lightgray;
}

/* Style the tables. */
section.cxx table {
  border-collapse: collapse;
}

section.cxx table tr td {
  padding-top: 0.25rem;
  padding-bottom: 0.25rem;
  padding-left: 0.75rem;
  padding-right: 0.75rem;
}

section.cxx table tr td {
  border-style: solid;
  border-width: 1.25px;
  border-color: lightgray;
}

section.cxx table + p {
  margin-top: 1rem;
}
