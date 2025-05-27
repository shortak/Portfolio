# Overview

This directory will contain examples using linked lists (without using the standard library unless otherwise noted).

# Creating a Simple Linked List (list.cpp)

This file contains the construction of a simple linked list and creating member functions to traverse them.

## Creating a List Element and List

For any linked list, we need a structure for the list and the list element (i.e. the nodes). The list will define any core properties (how the list should be initailized, the head and cursor pointers).

The list element on the other hand will be responsible for defining how each element should look. The our file, we have defined a simple struct (i.e. public class) that defines a node as 