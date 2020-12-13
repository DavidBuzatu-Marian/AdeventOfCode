#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

char oppositeDir(char& direction) {
    if (direction == 'S') {
        return 'N';
    } else {
        return 'E';
    }
}

char getDirection(const char& curr, const int& clock, const int& amount) {
    int i = 0;
    char res = curr;
    while (i < amount) {
        if (clock < 0) {
            if (res == 'N') {
                res = 'W';
            } else if (res == 'W') {
                res = 'S';
            } else if (res == 'S') {
                res = 'E';
            } else {
                res = 'N';
            }
        } else {
            if (res == 'N') {
                res = 'E';
            } else if (res == 'E') {
                res = 'S';
            } else if (res == 'S') {
                res = 'W';
            } else {
                res = 'N';
            }
        }
        i += 90;
    }
    return res;
}

int main() {
    ifstream f("day11_1.txt");
    unordered_map<char, int> dirs;
    dirs.insert({'E', 0});
    dirs.insert({'N', 0});
    char currDirection = 'E';
    while (!f.eof()) {
        string move;
        char direction;
        int amount = 0;
        f >> move;
        direction = move[0];
        amount = stoi(move.substr(1));
        if (direction == 'F') {
            if (currDirection == 'S' || currDirection == 'W') {
                dirs[oppositeDir(currDirection)] -= amount;
            } else {
                dirs[currDirection] += amount;
            }
        } else if (direction == 'S' || direction == 'W') {
            dirs[oppositeDir(direction)] -= amount;
        } else if (direction == 'N' || direction == 'E') {
            dirs[direction] += amount;
        } else if (direction == 'L') {
            currDirection = getDirection(currDirection, -1, amount);
        } else if (direction == 'R') {
            currDirection = getDirection(currDirection, 1, amount);
        }
    }
    cout << abs(dirs.find('N')->second) + abs(dirs.find('E')->second);
}