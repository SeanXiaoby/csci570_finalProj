//
// Created by Boyang Xiao on 12/5/22.
//

#include "CSequenceAligner.h"

CSequenceAligner::CSequenceAligner() {
    m_strSequence1 = "";
    m_strSequence2 = "";
    m_strAlign1 = "";
    m_strAlign2 = "";
    m_bIsAligned = true;
    m_nTotalCost = 0;
}


CSequenceAligner::CSequenceAligner(std::string strInputPath, std::string strOutputPath) {
    ReadTxtFiles(strInputPath);

    m_vDP = std::vector<std::vector<int> >(m_strSequence1.size() + 1, std::vector<int>(m_strSequence2.size() + 1, -1));
    m_vTrace = std::vector<std::vector<enumMove> >(m_strSequence1.size() + 1,
                                                   std::vector<enumMove>(m_strSequence2.size() + 1, Diag));
    m_bIsAligned = false;
    m_nTotalCost = 0;
}


void CSequenceAligner::ReadTxtFiles(std::string path) {
    std::ifstream infile;
    infile.open(path.data());
    assert(infile.is_open());

    std::vector<std::string> vContents;
    std::string strTemp;
    while (getline(infile, strTemp)) {
        vContents.push_back(CUtils::RemoveSpecialChar(strTemp));
        strTemp = "";
    }
    infile.close();

    bool bIsFirst = true;
    std::vector<int> vRepeatTimes1, vRepeatTimes2;
    std::string strSeq1, strSeq2;
    for (auto strItem: vContents) {
        if (CUtils::IsStringNum(strItem)) {
            if (bIsFirst) {
                vRepeatTimes1.push_back(std::stoi(strItem));
            } else {
                vRepeatTimes2.push_back(std::stoi(strItem));
            }
        } else {
            if (strSeq1.empty()) {
                strSeq1 = strItem;
            } else {
                strSeq2 = strItem;
                bIsFirst = false;
            }
        }
    }

    while (!vRepeatTimes1.empty()) {
        int nTimes = vRepeatTimes1[0];
        auto strRepeat = strSeq1;
        if (nTimes == strSeq1.size() - 1) {
            strSeq1 += strRepeat;
        } else {
            strSeq1.insert(nTimes + 1, strRepeat);
        }
        vRepeatTimes1.erase(vRepeatTimes1.begin());
    }

    while (!vRepeatTimes2.empty()) {
        int nTimes = vRepeatTimes2[0];
        auto strRepeat = strSeq2;
        if (nTimes == strSeq2.size() - 1) {
            strSeq2 += strRepeat;
        } else {
            strSeq2.insert(nTimes + 1, strRepeat);
        }
        vRepeatTimes2.erase(vRepeatTimes2.begin());
    }

    m_strSequence1 = strSeq1;
    m_strSequence2 = strSeq2;
}

void CSequenceAligner::WriteTxtFiles(std::string path, std::string output) {

}


