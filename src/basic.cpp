//
// Created by Boyang Xiao on 12/5/22.
//

#include "TestClass.h"
#include "CSequenceAligner.h"

int main(){
    std::string strPath = "../datapoints/in1.txt", str1, str2;
    auto pSAobj = new CSequenceAligner();

    pSAobj->ReadTxtFiles(strPath, str1, str2);

    return 0;
}