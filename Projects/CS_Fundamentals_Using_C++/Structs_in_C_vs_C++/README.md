# Overview

When it comes to data structures in C++, encapsulation is key. This directory will dig into what a struct is, why it is important and what make a C++s struct different from a C struct

# The Struct Data type

A struct is a user-defined data type that lets you group realted variables (members) together under one name

NOTE: The enum class is a special kind of struct

For example...

```cpp
struct Point
{
    int x;
    int y;
};

Point p;

p.x = 5;
p.y = 10;
```

We create the Point type, then initialize a Point-type variable p.
Our new variable, p, inherits the properties of the Point struct, meaning it has access to an x and y variable (not the same x and y but a copy of them).

```cpp
struct Point
{
    int x;
    int y;
};

Point p1;
Point p2;

p1.x = 5;
p1.y = 10;

p2.x = 7;
p2.y = 8;
```

p2 will not overide p1 despite being the same data type.

Essentially, upon initializing a variable with a user-defined data type, you create a copy of that type on the stack. It does not share states with other variables.
If you want to share states, you can use pointers as you would with native types.