//
// Created by Boyang Xiao on 12/5/22.
//

#include "CUtils.h"

bool CUtils::IsStringNum(std::string strInput) {
    if (strInput.empty()) return false;

    for (auto c: strInput) {
        if (!isdigit(c)) return false;
    }

    return true;
}

std::string CUtils::RemoveSpecialChar(std::string strInput) {
    for (auto iter = strInput.begin(); iter != strInput.end();) {
        if (*iter == '\r' || *iter == '\n' || *iter == '\t') {
            iter = strInput.erase(iter);
        } else {
            iter++;
        }
    }

    return strInput;
}
