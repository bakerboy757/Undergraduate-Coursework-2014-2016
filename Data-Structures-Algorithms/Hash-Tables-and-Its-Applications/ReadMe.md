<body>

<h2 align="center" class="style8"><font face="Arial">Project 5:&nbsp; <b>Hash Tables and Its Applications</b></font></h2>

<h3 align="center" class="style8"><b><font face="Arial">Due: </font><span class="style2">
11/27/2015</span></b></h3>
<hr class="style8">
<p align="left" class="style8"><font face="Arial"><b>Educational Objectives:</b>&nbsp; </font><font face="Times New Roman">Understand
and get familiar with the data structure hash tables, and its applications in managing user accounts.</font></p>
<p align="left" class="style8"><font face="Arial"><b>Statement of Work:</b>  </font><font face="Times New Roman"> Implement a
hash table ADT and other supporting user interfaces;&nbsp; develop a simple 
password server program.</font></p>
<p align="left" class="style8"><b><font face="Arial">Project Description:</font> </b></p>
<blockquote class="style6">
  <p align="left" class="style1">This project contains two parts. In the first 
	part of the project, you need to implement a hash table class template named 
	HashTable. In the second part of the project, you will develop a simple 
	password server program using the hash table you developed.</p>
	<p align="left"><font face="Times New Roman"><b>Task 1: Requirements of HashTable
  Class Template</b></font></p>
	<ul>
					<li>Your implementation of HashTable 
				must be in the namespace of cop4530. </li>
					<li>You must provide the template declaration and implementation in two different files hashtable.h 
				(containing HashTable class template declaration) and 
				hashtable.hpp (containing the implementation of member 
				functions). You must include hashtable.hpp inside hashtable.h as 
				we have done in the previous projects. The two files hashtable.h and 
					hashtable.hpp will be provided to you, which contain some 
					helpful functions that you will need to use in developing 
					the hash table class template.</li>
					<li>You must implement hash table 
				using the technique of chaining with separate lists (separate 
				chaining). That is, the internal data structure of the hash table 
				class template should be a vector of lists. You must use the STL 
					containers for the internal data structure instead of any containers you developed in the previous projects.</li>
					<li>You must at least implement all the 
				interfaces specified below for the HashTable class template. </li>
				<li></li>
				</ul>

</blockquote>
<p align="left" class="style4"><strong>Public HashTable interfaces (K and V are the 
				template parameters, i.e., the generic data type, which 
represent the key and value types, respectively)</strong></p>
<blockquote class="style6">
				<ul>
								<li>
								
								<strong>HashTable(size_t size = 101)</strong>: 
								constructor. Create a hash table, where the size 
								of the vector is set to prime_below(size) (where 
								size is default&nbsp; to 101), where prime_below() is 
								a private member function of the HashTable and 
								provided to you.</li>
								<li>
								
								<strong>~HashTable()</strong>: destructor. 
								Delete all elements in hash table.</li>
								<li>
								
								<strong>bool contains(const K &amp; k)</strong>: 
								check if key k is in the hash table.</li>
								<li>
								
								<strong>bool match(const std::pair&lt;K, V&gt; &amp;kv) 
								const</strong>: check if key-value pair is in 
								the hash table.</li>
								<li>
								
								<strong>bool insert(const std::pair&lt;K, V&gt; &amp; 
								kv):</strong> add&nbsp; the key-value pair kv 
								into the hash table. Don't add if kv is already 
								in the hash table. If the key is the hash table 
								but with a different value, the value should be 
								updated to the new one with kv. Return true if 
								kv is inserted or the value is updated; 
								return false otherwise (i.e., if kv is in the 
								hash table).</li>
								<li>
								
								<strong>bool insert (std::pair&lt;K,&nbsp; V&gt; &amp;&amp; 
								kv)</strong>: move 
								version of insert.</li>
								<li>
								
								<strong>bool remove(const K &amp; k)</strong>: delete 
								the key k and the corresponding value if it is in the hash table. Return true if 
								k 
								is deleted, return false otherwise (i.e., if key 
								k is not in the hash table).</li>
								<li>
								
								<strong>void clear()</strong>: delete all elements in 
								the hash table</li>
								<li>
								
								<strong>bool load(const char *filename)</strong>: 
								load the content of the file with name filename 
								into the hash table. In the file, each line 
								contains a single pair of key and value, 
								separated by a white space. </li>
								<li>
								
								<strong>void dump()</strong>: display all 
								entries in the hash table. If an entry contains 
								multiple key-value pairs, separate them by a 
								semicolon character (:) (see the provided 
								executable for the exact output format).</li>
								<li>
								
								<strong>bool write_to_file(const char *filename)</strong>: 
								write all elements in the hash table into a file 
								with name filename. Similar to the file format 
								in the load function, each line contains a pair 
								of key-value pair, separated by a white space.</li>
				</ul>

