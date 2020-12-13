#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> splitString(string command) {
    size_t pos;
    vector<string> res;
    while ((pos = command.find(" ")) != string::npos) {
        string comm = command.substr(0, pos);
        res.push_back(comm);
        command.erase(0, pos + 1);
    }
    res.push_back(command);
    return res;
}

pair<int, int> DFS(vector<string> &commands, const int &cntCommand) {
    int i = 0, accumulator = 0, cnt = 0;
    vector<int> visited(commands.size(), 0);
    while (i < commands.size() && !visited[i]) {
        vector<string> split = splitString(commands[i]);
        visited[i] = 1;
        if (cnt == cntCommand && split[0].compare("acc") != 0) {
            if (split[0].compare("nop") == 0) {
                split[0] = "jmp";
            } else {
                split[0] = "nop";
            }
            ++cnt;
        }
        if (split[0].compare("nop") == 0) {
            ++i;
            ++cnt;
            continue;
        }
        if (split[0].compare("acc") == 0) {
            accumulator += (stoi(split[1]));
            ++i;
        }
        if (split[0].compare("jmp") == 0) {
            i += (stoi(split[1]));
            ++cnt;
        }
    }

    return {i, accumulator};
}

int main() {
    ifstream f("day7_1.txt");
    vector<string> commands;
    int totalComm = 0;
    while (!f.eof()) {
        string line;
        getline(f, line);
        commands.push_back(line);
        if (line[0] == 'n' || line[0] == 'j') {
            ++totalComm;
        }
    }

    int i = 0, accumulator = 0, cntCommand = 0;
    while (i < commands.size() && cntCommand <= totalComm) {
        pair<int, int> res = DFS(commands, cntCommand);
        i = res.first;
        accumulator = res.second;
        ++cntCommand;
    }
    cout << accumulator << '\n';
}