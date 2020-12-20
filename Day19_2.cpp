#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
vector<int> visits(10000, 0);
pair<int, vector<vector<int>>> parseLine(string &line, string &message) {
    size_t pos = line.find(":");
    vector<vector<int>> res;
    vector<int> neighs;
    int node;
    if (pos != string::npos) {
        node = stoi(line.substr(0, pos));
        line.erase(0, pos + 2);
        while ((pos = line.find(" ")) != string::npos) {
            if (line[0] == '|') {
                res.push_back(neighs);
                neighs.clear();
            } else {
                neighs.push_back(stoi(line.substr(0, pos)));
            }
            line.erase(0, pos + 1);
        }
        if ((pos = line.find("\"")) != string::npos) {
            line.erase(0, pos + 1);
            message = line.substr(0);
            message.pop_back();
        }
    }
    if (message.size() > 0) {
        return {node, {}};
    }
    neighs.push_back(stoi(line));
    res.push_back(neighs);
    return {node, res};
}

void print(unordered_map<int, vector<vector<int>>> &nodes,
           vector<string> &messages,
           unordered_map<int, string> &nodes_messages) {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        cout << it->first << ": ";
        for (vector<int> neighs : it->second) {
            for (int n : neighs) {
                cout << n << " ";
            }
            cout << "| ";
        }
        cout << '\n';
    }
    for (auto it = nodes_messages.begin(); it != nodes_messages.end(); ++it) {
        cout << it->first << " " << it->second << '\n';
    }
    for (string mes : messages) {
        cout << mes << "\n";
    }
}

unordered_set<string> combineMessages(unordered_set<string> &v1,
                                      unordered_set<string> &v2) {
    if (v1.empty()) {
        return v2;
    }
    if (v2.empty()) {
        return v1;
    }
    unordered_set<string> res;
    for (string s1 : v1) {
        for (string s2 : v2) {
            res.insert(s1 + s2);
        }
    }
    return res;
}

unordered_set<string> DFS(
    unordered_map<int, vector<vector<int>>> &nodes, vector<string> &messages,
    unordered_map<int, unordered_set<string>> &nodes_messages,
    const int &currNode) {
    if (nodes.find(currNode) == nodes.end()) {
        return nodes_messages.find(currNode)->second;
    }
    unordered_set<string> msgs;
    auto it = nodes.find(currNode);
    for (vector<int> neighs : it->second) {
        msgs.clear();
        auto it_msgs = nodes_messages.find(currNode);
        if (neighs.size() > 1 && (neighs[1] == 8 || neighs[1] == 11) &&
            visits[neighs[1]] >= 5) {
            continue;
        }
        for (int neigh : neighs) {
            visits[neigh]++;
            unordered_set<string> neighMsgs =
                DFS(nodes, messages, nodes_messages, neigh);
            msgs = combineMessages(msgs, neighMsgs);
        }
        if (it_msgs == nodes_messages.end()) {
            nodes_messages.insert({currNode, msgs});
        } else {
            for (string msg : msgs) {
                it_msgs->second.insert(msg);
            }
        }
    }
    return nodes_messages.find(currNode)->second;
}

int main() {
    ifstream f("day19_1.txt");
    unordered_map<int, vector<vector<int>>> nodes;
    vector<string> messages;

    unordered_map<int, unordered_set<string>> nodes_messages;
    while (!f.eof()) {
        string line, message;
        getline(f, line);
        if (line.find(":") == string::npos) {
            messages.push_back(line);
        } else {
            pair<int, vector<vector<int>>> node = parseLine(line, message);
            if (node.second.size() == 0) {
                nodes_messages.insert({node.first, {message}});
            } else {
                nodes.insert(node);
            }
        }
    }
    unordered_set<string> valid_rules = DFS(nodes, messages, nodes_messages, 0);
    int ans = 0;
    for (string msg : messages) {
        if (valid_rules.count(msg) > 0) {
            ++ans;
        }
    }
    cout << ans << '\n';
}