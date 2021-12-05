

**CLIC (Command Line Interface Calculator)**

CLIC is a command line program intended to have all the functionality of a scientific calculator.

Github link: [https](https://github.com/wetbadger/kmir)[://](https://github.com/wetbadger/kmir)[github](https://github.com/wetbadger/kmir)[.](https://github.com/wetbadger/kmir)[com](https://github.com/wetbadger/kmir)[/](https://github.com/wetbadger/kmir)[wetbadger](https://github.com/wetbadger/kmir)[/](https://github.com/wetbadger/kmir)[kmir](https://github.com/wetbadger/kmir)

**How to use:**

Enter any mathematical expression. Supported operators are:

\+ addition

\- subtraction or unary

\* multiplication

/ division

^ exponent

() left and right parenthesis

= to assign a value to a variable.

For example: 

(1 + 2) \* 3

or

73 \* 1.618 ^ 2 + 37 \* 1.618 + 229

The correct answer will print to the console.

Type ‘end’ to close the program.

**How it's made:**

**Tokens:**

Tokens are how the computer identifies the fundamental elements of an expression. For example, given the expression "1 + 2 \* 3" we can see that we are working with 3 integers and two operators. Each token is distinguished by enumerated types such as TT\_INT, where TT stands for "Token Type."

**Lexer:**

After the user types an expression and presses enter, the input string is translated into tokens via the lexer. Each element in the string should be either a number, a mathematical operator, or a variable name. After the lexer reaches the end of the line, a vector of tokens is produced.

**Parser and Interpreter:**

Our calculator could simply go through each token from left to right, but that would not obey standard order of operations. For example, in the case of "1 + 2 \* 3" 1 + 2 would give us 3 multiplied by 3 giving us 9, which is the wrong answer! We must tell the computer to do multiplication before addition. To do this, we arrange the tokens into a data structure called a tree with the addition token serving as the root node of our tree in this case. Because this is a binary tree, each node can have only one parent, and no more than two children. According to our grammar definition, 2 numbers multiplied is called a term. When the parser sees the multiplication symbol, it knows to add the product of 2 and 3 to the factor 1. As the interpreter traverses the tree, operator nodes are converted to number nodes representing the solution to each term, factor, or expression. The root node will represent the correct answer.

This type of data structure, known as an abstract-syntax tree, is widely used in computer science from web servers to computer languages. [1]

**Integers and Floating points:**

In the future we want to make something that can solve expressions with any size number. Currently numbers over 2^31 can only be added, because multiplication with large numbers is a complicated subject.

Strings are only limited by the amount of memory a computer has, and so we chose to store the value of each number as a string. This way we can store a representation of any arbitrarily large number. Doing arithmetic with these numbers is another story.

We check for overflow by checking if the number is greater than the maximum size of INT minus the number being added to it. If there is overflow, there is a special method for doing long addition with two strings instead of numbers. This does not currently work for multiplication and division or exponents, as those are more challenging.[2]

Similarly, floating point arithmetic has many nuanced details. We were not able to resolve rounding errors or have greater than 16 decimal places of precision.[3]

**Error messages:**

Writing error messages was a bit like a game of whack-a-mole. There are many erroneous combinations of symbols a user could put into a calculator, and it is hard to guess them all. We weren’t sure whether to print errors as a function, or to make each error a separate class, so right now we use both approaches. Some errors we created are: NameError for unassigned variables, left and right parenthesis errors, and invalid number errors. We are trying to decide on a good convention for throwing errors, so more can be added in the future.

**Symbols:**

Strings of letters can be assigned a value with the ‘=’ operator. A table of words and their corresponding values is stored in a map and maintained as long as the program runs.

**Command-line Arguments:**

Running the program with the -v argument will start verbose mode. Right now this only displays the tokens as a list.

A file path can also be used as a command-line argument.

**Influences:**

We were heavily influenced by the first 4 videos in this series: 

[https](https://www.youtube.com/watch?v=Eythq9848Fg)[://](https://www.youtube.com/watch?v=Eythq9848Fg)[www](https://www.youtube.com/watch?v=Eythq9848Fg)[.](https://www.youtube.com/watch?v=Eythq9848Fg)[youtube](https://www.youtube.com/watch?v=Eythq9848Fg)[.](https://www.youtube.com/watch?v=Eythq9848Fg)[com](https://www.youtube.com/watch?v=Eythq9848Fg)[/](https://www.youtube.com/watch?v=Eythq9848Fg)[watch](https://www.youtube.com/watch?v=Eythq9848Fg)[?](https://www.youtube.com/watch?v=Eythq9848Fg)[v](https://www.youtube.com/watch?v=Eythq9848Fg)[=](https://www.youtube.com/watch?v=Eythq9848Fg)[Eythq](https://www.youtube.com/watch?v=Eythq9848Fg)[9848](https://www.youtube.com/watch?v=Eythq9848Fg)[Fg](https://www.youtube.com/watch?v=Eythq9848Fg)

This was helping us get a grasp on custom exceptions in c++: [https](https://riptutorial.com/cplusplus/topic/1354/exceptions)[://](https://riptutorial.com/cplusplus/topic/1354/exceptions)[riptutorial](https://riptutorial.com/cplusplus/topic/1354/exceptions)[.](https://riptutorial.com/cplusplus/topic/1354/exceptions)[com](https://riptutorial.com/cplusplus/topic/1354/exceptions)[/](https://riptutorial.com/cplusplus/topic/1354/exceptions)[cplusplus](https://riptutorial.com/cplusplus/topic/1354/exceptions)[/](https://riptutorial.com/cplusplus/topic/1354/exceptions)[topic](https://riptutorial.com/cplusplus/topic/1354/exceptions)[/1354/](https://riptutorial.com/cplusplus/topic/1354/exceptions)[exceptions](https://riptutorial.com/cplusplus/topic/1354/exceptions)


Works Cited

[1] R. Nystrom, “Parsing expressions,” *Parsing Expressions · Crafting Interpreters*. [Online]. Available: https://craftinginterpreters.com/parsing-expressions.html. [Accessed: 05-Dec-2021]. 

[2] “Introduction to multiplying huge integers,” *Multiplication using FFT*. [Online]. Available: https://www.aimath.org/news/congruentnumbers/howtomultiply.html. [Accessed: 05-Dec-2021]. 

[3] D. Goldberg, “Appendix D,” *What Every Computer Scientist Should Know About Floating-Point Arithmetic*, 05-Apr-2000. [Online]. Available: https://docs.oracle.com/cd/E19957-01/806-3568/ncg\_goldberg.html. [Accessed: 05-Dec-2021]. 
