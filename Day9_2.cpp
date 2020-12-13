#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

unordered_map<int, int> joltsFound;
vector<long long> cache;
long long solve(vector<int>& jolts, const int& joltsSize, const int& start) {
    if (start > joltsSize) {
        return 0;
    }
    if (start == joltsSize - 1) {
        return 1;
    }
    if (cache[start] != -1) {
        return cache[start];
    }
    long long res = 0;
    if (joltsFound.find(jolts[start] + 1) != joltsFound.end()) {
        res +=
            solve(jolts, joltsSize, joltsFound.find(jolts[start] + 1)->second);
    }
    if (joltsFound.find(jolts[start] + 2) != joltsFound.end()) {
        res +=
            solve(jolts, joltsSize, joltsFound.find(jolts[start] + 2)->second);
    }
    if (joltsFound.find(jolts[start] + 3) != joltsFound.end()) {
        res +=
            solve(jolts, joltsSize, joltsFound.find(jolts[start] + 3)->second);
    }
    return cache[start] = res;
}

int main() {
    fstream f("day9_1.txt");
    vector<int> jolts;

    unordered_map<int, int> dp;
    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();
    while (!f.eof()) {
        int jolt;
        f >> jolt;
        jolts.push_back(jolt);
    }
    sort(jolts.begin(), jolts.end());
    int joltsSize = jolts.size();
    cache.resize(jolts[joltsSize - 1] + 1, -1);
    for (int i = 0; i < joltsSize; ++i) {
        joltsFound.insert({jolts[i], i});
    }

    long long res = 0;
    res += solve(jolts, joltsSize, 0);
    if (jolts[1] <= 3) {
        res += solve(jolts, joltsSize, 1);
    }
    if (jolts[2] <= 3) {
        res += solve(jolts, joltsSize, 2);
    }
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
            .count() /
        1000000.0;
    cout << res << " " << duration << '\n';
}