#include <stdint.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> splitLine(string &line) {
    size_t pos;
    vector<string> res;
    while ((pos = line.find(" = ")) != std::string::npos) {
        res.push_back(line.substr(0, pos));
        line.erase(0, pos + 3);
    }
    res.push_back(line);
    return res;
}

uint64_t bitMask(string &mask, uint64_t value) {
    uint64_t res = 0;
    int pos = 0;
    while (pos < mask.size()) {
        uint64_t maskBit = 0;
        if (pos + 1 < mask.size() && mask[pos + 1] != 'X') {
            maskBit = mask[pos + 1] - '0';
            res |= (maskBit) << pos;
        } else {
            int valueBit = (value >> pos) & 1;
            // cout << "VALUE"
            //      << " ";
            // cout << valueBit << " " << pos << "\n";
            res |= (valueBit) << pos;
        }
        ++pos;
    }
    return res;
}

int main() {
    ifstream f("day13_1.txt");
    unordered_map<uint64_t, uint64_t> mem;
    string mask;
    while (!f.eof()) {
        string line;
        getline(f, line);
        vector<string> splittedLine = splitLine(line);
        if (splittedLine[0].compare("mask") == 0) {
            reverse(splittedLine[1].begin(), splittedLine[1].end());
            mask = splittedLine[1];
        } else {
            splittedLine[0].erase(0, 4);
            uint64_t memoryAddr = stol(splittedLine[0]);
            if (mem.find(memoryAddr) == mem.end()) {
                mem.insert({memoryAddr, bitMask(mask, stol(splittedLine[1]))});
            } else {
                mem.find(memoryAddr)->second =
                    bitMask(mask, stol(splittedLine[1]));
            }
        }
    }
    uint64_t sum = 0;
    for (auto it = mem.begin(); it != mem.end(); ++it) {
        sum += it->second;
    }
    cout << sum << '\n';
}