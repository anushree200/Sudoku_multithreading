SUDOKU_VALIDATION_USING_MULTITHREADING


CONTENTS
Assignment Description
What the Application Does
Technologies Used
Hardware Requirements to Compile and Run this Program
Operating System and its requirements
Installation of the C Compiler
Installing pthreads
Contents of the folder
About the Code
Executing the program
Creating a Makefile
Prerequisite Theory
Getting Help



ASSIGNMENT DESCRIPTION
This assignment focuses on developing a multithreaded program to validate Sudoku solutions effectively. The objective is to use pthreads to parallelize the validation process for rows, columns, and subgrids of an N * N Sudoku puzzle. By implementing two distinct workload distribution methods—Chunk and Mixed—students will analyze the performance of multithreading across various puzzle sizes and thread counts. The assignment also emphasizes experimental analysis by comparing the time taken for validation under different configurations and methods.




WHAT THE APPLICATION DOES
The application reads a Sudoku puzzle from an input file and validates whether the solution is correct by ensuring that all rows, columns, and subgrids contain unique values from 1 to N, where N is the puzzle's dimension. It uses multithreading to divide the validation tasks among threads, employing Chunk and Mixed methods for workload distribution. The program outputs the validation status of each thread's assigned task and finally determines whether the entire Sudoku puzzle is valid or invalid. It also records and reports the total execution time for performance analysis.



TECHNOLOGIES USED
C Language: The program is implemented in C, utilizing its robust features for system-level programming and performance-critical tasks. Pthreads Library: Used for creating and managing multiple threads, enabling parallel execution of Sudoku validation tasks.



HARDWARE REQUIREMENTS TO COMPILE AND RUN THIS PROGRAM
Processor: A multi-core processor is recommended to effectively utilize multithreading.
RAM: A minimum amount of RAM sufficient to handle the Sudoku puzzle and thread operations.
Storage: Adequate hard disk space to store the program, input, and output files.
Monitor: Required to view the output and monitor program execution.
Keyboard: Necessary to compile and execute the code.



OPERATING SYSTEM AND ITS REQUIREMENTS
This code can run on any operating system that supports a C compiler.

Linux: A Linux terminal with the GCC compiler installed is sufficient to compile and run the program. 
Windows: The MinGW (Minimalist GNU for Windows) environment can be used during development, providing a collection of GNU tools including the GCC compiler.




INSTALLATION OF C COMPILER
Windows [not recommended]
MinGW (Minimalist GNU for Windows) freeware which is the collection of GNU Compiler collection (GCC) was used to install the gcc compiler for windows.
The gcc compiler was used to compile and execute this C code.
If you want to replicate the environment, you can download the MinGW from MinGW
After installing MinGW, select the GCC compiler during setup.
Add the gcc to the windows environment variable so that the gcc command can be invoked from anywhere.

Linux
Linux: The program requires GCC, which is typically pre-installed. If not, install it using:
sudo apt update 
sudo apt install build-essential gcc --version



INSTALLING PTHREADS
Windows
Pthreads is not natively available on Windows, so you need to use an external library like pthreads-win32.

And When compiling the program, use the -lpthread flag to link the pthreads library.

Linux
Pthreads is usually pre-installed with GCC on Linux systems. To confirm, check for the pthread.h file in the system headers: find /usr/include -name pthread.h




CONTENTS OF THE FOLDER
Assign1src1-CO23BTECH11003.c : The source code which contains the chunk method
Assign1src2-CO23BTECH11003.c : The source code which contains the mixed method
Assign1src3-CO23BTECH11003.c : The source code which contains the sequential method
inp.txt : The input file which contains the value of N, K and the sudoku to be validated
Assgn1Readme-CO23BTECH11003.txt : The current file
Assgn1Report-CO23BTECH11003.pdf : Report giving the analysis of the experiments done and brief explanation of my approach coding Chunk, Mixed and Sequential methods [Without Early termination]. 
Earlytermination-Assign1src1-CO23BTECH11003.c : The source code which contains the chunk method with early termination.
Makefile : To compile all the src files at once



ABOUT THE CODE
This program implements parallel Sudoku validation using pthreads, offering two approaches: CHUNK-based and MIXED-based thread distribution. 
In the CHUNK-based approach, the Sudoku grid is divided into contiguous chunks of rows, columns, and subgrids, where each thread is assigned a fixed, continuous segment to validate independently. 
This reduces communication overhead, as each thread only processes its designated section. 
The algorithm reads the N × N grid and number of threads K from inp.txt, assigns K1 threads to validate rows, K2 to columns, and K3 to subgrids, logs the validation results with timestamps, and sorts and writes them to outputchunk.txt along with the final validity status and execution time.

