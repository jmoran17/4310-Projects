# Project 2

## Executable Files are included in the zip of the files

1. **Virtual Memory Paging**  
   Converts a 32-bit virtual address into its corresponding page number and offset based on a user-defined page size.  
   Run by typing  
   ./pageNumber

2. **Disk Scheduling Algorithms**  
   Implements and compares four disk scheduling methods:
   - FCFS (First-Come, First-Served)  
   - SSTF (Shortest Seek Time First)  
   - SCAN (Elevator)  
   - C-SCAN (Circular SCAN)  
   Each algorithm calculates total head movement and number of direction changes when servicing 1,000 cylinder requests across a 5,000-cylinder disk.  
   Run by typing  
   ./diskScheduler <initial head> <previous head>

3. **Logical Block Address Translation**  
   Translates a logical block number into its physical disk address in `<Cylinder, Track, Sector>` format.  
   Run by typing  
   ./logicalBlock