</blockquote>
<p class="style5"><strong>Private HashTable interfaces</strong></p>
<blockquote class="style6">
	<ul>
					<li><strong>void makeEmpty()</strong>: delete all elements 
					in the hash table. The public interface clear() will call 
					this function.</li>
					<li><strong>void rehash()</strong>: Rehash function. Called 
					when the number of elements in the hash table is greater 
					than the size of the vector.</li>
					<li><strong>size_t myhash(const K &amp;k)</strong>: return the 
					index of the vector entry where k should be stored.</li>
					<li><strong>unsigned long prime_below (unsigned long)</strong> 
					and <strong>void setPrimes(vector&lt;unsigned long&gt;&amp;)</strong>: two helpful 
					functions to determine the proper prime numbers used in 
					setting up the vector size. Whenever you need to set hash 
					table to a new size &quot;sz&quot;, call prime_below(sz) to determine 
					the new proper underlying vector size. These two functions 
					have been provided in hashtable.h and hashtable.hpp.</li>
	</ul>
	<p>You need to write a simple test program to test various functions of hash 
	table. More details are provided in a later part of this description.</p>
  <p align="left"><font face="Times New Roman"><b>Task 2: Requirement of the 
	Password Server Class (PassServer)</b></font></p>
  <ul>
    <li>Name the password server class as 
		PassServer. Its declaration and implementation should be provided in two 
		files, passserver.h and passserver.cpp, respectively.</li>
	<li>PassServer should be implemented as an adaptor class, with the HashTable 
	you developed as the adaptee class. The type for both K and V in HashTable 
	should be string. The key and value will be the username and password, 
	respectively.</li>
	<li>PassServer must store
      username and <i>encrypted</i> password pairs in the hash table. </li>
    <li>
      PassServer must at least support the following member functions: <br>
		<br>
		<strong>Public interfaces:</strong><ol>
        <li>
          <strong>PassServer(size_t size = 101)</strong>: constructor, create a 
			hash table of the specified size. You just need to pass this size 
			parameter to the constructor of the HashTable. Therefore, the real 
			hash table size could be different from the parameter size (because 
			prime_below() will be called in the constructor of the HashTable).</li>
		<li>
          <strong>~PassServer()</strong>: destructor. You need to decide what 
			you should do based on your design of PassServer (how you develop 
			the adaptor class based on the adaptee HashTable). In essence, we do 
			not want to have memory leak.</li>
		<li>
          <strong>bool load(const char *filename)</strong>: load a password file into
          the HashTable object. Each line contains a pair of username and 
			encrypted password.</li>
        <li>
								
								<strong>bool addUser(std::pair&lt;string,&nbsp; 
			string&gt; &amp; kv): </strong>add a new username and password.&nbsp; 
			The password passed in is in plaintext, it should be encrypted 
			before insertion. </font></li>
		<li>
								
								<strong>bool addUser(std::pair&lt;string, string&gt; 
			&amp;&amp; kv): </strong>move version of addUser. </font></li>
        <li>
								
								<strong>bool removeUser(const string &amp; k)</strong>: 
			delete an existing user with username k.</font></li>
        <li>
        <strong>bool changePassword(const pair&lt;string, string&gt; &amp;p, const string 
		&amp; newpassword)</strong>: change an existing user's password. Note 
		that both passwords passed in are in plaintext. They should be encrypted 
		before you interact with the hash table. If the user is not in the hash 
		table, return false. If p.second does not match the current password, 
		return false. Also return false if the new password and the old password 
		are the same (i.e., we cannot update the password).</li>
        <li>
        <strong>bool find(const string &amp; user):</strong> check if a user exists 
		(if user is in the hash table). </li>
        <li>
          <strong>void dump()</strong>: show the structure and
          contents of the HashTable object to the screen. Same format as the 
			dump() function in the HashTable class template.</font></li>
        <li>
         <strong>size_t size():</strong> return the size of the HashTable (the number of username/password pairs in the table).</font></li>
        <li>
        <strong>bool write_to_file(const char *filename):</strong> save the username and
          password combination into a file. Same format as the write_to_file() 
		function in the HashTable class template.</font></li>
      </ol>
    </li>
  </ul>

