@{include("./disclaimer.i")}

<h2>I Introduction</h2>

<p>
An information system is a system of actors with the goal of processing    information
, that is create, acquire, store, process, dispose, and disseminate information,  according to  the
information sytem's specification. Actors interact to adjust the system and process information.           
That specification defines the expected behavior of the information system including its  goals and
,most importantly, its constraints. We characterize information security as the discipline       of
protecting the information system from access, use, disruption, modification, or destruction by actors
in ways which are not allowed by its specification.
</p>

<p>This book's target audience are specific actors in an information system called information security actor, or SAs for short, which are tasked with three distinct activities:</p>
<ul>
  <li>observe the information system's specification (A1)</li>
  <li>observe the information system's behavior (A2)</li>
  <li>adjust the behavior of the information system to protect it from from access, use, disruption, modification, or destruction which are not allowed by its specification (A3)</li>
</ul>


<p>
For now, we assume SAs are considered as benign and try their best to follow the specificationin their actions.
Furthermore, we assume the specification is understood by them.
Given these assumptions, we want to operationalize the actions (A1), (A2), and (A3) in ways that a potential SA of an information system
might get an idea what to expect from his job. The further we operationalize, the further we inevitably specialize for a disctinct categories
of information systems. Chapter <a href="#">Chapter II Categories of Information Systems"</a> discusses various categories of information systems
before <a href="#">Chapter III "Observe, Enforce, Redefine"</a> discusses SAs in greater detail.</p>

<p>To operationalize, we can, however, add certain meta-requirements to the specification. One popular pick of requirements are
the requirements o f<em>confidentiality</em>, <em>integrity</em>, and <em>availability</em>:</p> 

<ul>
  <li><b>confidentiality</b>: the information system shall ensure confidentiality of information.
      That is, information is only disclosed to eligible entities</li>
  <li><b>integrity</b>: the information system shall ensurse integrity of information.
      That is, information is only modified by eligible entities</li>
  <li><b>availability</b>: the information system shall ensure availability of information.
      That is, information must be available to eligible entities</li>
</ul>

<p>The requirements <em>confidentiality</em>, <em>integrity</em>, and <em>availability</em> are frequently called the <em>CIA</em>-triad.</p>

<p>We can add more requirements. Another popular addition are the requirements of <em>authenticity</em>, <em>accountability</em>, <em>non-repudiation</em>, and <em>reliability</em>:</p>
<ul>
  <li><b>authenticity</b>: the information system shall ensure information as well as entities are genuine.</li>
  <li><b>accountability</b>: the information system shall ensure the ability to trace actions within the system to the entities responsible for them</li>
  <li><b>non-repudiation</b>: the information system shall ensure that an entity cannot credibly deny having performed and action within the system</li>
  <li><b>reliability</b>: the information system shall ensure its ability to consistently perform its intended functions correctly and dependably over time</li>
</ul>

<p>Some less popular ones are:</p>

<ul>
  <li>"The information system shall identify and mitigate information risks." which relies on the definition of information risk.</li>
  <li>"The information system shall reduce the adverse impact of incidents (from access, use, disruption, modification, or destruction in ways which are not allowed by its specification)".</li>
</ul>

<p>We observe that all these requirements are meta-requirements but they provide an idea on what information security is. As an SA entity, we need to materialize requirements of the
information system's specification in the information system's implementation. <p><a href="#">Chapter IV "Information security Requirements"</a> discusses various requirements of information
systems. This is then also the last chapter of the first book. Future books will deal with specific information systems, specific requirements, and specific security actors and their actions.</p>
