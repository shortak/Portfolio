# Comparison Summary

Below is a list of all the sequence containers and their strengths and weaknesses

|Feature             |Vector            |Deque             |List              |Forward List      |Array             |
|--------------------|:----------------:|:----------------:|:----------------:|:----------------:|:----------------:|
|Dynamic Size        |:white_check_mark:|:white_check_mark:|:white_check_mark:|:white_check_mark:|:x:               |
|Random Access       |:white_check_mark:|:white_check_mark:|:x:               |:x:               |:white_check_mark:|
|Fast Insert at Front|:x:               |:white_check_mark:|:white_check_mark:|:white_check_mark:|:x:               |
|Fast Insert at Back |:white_check_mark:|:white_check_mark:|:white_check_mark:|:white_check_mark:|:x:               |
|Fixed Size          |:x:               |:x:               |:x:               |:x:               |:white_check_mark:|
|Memory Locality     |:white_check_mark:|:x:               |:x:               |:x:               |:white_check_mark:|

NOTE: Memory locality refers to a sort of "spatial" distance between each memory. Containers that store elements in a contiguous block of memoryhave good locality whereas containers that stores their elements in noncontiguous blocks of memory have poor locaility. 

Containers with good locality offer fewer cache misses, better performance and the ability for the CPU to preload relevant data.