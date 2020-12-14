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

string bitMask(string &mask, uint64_t value) {
    string res = "";
    int pos = 0;
    while (pos < mask.size()) {
        uint64_t maskBit = 0;
        if (pos + 1 < mask.size() && mask[pos + 1] != '0') {
            res += (mask[pos + 1]);
        } else {
            int valueBit = (value >> pos) & 1;
            res += (valueBit) + '0';
        }
        ++pos;
    }
    return res;
}

void modifyAddresses(string addrs, string currAddrs, int lastX, uint64_t &val,
                     unordered_map<uint64_t, uint64_t> &mem) {
    size_t pos = addrs.find("X");
    if (pos == string::npos) {
        currAddrs += addrs.substr(lastX);
        uint64_t res = 0;
        int p = 0;
        for (char c : currAddrs) {
            uint64_t bit = c - '0';
            res |= bit << p;
            ++p;
        }
        mem[res] = val;
        return;
    }
    addrs[pos] = '0';
    currAddrs += string(addrs.begin() + lastX, addrs.begin() + pos + 1);
    modifyAddresses(addrs, currAddrs, pos + 1, val, mem);
    currAddrs[pos] = '1';
    modifyAddresses(addrs, currAddrs, pos + 1, val, mem);
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
            string newMemoryAddrs = bitMask(mask, memoryAddr);
            uint64_t value = stol(splittedLine[1]);
            modifyAddresses(newMemoryAddrs, "", 0, value, mem);
        }
    }
    uint64_t sum = 0;
    for (auto it = mem.begin(); it != mem.end(); ++it) {
        sum += it->second;
    }
    cout << sum << '\n';
}