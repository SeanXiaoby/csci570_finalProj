//
// Created by Boyang Xiao on 12/5/22.
//

#ifndef CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CUTILS_H
#define CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CUTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

class CUtils {
public:
    static bool IsStringNum(std::string strInput);

    static std::string RemoveSpecialChar(std::string strInput);
};


#endif //CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CUTILS_H
