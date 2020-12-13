#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <iostream>
using namespace std;

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
    int shipN = 0, shipE = 0;
    int waypointN = 1, waypointE = 10;
    char direction;
    int amount = 0;
    while (!f.eof()) {
        string move;
        f >> move;
        direction = move[0];
        amount = stoi(move.substr(1));

        if (direction == 'F') {
            shipN += amount * waypointN;
            shipE += amount * waypointE;
        }
        if (direction == 'N') {
            waypointN += amount;
        }
        if (direction == 'E') {
            waypointE += amount;
        }
        if (direction == 'S') {
            waypointN -= amount;
        }
        if (direction == 'W') {
            waypointE -= amount;
        }
        if (direction == 'L' || direction == 'R') {
            // BASED on the formula from:
            // https://math.stackexchange.com/questions/814950/how-can-i-rotate-a-coordinate-around-a-circle
            double theta = (double)amount * M_PI / 180;
            if (direction == 'R') {
                theta *= (-1);
            }
            int newWaypointE =
                round(cos(theta) * waypointE - sin(theta) * waypointN);
            int newWaypointN =
                round(sin(theta) * waypointE + cos(theta) * waypointN);
            waypointE = newWaypointE;
            waypointN = newWaypointN;
        }
    }
    cout << abs(shipN) + abs(shipE);
}