int CSequenceAligner::GetAlphaScores(char cInput1, char cInput2) {
    if (cInput1 == cInput2) return 0;

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


int CSequenceAligner::DoBasicAlignment() {
    // Initialization matrix
    for (int i = 0; i < m_strSequence1.size() + 1; ++i) {
        m_vDP[i][0] = i * GAP_PENALTY;
        m_vTrace[i][0] = Up;
    }
    for (int i = 0; i < m_strSequence2.size() + 1; ++i) {
        m_vDP[0][i] = i * GAP_PENALTY;
        m_vTrace[0][i] = Left;
    }

    // Dp formula
    for (int i = 1; i < m_strSequence1.size() + 1; ++i) {
        for (int j = 1; j < m_strSequence2.size() + 1; ++j) {
            auto char1 = m_strSequence1[i - 1], char2 = m_strSequence2[j - 1];
            int nTempCost1 = GetAlphaScores(char1, char2) + m_vDP[i - 1][j - 1];
            int nTempCost2 = m_vDP[i - 1][j] + GAP_PENALTY;
            int nTempCost3 = m_vDP[i][j - 1] + GAP_PENALTY;

//            m_vDP[i][j] = std::min(nTempCost1, std::min(nTempCost2, nTempCost3));
            if (nTempCost1 <= nTempCost2 && nTempCost1 <= nTempCost3) {
                m_vDP[i][j] = nTempCost1;
                m_vTrace[i][j] = Diag;
            } else if (nTempCost2 <= nTempCost1 && nTempCost2 <= nTempCost3) {
                m_vDP[i][j] = nTempCost2;
                m_vTrace[i][j] = Up;
            } else {
                m_vDP[i][j] = nTempCost3;
                m_vTrace[i][j] = Left;
            }
        }
    }

    m_nTotalCost = m_vDP[m_strSequence1.size()][m_strSequence2.size()];

    GenerateAlignments(m_strAlign1, m_strAlign2);

    m_bIsAligned = true;

    return m_nTotalCost;
}

int CSequenceAligner::DoEfficientAlignment() {
    return 0;
}

void CSequenceAligner::PrintDP() {
    if (m_vDP.empty()) {
        std::cout << "The DP matrix is empty..." << std::endl << std::endl;
    }

    int nRow = m_vDP.size(), nCol = m_vDP[0].size();

    for (int i = 0; i < nRow; i++) {
        for (int j = 0; j < nCol; j++) {
            std::cout << m_vDP[i][j] << "\t\t";
        }
        std::cout << std::endl;
    }
}

void CSequenceAligner::GenerateAlignments(std::string &str1, std::string &str2) {

    /* In this function, we use trace matrix to generate the alignment results
     * In the trace matrix, for each position, there are three types of origin:
     * { Diag / Left / Up }
     * --> If it is from diagonal side, then we push back both strings' char to the alignment
     * --> If it is from Left side, then we add a Gap to Alignment#1 and Push char to #2
     * --> If it is from Up side, then we add a Gap to Alignment#2 and Push char to #1
     * When we hit the position <0, 0>, we can terminate the loop
     * */

    int i = m_strSequence1.size(), j = m_strSequence2.size();
    str1 = "";
    str2 = "";
    while (i >= 0 && j >= 0) {
        auto char1 = i > 0 ? m_strSequence1[i - 1] : GAP_CHAR;
        auto char2 = j > 0 ? m_strSequence2[j - 1] : GAP_CHAR;
        if (m_vTrace[i][j] == Diag) {
            str1.push_back(char1);
            str2.push_back(char2);
            i--;
            j--;
        } else if (m_vTrace[i][j] == Left) {
            str1.push_back(GAP_CHAR);
            str2.push_back(char2);
            j--;
        } else {
            str1.push_back(char1);
            str2.push_back(GAP_CHAR);
            i--;
        }

        if (i == 0 && j == 0) {
            break;
        }
    }

    std::reverse(str1.begin(), str1.end());
    std::reverse(str2.begin(), str2.end());
}

int CSequenceAligner::ValidateAlignment(std::string strAlign1, std::string strAlign2) {

    if (strAlign1 == "" && strAlign2 == "") {
        strAlign1 = m_strAlign1;
        strAlign2 = m_strAlign2;
    }

    if (strAlign1.size() != strAlign2.size()) {
        std::cout << "Error: Two alignment strings have different lengths..." << std::endl;
        return -1;
    }

    int nCost = 0;

    for (int i = 0; i < strAlign1.size(); ++i) {
        auto char1 = strAlign1[i], char2 = strAlign2[i];

        if (char1 == GAP_CHAR || char2 == GAP_CHAR) {
            if (char1 == GAP_CHAR && char2 == GAP_CHAR) {
                std::cout << "Error: There are double-gaps in the alignments... " << std::endl;
                return -1;
            } else {
                nCost += GAP_PENALTY;
            }
        } else {
            nCost += GetAlphaScores(char1, char2);
        }
    }

    if (nCost != m_nTotalCost) {
        std::cout << "Error: Alignments' total cost does not add up to the minimum cost... " << std::endl;
        return -1;
    } else {
        std::cout << "Validated! Alignments' total cost adds up to the minimum cost!" << std::endl;
    }

    return nCost;
}

void CSequenceAligner::GetSequences(std::string &strSeq1, std::string &strSeq2) {
    strSeq1 = m_strSequence1;
    strSeq2 = m_strSequence2;
}

void CSequenceAligner::GetAlignments(std::string &strAlign1, std::string &strAlign2) {
    strAlign1 = m_strAlign1;
    strAlign2 = m_strAlign2;
}

void CSequenceAligner::PrintSequences(int nMaxLength) {
    std::cout << "Sequence #1 is: ";
    m_strSequence1.size() >= nMaxLength ? std::cout << m_strSequence1.substr(0, nMaxLength) + "..." : std::cout
            << m_strSequence1.size();
    std::cout << std::endl;
    std::cout << "Sequence #2 is: ";
    m_strSequence2.size() >= nMaxLength ? std::cout << m_strSequence2.substr(0, nMaxLength) + "..." : std::cout
            << m_strSequence2.size();
    std::cout << std::endl << std::endl;
}

void CSequenceAligner::PrintAlignments(int nMaxLength) {
    std::cout << "Alignment #1 is: ";
    m_strAlign1.size() >= nMaxLength ? std::cout << m_strAlign1.substr(0, nMaxLength) + "..." : std::cout
            << m_strAlign1.size();
    std::cout << std::endl;
    std::cout << "Alignment #2 is: ";
    m_strAlign2.size() >= nMaxLength ? std::cout << m_strAlign2.substr(0, nMaxLength) + "..." : std::cout
            << m_strAlign2.size();
    std::cout << std::endl << std::endl;
}


