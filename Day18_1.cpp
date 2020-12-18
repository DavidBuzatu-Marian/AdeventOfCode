#include <fstream>
#include <iostream>
#include <string>

using namespace std;

long long getResult(const string &line, int &start) {
    int op = -1;
    long long res = 0;
    for (; start < line.size() && line[start] != ')'; ++start) {
        int currNr = 0;
        if (line[start] == ' ') {
            continue;
        }
        if (line[start] == '(') {
            currNr = getResult(line, ++start);
        } else if (line[start] == '+') {
            op = 0;
            continue;
        } else if (line[start] == '*') {
            op = 1;
            continue;
        } else {
            currNr = line[start] - '0';
        }
        if (op == 1) {
            res *= currNr;
            op = -1;
        } else if (op == 0) {
            res += currNr;
            op = -1;
        } else {
            res = currNr;
        }
    }
    return res;
}

int main() {
    ifstream f("day18_1.txt");
    long long sum = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        int start = 0;
        long long r = getResult(line, start);
        sum += r;
        cout << r << "\n";
    }
    cout << sum << '\n';
}