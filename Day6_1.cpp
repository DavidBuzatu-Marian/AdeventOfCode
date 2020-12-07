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

unordered_set<string> getNeighs(vector<string> &line) {
    unordered_set<string> res;
    string partRes;
    int cnt = 0;
    for (auto it = line.begin(); it != line.end(); ++it) {
        if (cnt <= endOfNode) {
            ++cnt;
            continue;
        }
        if ((*it)[0] >= '0' && (*it)[0] <= '9') {
            continue;
            // this is nr. of bags
        }
        if ((*it)[(*it).size() - 1] == ',') {
            (*it).pop_back();
        }
        if ((*it).compare("bag") != 0 && (*it).compare("bags") != 0) {
            partRes += (*it);
            partRes += " ";
        } else {
            partRes.pop_back();
            res.insert(partRes);
            partRes.clear();
        }
    }
    partRes.pop_back();
    res.insert(partRes);
    return res;
}

int main() {
    fstream f("day6_1.txt");
    int ans = 0;
    unordered_map<string, unordered_set<string>> adjList;
    queue<string> nodes;
    unordered_set<string> visited;
    while (!f.eof()) {
        string line;
        getline(f, line);
        vector<string> parsedLine = parseLine(line);
        string node = getNode(parsedLine);
        unordered_set<string> neighs = getNeighs(parsedLine);
        adjList.insert({node, neighs});
        if (neighs.count("shiny gold") > 0) {
            ++ans;
            nodes.push(node);
            visited.insert(node);
        }
    }
    while (!nodes.empty()) {
        string currNode = nodes.front();
        nodes.pop();
        for (auto it = adjList.begin(); it != adjList.end(); ++it) {
            if (visited.count(it->first) == 0 &&
                it->second.count(currNode) > 0) {
                ++ans;
                nodes.push(it->first);
                visited.insert(it->first);
            }
        }
    }
    cout << ans << '\n';
}