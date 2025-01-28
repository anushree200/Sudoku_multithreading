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
- input.txt : The input file which contains the value of N, K and the sudoku to be validated
- ReadMe.pdf : The current file
- Report.pdf : Report giving the analysis of the experiment done