In contrast, the MIXED-based approach distributes the workload cyclically, ensuring more balanced processing. 
Instead of assigning contiguous chunks, threads validate rows, columns, and subgrids in a round-robin fashion, reducing idle time. 
The algorithm follows similar steps: reading the Sudoku grid, distributing validation tasks cyclically among K1, K2, and K3 threads, storing results with timestamps, and writing the sorted logs to outputmixed.txt. 

In addition to the CHUNK and MIXED parallel approaches, a SEQUENTIAL validation method was also implemented for experimentation. In this approach, a single thread processes the entire Sudoku grid without parallelization. 
The algorithm reads the N × N grid from input.txt, sequentially checks all rows, columns, and subgrids for duplicates, and logs the results in outputseq.txt. It records the total execution time and writes whether the Sudoku is valid or invalid. 
Since this method does not utilize multithreading, it serves as a baseline for performance comparison against the CHUNK and MIXED implementations. 

In addition, I have implemented Early termination of Chunk method, once after finding out that any of the row or column or subgrid has been invalid. I have implemented this without using
mutex deadlocks, So there is high possibility of thread synchronization errors due to race conditions.
What changes made? - Implemented additional logic at places where new threads are created to check if the sudoku is still valid [is_valid is  global variable used] , also check inside the runner functions, if it is not valid then thread exits using the pthread_exit(0) command. 
We can see that the time of execution is less than the previous implementation of Chunk method due to early termination.
 

EXECUTING THE PROGRAMS
To compile and run your program, you typically enter the following command in the command prompt:

gcc Assignsrc1-CO23BTECH11003.c -o out -lpthread -lm

and then, run the program with:

./out

Similarly for the other two source files.

Make sure inp.txt is in the same folder as the source files.
But it obviously seems a long command as there are many source files to be executed at the same time. So here is a better option.



CREATING A MAKEFILE
Instead of typing a long command every time, you can use a Makefile to simplify the compilation process. A Makefile automates the build process, especially useful when dealing with multiple source files.
Create a Makefile in your project directory with the following content:

final:

<tab>gcc Assignsrc3-CO23BTECH11003.c -o out -lpthread -lm
<tab>./out
<tab>gcc Assignsrc1-CO23BTECH11003.c -o out -lpthread -lm
<tab>./out
<tab>gcc Assignsrc2-CO23BTECH11003.c -o out -lpthread -lm
<tab>./out

Then:

Save the Makefile in the same directory as your source files.
Open a terminal in UBUNTU.
Navigate to your project directory.
Type make and press Enter. This will compile your project.
And you can see the 3 output files for each of the method in the folder.



PREREQUISITE THEORY
Pthreads (POSIX Threads) is a standard for implementing multithreaded programming in C. It provides a set of functions for creating, managing, and synchronizing threads in a parallel computing environment. Threads are lightweight units of execution that can run concurrently, which makes them an essential tool for improving performance in multi-core systems.

Thread Synchronization: The flag array ensures that threads execute in a controlled order when needed.

Thread Creation: In pthreads, threads are created using the pthread_create() function. Each thread runs a specific function concurrently with other threads.

Thread Joining: After a thread finishes its task, it can be joined with the main thread using pthread_join(). This ensures that all threads have completed before continuing with the rest of the program.

Parallelization with Pthreads Parallel programming involves dividing a task into smaller sub-tasks that can be processed simultaneously. By leveraging multiple cores of a processor, parallelization can significantly reduce the time required to solve large problems, such as Sudoku validation. In the case of pthreads, each thread can be assigned a subset of the validation task to be executed in parallel.


How Chunk and Mixed Algorithms Work?

Chunk Method
In the chunk method, a thread is assigned consecutive rows, columns or subgrids to validate. For example, if the number of rows is R and the number of threads for validating rows is K1, the chunk size p is calculated as p = R / K1.
Thread 1 will validate rows 1 to p
Thread 2 will validate rows p+1 to 2p
Thread 3 will validate rows 2p+1 to 3p
This continues for all threads.
The same allocation method is applied for columns and subgrids.

Mixed Method
In the mixed method, instead of assigning consecutive rows, columns, or subgrids, the workload is distributed evenly among the threads in a cyclic manner. For example, if the number of rows is R and the number of threads for validating rows is K1:
Thread 1 will validate rows 1, K1+1, 2K1+1, ...
Thread 2 will validate rows 2, K1+2, 2K1+2, ...
This pattern continues for all threads.
This approach tries to balance parallel and sequential execution to minimize time complexity.

Time Complexity:
Single-threaded validation takes O(N²).
Multithreaded execution distributes work, reducing validation time proportionally to the number of threads.

Parallel Speedup:
More threads reduce execution time, but excessive threads can cause overhead.
Efficient workload distribution (Chunk vs. Mixed) optimizes thread execution.



GETTING HELP
If you are stuck and need help in understanding the code as well as for executing this C program, you may please write to the email address: co23btech11003@iith.ac.in . Kindly provide with details of the exact issues that you are facing to get the correct guidance.


