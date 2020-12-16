#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> getNumbers(string &line) {
    size_t pos;
    vector<int> res;
    while ((pos = line.find(",")) != string::npos) {
        res.push_back(stoi(line.substr(0, pos)));
        line.erase(0, pos + 1);
    }
    res.push_back(stoi(line));
    return res;
}

vector<string> getRanges(string &line) {
    size_t pos;
    vector<string> res;
    if ((pos = line.find(" or ")) != string::npos) {
        res.push_back((line.substr(0, pos)));
        line.erase(0, pos + 4);
    }
    res.push_back((line));
    return res;
}

vector<pair<int, int>> getRangesPair(vector<string> &ranges) {
    size_t pos;
    vector<pair<int, int>> res;
    int p1, p2;
    for (int i = 0; i < ranges.size(); ++i) {
        if ((pos = ranges[i].find("-")) != string::npos) {
            p1 = stoi(ranges[i].substr(0, pos));
            ranges[i].erase(0, pos + 1);
        }
        p2 = stoi(ranges[i]);
        res.push_back({p1, p2});
    }
    return res;
}

string splitAtCol(string &line) {
    size_t pos;
    string field;
    if ((pos = line.find(": ")) != string::npos) {
        field = line.substr(0, pos);
        line.erase(0, pos + 2);
    }
    return field;
}

int inInterval(const unordered_map<string, vector<pair<int, int>>> &rangesMap,
               int &value) {
    for (auto it = rangesMap.begin(); it != rangesMap.end(); ++it) {
        for (int i = 0; i < it->second.size(); ++i) {
            if (it->second[i].first <= value && it->second[i].second >= value) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    ifstream f("day15_1.txt");
    unordered_map<string, vector<pair<int, int>>> rangesMap;
    int res = 0;
    vector<int> numbers;
    while (!f.eof()) {
        string line;
        getline(f, line);
        if (line.empty()) {
            continue;
        }
        if (line[0] >= 'a' && line[0] <= 'z') {
            string aux = line;
            string field = splitAtCol(line);
            if (aux.compare(line) == 0) {
                continue;  // message of your ticker/nearby ticket
            }
            vector<string> ranges = getRanges(line);
            vector<pair<int, int>> rangePairs = getRangesPair(ranges);
            rangesMap.insert({field, rangePairs});
        } else {
            vector<int> nums = getNumbers(line);
            for (int i = 0; i < nums.size(); ++i) {
                if (!inInterval(rangesMap, nums[i])) {
                    res += nums[i];
                }
            }
        }
        numbers = getNumbers(line);
    }
    cout << res << '\n';
    return 0;
}
