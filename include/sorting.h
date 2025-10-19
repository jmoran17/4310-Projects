#ifndef SORTING_H
#define SORTING_H

#include <vector>
#include <cstddef>  // for size_t

// Global arrays for multithreaded sorting
extern std::vector<int> arr;       // original array
extern std::vector<int> mergedArr; // final merged array

// Functions
void bubble(std::size_t start, std::size_t end);
void merge(std::size_t start1, std::size_t end1, std::size_t start2, std::size_t end2);

#endif
