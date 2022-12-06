//
// Created by Boyang Xiao on 12/5/22.
//

#include "CSequenceAligner.h"

CSequenceAligner::CSequenceAligner(std::string strInputPath, std::string strOutputPath){
    ReadTxtFiles(strInputPath);
    std::cout<<m_strSequence1<<std::endl;
    std::cout<<m_strSequence2<<std::endl<<std::endl;

    for(int i = 0; i < m_strSequence1.size(); ++i){
        std::cout<<m_strSequence1[i]<<", "<<m_strSequence2[i]<<": ";
        std::cout<<GetDeltaScores(m_strSequence1[i], m_strSequence2[i])<<std::endl;
    }

    std::cout<<std::endl;
}


void CSequenceAligner::ReadTxtFiles(std::string path){
    std::ifstream infile;
    infile.open(path.data());
    assert(infile.is_open());

    std::vector<std::string> vContents;
    std::string strTemp;
    while(getline(infile, strTemp)){
        vContents.push_back(strTemp);
        strTemp = "";
    }
    infile.close();

    bool bIsFirst = true;
    std::vector<int> vRepeatTimes1, vRepeatTimes2;
    std::string strSeq1, strSeq2;
    for(auto strItem : vContents){
        if(CUtils::IsStringNum(strItem)){
            if(bIsFirst){
                vRepeatTimes1.push_back(std::stoi(strItem));
            }else{
                vRepeatTimes2.push_back(std::stoi(strItem));
            }
        }else{
            if(strSeq1.empty()){
                strSeq1 = strItem;
            }else{
                strSeq2 = strItem;
                bIsFirst = false;
            }
        }
    }

    while(!vRepeatTimes1.empty()){
        int nTimes = vRepeatTimes1[0];
        auto strRepeat = strSeq1;
        if(nTimes == strSeq1.size()-1){
            strSeq1 += strRepeat;
        }else{
            strSeq1.insert(nTimes+1, strRepeat);
        }
        vRepeatTimes1.erase(vRepeatTimes1.begin());
    }

    while(!vRepeatTimes2.empty()){
        int nTimes = vRepeatTimes2[0];
        auto strRepeat = strSeq2;
        if(nTimes == strSeq2.size()-1){
            strSeq2 += strRepeat;
        }else{
            strSeq2.insert(nTimes+1, strRepeat);
        }
        vRepeatTimes2.erase(vRepeatTimes2.begin());
    }

    m_strSequence1 = strSeq1;
    m_strSequence2 = strSeq2;
}


int CSequenceAligner::GetDeltaScores(char cInput1, char cInput2) {
    if(cInput1 == cInput2)  return 0;

    switch (cInput1) {
        case 'A':
            switch (cInput2) {
                case 'C':
                    return 110;
                case 'G':
                    return 48;
                case 'T':
                    return 94;
            }
        case 'C':
            switch (cInput2) {
                case 'A':
                    return 110;
                case 'G':
                    return 118;
                case 'T':
                    return 48;
            }
        case 'G':
            switch (cInput2) {
                case 'A':
                    return 48;
                case 'C':
                    return 118;
                case 'T':
                    return 110;
            }
        case 'T':
            switch (cInput2) {
                case 'A':
                    return 94;
                case 'C':
                    return 48;
                case 'G':
                    return 110;
            }
    }
    return 0;
}
