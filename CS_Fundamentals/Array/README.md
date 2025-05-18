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

# Array Data Structures

For simple programs, arrays will suffice. However, for larger datasets and more complex programs, you may need other data types that are a bit more efficient.

## Vectors

Including the vector library in C++, programmers have access to the vector data type. 

```cpp
#include <vector>

using namespace std;

vector<int> nums;
```

Vectors work the same as a dynamic array, but handles heap allocations and manipulations under the hood in a way that is intuitive for the user. Anytime you see a use for a dynamic array, it would be best to use the vector library.

In fact, it may be beneficial to use vectors for static array use-cases as well. Some of the functions in the vector library are too good to pass up. Even though vectors make use of the heap rather than stack, it takes a good amount of work and expertise to create an algorithm for the native array to be faster than the vector (even if you are able, the gains are marginal).

Initializing, accessing and populating vectors can be done in the same way as an array.

### Vector Manipulation

For a defined vector...

```cpp
using namespace std;

vector<int> v;
```

You can perform the following functions. Check out the example code for [vectors](#vector_code) section to see how the functions works.

|Function                                     |Description                                                     |Time Complexity|
|---------------------------------------------|----------------------------------------------------------------|---------------|
|v.insert(*iterator*, *data*) *               |Insert data anywhere in the vector                              |O(n)           |
|v.push_back(*data*)                          |Insert data into the end of the vector                          |O(1)           |
|v.erase(*iterator*) *                        |Delete data anywhere from the vector                            |O(n)           |
|v.pop_back()                                 |Delete the last element from vector                             |O(1)           |
|sort(*start iterator*, *end iterator*)       |Sort a vector in ascending order                                |O(n*log n)     |
|stable_sort(*start iterator*, *end iterator*)|Sort a vector in ascending order, but maintain order of equal elements|O(n*log^2 n)|
|sort(*, *, greater<>())                      |Sort a vector in descending order                               |O(n*log n)     |
|stable_sort(*, *, greater<>())               |Sort a vector in ascending order, but maintain order of equal elements|O(n*log^2 n)|

* *This function can be used for a range of elements as well, view the example code for details.*

# Examples
## Vector Code
<details>
<summary>v.insert()</summary>

```cpp
using namespace std;

vector<int> v = {1,2,3,4,5};

v.insert(v.begin()+2, 9);

//Resulting vector: {1,2,9,3,4,5}
```

If you want to insert a range of elements?

```cpp
using namespace std;

vector<int> v1 = {1,4,5};
vector<int> v2 = {2,3};

v1.insert(v1.begin()+1, v2.begin(), v2.end());

//Resulting vector: {1,2,3,4,5}
``` 
</details>

<details>
<summary>v.push_back()</summary>

```cpp
using namespace std;

vector<int> v = {1,2,3,4,5};

v.push_back(6);

//Resulting vector: {1,2,3,4,5,6}
```
</details>

<details>
<summary>v.erase()</summary>

```cpp
using namespace std;

vector<int> v = {1,2,3,4,5};

v.erase(v.begin()+1);

//Resulting vector: {1,3,4,5}
```

If you want to delete a range of elements...

```cpp
using namespace std;

vector<int> v = {1,2,3,4,5};

v.erase(v.begin(), v.begin()+2);

//Resulting vector: {4,5}
```
</details>

<details>
<summary>v.pop_back()</summary>

```cpp
using namespace std;

vector<int> v = {1,2,3,4,5};

v.pop_back();

//Resulting vector: {1,2,3,4}
```
</details>

<details>
<summary>sort()</summary>

```cpp
using namespace std;

vector<int> v = {1,3,2,5,4};

sort(v.begin(), v.end());

//Resulting vector: {1,2,3,4,5}
```
</details>