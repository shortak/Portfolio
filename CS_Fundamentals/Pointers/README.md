# Overview

Pointers are a helpful tool that allows us to specify to the compiler whether or not we want to edit a value located at a specific memory address or perform the operation on a copy of that value...

Remember that when we say something like

```cpp
inline int Sum(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 5;
    int b = 6;

    int sum = Sum(a, b);
    return 0;
}
```

When we call the "Sum" function, we don't use actual values a and b, rather, we mean a copy of those values. Let's dive into what pointers are befor we dig into the above example.

# Pointers

Pointers allow us to get the address in which a variable is located.

```cpp
int p = 0;
int* n = &p;
```

int*: int pointer variable
&data: Gets the address where 'data' is stored. 

Keep in mind that int is different from int*. When we use a pointer, we are telling the compiler that we are refering to an address that stores an int type variable. When assigning a value to a pointer type variable, we need to &data...

```cpp
int* p = h; ; // Does NOT mean "go to address that has h
int* p = &h; // Correct
```

Any value passed into a pointer variable tells the compiler that that value is an address, so in essence passing any regular value into the pointer will throw out a compiler error (unless you somehow pass a valid address).

```cpp
string example = "hello"; // Lets assume that this is stored at address 0x1234
string* p = example; // Tell the complier that p is the address "hello"... doesn't make sense; throw out error

string* p = &example; // basically means string* p = 0x1234, this makes sense
```

## Passing by Reference

With pointers, you can use pass arguments by reference..

Lets take the "Sum" function we specified earlier and change it so that it uses a pass by reference. 

```cpp
inline int Sum(int& a, int& b)
{
    return a + b;
}
```

This now specifies that when we call the "Sum" function, we want to use the actual values in memory, not a copy. With a small function this may not seem necessary, but if we need to perform a function on a much larger variable...

```cpp
string* array = new string[1000000];

void StoreInArray(string array[])
{
    for (int i = 0; i < 1000000; ++i)
    {
        array[i] = "s";
    }
}
```

Here we try to store "s" into an array of size 1000000. Lets break down the issues here. 

Even though we allocate this string to the heap, the function will create a copy of the entire array to perform the operation. With a string array, that means 32 bytes * 1000000... an extra 32 megabytes!

This is risky since using a function with a pass by value argument, the function will copy that 32 MB array onto the stack EVEN THOUGH the actual array is on the heap. Therefore...

```cpp
string* array = new string[1000000];


void StoreInArray(string* array)
{
    for (int i = 0; i < 1000000; )
}

//Function Call: StoreInArray(array)
```

Would be the correct way to go about things. Since we pass by reference, we instruct the compiler to perform the function on the array in the heap rather than create a copy in the stack.
 
NOTE: You cannot actually pass an array using "&" like in the "Sum" function example. The ampersand implies a *single* address, you cannot access a range of addresses, which you would need to do for an array. Using a pointer, on the other hand, tells the compiler to go to the address of the first element of the array, which is correct. 

Additionally, keep a close eye on type matching...

Since we allocated the array to the heap... the variable "array" is a pointer, NOT an array. This is why we can call the function with StoreInArray(array). If the variable was on the stack instead and was actually an array rather a pointer, we would need to call it by doing StoreInArray(&array).

## Dereferencing

"Dereferencing" is a common term when talking about pointers...

```cpp
int x = 42;
int* ptr = &x;  // ptr holds the address of x

// Dereferencing ptr:
int y = *ptr;   // y now is 42, the value at the address ptr points to

*ptr = 100;     // changes x to 100, because *ptr is the same as x
```

When we use a pointer we are essentially "referencing" the address that holds the data.

By using "*" on a pointer type variable, we now dereference that pointer, meaning we're talking about the data stored at that address.

(We are basically pointing to an address here)