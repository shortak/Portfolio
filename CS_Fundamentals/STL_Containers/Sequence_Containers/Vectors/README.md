# Vectors

Including the vector library in C++, programmers have access to the vector container. 

```cpp
#include <vector>

using namespace std;

vector<int> nums;
```

Vectors work the same as a dynamic array, but handles heap allocations and manipulations under the hood in a way that is intuitive for the user. Anytime you see a use for a dynamic array, it would be best to use the vector library.

In fact, it may be beneficial to use vectors for static array use-cases as well. Some of the functions in the vector library are too good to pass up. Even though vectors make use of the heap rather than stack, it takes a good amount of work and expertise to create an algorithm for the native array to be faster than the vector (even if you are able, the gains are marginal).

Initializing, accessing and populating vectors can be done in the same way as an array.

## Vector Manipulation

For a defined vector...

```cpp
using namespace std;

vector<int> v;
```

You can perform the following functions. Check out the example code for [vectors](#vector-code) section to see how the functions works.

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

<details>
<summary>stable_sort</summary>

```cpp
using namespace std;

vector<int> v = {1,3,4,2,4,5}

stable_sort(v.begin(), v.end());

//Resuling vector: {1,2,3,4,4,5}
```
</details>

<details>
<summary>sort(greater<>())</summary>

```cpp
using namespace std;

vector<int> v = {1,3,2,5,4};

sort(v.begin(), v.end());

//Resulting vector: {5,4,3,2,1}
```
</details>

<details>
<summary>stable_sort(greater<>>())</summary>

```cpp
using namespace std;

vector<int> v = {1,3,4,2,4,5}

stable_sort(v.begin(), v.end());

//Resuling vector: {5,4,4,3,2,1}
```
</details>
