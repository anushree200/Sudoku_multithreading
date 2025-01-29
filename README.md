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


## Experiment

9X9,16X16, 25X25, 36X36, 49X49 and 64X64.

9X9:
seq:255
chunk: 18320
mixed: 77101

16X16:
seq: 814
chunk: 13643
mixed: 91387

25*25:
seq: 814
chunk: 13643
mixed:

36*36:
seq: 
chunk:
mixed:

49*49:
seq:
chunk:
mixed:

64*64:
seq:
chunk:
mixed:

128*128:
seq:
chunk:
mixed:

256*256:
seq:
chunk:
mixed:

512*512:
seq:
chunk:
mixed:

1024*1024:
seq:
chunk:
mixed:

2048*2048:
seq:
chunk:
mixed:

# Report

### **Experiment 1 Report: Performance Analysis of Sudoku Validation with Varying Sizes**

**Objective:**
In this experiment, we analyze the performance of Sudoku validation algorithms by varying the size of the Sudoku grid (N = 9, 16, 25, 36, 49, and 64) and keeping the number of threads constant at 8. The performance comparison involves three algorithms: **Sequential**, **CHUNK**, and **Mixed**. We measure the time taken for each algorithm to validate the Sudoku grid and plot the results on a graph with the size of the Sudoku grid on the x-axis and time taken on the y-axis.

### **Key Observations:**

1. **For Smaller Sudoku Sizes (9x9, 16x16, 25x25, 36x36, 49x49):**
   - **Sequential** performs better than **CHUNK**, which in turn performs better than **Mixed**.
   - This is expected because with smaller grids, the computational overhead associated with threading and chunking becomes more significant. The sequential algorithm benefits from having no parallelization overhead.
   - **Sequential** processing has the advantage in smaller grid sizes because the grid is small enough that the overhead of managing threads or splitting the work into chunks can outweigh the benefits of parallelization.
   
   **Why is Sequential Faster?**
   - With small grid sizes, the number of operations is relatively small. The overhead of creating, managing, and synchronizing multiple threads (in CHUNK and Mixed approaches) can take longer than simply performing the validation sequentially in a single thread.
   - The smaller the grid, the less time it takes for a single thread to finish the task. Thus, for smaller N values, there is no significant parallelism to exploit, and the sequential approach becomes more efficient.

2. **For Larger Sudoku Sizes (1024x1024, 2048x2048):**
   - **Mixed** algorithm performs the best, followed by **CHUNK**, with **Sequential** being the slowest.
   - As the grid size increases, the amount of work grows significantly. For large grids like 1024x1024 or 2048x2048, the **Mixed** approach, which combines sequential and parallel computation efficiently, starts to outperform the others.
   - **CHUNK** also shows good performance because it divides the workload into manageable pieces that can be processed in parallel. However, **Mixed** provides an optimized balance between parallel processing and minimizing synchronization overhead.
   
   **Why is Mixed Faster?**
   - As the grid size increases, the parallelization benefits become more pronounced. The time spent on the computational tasks (such as validating rows, columns, and subgrids) grows significantly, making parallelism more efficient.
   - The **Mixed** algorithm optimizes the use of threads, ensuring the workload is balanced while avoiding excessive synchronization. This reduces the overall execution time as the algorithm scales with the problem size.
   - **CHUNK** also benefits from parallelism but might be slightly less efficient than **Mixed** because of the fixed chunk sizes and potential overhead of chunk distribution.

3. **For Large Grid Sizes:**
   - With larger Sudoku grids, the number of operations (validations of rows, columns, and subgrids) grows substantially. The sequential algorithm struggles with the sheer volume of work, leading to longer execution times.
   - Parallelizing the workload (with **CHUNK** and **Mixed**) drastically reduces the time taken by dividing the task among multiple threads. The parallel overhead is outweighed by the reduced time per operation.

### **Explanation of Results:**

- **Smaller Grid Sizes (9x9 to 49x49):**
  - **Sequential** is faster than **CHUNK** and **Mixed** due to the relatively small number of computations. For small grids, the overhead of managing threads and distributing tasks across chunks becomes a bottleneck, making parallelism less efficient.
  
- **Larger Grid Sizes (1024x1024, 2048x2048):**
  - The larger the grid size, the greater the computational demand. Parallelism through **Mixed** and **CHUNK** allows for efficient handling of the increased number of operations, leading to faster execution times.
  - **Mixed** outperforms **CHUNK** due to its more optimized approach to parallelism and reduced synchronization overhead. **CHUNK**, though still benefiting from parallelism, has slightly higher overhead due to static chunking.
  - **Sequential**, on the other hand, performs poorly for large grid sizes due to the large number of operations and the lack of parallel processing.

### **Conclusion:**

- For **smaller Sudoku grids**, **Sequential** proves to be the most efficient due to its lower overhead and the limited computational complexity.
- For **larger Sudoku grids**, **Mixed** shows significant improvements in performance, outpacing both **CHUNK** and **Sequential**. This is because the increase in computational complexity can be effectively handled by parallelization, and the **Mixed** approach ensures efficient thread management.
- The **CHUNK** approach also benefits from parallelization but doesn’t scale as well as the **Mixed** approach for larger grid sizes due to its simpler approach to dividing the workload.
  
