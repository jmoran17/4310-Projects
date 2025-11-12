# 4310-Projects

Operating Systems Class Projects

## Project 1

This project shows focuses on a multi-threaded sorting application and CPU Process scheduling

1. **Multi-Threaded Sorting Application**

    Takes in a user input from the console and uses multiple threads in order to sort and recombine the users input

2. **CPU Process Scheduling Simulator**

    Implements can be used to compare four CPU process scheduling algorithms
    - FCFS (First-Come, First-Served)
    - SJF (Shortest Job First)
    - Preemptive Priority
    - RR (Round Robin)
    Each algorithm calculates Average wait time, Average response time, Average turnaround time, and CPU utilization percentage

## Project 2

Second project demonstrates key Operating System concepts through three simulation programs:

1. **Virtual Memory Paging**  

   Converts a 32-bit virtual address into its corresponding page number and offset based on a user-defined page size.

2. **Disk Scheduling Algorithms**

   Implements and compares four disk scheduling methods:
   - FCFS (First-Come, First-Served)  
   - SSTF (Shortest Seek Time First)  
   - SCAN (Elevator)  
   - C-SCAN (Circular SCAN)  
   Each algorithm calculates total head movement and number of direction changes when servicing 1,000 cylinder requests across a 5,000-cylinder disk.

3. **Logical Block Address Translation**  

   Translates a logical block number into its physical disk address in `<Cylinder, Track, Sector>` format.

**Deliverables:**  

- Source code (`.cpp` files for each task)  
- Executable files  
- `input.txt` (for Task 2 input)  
- `outputs.pdf` (screenshots of program results)  
- `readme.txt` (instructions on compilation and execution)

---

**Technologies Used:**  
- C++17  
- g++ Compiler  
- Command-line execution on Linux/Windows (MinGW)

---

**Author:** Joseph Moran  
California State Polytechnic University, Pomona  
Fall 2025
