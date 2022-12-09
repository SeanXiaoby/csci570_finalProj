//
// Created by Boyang Xiao on 12/7/22.
//

#include <iostream>
#include <string>
#include <cerrno>
#include <sys/resource.h>
#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
#include "CSequenceAligner.h"


using namespace std;

// extern int errno;

// getrusage() is available in linux. Your code will be evaluated in Linux OS.

long getTotalMemory() {
    struct rusage usage;
    int returnCode = getrusage(RUSAGE_SELF, &usage);
    if(returnCode == 0) {
        return usage.ru_maxrss;
    } else {
        //It should never occur. Check man getrusage for more info to debug.
        // printf("error %d", errno);
        return -1;
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Please type in the input path and the output path..." << std::endl;
        return errno;
    }

    std::string strPath = std::string(argv[1]);
    auto pObjAligner = new CSequenceAligner(strPath, strPath);
    pObjAligner->PrintSequences(50);


    // ****************My solution and evaluations*************** //

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    auto nCost = pObjAligner->DoEfficientAlignment();

    double totalmemory = getTotalMemory();
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;;
    long microseconds = end.tv_usec - begin.tv_usec; 
    double totaltime = seconds*1000 + microseconds*1e-3; 

    pObjAligner->PrintAlignments(50);
    cout << "Final cost is: " << nCost << endl << endl;

    // ****************My solution and evaluations ends********** //

    std::string strOutPath = std::string(argv[2]);
    pObjAligner->WriteTxtFiles(strOutPath, totaltime, totalmemory);


    printf("Total time:  %f\n", totaltime); 
    printf("Total memory:%f\n", totalmemory);



    delete pObjAligner;
    pObjAligner = nullptr;

    return 0;
}