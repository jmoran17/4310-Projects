#include "sorting.h"
#include <algorithm>

// Define the globals
std::vector<int> arr;
std::vector<int> mergedArr;

// Bubble sort in-place for a range of arr
void bubble(size_t start, size_t end){
    for(size_t i = start; i < end; ++i){
        for(size_t j = start; j < end - (i - start) - 1; ++j){
            if(arr[j] > arr[j+1]){
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Merge two sorted ranges into mergedArray using two pointers
void merge(size_t start1, size_t end1, size_t start2, size_t end2){
    mergedArr.clear();
    mergedArr.reserve((end1-start1)+(end2-start2));

    size_t i = start1, j = start2;
    while(i < end1 && j < end2){
        if(arr[i] < arr[j]) mergedArr.push_back(arr[i++]);
        else mergedArr.push_back(arr[j++]);
    }
    while(i < end1) mergedArr.push_back(arr[i++]);
    while(j < end2) mergedArr.push_back(arr[j++]);
}