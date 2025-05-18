# Overview

One of the biggest parts of computer science is understanding arrays and array manipulation. This directory will go over the array structure as well as efficient array manipulation.

# Array

Arrays are a native data structure that sores a collection of elements, typically of the same data type, in a contiguous block of memory. Each element in the array is accessed by an index or position.

This is NOT to be confused with storing each value as an ordered pair, there are other structures that do that, but in the cause of the basic array, they are only stored data in memory.

```cpp
int nums[1000];

for(int i = 0; i < nums.sizeof(nums); i++)
{
    nums[i] = i;
}
```

The above code constructs an ordered array of 1000 integers starting from 0. Note that there is no index being assigned... rather, if I wish to access an element at position 10...

```cpp
int a = nums[10];
```

What you are telling the compiler is to access the value stored 10 addresses down from the starting address of the array in memory (0x0000 -> 0x0010).

## Initializing Arrays

If you want to initialize an array to any value other than 0...

```cpp
int array[1000] = {/*Insert any constant value*/};
```

This efficiently initialized the array without need a "for" loop (saves computation power)

## Multidimensional Arrays

Arrays can also store other arrays...

```cpp
int grid[2][10];

for(int i = 0; i < 2; i++)
{
    for(int j = 0; j < 10; j++)
    {
        grid[i][j] = (i * 10) + j;
    }
}
```

This makes the following array...

```cpp
int grid[2][10] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                   {10, 11, 12, 13, 14, 15, 16, 17, 18, 19},};
```

Think of it as a grid on the xy-plane where i-index is the x-axis and the j-index is the y-axis.

NOTE: You can initialize a multidimensional array the same way as a one dimensional array...

```cpp
int grid[2][5] = {/*any constant value*/};
```

For each nested "for" loop, a new dimension is added...

```cpp
// 1D, 2D, 3D and so on...
int grid[10][10][10]...;

for(int i = 0; i < 10; i++)
{
    for(int j = 0; j < 10; j++)
    {
        for(int k = 0; k < 10; k++)
        {
            ...
        }
    }
}
```

NOTE: This code is not meant to compile, just to demonstrate how one might go about creating multidimensional array.

Keep track of how big the array is. For example, making a 10 dimensional array where each cell is an int type variable (4 bytes) will allocate a huge amount of memory and processing power to parse the array. In this case, it may be benefically to turn to other data types and strategies.

You can find the size of any array by using the "sizeof()" operator.

```cpp
int grid[2][10];

for(int i = 0; i < 2; i++)
{
    for(int j = 0; j < 10; j++)
    {
        grid[i][j] = (i * 10) + j;
    }
}

sizeof(grid);
```

In the above code, "sizeof(grid)" will show how much memory the grid array takes in bytes. In this case, it will output 80 (Total elements: 2 * 10 = 20, size of each element: 4 bytes).

## Dynamic Arrays

As you may have guessed one of the issues with using an array is that we need to know the size of the array at compile time. Naturally, an array is static, however, we may want to have an array that automatically allocates more memory as our data set grows...

```cpp
using namespace std;

int size;
cin >> size;
int* arr = new int[size];
/*Do what you need with the array*/
delete[] arr;
```

In the above code, we use a "dynamic" array. This makes use of the heap to avoid a stack overflow incase the array is too big. 

During runtime, the array size can be changed. However, If we already have data in the array and we wish to resize it, things get complicated.

```cpp
int* oldArr = new int[10];

for (int i = 0; i < 10; i++) {oldArr[i] = i * 10;}

int* newArr = new int[20]; 

for (int i = 0; i < 10; i++) {newArr[i] = oldArr[i];}

delete[] oldArr;

oldArr = newArr;  

```

We would need to create a copy of the old array, create a new array with the size that we want, then past the old array into the new array...

While it is possible to do this, operations that involve allocating to the heap can be risky if not handled with care. 

Luckily, we have libraries that handle everything under the hood...

# STL Containers

For simple programs, arrays will suffice. However, for larger datasets and more complex programs, you may need other data types that are a bit more efficient.

There are a variety of STL Containers that offer an efficienct way to navigate larger datasets.


### Iterators

Vectors have a different way to access its elements than what beginners may be used to. Elements are accessed through "iterators" rather than an integer index.

Iterators, unlike an integer index, are an object that act as a pointer. They offer protection from out of bounds (segfaults) and compatibility with STL algorithms (v.insert(), v.sort(), v.erase, etc.).

However, if you want fast, random access and readable code, stick to integer indexing (vectors supports random indexing, like normal arrays).

|Feature          |Iterator                             |Int Index                         |
|.................|.....................................|..................................|
|Type             |Object (pointer)                     |Integer                           |
|Access           |*it, it->                            |v[i]                              |
|Navigation       |++it, --it, it + n                   |++i, --i, i + n                   |
|Safety           | Safer with STL algorithms           |Can give a segfault               |
|Generality       |Works with all STL containers        |Only with random-access containers|
|STL Compatibility|Works with std::find, std::sort, etc.|Not compatible with STL algorithms|
|Expressiveness   |Can be used in generic code          |Less flexible                     |

NOTE: if can operation is down between an iterator and integer, the result will be an iterator, therefore, something like "v.begin() + 2" is valid.

## Set

Sets, similar to a vector, are a structure that holds a collection of elements.

However, unlike vectors, they work different from vectors under the hood

|Feature             |Vector                          |Set                          |
|....................|................................|.............................|
|Ordering            |Elements kept in insertion order|Elements kept in sorted order|
|Duplicates          |Allowed                         |Not Allowed                  |
|Access              |Random access                   |Only through iterators       |
|Underlying Structure|Dynamic array                   |Balanced Binary Search tree  |
|Search Speed        |O(n)                            |O(log n)                     |
|Insert Performance  |O(1)                            |O(log n)                     |
|Memory usage        |Less (more compact)             |More (sores tree structure)  |

For larger datasets that need to be sorted, use an ordered set, but for any other applications, vectors will suffice.

