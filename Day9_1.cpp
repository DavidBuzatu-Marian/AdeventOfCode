#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    fstream f("day9_1.txt");
    priority_queue<int, vector<int>, greater<int>> pq;
    vector<int> differencesCounter(4, 0);
    while (!f.eof()) {
        int jolt;
        f >> jolt;
        pq.push(jolt);
    }
    int prevJolt = 0;
    while (!pq.empty()) {
        int currJolt = pq.top();
        pq.pop();
        differencesCounter[currJolt - prevJolt]++;
        prevJolt = currJolt;
    }
    differencesCounter[3]++;  // always 3 difference at the end;
    cout << differencesCounter[1] * differencesCounter[3] << '\n';
}