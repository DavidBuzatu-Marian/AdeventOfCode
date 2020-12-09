#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_set<int> getSums(vector<int>& nums, const int& start) {
    unordered_set<int> res;
    int N = nums.size();
    for (int i = start; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            res.insert(nums[i] + nums[j]);
        }
    }

    return res;
}

pair<int, int> findMinMax(const vector<int>& nums, const int& start,
                          const int& end) {
    int mini = INT_MAX, maxi = INT_MIN;
    for (int i = start; i <= end; ++i) {
        maxi = max(maxi, nums[i]);
        mini = min(mini, nums[i]);
    }
    return {mini, maxi};
}

pair<int, int> findContiguousSum(const pair<int, int>& searched,
                                 const vector<int>& nums) {
    int low = 0, high = 0, currSum = 0;

    while (high < searched.second) {
        currSum += nums[high];
        if (currSum == searched.first) {
            return findMinMax(nums, low, high);
        }
        while (currSum > searched.first) {
            currSum -= nums[low];
            ++low;
        }
        ++high;
    }
    return {};
}

int main() {
    fstream f("day8_1.txt");
    vector<int> nums;
    int cnt = 0;
    pair<int, int> searched;
    while (!f.eof()) {
        int num;
        f >> num;
        if (nums.size() < 25) {
            nums.push_back(num);
        } else {
            unordered_set<int> sums = getSums(nums, nums.size() - 25);
            if (sums.count(num) == 0) {
                searched.first = num;
                searched.second = cnt;
                break;
            }
            nums.push_back(num);
        }
        ++cnt;
    }
    cout << searched.first << " " << searched.second << "\n";
    pair<int, int> res = findContiguousSum(searched, nums);
    cout << res.first << " " << res.second << '\n';
}