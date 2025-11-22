/*
 * CS4310 – Operating Systems
 * Project 2 – Task 1: Virtual Memory Paging
 *
 * Description:
 *   Converts a 32-bit virtual address into its page number
 *   and offset, based on a user-entered page size (in KB).
 * 
 */

#include <iostream>
using namespace std;

int main() {
    unsigned int virtualAddress;
    int pageSizeKB;

    cout << "Enter page size (in KB): ";
    cin >> pageSizeKB;

    cout << "Enter virtual address (in decimal): ";
    cin >> virtualAddress;

    // Convert KB to bytes
    unsigned int pageSizeBytes = pageSizeKB * 1024;

    // Calculate page number and offset
    unsigned int pageNumber = virtualAddress / pageSizeBytes;
    unsigned int offset = virtualAddress % pageSizeBytes;

    cout << "The address " << virtualAddress
         << " contains: page number = " << pageNumber
         << " offset = " << offset << endl;

    return 0;
}
