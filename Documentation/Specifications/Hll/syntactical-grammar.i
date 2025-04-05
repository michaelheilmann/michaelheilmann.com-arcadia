<h2>Syntactical Grammar</h2>

<h3>Expression-level syntax</h3>

<p><code style="font-family:monospace">
<my-lhs>expression:</my-lhs><my-rhs>unaryLogicalExpression</my-rhs>
<my-lhs>unaryLogicalExpression:</my-lhs><my-rhs>notOperator* logicalExpression</my-rhs>
<my-lhs>logicalExpression:</my-lhs><my-rhs>orExpression</my-rhs>
<my-lhs>orExpression:</my-lhs><my-rhs>andExpression (orOperator andExpression)*</my-rhs>
<my-lhs>andExpression:</my-lhs><my-rhs>equalityExpression (andOperator equalityExpression)?</my-rhs>
<my-lhs>equalityExpression:</my-lhs><my-rhs>relationalExpression (equalityOperator relationalExpression)?</my-rhs>
<my-lhs>relationalExpression:</my-lhs><my-rhs>additiveExpression (relationalOperator additiveExpression)?</my-rhs>
<my-lhs>additiveExpression:</my-lhs><my-rhs>multiplicativeExpression (additiveOperator multiplicativeExpression)*</my-rhs>
<my-lhs>multiplicativeExpression:</my-lhs><my-rhs>unaryAdditiveExpression (multiplicativeOperator unaryAdditiveEpxression)*</my-rhs>
<my-lhs>unaryAdditiveExpression:</my-lhs><my-rhs>unaryAdditiveEpxression* (exponentiationExpression)*</my-rhs>
<my-lhs>exponentiationExpression:</my-lhs><my-rhs>callExpression (exponentiationOperator exponentiationExpression)*</my-rhs>
<my-lhs>callExpression:</my-lhs><my-rhs>accessExpression argumentList?</my-rhs>
<my-lhs>primaryExpression:</my-lhs><my-rhs>literal<br/>
                                    <b>name</b></br>
                                    <b>leftParenthesis</b> expression <b>rightParenthesis</b></my-rhs>
<my-lhs>argumentList:</my-lhs><my-rhs><b>leftParenthesis</b> expressionList? <b>rightParenthesis</b></my-rhs>
<my-lhs>expressionList:</my-lhs><my-rhs>expression (<b>comma</b> expression)</my-rhs>
</code></p>

<h3>Package-level syntax</h3>
<p><code style="font-family:monospace">
<my-lhs>packageDeclaration:</my-lhs><my-rhs><b>package</b> name packageBodyDeclaration</my-rhs><br/>

<my-lhs>typeDeclaration:</my-lhs><my-rhs>classDeclaration<br/>
                                         enumerationDeclaration<br/>
                                         interfaceDeclaration</my-rhs><br/>

<my-lhs>classDeclaration</my-lhs>
  <my-rhs>
  <b>class</b> name (<b>extends</b> type)? (<b>implements</b> typeList)? classBodyDeclaration
  </my-rhs><br/>

<my-lhs>enumerationDeclaration</my-lhs>
  <my-rhs>
  <b>enumeration</b> name enumerationBodyDeclaration
  </my-rhs><br/>

<my-lhs>interfaceDeclaration</my-lhs>
  <my-rhs>
  <b>interface</b> name (<b>extends</b> typeList)?
  interfaceBodyDeclaration
  </my-rhs><br/>


<my-lhs>packageBodyDeclaration</my-lhs>
  <my-rhs>
  <b>is</b> packageBodyElementDeclaration* <b>end</b>
  </my-rhs><br/>

<my-lhs>classBodyDeclaration</my-lhs>
  <my-rhs>
  <b>is</b> classBodyElementDeclaration* <b>end</b>
  </my-rhs><br/>

<my-lhs>enumerationBodyDeclaration</my-lhs>
  <my-rhs>
  <b>is</b> enumerationBodyElementDeclaration* <b>end</b>
  </my-rhs><br/>

<my-lhs>interfaceBodyDeclaration</my-lhs>
  <my-rhs>
  <b>is</b> interfaceBodyElementDeclaration* <b>end</b>
  </my-rhs><br/>

<my-lhs>packageBodyElementDeclaration</my-lhs>
  <my-rhs>
  classDeclaration<br/>
  enumerationDeclaration<br/>
  interfaceBodyDeclaration
  </my-rhs><br/>

<my-lhs>classBodyElementDeclaration</my-lhs>
  <my-rhs>
  attributeDeclaration<br/>
  methodDeclaration<br/>
  constructorDeclaration<br/>
  destructorDeclaration<br/>
  </my-rhs><br/>

<my-lhs>enumerationBodyElementDeclaration</my-lhs>
  <my-rhs>
  enumerationElementDeclaration*
  </my-rhs><br/>

<my-lhs>interfaceBodyElementDeclaration</my-lhs>
  <my-rhs>
  methodDeclaration
  </my-rhs><br/>
                
             
<my-lhs>typeList</my-lhs>
  <my-rhs>
  type (<b>comma</b> type)*
  </my-rhs>
<my-lhs>type</my-lhs>
  <my-rhs>
  qualifiedName
  </my-rhs>       
                                                                            
</code></p>

<h3>Class-, enumeration-, and interface-level syntax</h3>

<p><code style="font-family:monospace">
<my-lhs>constructorDeclaration:</my-lhs><my-rhs><b>constructor</b> parameterList callableBody</my-rhs><br/>
<my-lhs>destructorDeclaration:</my-lhs><my-rhs><b>destructor</b> parameterList callableBody</my-rhs><br/>

<my-lhs>methodDeclaration:</my-lhs><my-rhs><b>method</b> methodModifiers name parameterList type callableBody</my-rhs><br/>

<my-lhs>parameterList:</my-lhs><my-rhs><b>leftParenthesis</b>(parameter (<b>comma</b> parameter)*)?<b>rightParenthesis</b></my-rhs><br/> 
<my-lhs>parameter:</my-lhs><my-rhs>name type</my-rhs>
<my-lhs>callableBody:</my-lhs><my-rhs><b>is</b> statementList <b>end</b></my-rhs>                                                                           
</code></p>

<h3>Statement-level syntax</h3>

<p><code style="font-family:monospace">
<my-lhs>statementList:</my-lhs><my-rhs>statement*</my-rhs><br/>
<my-lhs>statement:</my-lhs><my-rhs>expressions</my-rhs><br/>                                                                       
</code></p>
