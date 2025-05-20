# How They Work

The "for" loop is an iterative processes where the number of iterations is controlled by predetermined conditions. 

For example...

```cpp
for(int i = 0; i < 1000; ++i) 
{
    // Whater you want to do in your programs
}
```

The above code reads as follows...

1. Start the first iteration for i = 0
2. Increment the counter (i) by one (++i)
3. Continue until i = 999

Any of these conditions can be changed.

# Range Based Conditions

Lets way we have a vector letters = {a, b, c} and we want to iterate across it...

```cpp
for(int i = 0; i < letters.size(); ++i)
{
    char letter = letters[i];
    // Process involving element
}
```

The above code shows how one might do this... but there is an easier way.

```cpp
for(char letter : letters)
{
    // Process involving letter
}
```

This way, we initialize a new variable "letter". This loop will automatically iterate through each element of "letters" (as shown by ": letters") while storing each element in "letter". This offers a more efficient way to perform operations based on the elements of our vector. 

Furthermore, you can use a pass by reference to change the element in the vector without needing to spend extra steps to reassign the value. 

```cpp
for (char& letter : letters)
{
    letter = e;
}


// VS

for (int i = 0; i < letters.size(); ++i)
{
    letters[i] = e;
}
```

The benefits based on the above example are not apparent at first, and indeed, if you are simply changing the elements of a vector, there is also no benefit, however...

```cpp
for(int i = 0; i < digits.size(); ++i)
        {
            // Get the first set of letters (if digits[1] = '2' then letters = "abc")
            string letters = GetLetters(digits[i], letterList);
            temp.clear();

            for(string& combination : result)
            {
                // Build the combination
                for(char letter : letters)
                {
                    temp.push_back(combination + letter);
                }
            }
            result = temp;
        }
        return result;
```

In situations where you want to perform an operation based on the element AND change the element at the same time, a pass by reference is the best method.