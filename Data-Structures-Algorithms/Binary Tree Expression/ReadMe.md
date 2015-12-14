<center>
<h1>Project 4: Binary Tree and Its Application</h1>
</center>

<center><h2>Due: 11/09/2015</h2></center>

<P>
<strong>Educational Objectives:</strong>
Experience with binary tree and its application in converting postfix
expressions into infix expressions, experience in developing recursive
algorithms.
</P>

<p>
<strong>Statement of Work:</strong>

Implement a binary expression tree and use the tree to convert postfix
expressions into infix expressions
</p>


<h2>Project Requirements:</h2>

<p>In this project, you are asked to develop a binary expression tree
and use the tree to convert postfix expressions into infix expressions. 
In this project, a postfix expression may contain 4 types of operators:
multiplication (*), division (/), plus (+), and minus (-). We assume
that multiplication and division have the same precedence, and plus and
minus have the same precedence. Moreover, multiplication and division
have higher precedence than plus and minus. All operators are left 
associative.</p>


<p><strong>Binary Expression Tree:</strong>. 

Name your binary expression tree class as "BET". Your BET must have a
nested structure named "BinaryNode" to contain the node related
information (including, e.g., element and pointers to children
nodes). In addition, BET must at least support the following interfaces. 

<ul><p>Public interfaces</p>
<li> <b>BET()</b>: default zero-parameter constructor.
<li> <b>BET(const string postfix)</b>: one-parameter constructor, where
parameter "postfix" is string containing a postfix expression. The tree
should be built based on the postfix expression. Tokens in the postfix
expression are separated by space.
<li><b>BET(const BET&)</b>: copy constructor.
<li><b>~BET()</b>: destructor.
<li><b>bool buildFromPostfix(const string postfix)</b>: parameter
"postfix" is string containing a postfix expression. The tree should be
built based on the postfix expression. Tokens in the postfix expression
are separated by space. If the tree contains nodes before the function
is called,  you need to first delete the existing nodes. Return true if
the new tree is built successfully. Return false if an error is encountered.
<li><b>const BET & operator= (const BET &)</b>: assignment operator.
<li><b>void printInfixExpression()</b>: call the private version of the
printInfixExpression function to print out the infix expression. 
				<li><strong>void printPostfixExpression()</strong>: call the 
				private version of the printPostfixExpression function to print 
				out the postfix expression.<li><strong>size_t size()</strong>: 
				call the&nbsp; private version of the size function to return 
				the number of nodes in the tree.<li><strong>size_t leaf_nodes()</strong>: 
				call the private version of the leaf_nodes function to return 
				the number of leaf nodes in the tree.<li><b>bool empty()</b>: return true if the tree is empty. Return false otherwise.
</ul>

<ul><p>Private interfaces <b>(all the required private member functions must be implemented recursively)</b>:</p>
<li><b>void printInfixExpression(BinaryNode *n)</b>: print to the
standard output the corresponding infix expression. Note that you may
need to add parentheses depending on the precedence of operators. You
should not have unnecessary parentheses.
<li><b>void makeEmpty(BinaryNode* &t)</b>: delete all nodes in the subtree pointed to by t. Called by functions such as the destructor.
<li><b>BinaryNode * clone(BinaryNode *t) const</b>: clone all nodes in
the subtree pointed to by t. Called by functions such as the assignment
operator=. 
				<li><strong>void printPostfixExpression(BinaryNode *n):</strong> 
				print to the standard output the corresponding postfix 
				expression.<li><strong>size_t size(BinaryNode *t)</strong>: 
				return the number of nodes in the subtree pointed to by t.<li>
				<strong>size_t leaf_nodes(BinaryNode *t)</strong>: return the 
				number of leaf nodes in the subtree pointed to by t.</ul>

<p><strong>Conversion to Infix Expression:</strong>. 

