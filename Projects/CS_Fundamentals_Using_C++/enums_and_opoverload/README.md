# Overview

One of the core concepts of C++ is to make intuitive and readable code. This directory contains programs that use strategies to accomplish this:
1. Enum
2. Operator Overloading

# Enum: 

Enum is a user-defined type in C++ to assign names to a set of integer constants, making code more readable and manageable

There are two types of enums you can use in C++...

1. enum (enum.cpp)
2. enum class (enumclass.cpp)

(both files uses enumerators to create and perform operations on a "days" datatype as an example)

Enum is no different from manually assigning integers to names, for example...



```cpp 
enum Color{RED, GREEN, BLUE};
```

is the same as 

```cpp 

RED = 1;
GREEN = 2;
BLUE = 3;

```

The reason for the enum, is to make it so that the named variables will have their own type. This way, a "Color" type variable won't be able to work with an "int" type variable, thus avoiding logical bugs in the code. 

## enum class vs. enum



```cpp 

enum class Color{RED, GREEN, BLUE};
enum class Day{MON, TUE, WED};

int a = Color::RED + Day::MON; // This will not compile, despite both values being integers

```

is much more type strict whereas...

```cpp 

enum Color{RED, GREEN, BLUE};
enum Day{MON, TUE, WED};

int a = RED + TUE; // This will still compile but this does not make sense to do (or you may not want to do this)

```

is not as type strict, causing logical bugs. However there may be cases where you want implicit type conversion for the sake
of readability, for example...

```cpp 

enum Day{MON, TUE, WED};

day d = MON;

if (d == MON) 
{
    cout << "It is Monday!" << endl;
}


```

May be more convenient than

```cpp 

enum class Day{MON, TUE, WED};

day d = Day::MON;

if (d == Day::MON) 
{
    cout << "It is Monday!" << endl;
}


```
At the end of the day, it is up to the user to decide if the tradeoffs are worht it.


# Operator Overloading:

Operator overloading provides a way to assign new meaning to certain operators depending on the data type

For example, we know that something like 

```cpp
i++
```
Increments the variable i by 1, however, lets say we are working with a data type where incrementing means increasing the value by 2...

```cpp
inline datatype operator++ (datatype d)
{
    return static_cast<datatype>(static_cast<int>(d) + 2); //cast type to int to perform operation, 
                                                           //then cast to datatype to preserve type
}
```

This way, if we use the "++" operator with the "datatype" type, it will increment by 2 instead of 1

NOTE: You need to use static_cast here to make sure you can perform an integer operation (or any operation in this case)