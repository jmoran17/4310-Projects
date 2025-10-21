#include "sorting.h"
#include <iostream>
#include <thread>
#include <mutex>

int main(){
    // Initialize the array
    arr = {7,8,5,10,20,15,4,3,2,1,40};
    size_t mid = arr.size() / 2;

    // Start sorting threads (sort each half concurrently)
    std::thread t1(bubble, 0, mid);
    std::thread t2(bubble, mid, arr.size());

    t1.join();
    t2.join();

    // Start merging thread
    std::thread t3(merge, 0, mid, mid, arr.size());
    t3.join();

    // Print sorted result
    std::cout << "Sorted array:\n";
    for(const auto& num : mergedArr){
        std::cout << num << " ";
    }
    std::cout << std::endl;
}