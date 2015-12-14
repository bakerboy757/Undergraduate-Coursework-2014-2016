<h2 align="center"><font face="Arial">Project 3:&nbsp; <b>Stack and Its
Applications</b></font></h2>

<h3 align="center"><b><font face="Arial">Due: 10/16/2015</font></b></h3>
<hr>
<p align="left"><font face="Arial"><b>Educational Objectives:</b>&nbsp;
Understand the stack ADT and its applications. Understand infix to postfix
conversion and postfix expression evaluation.</font></p>
<p align="left"><font face="Arial"><b>Statement of Work:</b> Implement a generic
stack container as an adaptor class template. Implement a program that converts infix expression to postfix
expression and implement a program that evaluates postfix expression using the
stack container you develop.</font></p>
<p align="left"><b><font face="Arial">Project Description:&nbsp;</font> </b></p>
<p style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">A
<b>Stack</b> is a type of data container/ data structure that implements the
LAST-IN-FIRST-OUT (LIFO) strategy for inserting and recovering data. This is a
very useful strategy, related to many types of natural programming tasks as we 
have discussed in class. 
</span></font></p>
<p style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">Remember
that in the generic programming paradigm, every data structure is supposed to
provide <i>encapsulation</i> of the data collection, enabling the programmer to
interact with the entire data structure in a meaningful way as a <b>container of
data</b>. By freeing the programmer from having to know its implementation
details and only exporting the interface of its efficient operations, a
generic <b>Stack</b> provides separation of data access/manipulation from
internal data representation. Programs that access the generic <b>Stack</b> only
through the interface can be re-used with any other <b>Stack</b> implementation.
This results in modular programs with clear functionality and that are more
manageable.</span></font><span style="font-size: 11pt; font-family: Helvetica;">
&nbsp;
<o:p>
</o:p>
</span></p>
<p class="MsoNormal"><b><u><font face="Arial">Goals:&nbsp;
<o:p>
</o:p>
</font></u></b></p>
<ol style="margin-top: 0in;" start="1" type="1">
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Implement
    a generic Stack<o:p>
    as an adaptor class template</o:p></font></span></li>
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Write
    a program that parses infix arithmetic expressions to postfix arithmetic
    expressions using a Stack<o:p>
    </o:p>
    </font></span></li>
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Write
    a program that evaluates postfix arithmetic expressions using a Stack</font></span></li>
</ol>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">More
detailed descriptions for each of the above tasks are now provided. 
&nbsp;
<o:p>
</o:p>
</font></span></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><b><u><span style="font-size: 11pt">
Task1: Implement </span></u></b><span style="font-size: 11pt"><b><u>Stack 
adaptor class template:</u></b>
&nbsp;
<o:p>
</o:p>
</span></font></p>
<ul style="margin-top: 0in;" type="disc">
  <li class="MsoNormal" style="text-align: justify;"><b><font face="Arial">
	<span style="font-size: 11pt">Stack</span></font></b><font face="Arial"><span style="font-size: 11pt">
    MUST store elements internally using a proper C++ STL container (of course, 
	you cannot use the C++ STL stack container).</span></font></li>
  <li class="MsoNormal" style="text-align: justify;"><font face="Arial">
	<span style="font-size: 11pt">Your<b> Stack</b> implementation MUST:<o:p>
    </o:p>
    </span></font></li>
  <ul style="margin-top: 0in;" type="circle">
    <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">be
      able to store elements of an arbitrary type. <o:p>
      </o:p>
      </font></span></li>
    <li class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">Every
      <b>Stack</b> instance MUST accept
      insertions as long as the system has enough free memory. 
      </span></font></li>
  </ul>
  <li class="MsoNormal" style="text-align: justify;"><font face="Arial"><b>
	<span style="font-size: 11pt">Stack</span></b><span style="font-size: 11pt">
    MUST implement the full interface specified below<o:p>
    </o:p>
    </span></font></li>
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">You
    MUST provide the template and the
    implementation in two different files stack.h and stack.hpp, respectively. 
	You must include stack.hpp into stack.h</font></span></li>
	<li class="style2" style="text-align: justify;">Your stack implementation 
	MUST be in the namespace cop4530.</li>
