#include "sorting.h"
#include "scheduler.h"
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

    std::string filename = "input.txt";
    std::vector<Process> Processes;

    try {
        Processes = parseProcess(filename);
    } catch(const std::exception& e) {
        std::cerr << "Error reading file: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Choose a scheduling algorithm:\n";
    std::cout << "1 - FCFS\n";
    std::cout << "2 - SJF\n";
    std::cout << "3 - Preemptive Priority\n";
    std::cout << "4 - Round Robin\n";
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    Metrics metrics;
    int quantum = 4; // default for RR

    switch(choice) {
        case 1:
            metrics = FCFS(Processes);
            std::cout << "FCFS Results:\n";
            break;
        case 2:
            metrics = SJF(Processes);
            std::cout << "SJF Results:\n";
            break;
        case 3:
            metrics = Preemptive(Processes);
            std::cout << "Preemptive Priority Results:\n";
            break;
        case 4:
            std::cout << "Enter quantum for Round Robin: ";
            std::cin >> quantum;
            metrics = RR(Processes, quantum);
            std::cout << "Round Robin Results:\n";
            break;
        default:
            std::cerr << "Invalid choice.\n";
            return 1;
    }

    // Print metrics
    std::cout << "Average Waiting Time: " << metrics.avgWait << "\n";
    std::cout << "Average Turnaround Time: " << metrics.avgTurn << "\n";
    std::cout << "CPU Utilization: " << metrics.cpuUtil << "%\n";

}
