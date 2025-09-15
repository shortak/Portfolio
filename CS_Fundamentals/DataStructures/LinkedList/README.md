# What is a Linked list?

Linked lists store data in a non-contiguous stretch of memory. Each node of a linked list contains it's relevant data and a pointer to the location in memory that contains the next node (In some cases, node will also have a pointer to the location in memory that contains the previous node, these are known as doubly-linked lists).



## Advantages and Disadvantages

Advantages:
- Allows for efficient insertion (O(1)) 
- Memory is dynamically allocated i.e. the size of the list can grow and is not limited to the size allocated at compile-time
- No wasted memory, i.e. no extra memory is allocated to account for extra growth as you might see with arrays.
- Lists can be much more easily split and merged

Disadvantages:
- Extra memory is needed to store the pointer
- Since list nodes are scattered in memory, there is less cache locality
- No direct access, any random access must be done in O(n) time

# Basic Algorithms

Any complex algorithms can be broken down into basic algorithms. For example, a linked list reversal is simply an application of a "swap" algorithm. The following is a list of basic algorithms pertaining to linked lists.

1. Traversal
2. Traverse to node given data value
3. Access node before a given index
4. Access node after a given index
5. Insert node
6. Delete node
7. Swap nodes

Having a deep understanding of these algorithm will set a solid foundation to develop other algorithms without needing to memorize everything.

# Basic Algorithms cont.

Moving forward, lets clarify some of the terminology used...

"Link node A to B" = make node A's next node node B
"Upstream node" = the node previous to the current
"Downstream node" = the node next to the current

## Traversal

![Traversal Illustration](Traverse.jpg "Traversal Illustration")

Almost all algorithms will use traversal in their implementation. We initialize a pointer type variable for our node object to the head of the list, then increment the pointer by accessing the object's "next" pointer via some sort of loop.

## Traverse to node with a given data value

If you know the data in the node you are looking for (e.g. need to access a node containing a certain key), traverse throught the list while keeping track of the data variabel in the node object the current pointer is looking at. You can use simple logic operators to exit the loop and perform whatever operation you need.

## Access before and after a given index

![Access Illustration](Accessidx.jpg "Access Illustration")

Sometimes you may not know the specific data you are trying to access... in such cases, you may use a provided index (often passed in as a method parameter). It is important to note that given the nature of traversal a given index does not necessarily fall on the node which is why we need algorithms for accessing befoer and after a given index

We can use a for loop to traverse the list an "index" number of times and depending which access method we want, either look at the prev or next node. 

IMPORTANT: if we are using a singly linked list, to keep track of the previous node, we must initialize a prev AND current node so that we can keep track of the last visited node as we traverse.

## Insert node

![Insert Illustration](Insert.jpg "Insert Illustration")

This is a very common algorithm, you will see these in any kind of swap, merge or any pointer manipulation related algorithm. 

1. Initialize a temp node
2. Traverse to where we need to insert
3. Link the temp node to the next node FIRST
4. Link the current node to the temp node
5. DELETE current node**

** Some compilers may take care of garbage collection on their own, but if you are using a lower level langauge, you will need to delete any temp nodes to avoid memory leaks

NOTE: Linking a downstram node or storing it's pointer into another variable is normally the first step in these algorithms. This is to maintain access that block of memory to perform additional operations, like a swap or delete.

## Delete node

![Delete Illustration](Delete.jpg "Delete Illustration")

Deleting a node involves keeping track of 3 nodes, the current node that you're using to traverse, the next and previous nodes. 

1. Traverse to the node you wish to delete 
2. Link the prev and next nodes
3. Delete the current node.

* If you wish to optimize for space, you could access the nodes with current (prev), current->next (current) and current-next->next (next). This way, you need only initialize one pointer-type variable.

## Swap node

![Swap Illustration](Swap.jpg "Swap Illustration")

The swap algorithm is a little more involved...

1. Initialize a prev, current and next pointer.
2. Traverse to the leftmost node invovled in the swap using the current pointer.
3. Store the upstream node (next) into a temp node
4. Link current's node to the temp node's next node
5. Link temp's node to current's node
6. Link prev's node to current's node's next node
7. Delete the temp pointer.
