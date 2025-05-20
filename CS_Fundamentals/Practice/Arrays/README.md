# Overview

This directory contains my practice problems from Leetcode. Any new learnings will be catalogued here.

# Removing Dupes
Relevant files: [remove_dupes_from_sorted_array_atmpt1.cpp](remove_dupes_from_sorted_array_atmpt1.cpp) and [remove_dupes_from_sorted_aray_atmpt2](remove_dupes_from_sorted_array_atmpt2.cpp)

Both files are viable and get the job done... However, attempt 2 offers a much more efficient and faster method. The time complexity of the first is O[n^2] which the second is O[1].


# Three Sum
Relevant files: [3Sum](3Sum.cpp)

Prompt: 

Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Solution:

```cpp
class Solution 
{
public:

    

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> result;

        // Step 1: Sort the array
        sort(nums.begin(), nums.end());

        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) 
        {
            // Skip duplicates for the first number
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) 
            {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) 
                {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicates for left and right
                    while (left < right && nums[left] == nums[left + 1]) ++left;
                    while (left < right && nums[right] == nums[right - 1]) --right;

                    ++left;
                    --right;
                }
                else if (sum < 0) {++left; /*Need a larger sum*/}
                else {--right; /*Need a smaller sum*/}
            }
        }

        return result;
    }
};
```

Explanation:

The priority here is to avoid the naive solution of brute forcing by iterating through each number, then finding the sum of the triplets. The main strategys are to sort the vector first. This way, we can calculate the sum of a triplet, then iterate left or right depending on if we want a bigger sum or not.

Important Strategies:

1. Pointer method
    1. Sort the array
    2. Choose a value i and two other pointers realtive to i to perform necessary operation (sum the elements in this case).
    3. Depending on the result, increase or decrease the left and right pointers (not i) 

2. Skip duplicate elements 
    - Avoids picking the same triplets rather than checking the triplets after picking them out (Since you never choose the triplet in the first place, you avoid spending too much processing time by never choosing a duplicate triplet).

# Matrix Combinations

Relevant Files: [combinations.cpp](combinations.cpp)

Prompt: 

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Key Concepts:

- Matrix Combinations
- String Construction

Solution:

```cpp
class Solution {
public:
    inline string GetLetters(char num, vector<string> letterList)
    {
        // Since letters[0] contains the letters for the number 2
        int letterIndex = (num - '0')-2;
        return letterList[letterIndex];
    }

    vector<string> letterCombinations(string digits) 
    {
        vector<string> letterList = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        // Vector for storing a combination to then store into result vector
        vector<string> temp;
        vector<string> result = {""};

        if(digits == "") return {};

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
    }
};
```

The above code implements a cartesian product algorithm. Basically, we are asked to find all possible combinations of two vectors (remember that strings are vectors of charcters). The approach here is the find the word set associated with the digits entered by the user, then treat them as the vectors for which we need to find the combinations for. 

Lets check out a iteration-by-iteration analysis...

```cpp
//iteration 1 (word set is abc)

// Get the first set of letters (if digits[0] = '2' then letters = "abc")
string letters = GetLetters(digits[i], letterList);
temp.clear();

//combination == "", result == ""
for(string& combination : result)
{
    // Build the combination
    for(char letter : letters /*(abc)*/)
    {
        temp.push_back(combination + letter); // Since we use pass by reference, the "combination" string also gets built
    }
}
result = temp; // result == {"a", "b", "c"}
```

```cpp
// iteration 2 FINAL (word set is def)

// Get the second set of letters (if digits[1] = '3' then letters = "def")
string letters = GetLetters(digits[i], letterList);
temp.clear();

//combination is an element of result, result == {"a", "b", "c"}
for(string& combination : result)
{
    // Build the combination
    for(char letter : letters /*(def)*/)
    {
        temp.push_back(combination + letter);
        /*ad, then ae, then af... go to next iter in result loop*/
        /*bd, then be, then bf... go to next iter in result loop*/
        /*cd, then ce, then cf... go to nect iter in result loop*/
    }
}
result = temp; // result == {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}
```