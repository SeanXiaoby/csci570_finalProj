//
// Created by Boyang Xiao on 12/5/22.
//

#ifndef CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CSEQUENCEALIGNER_H
#define CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CSEQUENCEALIGNER_H

#include <string>
#include <vector>
#include <iostream>
#include "stdio.h"
#include <algorithm>
#include <math.h>
#include <fstream>
#include <cassert>
#include "CUtils.h"


class CSequenceAligner {
public:
    CSequenceAligner(){};     // default constructor
    CSequenceAligner(std::string strInputPath, std::string strOutputPath);
    ~CSequenceAligner(){};    // default destructor


    // Read Txt file and save it to the member strings
    void ReadTxtFiles(std::string path);

    // Write strings to the txt file
    void WriteTxtFiles(std::string path, std::string output);

    // Get member sequences
    void GetSequences(std::string &strSeq1, std::string &strSeq2){
        strSeq1 = m_strSequence1;
        strSeq2 = m_strSequence2;}

private:
    // Get delta of error scores for two nitrogenous bases
    int GetDeltaScores(char cInput1, char cInput2);


private:
    std::string m_strSequence1;
    std::string m_strSequence2;


};


#endif //CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CSEQUENCEALIGNER_H
