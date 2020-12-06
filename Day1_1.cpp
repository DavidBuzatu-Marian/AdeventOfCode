#include <algorithm>  // std::sort
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    vector<int> nums;
    int target = 2020;
    fstream f("day1_1.txt");
    while (!f.eof()) {
        int record;
        f >> record;
        nums.push_back(record);
    }
    int N = nums.size();
    sort(nums.begin(), nums.end());
    for (int i = 0; i < N - 2; ++i) {
        int left = i + 1;
        int right = N - 1;
        int currT = target - nums[i];
        while (left < right) {
            if (currT == nums[left] + nums[right]) {
                cout << nums[i] << " " << nums[left] << " " << nums[right]
                     << '\n';
                --right;
                ++left;
            } else if (currT < nums[left] + nums[right]) {
                --right;
            } else {
                ++left;
            }
        }
    }
    return 0;
}