</blockquote>
<p class="style7">Private interfaces:</p>
<ul class="style9">
				<li>
				<p class="style6"><strong>string encrypt(const string &amp; str)</strong>: 
				encrypt the parameter str and return the encrypted string.</p>
				</li>
</ul>
<blockquote class="style10">
				<p class="p5">For this
    project, we shall use the GNU C Library's <span class="s2"><b>crypt()</b></span>
    method to encrypt the password.&nbsp; The algorithm for the <span class="s2">crypt()</span>
    method shall be MD5-based.&nbsp; The <i>salt</i> shall be the character
    stream &quot;<span class="s2">$1$########</span>&quot;.&nbsp;&nbsp; The
    resulting encrypted character stream is the</p>
				<blockquote>
								<p class="p5"><font face="Courier New">&quot;<span class="s2">$1$########</span>&quot;
      + ‘$' + 22 characters = 34 characters in total.&nbsp;</font></p>
				</blockquote>
				<p class="p5">A user password is the sub string containing the last 22
    characters, located after the 3<span class="s4"><sup>rd</sup></span> ‘$'.&nbsp;</p>
				<p class="p5"><b>Note:</b> A sample program to demonstrate the use of the 
				<span class="s2"><b>crypt()</b></span>
    method is also provided. In order compile a program calling crypt(), you may 
	need to link with the crypt library. You can read more information on the 
	manual page of crypt().</p>
</blockquote>
<p class="style8">&nbsp;</p>
<p class="style6">In addition to developing the HashTable class tempalte and the PassServer 
class, you need to write a driver program to test your code. Name the driver 
program as proj5.cpp.</p>
<ul class="style7">
				<li>A partial implementation of proj5.cpp is provided to you, 
				which contains a Menu() function. You must use this function as 
				the standard option menu for user to type input.&nbsp; You may not alter the Menu function.</li>
				<li>The driver program must
      re-prompt the user for the next choice from the menu and exit the program
      only when the user selection the exit &quot;x&quot; option.</font></li>
				<li>
				<p align="left">&nbsp;</li>
</ul>
<p class="style8"><b>Extra-credit part I (10 points)</b>&nbsp;</p>
<p class="style8">You may submit an alternative version to your program named 
<span class="s2">sproj5.cpp</span>,
  in which the program hides the user's entries whenever the user keys in a
  password or new password.&nbsp;</p>
<ul class="style9">
				<li>
				<p class="p5">Do not use the getpass() function, which is 
					obsolete.</p>
				</li>
</ul>
<p class="style8"><b>Extra-credit part II (10 - 20 points)</b>&nbsp;</p>
<p class="style8">Develop a nice graphical user interface (GUI) for this project. Your GUI must support 
  at least the user interfaces supported by the plain-text version user manual in the provided code. 
  For this part, you can work on Windows or Mac (10 extra points). If you work 
	on linprog.cs.fsu.edu, you have additional 10 points (that is you will get 
	20 extra points) for GUI.</p>
