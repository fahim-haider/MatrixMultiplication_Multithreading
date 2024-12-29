# MatrixMultiplication_Multithreading
## Purpose
Create a matrix multiplication program in C++ and iteratively build more 
functions on top of the simple program. The stages of development is as follows:

    1 - Simple matrix multiplication: using a single thread to perform the task

    2 - Multithreaded matrix multiplication: introducing threads to speed up task

    3 - Tiling implementation: utilize tiling to increase cache hit ratio to speed up task

    4 - C++ AMP library implemention: become familiar with industry standard tools to 
    parallelize compelx computations (TO DO)

## Concepts Learnt
-Multithreading: Multiple threads were used in C++ to complete the computations faster. The 
effect of overhead from thread creation and destruction was observed. In addition, increasing 
the number of threads decreased the computation time, and using multiple threads was always 
faster than using a single thread as seen in the results.

-Windows semaphores: Basic semaphore structures were designed to restrict access 
to the result matrix to one thread at a time. They were not necessary since every
thread was responsible for their own part of the matrix so they were left commented. 
When they were included in the program, they would increase the time to complete the 
computations since the threads would need to wait for the locking and unlocking 
overhead.

-Tiling: The matrices were divided into small blocks (tiles) to limit the data accesses
of the matrix to small regions in memory over one iteration. Doing so improves the cache 
hit ratio by accessing data in one region multiple times before moving to the next and 
replacing the cache contents.

-Program Modularity: The program was divided based on the method of matrix multiplication 
used. The source and header files were divided into folders to efficiently program the 
project while minimizing code duplication from repetitive tasks such as filling the matrices.

-GDB interface with VisualStudioCode: I learned alot about the VSCode interface to efficiently 
compile and debug the program by utilizing the .gitignore, tasks.json and launch.json files

-Extern keyword: The extern keyword was used when defining variables and matrices to
minimize the number of duplicate declarations produced between the source files.

## Result Findings
There were two main program tasks: fill the input matrices with random numbers, and 
calculate the product then store it in the result matrix. The results of the project 
can be found in the Results.md file!

-Simple matrix multiplication
The slowest out of all 4 methods attempted for both tasks. The matrix fill task took 
a long time since each element of both input matrices needed to be filled. The product 
calculation also took a long time since data needed to be accessed and manipulated 
for each index.

-Matrix multiplication using multiple threads
This method was faster than the simple algorithm since it efficiently divided the tasks 
by threads. The matrix fill task was faster since each thread had its own column to fill. 
The calculation task was faster for the same reason.

-Simple matrix multiplication using tiling
This method was surprisingly faster than multithreading for the calculation task. For the 
matrix fill task, tiling did not have any effect since the program is writing data and 
not accessing data so it is similar to the simple algorithm. The calculation task being faster 
in this simple tiling algorithm suggests that cache inefficiency is a major bottleneck for this 
application.

-Matrix multiplication using multiple threads and tiling
This method was fastest! Again, the matrix fill task was similar to the multithreading algorithm 
for the same reason mentioned above. With the addition of tiling, the cache was used much more 
efficiently which lead to the calculation time being the best across all algorithms.

## Program Execution Instructions
Simply run '.\program.exe' in the terminal and the results will be printed to the Results.md file.
Your results may vary from mine because of different systems, so please do share your findings!

## Author: github.com/fahim-haider