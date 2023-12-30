# Abaporu Lang
![Abaporu Original Painting](https://upload.wikimedia.org/wikipedia/pt/thumb/b/bd/Abaporu.jpg/253px-Abaporu.jpg)

## Overview
Abaporu lang is an esoteric programing language developed by me as a fun project to do during the new year's holliday. The name of the esolang comes from a famous brazilian painting named **Abaporu** made by Tarlisa do Amaral. You can see more about it [here](https://en.wikipedia.org/wiki/Abaporu).

The way this esolang works is similar in functionality to [Brainfuck](about:blank) and the programing style is based in [Piet](https://esolangs.org/wiki/Piet), where you use colors to represent instructions.

## Instaling
To use the language by your own, you can clone this repository in your computer with NodeJs installed and run:
`node index.js -p <your-input-file.abapl> -o <path-you-want-to-output-canva>`

**Note**: the output functionality is not yet implemented, but it is mandatory to run the program.

## Basic usage
As previously said, you use colors to determine the instructions your program should follow. I say should because as this documentation is written, I'd spent less then 5 hours into the Abaporu's interpreter.

### List of implemented instructions


| Name     | Function                                                                   | Hex     |
|----------|----------------------------------------------------------------------------|---------|
| addOne   | Add one to the current cell of the list                                    | #FF0000 |
| subOne   | Subtract one to the current cell of the list                               | #0000FF |
| nextcell | Move the pointer to the next cell of the list                              | #00FF00 |
| prevCell | Move the pointer to the previous cell of the list                          | #FFF800 |
| put      | Puts the value of the current cell in the `stdout` using ASCII table       | #FFFFFF |
| putVal   | Puts the value of the current cell in the `stdout` as it is                | #555555 |
| endBlock | End a previously declared block. More on blocks in one of the next topics. | #FFA500 |
### Comentaries
As it is impossible to keep track of all the things instructions do while developing in Abaporu Lang, I implement comments in the `.abapl`.</br>
#### Single line comment
```
* This is a single line comment in Abaporu Language
#FFFFFF
```

#### Comment Block
```
| Comment blocks  are great to
express
complex
things
during 
your
code |
```

Both `Single Line Comments` and `Comment Blocks` behave as comments in other languages like C and Java. So they do not interfeer in the run of you code.


### How to think during your development?
As I said, the way the interpreter works is similar to the ideia of Brainfuck. In the start of the process of interpreting your art, the runtime sausage (as I will call the array of values used by the interpreter) starts
with one element with value 0 (zero).</br>

So, lets imagine your running the file `./examples/SimpleHelloWorld.abapl`.</br>

1 - The program start to add one to the current cell (position 0 (zero) of the sausage) 72 times, because thats the charcode for the uppercase 'H' in the ASCII Table. </br>

2- The interpreter indentifies the instruction `put` represented by the color \<white>(#FFFFFF) and send it to the `stdout` of your terminal using the [fromCharCode](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/fromCharCode) function.

3 - The interpreter identifies the instruction `nextcell` represented by the color <svg width="20" height="20" xmlns="http://www.w3.org/2000/svg"><rect width="100%" height="100%" fill="#00FF00"/></svg>(#00FF00)<br/>
**Note**: everytime you do `nextCell`into a cell that does not already exist in the sausage, its value is iniciated with 0 (zero) 

And the process goes the same to every other letter of the phrase. </br>

After the interpreter reads all of the colors of your art, it will send `LF` to the `stdout` indicating the end of the process.

## "Advanced" usage

You may have noticed in the `SimpleHelloWorld.abapl` example that the letters `l` and `o` needed to be declared twice and thought that's a waste of your time and creativity. I agree with you and thats why I implemented the concept of blocks in the Abaporu Lang. </br>
### Defining a block
You can think about a block as you think about a function that returns nothing and receives nothing only working in the global scope of your code. </br>
To define a new block in your art, you just need to use a color that does not represent any instruction,  write the set of instructions of your block and then close the block with <svg width="20" height="20" xmlns="http://www.w3.org/2000/svg"><rect width="100%" height="100%" fill="#FFA200"/></svg>(#FFA200).</br>
To use the instructions of the block, you just need to call it again using the same color you defined before.</br>
**Note**: As this documentation is written, I did not  have made an IDE yet, sou you will need to keep track of the `pointer` position in yout head if you want to make complex things with `blocks`

### Example of `block`
```
* Defines a block that will put and go to the next cell of the sausage
#AAAAAA
	#FFFFFF
    #00FF00
#FFA500

* Imagine the list of  instructions to generate 'H' here.

#AAAAAA
```
`[stdout]: H`</br>

**Note**: Better usage of blocks can be found in `./examples/BlockHelloWorld.abapl`

## Is Abaporu finished?
No, I need to implement loops, an output function and make an IDE.
