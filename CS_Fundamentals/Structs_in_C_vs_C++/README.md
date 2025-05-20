# Overview

When it comes to data structures in C++, encapsulation is key. This directory will dig into what a struct is, why it is important and what make a C++s struct different from a C struct

Examples of structs in C and C++ can be found in the [Point.c](Point.c) and [Point.cpp](Portfolio/Projects/CS_Fundamentals_Using_C%2B%2B/Point.cpp) files.
Examples of structs in C and C++ can be found in the [Point.c](Point.c) and [Point.cpp](Point.cpp) files.

# The Struct Data Type

@@ -63,95 +63,95 @@

In essence, C structs are only limited to member variables.

NOTE: Access Specifiers are reserved for "class" rather than "struct"; class is not much different than structs in practice, it just offers access specifiers which will be explored in the [classes in C++](Portfolio/Projects/CS_Fundamentals_Using_C%2B%2B/Classes_in_C%2B%2B/) directory.
NOTE: Access Specifiers are reserved for "class" rather than "struct"; class is not much different than structs in practice, it just offers access specifiers which will be explored in the [classes in C++](../Classes_in_C%2B%2B/) directory.

## Simulating a Member Function in C vs Member Functions in C++

The C++ programmer has the benefit of member functions...

```cpp
struct Point 
{
    int x;
    int y;

    void move() {
        x += 1;
        y += 1;
    }
};

int main() 
{
    Point p = {0, 0};   

    p.move();

    return 0;
}
```
Which allows the function ("move" in the above code) to only be used for the Point-type variables.

A C programmer can, however, simulate object-like behavior...

```c
struct Point 
{

    int x;
    int y;

};

void move(struct Point* p)
{
    p -> x += 1;
    p -> y += 1;
}

int main()
{
    struct Point p = {0, 0};
    move(&p);

    return 0;
}
```

The above code specifies a function called "move" which acts as a member function.

The issue here is that the "move" function is not specific to a Point-type variable, meaning it is technically possible to use the move function with another struct...

```c
struct Point 
{

    int x;
    int y;

};

struct PolarPoint
{
    int r;
    int theta;
};

void move(struct Point* p)
{
    p -> x += 1;
    p -> y += 1;
}

int main()
{
    struct PolarPoint p = {1, 3};
    move((struct Point*)& p);

    return 0;
}
```
In the above code, we force a cast from a PolarPoint type to a Point type. The compiler will trust the user and assume that the behavior is defined when it is not.

This causes bugs that will be ignored by the compiler, leaving it up to the C programmer to find and resolve the issue.
