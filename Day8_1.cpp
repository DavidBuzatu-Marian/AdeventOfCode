#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_set<int> getSums(queue<int> nums) {
    unordered_set<int> res;
    vector<int> numsVec;
    while (!nums.empty()) {
        numsVec.push_back(nums.front());
        nums.pop();
    }
    int N = numsVec.size();
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            res.insert(numsVec[i] + numsVec[j]);
        }
    }
    return res;
}

int main() {
    fstream f("day8_1.txt");
    queue<int> nums;
    while (!f.eof()) {
        int num;
        f >> num;
        if (nums.size() < 25) {
            nums.push(num);
        } else {
            unordered_set<int> sums = getSums(nums);
            if (sums.count(num) == 0) {
                cout << num << " ";
                break;
            }
            nums.pop();
            nums.push(num);
        }
    }
}