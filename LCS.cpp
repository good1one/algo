#include <iostream>
#include <vector>
#include <string>


struct LCS {
    size_t sz1, sz2;
    std::vector<int> FirstSeq;
    std::vector<int> SecondSeq;

    std::vector<std::vector<int>> matrix;
    std::vector<int> SubSeq;

    LCS() {
        std::cin >> sz1;
        ++sz1;
        FirstSeq.resize(sz1);
        for (size_t i = 1; i < sz1; ++i) {
            std::cin >> FirstSeq[i];
        }

        std::cin >> sz2;
        ++sz2;
        SecondSeq.resize(sz2 + 1);
        for (size_t i = 1; i < sz2; ++i) {
            std::cin >> SecondSeq[i];
        }

        matrix.resize(sz1, std::vector<int>(sz2));
    }

    void Filling_Matrix() {
        for (int i = 1; i < sz1; ++i) {
            for (int j = 1; j < sz2; ++j) {
                if (FirstSeq[i] == SecondSeq[j]) {
                    matrix[i][j] = 1 + matrix[i - 1][j - 1];
                } else {
                    matrix[i][j] = std::max(matrix[i][j - 1], matrix[i - 1][j]);
                }
            }
        }
    }

    void Get_SubSeq() {
        int i = (int)sz1, j = (int)sz2;
        --i; --j;
        while (i > 0 && j > 0) {
            if (FirstSeq[i] == SecondSeq[j]) {
                SubSeq.push_back(FirstSeq[i]);
                --i; --j;
            } else if (matrix[i - 1][j] == matrix[i][j])
                --i;
            else if (matrix[i][j - 1] == matrix[i][j])
                --j;
        }
    }

    void Out() {
        for (int i = (int)SubSeq.size() - 1; i >= 0; --i) {
            std::cout << SubSeq[i] << ' ';
        }
    }
};


int main() {
    LCS s;
    s.Filling_Matrix();
    s.Get_SubSeq();
    s.Out();
}

