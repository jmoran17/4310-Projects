#include <iostream>

int main(){
    //read inputs
    int pageSizeKB;
    unsigned int virtualAddress;

    std::cout<<"Please enter Virtual Address (Decimal): ";
    std::cin>>virtualAddress;
    std::cout<<"Please enter page size (kb): ";
    std::cin>>pageSizeKB;

    unsigned int pageSizeBytes = pageSizeKB * 1024;

    unsigned int pageNumber = virtualAddress / pageSizeBytes;
    unsigned int offset = virtualAddress % pageSizeBytes;
    
    std::cout<< "The address"<< virtualAddress
        <<" Contains: page number = " << pageNumber
        <<" offset = "<< offset<<std::endl;
    
    return 0;
}