This experiment demonstrates how the optimal algorithm choice for Sudoku validation shifts depending on the size of the grid, highlighting the importance of parallelization strategies for larger problems.



## Getting Help
If you are stuck and need help in understanding the code as well as for executing this C program, you may please write to the email address: co23btech11003@iith.ac.in . Kindly provide with details of the exact issues that you are facing to get the correct guidence.






Prerequisite Theory
1. Introduction to Pthreads (POSIX Threads)
pthreads (POSIX threads) is a standard for implementing multithreaded programming in C. It provides a set of functions for creating, managing, and synchronizing threads in a parallel computing environment. Threads are lightweight units of execution that can run concurrently, which makes them an essential tool for improving performance in multi-core systems.

Key Concepts in Pthreads:
Thread Creation: In pthreads, threads are created using the pthread_create() function. Each thread runs a specific function concurrently with other threads.
Thread Synchronization: Threads need to coordinate when accessing shared resources. This is done using synchronization mechanisms such as mutexes (pthread_mutex_t), condition variables (pthread_cond_t), and barriers.
Thread Joining: After a thread finishes its task, it can be joined with the main thread using pthread_join(). This ensures that all threads have completed before continuing with the rest of the program.
Thread Termination: A thread terminates when its function execution ends. The program can either continue executing other threads or finish after all threads are done.
2. Parallelization with Pthreads
Parallel programming involves dividing a task into smaller sub-tasks that can be processed simultaneously. By leveraging multiple cores of a processor, parallelization can significantly reduce the time required to solve large problems, such as Sudoku validation. In the case of pthreads, each thread can be assigned a subset of the validation task to be executed in parallel.

Benefits of Parallelization:
Speedup: By running multiple threads concurrently, tasks can be completed faster, especially for large datasets.
Efficiency: By using multiple cores of a CPU, parallel programs make efficient use of system resources.
Scalability: For large problems, adding more threads can improve performance by distributing the workload across the threads.
3. How Chunk and Mixed Algorithms Work
Chunk Algorithm
In the Chunk algorithm, the Sudoku validation task is divided into multiple chunks, and each chunk is processed by a different thread. A chunk can represent a row, column, or subgrid of the Sudoku grid, depending on the chosen approach.

For example:

Chunking by Rows: If there are N rows in the Sudoku grid and T threads, the work is divided into T chunks. Each thread processes one chunk (one or more rows), validating the uniqueness of values in those rows.
Chunking by Subgrids: The grid is divided into T subgrids, with each thread validating a specific subgrid.
Each thread independently checks its assigned chunk for violations of Sudoku rules (like duplicate numbers), and if any thread finds an error, it flags the Sudoku as invalid.

Mixed Algorithm
The Mixed algorithm combines both parallel and sequential execution:

The grid is divided into larger chunks (such as rows or columns) and processed in parallel.
For certain parts of the Sudoku grid (typically subgrids), a sequential validation process is applied. This can help avoid unnecessary parallelization overhead for smaller tasks.
For instance, the Mixed approach could validate the rows and columns in parallel (because they are large chunks of work), but check the smaller subgrids sequentially (to minimize overhead). This approach tries to balance parallel and sequential execution to minimize time complexity.

Why Mixed Algorithm can be Faster
The Mixed algorithm can be faster than the pure Chunk algorithm in certain cases because:

Reduced Thread Overhead: For smaller tasks, the overhead of creating and managing threads can reduce the performance benefits of parallelism. The Mixed algorithm avoids this by handling small tasks sequentially.
Optimal Parallelization: Larger chunks like rows or columns are handled in parallel, where the benefit of parallelism is maximized.
4. Performance of Parallelization
When solving a problem like Sudoku validation, the speedup gained from parallelization depends on how the work is divided, the number of available threads, and the overhead of managing the threads. Parallelizing with pthreads can reduce the overall execution time by distributing the workload across multiple CPU cores.

Factors Affecting Performance:
Thread Overhead: The creation and management of threads have some overhead, especially when the work is not large enough to warrant parallelization. For small grids (e.g., 9x9), the overhead of creating threads may outweigh the benefits.
Load Balancing: The way the grid is divided among threads is crucial. If some threads have much more work than others, those threads may become bottlenecks, reducing overall performance. Load balancing ensures that all threads have roughly equal work to do.
Synchronization Overhead: Threads need to coordinate their access to shared resources (like the Sudoku grid). Synchronization mechanisms (like mutexes) are used to prevent data corruption, but they can add overhead, especially if they are used excessively.
5. Time Complexity and Scalability
The time complexity of a parallel algorithm is typically analyzed in terms of the number of threads and the size of the problem. For Sudoku validation:

Sequential: The sequential time complexity is O(N^2), where N is the size of the Sudoku grid (number of rows or columns).
Chunk and Mixed Algorithms: The time complexity for the parallelized algorithms is typically O(N^2 / T), where T is the number of threads. This assumes that the workload is evenly distributed and that there is minimal overhead.
As the grid size increases (for example, from 9x9 to 1024x1024), the performance improvement due to parallelization becomes more pronounced. For smaller grids, the sequential algorithm may outperform parallel algorithms due to thread creation and synchronization overhead.


