#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void parseIDLine(string &line, vector<int> &ids) {
    size_t pos = 0;
    while ((pos = line.find(',')) != std::string::npos) {
        string value = line.substr(0, pos);
        if (value.compare("x") != 0) {
            ids.push_back(stoi(value));
        }
        line.erase(0, pos + 1);
    }
    if (line.compare("x") != 0) {
        ids.push_back(stoi(line));
    }
}

int main() {
    ifstream f("day12_1.txt");
    int ID, minTime = INT_MAX, minID = 0, minMinutes = 0;
    string idLine;
    vector<int> ids;
    f >> ID;
    f >> idLine;
    parseIDLine(idLine, ids);
    for (int id : ids) {
        int timeAroundID = id * (ID / id);
        if (timeAroundID == ID) {
            cout << 0 << "\n";
            return 0;
        } else {
            timeAroundID += id;
            if (minTime > timeAroundID) {
                minTime = timeAroundID;
                minID = id;
                minMinutes = timeAroundID - ID;
            }
        }
    }
    cout << minID * minMinutes << '\n';
}