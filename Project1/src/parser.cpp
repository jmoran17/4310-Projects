#include <sstream>
#include <fstream>
#include <iostream>
#include "parser.h"

//parse file to get process information
std::vector<Process> parseProcess(const std::string& filename){
    std::vector<Process> processes;
    std::ifstream file(filename);
    
    //throw error if file is not able to opened
    if(!file.is_open()){
        throw std::runtime_error("cannot open file");
    }
    
    std::string line;
    //while loop setting Process information in the p object
    while (std::getline(file, line)){
        std::istringstream ss(line);
        Process p;
        ss >> p.Pid >> p.arrivalTime >> p.burstTime >> p.priority;
        if(ss.fail()){
            throw std::runtime_error("Invalid Line");
        }
        processes.push_back(p);
    }

    return processes;
}