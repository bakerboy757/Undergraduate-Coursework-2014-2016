<h4 class="style1">Project 2: Doubly-Linked List Container</h4>
<p class="style1">Due 10/02/2015</p>
<p class="style2"><strong>Educational Objectives</strong>: Understanding generic 
programming and information hiding by developing generic containers. Getting 
familiar with the concept of class template and its usage. Use of nested (iterator) 
classes. Use of namespace. Operator overloading.&nbsp; </p>
<p class="style2"><strong>Statement of Work</strong>: Implement a doubly-linked 
list class template List and its associated iterators</p>
<p class="style2"><strong>Requirements</strong>:</p>
<ol>
	<li>
	<p class="style2">A header file List.h is provided, which contains the 
	interfaces of the doubly-linked list class template List. In particular, it 
	contains a nested Node structure, and two nested iterators class (iterator 
	and const_iterator). You cannot change anything in the List.h file.</p>
	</li>
	<li>
	<p class="style2">A driver program test_list.cpp has been included. It is 
	used to test your implementation of the doubly-linked list class template 
	for different data types (it tests List&lt;int&gt; and List&lt;string&gt;. Similarly, 
	you cannot change anything in the test_list.cpp file.</p>
	</li>
	<li>
	<p class="style2">You need to implement the member functions of the doubly-linked list 
	class template List in a file named List.hpp. Note that, List.hpp has been 
	included in the header file List.h (towards the end of the file). As we have 
	discussed in class, you should not try to compile List.hpp (or List.h). 
	You need to implement all the member functions of List&lt;T&gt;, List&lt;T&gt;::iterator, 
	and List&lt;T&gt;::const_iterator, and non-class global overloaded functions 
	operator==(), operator!=(), and operator&lt;&lt;() included in List.h. The design of the List container follows the one 
	presented in the textbook. It has three member variables, theSize, head, and 
	tail. theSize records the number of elements in the list. The head and tail 
	pointers point to the sentinel nodes. They represent the beginning and end 
	markers. They do not store any real elements in the list. It is OK for you to use the code provided in the 
	textbook. We describe the requirements of each function in the following (we 
	may not write the function signatures in detail, please refer to the List.h 
	file for the detailed function declaration).</p>
	</li>
</ol>
<p class="style2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Member functions of nested const_iterator class:</p>
<ul class="style3">
	<li>
	<p class="style2">const_iterator(): default zero-parameter constructor. Set 
	pointer current to NULL (nullptr for c++ 2011).</p>
	</li>
	<li>
	<p class="style2">operator*(): returns a reference to the corresponding 
	element in the list by calling retrieve() member function.</p>
	</li>
	<li>
	<p class="style2">operator++(), operator++(int), operator--(), operator--(int): 
	prefix and postfix increment and decrement operators.</p>
	</li>
	<li>
	<p class="style2">operator==() and operator!=(): two iterators are equal if 
	they refer to the same element.</p>
	</li>
	<li>
	<p class="style2">retrieve(): return a reference to the corresponding 
	element in the list.</p>
	</li>
	<li>
	<p class="style2">const_iterator(Node *p): one-parameter constructor. Set 
	pointer current to the given node pointer p.</p>
	</li>
</ul>
<p class="style2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Member functions of nested iterator class:</p>
<ul class="style3">
	<li>
	<p class="style2">iterator(): default zero-parameter constructor.</p>
	</li>
	<li>
	<p class="style2">operator*(): returns a reference to the corresponding 
	element in the list by calling retrieve() member function.</p>
	</li>
	<li>
	<p class="style2">operator++(), operator++(int), operator--(), operator--(int): 
	prefix and postfix increment and decrement operators.</p>
	</li>
	<li>
	<p class="style2">const_iterator(Node *p): one-parameter constructor. </p>
	</li>
</ul>
<p class="style2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
Member functions of List class template&nbsp;</p>
<ul class="style3">
	<li>
	<p class="style2">List(): Default zero-parameter
	constructor. Call init() to initialize list member variables.</p>
	</li>
	<li>
	<p class="style2">List(const List &rhs): Copy constructor. Create the new 
	list using elements in existing list rhs.</p>
	</li>
	<li>
	<p class="style2">List(List &amp;&amp;rhs): move constructor.</p>
	</li>
	<li>
	<p class="style2">List(int num, const T &amp; val = T()): Construct 
		a list with num elements, all initialized with value val.</p>
	</li>
	<li>
	<p class="style2">List(const_iterator start, const_iterator 
		end): construct a List with elements from another list between start and 
		end. Including the element referred to by the start iterator, but not 
	the end iterator, that is 
		[start, end).</p>
	</li>
	<li>
	<p class="style2">~List(): destructor. You should properly reclaim memory 
		(used by head and tail nodes).</p>
	</li>
	<li>
	<p class="style2">operator==(List &amp;rhs): copy assignment operator</p>
	</li>
	<li>
	<p class="style2">operator==(List &amp;&amp;rhs): move assignment operator</p>
	</li>
	<li>
	<p class="style2">size(): return the number of elements in the
	List. </p>
	</li>
	<li>
	<p class="style2">empty(): return true if no element is in the
	list; otherwise, return false.</p>
	</li>
	<li>
	<p class="style2">clear(): delete all the elements in the list</p>
	</li>
	<li>
	<p class="style2">reverse(): reverse the order of the elements
	in the list. That is, the original first element becomes the
	last, while the original last becomes the first. </p>
	</li>
	<li>
	<p class="style2">front() and back(): return reference to the
	first and last element in the list, respectively. </p>
	</li>
	<li>
	<p class="style2">push_front() and push_back(), insert the new object as the 
	first and last element into the list, respectively; and their move versions. </p>
	</li>
	<li>
	<p class="style2">pop_front() and pop_back(), delete the first
	and last element in the list, respectively. </p> 
	</li>
	<li>
	<p class="style2">remove(const T &amp; val): delete all nodes with 
		value equal to val from the list.</p>
	</li>
	<li>
	<p class="style2">print(ostream &amp;os, char ofc = &#39; &#39;): print all 
		elements in the list, using character ofc as the deliminator between 
	elements in the list.</p>
	</li>
	<li>
	<p class="style2">begin(): return iterator to the first element
	in the list.</p>
	</li>
	<li>
	<p class="style2">end(): return iterator to the end marker of
	the list (tail).</p>
	</li>
	<li>
	<p class="style2">insert(iterator itr, const T &amp; val): insert 
		value val ahead of the node referred to by itr; and its move version</p>
	</li>
	<li>
	<p class="style2">erase(iterator itr): delete node referred to 
		by itr. The return value is an iterator to the following node.</p>
	</li>
	<li>
	<p class="style2">erase(iterator start, iterator end): delete 
		all nodes between start and end (including start but not end), that is, 
		all elements in the range [start, end).</p>
	</li>
	<li>
	<p class="style2">init(): initialize the member variables of
	list. </p>
	</li>
</ul>
<p class="style2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 
Non-class global functions&nbsp;</p>
<ul class="style3">
	<li>
	<p class="style2">operator==(const List&lt;T&gt; &amp; lhs, 
		const List&lt;T&gt; &amp; rhs): check if two lists contain the same sequence of 
		elements. Two lists are equal if they have the same number of elements 
		and the elements at the corresponding position are equal.</p>
	</li>
	<li>
	<p class="style2">operator!=(const List&lt;T&gt; &amp; lhs, 
		const List&lt;T&gt; &amp; rhs): opposite of operator==().</p>
	</li>
	<li>
	<p class="style2">operator&lt;&lt;(ostream &amp; os, const 
		List&lt;T&gt; &amp; l): print out all elements in list l by calling 
		List&lt;T&gt;::print() function.&nbsp; </p>
	</li>
</ul>

<ol>
	<li value="4">
	<p class="style2">Write a makefile for your project and name your executable 
	as proj2.x. Your program must be able to compile and run on the linprog 
	machines.</p>
	</li>
	<li>
	<p class="style2">Analyze the worst-case run-time complexity of the member 
	function reverse() of the List. Give the complexity in the form of Big-O. 
	Your analysis can be informal; however, it must be clearly understandable by 
	others. Name the file containing the complexity analysis as &quot;analysis.txt&quot;. </p>
	</li>
</ol>
<p class="style2"><strong>Downloads</strong></p>
<p class="style4">Click <a href="proj2_provided.tar">here</a> to download the tar file, which contains the 
following files: List.h, test_list.cpp, and proj2.x. The sample executable 
program proj2.x was compiled on a linprog machine. test_list.cpp is the source 
code for compiling proj2.x (which will need the implementation of List).</p>
<p class="style2"><strong>Submission</strong></p>
<p class="style4">Turn in List.hpp, makefile, and analysis.txt in a tar file via the 
blackboard. Please do not include the List.h file. Note that you cannot change 
the List.h file, and we will not use your List.h even if you submit it.</p>
