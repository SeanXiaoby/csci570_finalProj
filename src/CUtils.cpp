//
// Created by Boyang Xiao on 12/5/22.
//

#include "CUtils.h"

bool CUtils::IsStringNum(std::string strInput){
    if(strInput.empty())    return false;

    for(auto c : strInput){
        if(!isdigit(c))   return false;
    }

    return true;
}