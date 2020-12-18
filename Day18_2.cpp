#include <fstream>
#include <iostream>
#include <string>

using namespace std;

long long getResult(const string &line, int &start) {
    long long res = 0;
    int op = 0;
    for (; start < line.size() && line[start] != ')'; ++start) {
        long long currNr = 0;
        if (line[start] == ' ') {
            continue;
        }
        if (line[start] == '(') {
            currNr = getResult(line, ++start);
        } else if (line[start] == '+') {
            op = 1;
            continue;
        } else if (line[start] == '*') {
            long long r = getResult(line, ++start);
            res *= r;
            --start;
            continue;
        } else {
            currNr = line[start] - '0';
        }
        if (op) {
            res += currNr;
            op = 0;
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