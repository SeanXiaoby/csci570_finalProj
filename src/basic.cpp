//
// Created by Boyang Xiao on 12/5/22.
//

#include <iostream>
#include <string>
#include <cerrno>
#include "CSequenceAligner.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3){
        std::cout<<"Please type in the input path and the output path..."<<std::endl;
        return errno;
    }

    std::string strPath = std::string(argv[1]);
    auto pSAobj = new CSequenceAligner(strPath, strPath);

    cout<< "Final cost is: "<<pSAobj->DoBasicAlignment()<<endl<<endl;

    delete pSAobj;
    pSAobj = nullptr;

    return 0;
}