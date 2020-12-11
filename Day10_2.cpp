#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
vector<int> directionsI = {-1, -1, -1, 0, 0, 1, 1, 1};
vector<int> directionsJ = {-1, 0, 1, -1, 1, -1, 0, 1};
int inBounds(const int &i, const int &j, const int &N, const int &M) {
    return (i >= 0 && i < N) && (j >= 0 && j < M);
}

int checkAdjacency(vector<vector<char>> &matrix, const int &i, const int &j,
                   const char &check) {
    int cnt = 0;
    int N = matrix.size(), M = matrix[0].size();
    for (int k = 0; k < directionsI.size(); ++k) {
        int newI = i + directionsI[k];
        int newJ = j + directionsJ[k];
        while (inBounds(newI, newJ, N, M) && matrix[newI][newJ] == '.' &&
               matrix[newI][newJ] != check) {
            newI += directionsI[k];
            newJ += directionsJ[k];
        }
        if (inBounds(newI, newJ, N, M) && matrix[newI][newJ] == check) {
            ++cnt;
        }
    }
    return cnt;
}

int BFS(vector<vector<char>> &matrixOfSeats) {
    vector<vector<char>> newMatrixOfSeats(matrixOfSeats);
    int changed = 0;
    for (int i = 0; i < matrixOfSeats.size(); ++i) {
        for (int j = 0; j < matrixOfSeats[0].size(); ++j) {
            if (matrixOfSeats[i][j] == 'L' &&
                checkAdjacency(matrixOfSeats, i, j, '#') == 0) {
                newMatrixOfSeats[i][j] = '#';
                changed = 1;
            } else if (matrixOfSeats[i][j] == '#' &&
                       checkAdjacency(matrixOfSeats, i, j, '#') > 4) {
                newMatrixOfSeats[i][j] = 'L';
                changed = 1;
            }
        }
    }
    matrixOfSeats = newMatrixOfSeats;
    return changed;
}

int main() {
    ifstream f("day10_1.txt");
    vector<vector<char>> matrixOfSeats;
    while (!f.eof()) {
        string line;
        f >> line;
        vector<char> lineChar(line.begin(), line.end());
        matrixOfSeats.push_back(lineChar);
    }
    int ans = 0;
    while (BFS(matrixOfSeats) == 1)
        ;
    for (int i = 0; i < matrixOfSeats.size(); ++i) {
        for (int j = 0; j < matrixOfSeats[0].size(); ++j) {
            if (matrixOfSeats[i][j] == '#') {
                ++ans;
            }
        }
    }
    cout << ans << '\n';
}