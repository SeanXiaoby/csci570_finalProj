//
// Created by Boyang Xiao on 12/5/22.
//

#include <iostream>
#include <string>
#include <cerrno>
#include "CSequenceAligner.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Please type in the input path and the output path..." << std::endl;
        return errno;
    }

    std::string strPath = std::string(argv[1]);
    auto pObjAligner = new CSequenceAligner(strPath, strPath);
    pObjAligner->PrintSequences(50);

    auto nCost = pObjAligner->DoBasicAlignment();

    pObjAligner->PrintAlignments(50);

    cout << "Final cost is: " << nCost << endl << endl;

    pObjAligner->ValidateAlignment();

    std::string strOutPath = std::string(argv[2]);
    pObjAligner->WriteTxtFiles(strOutPath);

    delete pObjAligner;
    pObjAligner = nullptr;

    return 0;
}