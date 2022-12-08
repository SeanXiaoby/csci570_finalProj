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

#define GAP_PENALTY 30
#define GAP_CHAR '_'

enum enumMove {
    Diag, Left, Up
};

class CSequenceAligner {
public:
    CSequenceAligner();     // default constructor
    CSequenceAligner(std::string strInputPath, std::string strOutputPath);  // Parametered constructor
    ~CSequenceAligner() {};    // default destructor


    // Read Txt file and save it to the member strings
    void ReadTxtFiles(std::string path);

    // Write strings to the txt file
    void WriteTxtFiles(std::string path, std::string output);

    // Get member sequences
    void GetSequences(std::string &strSeq1, std::string &strSeq2);

    // Get member sequences
    void GetAlignments(std::string &strAlign1, std::string &strAlign2);

    // Do the basic Sequence Alignment
    int DoBasicAlignment();

    // Do the Memory efficient Sequence Alignment
    int DoEfficientAlignment();

    // Print the DP matrix
    void PrintDP();

    // Validate two alignments and get total cost
    int ValidateAlignment(std::string strAlign1 = "", std::string strAlign2 = "");

    // Print Sequences
    void PrintSequences(int nMaxLength = 50);

    // Print Alignment results
    void PrintAlignments(int nMaxLength = 50);

private:
    // Get alpha of error scores for two nitrogenous bases
    int GetAlphaScores(char cInput1, char cInput2);

    // Get Gap penalty
    int GetGapPenalty() {
        return GAP_PENALTY;
    }

    // Generate Alignments from Trace matrix
    void GenerateAlignments(std::string &str1, std::string &str2);

    // Recursion helper function for Divide and conquer solution
    void DChelper();


private:
    std::string m_strSequence1;
    std::string m_strSequence2;

    std::vector<std::vector<int> > m_vDP;
    std::vector<std::vector<enumMove> > m_vTrace;

    int m_nTotalCost;
    std::string m_strAlign1;
    std::string m_strAlign2;

    bool m_bIsAligned;


};


#endif //CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CSEQUENCEALIGNER_H
