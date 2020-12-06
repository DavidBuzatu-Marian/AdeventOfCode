#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int countTreesWithSteps(const vector<vector<char>>& matrix, const int& stepI,
                        const int& stepJ, const int& N, const int& M) {
    int j = 0, nrTrees = 0, i = 0;
    while (i < N) {
        if (matrix[i][j] == '#') {
            ++nrTrees;
        }
        i = (i + stepI);
        j = (j + stepJ) % M;
    }
    return nrTrees;
}

int main() {
    ifstream f("day3_1.txt");
    vector<vector<char>> matrix;
    int N = 0, M = 0;
    while (!f.eof()) {
        string line;
        f >> line;
        if (M == 0) {
            M = line.size();
        }
        matrix.push_back({});
        for (int i = 0; i < M; ++i) {
            matrix[N].push_back(line[i]);
        }
        ++N;
    }
    int res = 1;
    res *= countTreesWithSteps(matrix, 1, 1, N, M);
    res *= countTreesWithSteps(matrix, 1, 3, N, M);
    res *= countTreesWithSteps(matrix, 1, 5, N, M);
    res *= countTreesWithSteps(matrix, 1, 7, N, M);
    res *= countTreesWithSteps(matrix, 2, 1, N, M);
    cout << res;
}