To convert a postfix expression into an infix expression using binary
expression tree involves two steps. First, you need to build a binary expression
tree from the postfix expression. Second, you need to print the nodes of the
binary expression tree using inorder traversal of the tree. </p>

<p>The basic operation of building a binary expression tree from a postfix
expression is similar to that of evaluating postfix expression. They all involve
the use of stack to hold intermediate results. Essentially, when you encounter
an operand, you create a node to contain the operand and push it into a stack. When you
encounter an operator, you pop out the corresponding operands from
the stack, and build a new tree, and then push the new tree into the stack.
After you have processed all tokens in the postfix expression, the stack has the
binary expression tree. Please refer to Section 4.2.2 for building binary
expression from postfix expression.</p>

<p>Note that during the conversion from postfix to infix expression, parentheses
may need to be added to ensure that the infix expression has the same value (and the same evaluation order) as
the corresponding postfix expression. You cannot add unnecessary
parentheses. Tokens in an infix expression should also be separated by a space. The following are a few examples of postfix expressions and
the corresponding infix expressions.</p> 

<table border="1" width="100%">
  <tr>
    <td width="50%">postfix expression</td>
    <td width="50%">infix expression</td>
  </tr>
  <tr>
    <td width="50%">4 50 6 + +</td>
    <td width="50%">4 + ( 50 + 6 )</td>
  </tr>
  <tr>
    <td width="50%">4 50 + 6 +</td>
    <td width="50%">4 + 50 + 6</td>
  </tr>
  <tr>
    <td width="50%">4 50 + 6 2 * +</td>
    <td width="50%">4 + 50 + 6 * 2</td>
  </tr>
  <tr>
    <td width="50%">4 50 6 + + 2 *</td>
    <td width="50%">( 4 + ( 50 + 6 ) ) * 2</td>
  </tr>
<tr>
	<td width="50%">a b + c d e + * *</td>
	<td width="50%">( a + b ) * ( c * ( d + e ) )</td>
</tr>
</table>
&nbsp;

<p><strong>Other Requirements</strong>:</p>
<ul>
	<li>Analyze the worst-case time complexity of the private member function
	<strong>makeEmpty(BinaryNode* &amp; t)</strong> of the binary expression tree. 
	Give the complexity in the form of Big-O. Your analysis can be informal; 
	however, it must be clearly understandable by others. Name the file 
	containing the complexity analysis as &quot;analysis.txt&quot;. </li>
	<li>You can use any C++/STL containers and algorithms</li>
	<li>If you need to use any containers, you must use the ones provided in 
	C++/STL. You cannot use the ones you developed in the previous projects.</li>
	<li><font face="Arial">Your program MUST 
	re-prompt the user for the next infix expression. Your program must be able 
	to process several inputs before terminating.</font></li>
	<li>
	<p class="style8">Your program MUST check invalid postfix expressions and 
	report errors. We consider the following types of postfix expressions as 
	invalid expressions: 1) an operator does not have the corresponding 
	operands, 2) an operand does not have the corresponding operator. Note that 
	an expression containing only a single operand is a valid expression (for 
	example, &quot;6&quot;). In all other cases, an operand needs to have an operator.&nbsp;</p>
	</li>
</ul>
<p>A driver program to test the BET implementation is provided to you. It accepts input from terminal,
or the input is redirected from a file that contains the postfix
expressions to be converted. Each line in the file (or typed by user)
represents a postfix expression. We assume that the tokens in a postfix
expression are separated by space.</p> 

<p><strong>Provided Code</strong>

<p> 
The
<a href="proj4_provided.tar">tar</a> file contains the following files:
<ol>
<li>proj4_driver.cpp: the driver program.
<li>proj4.x: executable code (compiled on linprog.cs.fsu.edu)
</ol>

<p><strong>Deliverable Requirements</strong> 

<p>Turn in the tar file containing all c++ source files and header files that you 
may develop for this project, the makefile, , and the analysis.txt via the blackboard
system. 
