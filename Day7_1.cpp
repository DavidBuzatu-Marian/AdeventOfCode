#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<string> splitString(string& command) {
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

int main() {
    ifstream f("day7_1.txt");
    vector<string> commands;
    while (!f.eof()) {
        string line;
        getline(f, line);
        commands.push_back(line);
    }
    vector<int> visited(commands.size(), 0);

    int i = 0, accumulator = 0;
    while (!visited[i]) {
        vector<string> split = splitString(commands[i]);
        visited[i] = 1;
        if (split[0].compare("nop") == 0) {
            ++i;
            continue;
        }
        if (split[0].compare("acc") == 0) {
            accumulator += (stoi(split[1]));
            ++i;
        }
        if (split[0].compare("jmp") == 0) {
            i += (stoi(split[1]));
        }
    }
    cout << accumulator << '\n';
}