</ul>
<p class="MsoNormal" style="text-align: justify;"><b><u><font face="Arial">Interface:
&nbsp;</font><span style="font-family: Helvetica;">
<o:p>
</o:p>
</span></u></b></p>
<blockquote>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">The
interface of the<b> Stack</b> class template is specified below.</span></font><span style="font-size: 11pt; font-family: Helvetica;">
<o:p>
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><b>
<span style="font-size: 11pt">Stack</span></b><span style="font-size: 11pt"><b>()</b>: 
zero-argument constructor. &nbsp;&nbsp;</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>~Stack
()</b>: destructor.</span>&nbsp;&nbsp;</font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><b>
<span style="font-size: 11pt">Stack</span></b><span style="font-size: 11pt">
<b>
(const Stack&lt;T&gt;&amp;)</b>: copy constructor.</span><span style="font-size: 11pt">&nbsp;&nbsp;&nbsp;</span></font></p>
<p class="style8"><strong>Stack(Stack&lt;T&gt; &amp;&amp;)</strong>: move constructor.</p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial">
<span style="font-size: 11pt"><b>Stack&lt;T&gt;&amp;
operator= (const Stack &lt;T&gt;&amp;)</b>: copy assignment operator=</span>.</font></p>
<p class="style9"><strong>Stack&lt;T&gt; &amp; operator=(Stack&lt;T&gt; &amp;&amp;)</strong>: move 
assignment operator=</p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>bool
empty() const</b>: returns true if the <b> Stack</b> contains no elements, and false
otherwise.
&nbsp;
<o:p>
</o:p>
</span></font></p>
<p class="style5">void clear(): <span class="style6">delete all elements from 
the stack.</span></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial">
<span style="font-size: 11pt"><b>void
push(const T&amp; x)</b>: adds &nbsp;x&nbsp; to the <b>Stack</b>.
&nbsp;
<o:p>
copy version.</o:p></span></font></p>
<p class="style2" style="text-align: justify;">
<o:p>
<strong>void push(T &amp;&amp; x)</strong>: adds x to the Stack. move version.</o:p></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>void
pop()</b>: removes and discards the most recently added element of the <b>Stack</b>.
&nbsp;
<o:p>
</o:p>
</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>T&amp;
top()</b>: mutator that returns a reference to the most recently added element of
the <b>Stack</b>.
&nbsp;
<o:p>
</o:p>
</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>const
T&amp; top() const</b>: accessor that returns the most recently added element of the
<b>Stack</b>.
&nbsp;
<o:p>
</o:p>
</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>int
size() const</b>: returns the number of elements stored in the <b>Stack</b>.
</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>void
print(std::ostream&amp; os, char ofc = ' ') const</b>: print elements of Stack to ostream os. ofc is the separator between elements in the stack when they are printed out. 
<b>Note that print() prints elements in the opposite
order of the Stack (that is, the oldest element should be printed first).</b></span></font></p>
</blockquote>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial">
<span style="font-size: 11pt">The
following non-member global functions should also be supported.</span></font></p>
<blockquote>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>std::ostream&amp;
operator&lt;&lt; (std::ostream&amp; os, const Stack&lt;T&gt;&amp; a)</b>:
invokes the <b> print()</b> method to print the <b> Stack&lt;T&gt;</b><strong> a</strong> in the specified ostream</span></font><span style="font-size: 11pt; font-family: Helvetica;">
&nbsp;
<o:p>
&nbsp;
</span></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>bool
operator== (const Stack&lt;T&gt;&amp;, const Stack &lt;T&gt;&amp;)</b>: returns 
true if the two compared <b>Stack</b>s have the same elements, in
the same order. 
&nbsp;
<o:p>
</o:p>
</span></font></p>
<p class="MsoNormal" style="text-align: justify;">
<o:p>
</o:p>
<font face="Arial"><span style="font-size: 11pt"><b>bool
operator!= (const Stack&lt;T&gt;&amp;, const Stack &lt;T&gt;&amp;)</b>: opposite 
of operator==().</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt"><b>bool
operator&lt;= (const Stack&lt;T&gt;&amp; a, const Stack
&lt;T&gt;&amp; b)</b>: returns true if every element in <b>Stack</b> <b>a</b>
is smaller than
or equal to the corresponding element of<b> Statck b</b>, i.e., if repeatedly invoking top() and pop()
on both <strong>a</strong> and <strong>b, </strong>&nbsp;we will generate a sequence of elements a_i from a
and b_i from b, and for every i,&nbsp; a_i &le; b_i, until <strong>a</strong> is empty.
&nbsp;
<o:p>
&nbsp;
</span></font></p>
</blockquote>
<p class="style7" style="text-align: justify; width: 1113px;">Analyzing the worst-case 
run-time complexity of the member function clear() of Stack. Give the complexity 
in the form of Big-O. Your analysis can be informal; however, it must be clearly 
understandable by others.&nbsp; Note that the time complexity of the function 
clear() depends on the underlying adaptee class you use for the implementation of 
Stack. Name the file containing the complexity analysis as &quot;analysis.txt&quot;, in 
which, you should state the time complexity of clear() in the Big-O notation, 
your discussions on why it is so, in particular, you need to include the 
information on the underlying adaptee class you used in the implementation of 
the Stack.</p>
<p class="MsoNormal" style="text-align: justify;"><b><u>
<span style="font-size: 11pt"><font face="Arial">Task2:
Convert infix arithmetic expressions into postfix arithmetic expressions and
evaluate them (whenever possible)</font></span></u></b><span style="font-size: 11pt"><font face="Arial">
&nbsp;
<o:p>
</o:p>
</font></span></p>
<blockquote>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">For
the sake of this exercise, an arithmetic expression is a sequence of <b>space-separated</b>
strings. Each string can represent an operand, an operator, or parentheses. 
 &nbsp;
