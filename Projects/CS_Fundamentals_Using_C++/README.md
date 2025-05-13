One of the core concepts of C++ is to make intuitive and readable code. This directory contains programs that use strategies to accomplish this:
1. Enum
2. Operator Overloading

Enum: 
Enum is a user-defined type in C++ to assign names to a set of integer constants, making code more readable and manageable

There are two types of enums you can use in C++...

1. enum (enum.cpp)
2. enum class (enumclass.cpp)

Enum is no different from manually assigning integers to names
<pre>```cpp enum Color{RED, GREEN, BLUE};```</pre>

is the same as 

<pre> ```cpp 

RED = 1;
GREEN = 2;
BLUE = 3;

</pre>

The reason for the enum, however, is to make it so that the named variables will have their own type. This way, a "Color" type variable won't be able to work with an "int" type variable, thus avoiding logical bugs in the code.

enum class vs. enum

<pre> ```cpp 

enum class Color{RED, GREEN, BLUE};
enum class Day{MON, TUE, WED};

int a = Color::RED + Day::MON; // This will not compile, despite both values being integers

```</pre>

is much more type strict whereas 

<pre> ```cpp 

enum Color{RED, GREEN, BLUE};
enum Day{MON, TUE, WED};

int a = RED + TUE; // This will still compile but this does not make sense to do (or you may not want to do this)

```</pre>

is not as type strict, allowing for bugs