<h2 style="text-align: justify; font-family: Arial; font-style: normal; font-variant: normal; font-weight: normal; font-size: 16px; line-height: normal; font-size-adjust: none; font-stretch: normal;" class="style11">
<b>Provided Partial Code</b></h2>
<blockquote class="style8">
  <p class="p12">The following <a href="proj5_provided.tar">partial
  code</a> has been provided to you.</p>
  <ol>
				<li>
				hashtable.h: partial implementation
				</li>
				<li>
				hashtable.hpp: partial implementation
				</li>
				<li>
				<span class="s5">proj5.cpp: driver program, partial 
	implementation.</span></li>
				<li>
				proj5.x : <span class="s3">sample
  executable for </span>linprog.cs.fsu.edu</li>
				<li>
				<span class="s2">sproj5.x:
  </span>sample executable with hidden password entries for <span class="s2">linprog.cs.fsu.edu</span></li>
				<li>
				<span class="s2">test1:</span>
  sample test case (which contains the commands that a user will type. You can 
	redirect it to proj5.x as &quot;proj5.x &lt; test1&quot;.</li>
				<li>
				<span class="s2">scrypt.cpp:</span>
  sample program to use crypt() to encrypt password.<b>&nbsp;</b></li>
				<li>
				<span class="s2">scrypt.x:</span>
  executable code of scrypt.cpp.</li>
	</ol>

</blockquote>
<h2 style="text-align: justify; font-family: Arial; font-style: normal; font-variant: normal; font-weight: normal; font-size: 16px; line-height: normal; font-size-adjust: none; font-stretch: normal;" class="style11"><b>Deliverables</b></h2>
<blockquote class="style8">
  <p class="p14">1.<span class="s5">&nbsp; </span>Your implementation must be
  entirely contained in the following files, which MUST be named in the same
  way.&nbsp;</p>
  <ol>
				<li>
				hashtable.h
				</li>
				<li>
			
				hashtable.hpp</li>
				<li>
			
				passserver.h</li>
				<li>
			
				passserver.cpp</li>
				<li>
			
				proj5.cpp</li>
				<li>
			
				sproj5.cpp (optional, for extra-credit part I)</li>
				<li>
			
				gpass.cpp (optional, extra-credit part II. For this part, you do 
				not need to follow the given name).</li>
				<li>
			
				makefile</li>
	</ol>
  <p class="p17">2. Submit all the files in a tar file via the blackboard system. If you have implemented the extra-points functions, please indicate so when you submit your homework. 
  Please also indicate if you implement the GUI on Windows, Mac, or linprog. If you implement the GUI on Windows or Mac, you need to set up a time with 
	the TA to demo your code.</p>
  <p class="p17">3.<span class="s5">&nbsp; For the non-GUI part, y</span>our program must compile on <span class="s2">linprog.cs.fsu.edu</span>.
  If you program does not compile on linprog, the grader cannot test your submission. Your
  executable(s) must be named proj5<span class="s2">.x</span> and <span class="s2">sproj5.x</span>
  (for extra-credit option).</p>
  <p class="p18">4.<span class="s5">&nbsp;&nbsp; </span>The interaction and
  output (including error messages) of your client's executable(s) must behave
  in the same manner as the distributed proj5.x and sproj5.x (on linprog.cs.fsu.edu)</span>.&nbsp;For
  example, one of the ways to test your program would be to run a
  &quot;diff&quot; command between the output file(s) created by your
  executable(s) and the output file(s) created by the distributed executable(s).&nbsp;</p>
  <p class="p17">5. Note that, your GUI must work completely, we will not 
  grade any partial implementation, for example, the code that cannot be compiled or cannot run. 
	No partial credits are given for this part.
  <p class="p20">Points will be deducted for not complying with these
  requirements.</p>
  <p class="MsoNormal" style="text-align: justify;">&nbsp;</p>
</blockquote>

</body>
