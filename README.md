# DS
<h1>Way Words Are Stored in TXT file.</h1>
<ul>
  <li>Words are stored as <b>WORD</b> followed by its <b>MEANING</b>.</li>
  <li>Begining of a <b>WORD</b> is denoted by a <b>'&'</b> symbol.</li>
  <li>Begining of the <b>MEANING</b> is denoted by <b>':'</b> (same as end of <b>WORD</b>).</li>
  <li>End of <b>MEANING</b> is denoted by <b>'%'</b>.</li>
</ul>
<hr>
<h1>WORKING</h1>
<hr>
<h2>READING AND CREATING BST</h2>
<ul>
  <li>Reads <b>WORD</b>S (and its <b>MEANING</b>) from the "dictionary.txt" file<br>And stores them in a Binary Search Tree.</li>
  <li>Storing is done using the strcmp function.</li>
  <li>Compare <b>WORD</b> of node (if node exists) and the <b>WORD</b> from the TXT file.</li>
  <li>If function [<b>WORD</b> of node > <b>WORD</b> from TXT file] returns positive integer, move/add to the left ndoe.</li>
  <li>Else If function returns negative integer, move/add to the right node.</li>
  <li>Else Duplicate node exists // display already exists</li>
</ul>
<hr>
<h2>ADDING NEW <b>WORD</b></h2>
<ul>
  <li>Creates Node , reads word from user , validates (see function add() )</li>
  <li>Traverse the BST using strcmp function</li>
  <li>If function [<b>WORD</b> of node > <b>WORD</b> user input] returns positive integer, move/add to the left ndoe.</li>
  <li>If function returns negative integer, move/add to the right node.</li>
  <li>Else Duplicate node exists // display already exists and display the <b>MEANING</b>.</li>
</ul>
<hr>
<h2>SEARCHING</h2>
<hr>
<ul>
  <li>Takes the <b>WORD</b> to be searched as an arguement</li>
  <li>Traverse the BST using strcmp function.</li>
  <li>If function [<b>WORD</b> of node > <b>WORD</b> user input] returns positive integer, move to the left ndoe.</li>
  <li>If function returns negative integer, move to the right node.</li>
  <li>Else Node reached // display the <b>MEANING</b>.</li>
</ul>
<hr>
<h2>UPDATING DESCRIPTION</h2>
<hr>
<ul>
  <li>Traverse throught the BST using <b>WORD</b> (same as SEARCH)</li>
  <li>If match found update the description (user input)</li>
</ul>
<hr>
<h2>SAVE AND EXIT</h2>
<hr>
<ul>
  <li>Traverse through BST using DFS (Preorder). </li>
  <li>Write each <b>WORD</b> and its <b>MEANING</b> to the TXT file</li>
  <li>PROCEDURE<ul>
    <li>First add '&' char followed by <b>WORD</b> followed by ':' followed by <b>MEANING</b> followed by '%' to the TXT file.</li>
    </ul></li>
  <li>NOTE : FILE IS OVERWRITTEN EVERYTIME U HIT "SAVE AND EXIT".</li>
</ul>
