# Overview

Linked lists are a fundamental data structure that allows for efficient insertion and deletion operations similar to arrays.  

It is also used to implement other data structures like the stack, queue and deque.

|                   |Linked Lists  |Arrays    |
|-------------------|--------------|----------|
|Data Structure     |Non-contiguous|Contiguous|
|Memory Allocation  |Allocated 1-by-1 to indiv. elements|Allocated to the whole array|
|Insertion/ Deletion|Efficient |Inefficient|
|Access             |Sequential|Random|

Lets break it down..

## Linked Lists vs. Arrays
### Data Structure

When dealing with data structures that deal with multiple elements like an array or linked list, one of the things we need to worry about is how where and how the data is stored in memory.

Data structures can be either contiguous, meaning all elements are stored sequentially in memory, or non-contiguous, meaning the elements are scatter across memory.

For this reason, we would typically store a linked list in the heap rather than the stack. A scattered memory (or fragmented memory) can make it difficult to fit other elements into stack, causing a stack overflow. 

### Memory allocation

Memory and linked lists are allocated in memory a bit differently. Typically, you would need to define how big you want your array to be before you can use it. After declaring the size of the array, the whole array is then allocated to memory, regardless of how much the array is in use.

```cpp
int arr[100]

for (int i = 0; i < 100; i++)
{
    arr[i] = 1;
}
```
Regardless of what "i" we are on, the compiler will still allocate the full size array to memory. This is fine if we know how big we want the array, but it becomes a problem if...

1. The array is wayyyyyy too big
2. The array changes size during runtime

Linked lists on the other hand allocate its elements to memory one by one. This may be slower, but it is much better for large or dynamic arrays. 

### Insertion and Deletion

Linked lists offer much faster insertion and deletion (O(1)) since that operation only involves one element. Arrays on the other hand need to shift all subsequent elements accordingly in order to perform the operation, the larger the array, the longer the operation takes (O[n]).

### Access

Linked lists can only access its elements sequentially whereas arrays can access any element randomly. In other words, linked lists can only go to wherever the current node is connected and cannot jump to a node that isn't connected to the current one.

```cpp
current->next //Jump to next node
current->prev //Jump to prev node
```

So, if you require quick access to non-sequential information, arrays are the way to go. 