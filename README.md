# Heap Allocator 

This is a basic heap allocator that makes use of mmap() to allocate memory. Currently I have a basic double linked list of a allocated memory and free memory. It keeps track of the memory and moves the memory between both lists depending on whether it is allocated or not. This is part of my studies :3 

Future goals:  
[ ] Actually freeing memory with munmap()  
[ ] Shrinking chunks  
[ ] Coalease chunks  
[ ] Memory optimisations  