<o:p>
</o:p>
 </span></font></p>
<p class="style8">Operands: can be either a numerical value or a variable. A 
variable name only consists of alphanumerical letters and the underscore letter 
&quot;_&quot;. A variable name starts with a English letter. Numerical operands can be 
either integer or floating point values. </p>
<p class="style7" style="text-align: justify;"><font face="Arial">
<span style="font-size: 11pt">Examples
of operands: &quot;34&quot;, &quot;5&quot;, &quot;5.3&quot;, &quot;a&quot;, &quot;ab&quot;, &quot;b1&quot;, 
and &quot;a_1&quot;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span></font></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Operators:
one of the characters &quot;+&quot;, &quot;-&quot;, &quot;*&quot;, or
&quot;/&quot;. As usual, &quot;/&quot; and &quot;*&quot; are regarded as having
higher precedence than &quot;+&quot; or &quot;-&quot;. Note that all supported 
operators are binary, that is, they require two operands.
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Parentheses:
&quot;(&quot; or &quot;)&quot;
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">An
Infix arithmetic expression is the most common form of arithmetic expression
used.<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Examples:
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
( 5 + 3 ) * 12&nbsp; - 7&nbsp; is an infix
arithmetic expression that evaluates to 89<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
5 + 3 * 12 – 7 is an infix arithmetic expression that evaluates to 34
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">For
the sake of comparison, postfix arithmetic expressions (also known as reverse
Polish notation) equivalent to the above examples are:
&nbsp;
<o:p>
 </font>
</span><span style="font-size: 11pt; font-family: Helvetica;">
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt; font-family: Helvetica;"><span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span>5 3 + 12 * 7 – <o:p>
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt; font-family: Helvetica;"><span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span>5 3 12 * + 7 – 
&nbsp;
<o:p>
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt; font-family: Helvetica;">Two
characteristics of the Postfix notation are (1) any operator, such as
&quot;+&quot; or &quot;/&quot; is applied to the two prior operand values, and
(2) it does not require the use of parenthesis.
&nbsp;
<o:p>
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">More
examples:<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
a + b1 * c + ( dd * e + f ) * G&nbsp; in Infix notation
becomes<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
a b1 c * +&nbsp; dd e * f + G * +&nbsp; in
Postfix notation
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">To
implement infix to postfix conversion with a stack, one parses the expression as
sequence of <b>space-separated</b> strings. When an operand is read in the input, it is immediately output.&nbsp; Operators (i.e., &quot;-&quot;, &quot;*&quot;) may have to be saved by
placement in an operator stack. We also stack left parentheses. Start with an
initially empty operator stack.
&nbsp;
<o:p>
 </font>
