  <h2>2. How a ARMS1 works</h2>
  <p>
  ARMS1 allows for the creation of objects and maintains a set of these created objects called the <em>universe</em> \(U\).
  When an object \(x\) is created, a type \(a\) is associated with that object.
  That type \(a\) provides means to ARMS1 to determine the objects reachable from that object \(x\) and to properly destroy the object \(x\).
  To determine which objects are to be retained and are to be destroyed, ARMS1 starts from a subset of the universe called the <em>root set</em> \(R \subseteq U\) and visits all objects transitively reachable from \(R\).
  The reachable objects are called <em>live objects</em> \(L \subseteq U\).
  All other objects are called <em>dead objects</em> \(D\). \(L\) and \(D\) are disjoint and partition the universe in such that \(U = L \cup D\)
  (also note that \(R \subseteq L\) and \(R \cap D = \emptyset\)).
  ARMS1 removes all dead objects \(D\) from the universe \(U\) such that \(U@@new = U@@old - D\) and destroys them.
  </p>
