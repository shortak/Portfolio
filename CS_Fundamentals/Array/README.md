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