# Abaporu Lang
![Abaporu Original Painting](https://upload.wikimedia.org/wikipedia/pt/thumb/b/bd/Abaporu.jpg/253px-Abaporu.jpg)

## Overview
Abaporu lang is an esoteric programing language developed by me as a fun project to do during the new year's holliday. The name of the esolang comes from a famous brazilian painting named **Abaporu** made by Tarlisa do Amaral. You can see more about it [here](https://en.wikipedia.org/wiki/Abaporu).

The way this esolang works is similar in functionality to [Brainfuck](about:blank) and the programing style is based in [Piet](https://esolangs.org/wiki/Piet), where you use colors to represent instructions.

## Instaling
To use the language by your own, you can clone this repository in your computer with NodeJs installed and run:
`node index.js -p <your-input-file.abapl> -o <path-you-want-to-output-canva>`

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
| endLoop  | End a previously started loop. More on loops in one of the next topics.    | #3FFFE8 |
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
**Note**: As this documentation is written, Abaporu Lang does NOT support declaration of blocks inside blocs

## Loops
Even with the use of `blocks` your art may look awful because of the times you have to repeat `#FF0000` `#0000FF` to put the letters you want.
That's why I've implemented the concept of loops in this beautiful language.

### Using loops
The loops inside Abaporu language kind of work like a basic `for` loop, where you declare a range and the code inside the loop runs until the range reach its limit.
For examplo, a `for` loop in javascript that runs 10 times look like this:

```javascript
for(let i = 0; i < 10; i++){
    console.log('This will run 10 times')
}
```
Similarly, to use loops in Abaporu, you have to declare it using a "keyword", and assign a range for it.

Every `loop` **MUST** start with `#11` meaning that a `loop`, will never be red. The other 6 elements of a Hex color, will determine the range of the loop.
The code that should be executed during the loop will be all the instructions between loop declaration and `endLoop`(#3FFFE8)
So, for example, to declare a loop that will run 10 times you do:
```
#11000A
    * Some Abaporu code here
#3FFFE8
* There is no need to call a loop after declaring it, as it's execution is linear and will be deleted of the runtime after its range is reached.
```

So in this case, I declared a loop with `#11000A`.
`#11` declare it as a loop and `000A` is 10 in HEX. You can use a conversor to determine the color you need.

**Note**: As yout propably already discovered, Abaporu lang has a limitation of 65535 to the range of it's loops. If by any misterious reason you need a loop bigger than that, you can use two loops operating on the same sausage element.
**Note**: As this documentation is written, there is no suport for loops inside loops.
**Note**: Better use of loops can be found in the `examples` folder of this project.

## Wondering what your code look like?
Open the output link sent after every succesfull running of this interpreter.
