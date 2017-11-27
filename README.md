# B* or B+ Tree

This program provides a search execution benchmark of B* Tree.

The search benchmark consists of two parts:
<ul>
<li>
  The first one gets the number of comparisons, number of transfers from disk and execution time from the preprocessing           part, that's the period which the program is building the tree.
</li>

<li>
  The second one is based on the same criterias, but get them from the searching period in the tree.
</li>
</ul>

At the end of the execution a message is printed showing if the key was found or not and a message containing all the benchmark data.

This project also provides a function to generate your file to search a key in. It creates a binary file with determined number of inputs (aka registers) using the struct: 

```
typedef struct{
	int key;
	long dado1;
	char dado2[TAM_CHAR_REGISTRO];
} Register;
```

The inputs are sorted by "key" value and you can define ascending, descending or random order. The key value is the main value, the others are not used in this project. More informations below:

## How to execute?

To compile:

`make`

Compiling the program generates a executable file called b+tree.
To run there's some allowed options:

<ol>
  <li> If you want to generate an input file, you can use the -g, -n, -o and -P tags.
  <ul>
    <li> -g number - where "number" is the quantity of registers. The -g tag is not optional if you want to create an instance.        Will be generated keys starting at 0 to "number" </li>
    <li> -n name - where "name" is the name of your file instance. This argument is optional and the standart is "arquivo.bin"       </li>
    <li> -o order - where "order" is the order that you want to create your file. Is an optional tag and the standart is ascending. You can use "a" for ascending, "d" for descending and "r" for random order.
    </li>
    <li> -P - this tag is used if you want to print the generated values.
    </li>
  </ul>
  </li>
  <li> To starts a search:
    <ul>
    <li> -p number - where "number" is the key you want to search </li>
    </ul>
    </li>
    <li> Only emphasizing that you can run all this commands in the same execution. </li>
</ol>

## Usage Example

 - To generate an input file called "file.bin" with 100000 lines in descending order

`./b+tree -g 100000 -o d -n file.bin`

 - Using the file created above to perform a search on it. In this case we are searching for key 50000.

`./b+tree -p 50000`

