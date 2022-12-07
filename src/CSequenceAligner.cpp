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
    std::cout << "Sequence #1 is: ";
    m_strSequence1.size() >= 30 ? std::cout << "<Sequence too long to display...>" : std::cout << m_strSequence1.size();
    std::cout << std::endl;
    std::cout << "Sequence #2 is: ";
    m_strSequence2.size() >= 30 ? std::cout << "<Sequence too long to display...>" : std::cout << m_strSequence2.size();
    std::cout << std::endl << std::endl;

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

void CSequenceAligner::GetSequences(std::string &strSeq1, std::string &strSeq2) {
    strSeq1 = m_strSequence1;
    strSeq2 = m_strSequence2;
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
    // Initialization step
    for (int i = 0; i < m_strSequence1.size() + 1; ++i) {
        m_vDP[i][0] = i * GAP_PENALTY;
        m_vTrace[i][0] = Up;
    }
    for (int i = 0; i < m_strSequence2.size() + 1; ++i) {
        m_vDP[0][i] = i * GAP_PENALTY;
        m_vTrace[0][i] = Left;
    }

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



//    PrintDP();

    return m_vDP[m_strSequence1.size()][m_strSequence2.size()];
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


