#include <iostream>
#include <vector>
#include "FCITable.h"

int main (){
    
    int numOfFCIs;
    int lenOfLongestFCI;

    std::cout << "Enter # of FCIs: ";
    std::cin  >> numOfFCIs;

    std::cout << "Enter len of the longest FCI: ";
    std::cin  >> lenOfLongestFCI;

    FCITable FCIBigTable(lenOfLongestFCI);

    /*Entering all FCIs*/
    for(int i=0 ; i<numOfFCIs ; i++){
        
        std::string tempItemset;
        int         tempSupport;

        std::cout << "Enter FCI " << i+1 << " :" << std::endl;
        std::cin >> tempItemset >> tempSupport;

        FCIBigTable.addFCI(tempItemset, tempSupport);
    }
    
    /* recover all FIs from FCIs */
    FCIBigTable.FIRecover();
}
