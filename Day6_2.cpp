#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int endOfNode = 0;

vector<string> parseLine(string &line) {
    size_t pos;
    vector<string> res;
    while ((pos = line.find(" ")) != string::npos) {
        string word = line.substr(0, pos);
        res.push_back(word);
        line.erase(0, pos + 1);
    }
    return res;
}

string getNode(vector<string> &line) {
    string res;
    endOfNode = 0;
    for (auto it = line.begin(); it != line.end(); ++it) {
        ++endOfNode;
        if ((*it).compare("bags") != 0) {
            res += (*it);
            res += " ";
        } else {
            res.pop_back();
            break;
        }
    }
    endOfNode++;
    return res;
}

unordered_map<string, int> getNeighs(vector<string> &line) {
    unordered_map<string, int> res;
    string partRes;
    int cnt = 0, nrBags = 0;
    for (auto it = line.begin(); it != line.end(); ++it) {
        if (cnt < endOfNode) {
            ++cnt;
            continue;
        }
        if ((*it)[0] >= '0' && (*it)[0] <= '9') {
            nrBags = stoi(*it);
            continue;
        }
        if ((*it)[(*it).size() - 1] == ',') {
            (*it).pop_back();
        }
        if ((*it).compare("bag") != 0 && (*it).compare("bags") != 0) {
            partRes += (*it);
            partRes += " ";
        } else {
            partRes.pop_back();
            res.insert({partRes, nrBags});
            partRes.clear();
            nrBags = 0;
        }
    }
    partRes.pop_back();
    res.insert({partRes, nrBags});
    return res;
}

int getScores(unordered_map<string, int> &neighs,
              unordered_map<string, unordered_map<string, int>> &adjList) {
    int ans = 0;
    for (auto it = neighs.begin(); it != neighs.end(); ++it) {
        if (it->second != 0) {
            ans = ans + it->second +
                  it->second *
                      getScores(adjList.find(it->first)->second, adjList);
        }
    }
    return ans;
}

int main() {
    fstream f("day6_1.txt");
    int ans = 0;
    unordered_map<string, unordered_map<string, int>> adjList;
    unordered_map<string, int> scores;
    unordered_set<string> visited;
    while (!f.eof()) {
        string line;
        getline(f, line);
        vector<string> parsedLine = parseLine(line);
        string node = getNode(parsedLine);
        unordered_map<string, int> neighs = getNeighs(parsedLine);
        adjList.insert({node, neighs});
    }

    auto it = adjList.find("shiny gold");
    ans = getScores(it->second, adjList);
    cout << ans << '\n';
}