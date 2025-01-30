# Sudoku_multithreading

## CONTENTS

## ASSIGNMENT DESCRIPTION
This assignment focuses on developing a multithreaded program to validate Sudoku solutions effectively. The objective is to use pthreads to parallelize the validation process for rows, columns, and subgrids of an N * N Sudoku puzzle. By implementing two distinct workload distribution methods—Chunk and Mixed—students will analyze the performance of multithreading across various puzzle sizes and thread counts. The assignment also emphasizes experimental analysis by comparing the time taken for validation under different configurations and methods. 

## What the Application Does

The application reads a Sudoku puzzle from an input file and validates whether the solution is correct by ensuring that all rows, columns, and subgrids contain unique values from 1 to N, where N is the puzzle's dimension. It uses multithreading to divide the validation tasks among threads, employing Chunk and Mixed methods for workload distribution. The program outputs the validation status of each thread's assigned task and finally determines whether the entire Sudoku puzzle is valid or invalid. It also records and reports the total execution time for performance analysis.


## Technologies Used

C Language: The program is implemented in C, utilizing its robust features for system-level programming and performance-critical tasks.
Pthreads Library: Used for creating and managing multiple threads, enabling parallel execution of Sudoku validation tasks.


### Hardware Requirements to Compile and Run this Program

- Processor: A good processor with a decent number of cores to effectively utilize multithreading for parallel execution.  
- RAM: A minimum amount of RAM sufficient to handle the Sudoku puzzle and thread operations.  
- Storage: Adequate hard disk space to store the program, input, and output files.  
- Monitor: Required to view the output and monitor program execution.  
- Keyboard: Necessary to compile and execute the code.

## Operating System and its requirements
This code can run on any operating system that supports a C compiler.

Linux: A Linux terminal with the GCC compiler installed is sufficient to compile and run the program.
Windows: The MinGW (Minimalist GNU for Windows) environment was used during development, providing a collection of GNU tools including the GCC compiler.



## Installation of the C Compiler
### Windows
MinGW (Minimalist GNU for Windows) freeware which is the collection of GNU Compiler collection (GCC)
was used to install the gcc compiler for windows. 

The gcc compiler was used to compile and execute this C code.

If you want to replicate the environment, you can download the MinGW from 
[MinGW](https://sourceforge.net/projects/mingw/)

After installing the MinGW, you can select the gcc compiler and the same will get installed.

Add the gcc to the windows environment variable so that the gcc command can be invoked from anywhere. 

### Linux

Open the terminal and run the following commands to install GCC:
`sudo apt update
sudo apt install build-essential
gcc --version`

This ensures GCC is installed and configured properly.

## Installing pthreads 

### Windows
Pthreads is not natively available on Windows, so you need to use an external library like pthreads-win32.

And When compiling the program, use the -lpthread flag to link the pthreads library.

### Linux
Pthreads is usually pre-installed with GCC on Linux systems. To confirm, check for the pthread.h file in the system headers:
`find /usr/include -name pthread.h`


## Contents of the folder
- Assignsrc1-CO23BTECH11003.c : The source code which contains the chunk method
- Assignsrc2-CO23BTECH11003.c : The source code which contains the mixed method
- Assignsrc3-CO23BTECH11003.c : The source code which contains the sequential method
- inp.txt : The input file which contains the value of N, K and the sudoku to be validated
- Assgn1Readme-CO23BTECH11003.txt : The current file
- Assgn1Report-CO23BTECH11003.pdf : Report giving the analysis of the experiment done


## About the Code

This program implements parallel Sudoku validation using POSIX threads (pthreads), offering two approaches: CHUNK-based and MIXED-based thread distribution. In the CHUNK-based approach, the Sudoku grid is divided into contiguous chunks of rows, columns, and subgrids, where each thread is assigned a fixed, continuous segment to validate independently. This reduces communication overhead, as each thread only processes its designated section. The algorithm reads the `N × N` grid and number of threads `K` from `input.txt`, assigns `K1` threads to validate rows, `K2` to columns, and `K3` to subgrids, logs the validation results with timestamps, and sorts and writes them to `outputchunk.txt` along with the final validity status and execution time.  

In contrast, the MIXED-based approach distributes the workload cyclically, ensuring more balanced processing. Instead of assigning contiguous chunks, threads validate rows, columns, and subgrids in a round-robin fashion, reducing idle time. The algorithm follows similar steps: reading the Sudoku grid, distributing validation tasks cyclically among `K1`, `K2`, and `K3` threads, storing results with timestamps, and writing the sorted logs to `outputmixed.txt`. While CHUNK-based validation is efficient for large Sudoku grids with sufficient threads, it may lead to workload imbalance. MIXED-based validation ensures a more even distribution of tasks, but requires synchronization to handle cyclic assignments. Both implementations leverage pthreads for concurrency and log sorting for orderly output, ensuring efficient parallel Sudoku validation.

In addition to the CHUNK and MIXED parallel approaches, a SEQUENTIAL validation method was also implemented for experimentation. In this approach, a single thread processes the entire Sudoku grid without parallelization. The algorithm reads the `N × N` grid from `input.txt`, sequentially checks all rows, columns, and subgrids for duplicates, and logs the results in `outputseq.txt`. It records the total execution time and writes whether the Sudoku is valid or invalid. Since this method does not utilize multithreading, it serves as a baseline for performance comparison against the CHUNK and MIXED implementations. While SEQUENTIAL validation is simpler and avoids thread synchronization overhead, it is significantly slower for large grids due to the lack of concurrency.


## Executing the program

To compile and run your program, you typically enter the following command in the command prompt:

`gcc Assignsrc1-CO23BTECH11003.c -o out -lm`

and then, run the program with:

`./out`

Similarly for the other two source files.

Make sure inp.txt is in the same folder as the source files.




## Getting Help
If you are stuck and need help in understanding the code as well as for executing this C program, you may please write to the email address: co23btech11003@iith.ac.in . Kindly provide with details of the exact issues that you are facing to get the correct guidence.



