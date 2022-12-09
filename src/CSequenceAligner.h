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
    void WriteTxtFiles(std::string path, int nTotalTime = -1, int nTotalMemory = -1);

    // Get member sequences
    void GetSequences(std::string &strSeq1, std::string &strSeq2);

    // Get member sequences
    void GetAlignments(std::string &strAlign1, std::string &strAlign2);

    // Do the basic Sequence Alignment
    int DoBasicAlignment();

    // Do the Memory efficient Sequence Alignment
    int DoEfficientAlignment();

    // Validate two alignments and get total cost
    int ValidateAlignment(std::string strAlign1 = "", std::string strAlign2 = "");

    // Print Sequences
    void PrintSequences(int nMaxLength = 50);

    // Print Alignment results
    void PrintAlignments(int nMaxLength = 50);

public:
    // Get alpha of error scores for two nitrogenous bases
    int GetAlphaScores(char cInput1, char cInput2);

    // Get Gap penalty
    int GetGapPenalty() {
        return GAP_PENALTY;
    }

    // Generate Alignments from Trace matrix
    void GenerateAlignments(std::string &str1, std::string &str2, std::vector<std::vector<enumMove> > vTrace);

    // Print the DP matrix
    void PrintDP(std::vector<std::vector<int> > vDP);

    // Print the Trace matrix
    void PrintTrace(std::vector<std::vector<enumMove> > vDP);

    // Recursion helper function for Divide and conquer solution
    std::pair<std::string, std::string> DChelper(std::string strSeq1, std::string strSeq2);

    // Standard alignment for DC solution
    std::pair<std::string, std::string> StandardAlignment(std::string strSeq1, std::string strSeq2);

    // Forward linear space alignment for DC
    std::vector<int> ForwardAlignment(std::string strSeq1, std::string strSeq2);

    // Backward linear space alignment for DC
    std::vector<int> BackwardAlignment(std::string strSeq1, std::string strSeq2);

    // Calculate whole cost
    int CalculateCost(std::string strAlign1, std::string strAlign2);


public:
    std::string m_strSequence1;
    std::string m_strSequence2;

    int m_nTotalCost;

    std::string m_strAlign1;
    std::string m_strAlign2;

};


#endif //CSCI_570_FINALPROJECT_SEQUENCE_ALIGNMENT_CSEQUENCEALIGNER_H
