# B* or B+ Tree

This program provides a execution analysis of B* Tree. 

The analysis consists of two parts:
<ul> 
<li> 
  The first one gets the number of comparisons, number of transfers from disk and execution time from the preprocessing           part, that's the period which the program is building the B* tree. 
</li>

<li> 
  The second one is based on the same criterias, but get them from the searching period in the tree.
</li>
</ul>

At the end of the execution a message is printed showing if the register was found or not and a message containing all the analysis content.

## How to execute?

To compile:

`make`

To run there's some allowed options:

<ol>
  <li> If you want to generate an instance file, you can use the -g, -n, -o and -P tags.
  <ul>
    <li> -g number - where number is the quantity of registers. The -g tag is not optional if you want to create an instance.       </li>
    <li> -n name - where name is the name of your file instance. This argument is optional and the standart is "arquivo.bin"       </li>
    <li> -o order - where order is the order that you want to create your file. Is an optional tag and the standart is crescent. You can use "c" for crescent, "d" for decrescent and "a" for random.
    </li>
    <li> -P - this tag is used if you want to show the generated values.
    </li>
  </ul>
  </li>
  <li> To starts a search:
    <ul>
    <li> -p number - where number is the key you want to look for </li>
    </ul>
    </li>
    <li> Only emphasizing that you can run all this commands in the same execution. </li>
</ol>


