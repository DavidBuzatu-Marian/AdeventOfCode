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

void updateMap(const int &index, unordered_map<int, pair<int, int>> &map,
               int &turn) {
    auto it = map.find(index);
    if (it != map.end()) {
        map[index] = {it->second.second, ++turn};
    } else {
        map[index] = {++turn, turn};
    }
}

int main() {
    ifstream f("day14_1.txt");
    unordered_map<int, pair<int, int>> cnts;
    int turn = 0;
    vector<int> numbers;
    while (!f.eof()) {
        string line;
        getline(f, line);
        numbers = getNumbers(line);
    }
    for (int x : numbers) {
        turn++;
        cnts.insert({x, {turn, turn}});
    }
    int lastSpoken = *(numbers.rbegin());
    while (turn < 30000000) {
        auto it = cnts.find(lastSpoken);
        if (it != cnts.end()) {
            if (it->second.first == it->second.second) {
                lastSpoken = 0;
                updateMap(lastSpoken, cnts, turn);
            } else {
                int diff = it->second.second - it->second.first;
                updateMap(diff, cnts, turn);
                lastSpoken = diff;
            }
        } else {
            lastSpoken = 0;
            updateMap(lastSpoken, cnts, turn);
        }
        // cout << turn << ": " << lastSpoken << '\n';
    }
    cout << lastSpoken << '\n';
    return 0;
}