</span><span style="font-size: 11pt; font-family: Helvetica;">
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Follow
these 4 rules for processing operators/parentheses:
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<ol style="margin-top: 0in;" start="1" type="1">
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">If
    input symbol is &quot;(&quot;, push it into stack.</font></span></li>
</ol>
<ol style="margin-top: 0in;" start="2" type="1">
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">If
    input operator is &quot;+&quot;, &quot;-&quot;, &quot;*&quot;, or
    &quot;/&quot;, repeatedly print the top of the stack to the output and pop
    the stack until the stack is either (i) empty ; (ii) a &quot;(&quot; is at
    the top of the stack; or (iii) a lower-precedence operator is at the top of
    the stack. Then push the input operator into the stack.</font></span></li>
</ol>
<ol style="margin-top: 0in;" start="3" type="1">
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">If
    input operator is &quot;)&quot; and the last input processed was an
    operator, report an error. Otherwise, repeatedly print the top of the stack
    to the output and pop the stack until a &quot;(&quot; is at the top of the
    stack. Then pop the stack discarding the parenthesis. If the stack is
    emptied without a &quot;(&quot; being found, report error.</font></span></li>
</ol>
<ol style="margin-top: 0in;" start="4" type="1">
  <li class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">If
    end of input is reached and the last input processed was an operator or
    &quot;(&quot;, report an error. Otherwise print the top of the stack to the
    output and pop the stack until the stack is empty.&nbsp; If an
    &quot;(&quot; is found in the stack during this process, report error.</font></span></li>
</ol>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">For
more details on how the conversion works, look up the lecture notes and Section 3.6 of the textbook.</font><b><u><font face="Arial"></font></u></b></span><u><b><span style="font-size: 11pt; font-family: Helvetica;"></o:p>
</span></b>
</u></p>
</blockquote>
<p class="MsoNormal" style="text-align: justify;"><b><u><span style="font-size: 11pt"><font face="Arial">Evaluating
postfix arithmetic expressions
</font></span>
</u></b></p>
<blockquote>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">After
converting a given expression in infix notation to postfix notation, you will
evaluate the resulting arithmetic expression IF all the operands are numeric (int,
float, etc.) values. Otherwise, if the resulting postfix expression contains
characters, your output should be the same as the input (the postfix expression).
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Example
inputs:<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">5
3 + 12 * 7 – <o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">5
3 12 * + 7 –<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">3
5 * c – 10 /
&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Example
outputs:<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">89<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">34<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">3
5 * c – 10 /
&nbsp;
<o:p>
 </font>
</span><span style="font-size: 11pt; font-family: Helvetica;">
</o:p>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">To
achieve this, you will have an operand stack, initially empty. Assume that the
expression contains only numeric operands (no variable names). Operands are
pushed into the stack as they are ready from the input. When an operator is read
from the input, remove the two values on the top of the stack, apply the
operator to them, and push the result onto the stack. If an operator is read and
the stack has fewer than two elements in it, report an error.&nbsp; If
end of input is reached and the stack has more than one operand left in it,
report an error. If end of input is reached and the stack has exactly one
operand in it, print that as the final result, or 0 if the stack is empty.
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">For
more information on the evaluation of postfix notation arithmetic expressions,
look up the lecture notes and Section 3.6 of the textbook. 
<o:p>
</o:p>
</font>
</span></p>
</blockquote>
<p class="MsoNormal" style="text-align: justify;"><b><u><span style="font-size: 11pt"><font face="Arial">Summarizing
task 2</font></span></u></b><span style="font-size: 11pt"><font face="Arial">.
<o:p>
</o:p>
</font></span></p>
<blockquote>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">Your
program should expect as input from (possibly re-directed) stdin a series of
space-separated strings. If you read a1 (no space) this is the name of the
variable a1 and not &quot;a&quot; followed by &quot;1&quot;.&nbsp; Similarly,
if you read &quot;bb 12&quot;, this is a variable &quot;bb&quot; followed by the
number &quot;12&quot; and not &quot;b&quot; ,&quot;b&quot;, &quot;12&quot; or
&quot;bb&quot;, &quot;1&quot; ,&quot;2&quot;. The resulting
postfix expression should be printed to stdout.
<o:p>
</o:p>
 </span></font></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">Your
program should evaluate the computed postfix expressions that contain only
numeric operands, using the above algorithm, and print the results to stdout.</span></font><b><u><span style="font-family: Helvetica;"></o:p>
</span>
</u></b></p>
</blockquote>
<p class="MsoNormal" style="text-align: justify;"><b><u><font face="Arial">Restrictions
</font>
</u></b></p>
<blockquote>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt">
<font face="Arial">The infix to postfix conversion MUST be able to convert expressions containing
both numbers and variable names.&nbsp;
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;">Your<span style="font-size: 11pt"><font face="Arial"> program MUST be able to produce floating number evaluation (i.e., deal
with floats correctly).
<o:p>
</o:p>
</font>
</span></p>
<p class="MsoNormal" style="text-align: justify;"><font face="Arial">
<span style="font-size: 11pt">Your program MUST NOT attempt to evaluate postfix expressions containing
variable names. It should print the postfix-converted result to stdout
and MAY NOT throw an exception nor reach a runtime error in that
case. 
<o:p>
</o:p>
 </span></font></p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt">
<font face="Arial">Your program MUST check for mismatched parentheses (this 
should be taken care of if you infix to postifx expression conversion is 
performed properly.
<o:p>
</o:p>
</font>
</span></p>
<p class="style8">Your program MUST check invalid infix expressions and report 
errors. We consider the following types of infix expressions as invalid 
expressions: 1) an operator does not have the corresponding operands, 2) an 
operand does not have the corresponding operator; or ) mismatched parentheses. 
Note that some checks can be performed in the expression conversion or postfix 
evaluation.</p>
<p class="MsoNormal" style="text-align: justify;"><span style="font-size: 11pt">
<font face="Arial">Your program MUST re-prompt the user for the next infix 
expression. Your program must be able to process several inputs before 
terminating (check the provided executable in2post.x to see the behavior of the 
program).</font></span></p>
</blockquote>
<p style="text-align: justify;"><font face="Arial"><b><span style="font-size: 11pt">Deliverable
</span></b><span style="font-size: 11pt"><b>Requirements</b></span></font></p>
<blockquote>
  <p style="text-align: justify;"><span style="font-size: 11pt"><font face="Arial">Your
  implementation should be contained in three files, which MUST be named
  stack.h, stack.hpp and in2post.cpp. Submit your implementation in a tar file including the three files (stack.h, 
	stack.hpp, and in2post.cpp), the makefile you use, and the analysis.txt file 
	for time complexity of the clear() function of Stack.</font></span></p>

</blockquote>
<p style="text-align: justify;"><b><span style="font-size: 11pt"><font face="Arial">Sample
Executable Code</font></span></b></p>
<blockquote>
  <p style="text-align: justify;"><font face="Arial"><span style="font-size: 11pt">You
  can download the <a href="proj3_provided.tar">tar</a> file containing a sample 
	executable code of the project (compiled on linprog) and a test driver for 
	Stack. There files are included in the tar file:</span></font></p>
	<ol>
		<li>
		in2post.x: executable program of the project
		</li>
		<li>
		test_stack1.cpp: source code of the test driver
		</li>
		<li>
		test_stack1.x: executable code of the test driver
		</li>
		<li>
		test0.txt: example test cases for in2post.x</li>
	</ol>
</blockquote>
<p style="text-align: justify;"><strong>Note</strong></p>
<p style="text-align: justify;" class="style7">This is our first capstone 
assignment. Make sure you do well for this project in order to pass this class. 
As discussed at the beginning of this course, failing a capstone assignment 
automatically means a fail of the class.</p>
<p class="MsoNormal" style="text-align: justify">&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp; </p>
