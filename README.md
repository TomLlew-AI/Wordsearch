<h1>Wordsearch Puzzle</h1>
<h2>About</h2>
<p>This is a program written in C++ that aims to generate a wordsearch puzzle given words by the user</p>
<h2>How to run</h2>
<ol>
  <li>Download the repository as a zip file</li>
  <li>Locate the downloaded zip file, and unpack it. The zip file name is likely to be: "Wordsearch-master.zip", or something similar</li>
  <li>Now, open the terminal, and locate the folder using cd Downloads/Wordsearch-master/Generator if the folder is in the Downloads folder</li>
  <li>Then, compile the program using this command: g++ -std=c++11 main.cpp -o generator_exec</li>
  <li>An executable called generator_exec should be produced. Now run ./generator_exec WIDTH HEIGHT WORD1 WORD2
  <ul>
    <li>Replace WIDTH with the width of the wordsearch puzzles that takes a positive integer, e.g. 20</li>
    <li>Replace HEIGHT with the height of the wordsearch puzzles that takes a positive integer, e.g. 15</li>
    <li>Replace WORD1 and WORD2 with the words you want to include in your wordsearch puzzle. You may add more words if you wish</li>
    <li>Here is an example command that sets up a 5x7 wordsearch puzzle that includes the words Cat, Dog, and Rat</li>
    <ul>
      <li>./generator_exec 5 7 Cat Dog Rat</li>
    </ul>
    <li>Currently there is a bug where only the height and width must be the same. This will be fixed in the future.</li>
  </ul>
  
  </li>
</ol>
<p>If everything goes successfully, the wordsearch grid should be printed in the terminal, along with the list of words to be found.</p>
