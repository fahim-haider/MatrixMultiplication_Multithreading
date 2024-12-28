# MatrixMultiplication_Multithreading
## Purpose
Create a matrix multiplication program in C++ and iteratively build more 
functions on top of the simple program. The stages of development is as follows:
    1 - Simple matrix multiplication: using a single thread to perform the task
    2 - Multithreaded matrix multiplication: introducing threads to speed up task
    3 - Tiling implementation: utilize tiling to increase cache hit ratio to speed up task
    4 - Thread pools: utilize thread pools to hand each thread a task to reduce 
    overhead from thread creation (TBC)
    5 - C++ AMP library implemention: become familiar with industry standard tools to 
    parallelize compelx computations

## Concepts Learnt
-Multithreading: using multiple threads to perform matrix multiplication in C++

-Windows semaphores: although not necessary for this application, 
basic implementation of semaphores for result matrix access was established 
before being removed

-Tiling: a method to enhance cache hits to increase performance

-Program Modularity: dividing the source and include files to efficiently 
program the project while minimizing code duplication

-GDB interface with VisualStudioCode; learned alot about the VSCode interface to efficiently 
handle project files utilizing .gitignore, tasks.json and launch.json files

-Extern keyword: efficiently declaring and defining shared variables and matrices
to minimize the number of duplicate declarations produced between src files

-Thread pools??

## Author: github.com/fahim-haider