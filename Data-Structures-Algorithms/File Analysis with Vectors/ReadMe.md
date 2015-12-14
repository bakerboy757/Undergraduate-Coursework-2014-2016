<h4 class="style1">Project 1: Word, Number, and Character Usage Statistics</h4>

<p class="style1"><strong>Due on 09/18/2015 (</strong>100 Points)</p>

<hr />

<p class="style9"><strong>Educational Objectives: </strong>Refresh C/C++ 

programming skills. Use C++ I/O streams, string class, and STL containers and 

algorithms. Use makefile to organize and compile programs. Use debugger to 

identify and address 

programming problems.</p>

<p class="style9"><strong>Statement of Work:</strong> Implement a program that 

collects the statistics of word, number, and character usage in a file (redirected as 

the standard input).&nbsp; </p>

<p class="style9"><strong>Requirements:</strong></p>

<ol>

	<li>

	<p class="style2"><span class="style7">Create a subdirectory called </span> <tt>

	<span class="style7">proj1</span></tt><span class="style7">.&nbsp;</span></p>

	</li>

	<li>

	<p class="style2"><span class="style7">For this project you need to create at least two files:

	</span>

	<tt><span class="style7">proj1.cpp</span></tt><span class="style7">, and 

	</span> <tt><span class="style7">makefile</span></tt><span class="style7">. Both files should be placed in 

	the </span> <tt><span class="style7">proj1</span></tt><span class="style7"> directory. 

	</span> </p>

	</li>

	<li>

	<p class="style2"><span class="style7">The file </span> <tt>

	<span class="style7">proj1.cpp</span></tt><span class="style7"> should contain the main 

	function, </span> <tt><span class="style7">int main()</span></tt><span class="style7">. In the main() function, the program should 

	read the input until it reaches the end, counting the number of times each 

	word, number, and character is used. A word is defined as a sequence of 

	letters (&#39;a&#39;..&#39;z&#39; or &#39;A&#39;..&#39;Z&#39;). Words are case insensitive (&quot;AA&quot;, &quot;Aa&quot;, &quot;aA&quot;, 

	and &quot;aa&quot; are the same). A number is defined as a sequence of digits 

	(&#39;0&#39;..&#39;9&#39;). Note that both words and numbers can be of length of 1, that is, 

	contain one letter or one digit, respectively. Different sequences represent 

	different numbers. For example, number &quot;001&quot; is different from number &quot;1&quot;. 

	Words are separated by numbers or other non-letter and non-digit characters. 

	Numbers are separated by words or other non-letter and non-digit characters. 

	Your program should record the number of times each word, number, and 

	character happens. The program should then output the ten most used 

	characters, the ten most used numbers, and the ten most used words as well 

	as the number of times these characters/numbers/words are used. Since words 

	are case insensitive, the program only outputs lower case words. The 

	characters, numbers and words should be outputted in the descending order 

	based on the number of times they are used. When two characters happen in 

	the same number of times, the character with a smaller ASCII value should be 

	considered as being used more frequently. When two words (numbers) happen in 

	the same number of times, the word (number) that occurs earlier in the input 

	should be considered as being used more frequently.&nbsp; </span> </p>

	</li>

	<li>

	<p class="style9">An example executable code of the program is provided to 

	you. You should make the outputs of your program the same as those of 

	&#39;proj1.x&#39;. When printing characters, use &#39;\t&#39; for tab and &#39;\n&#39; for newline. 

	All other characters should be outputted normally. </p>

	</li>

	<li>

	<p class="style2"><span class="style7">Write a </span> <tt>

	<span class="style7">makefile</span></tt><span class="style7"> for your project that compiles 

	an executable called </span> <tt><span class="style7">proj1.x</span></tt></p>

	</li>

	<li>

	<p class="style9">You are encouraged to use any C++ STL containers and 

	algorithms. You should also use C++ string class instead of the built-in 

	string type. </p>

	</li>

	<li>

	<p class="style9">Your program must be able to compile and run on linprog.</p>

	</li>

</ol>

<p class="style9"><strong>Example executable code</strong></p>

<blockquote>

	<p class="style7">Click <a href="proj1_provided.tar">here</a> to download the example 

	executable code and 4 test cases. The executable code was compiled on a 

	linprog machine.&nbsp;One bonus point is given to the first student who 

	identifies a problem in the example executable code (no known problems with 

	the provided code).</p>

	<p class="style7">You need to redirect one of the test case files as the standard input to 

	the executable code, for example: </p>

</blockquote>

<p class="style3"><tt><span class="style7">proj1.x &lt; test0</span></tt> 

<span class="style7"> 

<br />

</span>

</p>

<p class="MsoNormal"><b style="mso-bidi-font-weight:normal">

<span style="mso-ascii-theme-font: major-latin; mso-hansi-theme-font: major-latin" class="style7">

Submission</span></b><span style="mso-ascii-theme-font: major-latin; mso-hansi-theme-font: major-latin" class="style7">

</span></p>

<p class="style8" style="mso-ascii-theme-font: major-latin; mso-hansi-theme-font: major-latin">

Tar all the source codes, including proj1.cpp and the makefile into a single 

file and submit online via blackboard (don’t use dropbox; use the link following 

the assignment to submit). Make sure you tar your programs correctly. You are 

responsible for incorrect submissions (for example, empty tar file). You can 

untar the file <b style="mso-bidi-font-weight:normal">under a different 

directory</b> to make sure that you do include all the right source files. Same 

late policy applies if the submission is incorrect and you need to submit a new 

version.<o:p></o:p></p>

<p class="style3">

<o:p></o:p>

<span style="mso-ascii-theme-font: major-latin; mso-hansi-theme-font: major-latin" class="style7">

You should also be able to download your submission and verify if it is correct. 

If you cannot download the submission, contact the blackboard support team at 

FSU.<o:p></o:p></span><o:p></o:p></p>

<p class="style8">Note that in addition to the provided test cases, we will also 

test your program using additional test files. Your program must be able to pass 

all the test cases in order to obtain a full score for the corresponding 

components.</p>
