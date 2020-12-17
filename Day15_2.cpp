#include <algorithm>
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

void updateInterval(
    const unordered_map<string, vector<pair<int, int>>> &rangesMap, int &value,
    int &pos, unordered_map<string, vector<int>> &positions) {
    for (auto it = rangesMap.begin(); it != rangesMap.end(); ++it) {
        for (int i = 0; i < it->second.size(); ++i) {
            if (it->second[i].first <= value && it->second[i].second >= value) {
                positions[it->first][pos]++;
            }
        }
    }
}

int sum(vector<int> vec) {
    int s = 0;
    for (int x : vec) {
        s += x;
    }
    return s;
}

int pos(vector<int> &vec, int &x) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == x) {
            return i;
        }
    }
    return -1;
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
    unordered_map<string, vector<int>> rangesCnt;
    long long res = 1;
    vector<int> numbers;
    vector<int> ticket, found(100, 0);
    unordered_map<string, int> positions;
    int foundTicket = 0, currPosition = 20;
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
                if (foundTicket == 0) {
                    foundTicket++;
                }
                continue;  // message of your ticket/nearby ticket
            }
            vector<string> ranges = getRanges(line);
            vector<pair<int, int>> rangePairs = getRangesPair(ranges);
            rangesMap.insert({field, rangePairs});
            rangesCnt.insert({field, vector<int>(20)});
        } else {
            vector<int> nums = getNumbers(line);
            if (foundTicket > 1) {
                int invalid = 0;
                for (int i = 0; i < nums.size(); ++i) {
                    if (!inInterval(rangesMap, nums[i])) {
                        invalid = 1;
                    }
                }
                if (!invalid) {
                    for (int i = 0; i < nums.size(); ++i) {
                        updateInterval(rangesMap, nums[i], i, rangesCnt);
                    }
                }
            } else {
                ticket = nums;
                ++foundTicket;
            }
        }
        numbers = getNumbers(line);
    }
    while (currPosition > 0) {
        int mini = INT_MAX;
        unordered_map<string, vector<int>>::iterator miniIt;
        for (auto it = rangesCnt.begin(); it != rangesCnt.end(); ++it) {
            if (sum(it->second) < mini) {
                mini = sum(it->second);
                miniIt = it;
            }
        }
        vector<pair<int, int>> partMini;
        for (int i = 0; i < miniIt->second.size(); ++i) {
            partMini.push_back({miniIt->second[i], i});
        }

        sort(partMini.begin(), partMini.end(), greater<pair<int, int>>());
        for (int i = 0; i < miniIt->second.size(); ++i) {
            if (!found[partMini[i].second]) {
                positions[miniIt->first] = partMini[i].second + 1;
                found[partMini[i].second] = 1;
                break;
            }
        }
        rangesCnt.erase(miniIt);
        --currPosition;
    }
    for (auto it = positions.begin(); it != positions.end(); ++it) {
        if (it->first.find("departure") != string::npos) {
            res *= ticket[it->second - 1];
        }
        cout << it->first << " " << it->second << '\n';
    }
    cout << res << '\n';
    return 0;
}
