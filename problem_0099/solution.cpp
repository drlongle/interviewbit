/*
Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears more than floor(n/2) times.

You may assume that the array is non-empty and the majority element always exist in the array.

Example :

Input : [2, 1, 2]
Return  : 2 which occurs 2 times which is greater than 3/2. 
*/

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define ull unsigned long long

using namespace std;

class Solution {
public:
    int my_majorityElement(const vector<int> &nums);
    int majorityElement(vector<int> &num) {
        int majorityIndex = 0;
        for (int count = 1, i = 1; i < num.size(); i++) {
            num[majorityIndex] == num[i] ? count++ : count--;
            if (count == 0) {
                majorityIndex = i;
                count = 1;
            }
        }

        return num[majorityIndex];
    }
};

int Solution::my_majorityElement(const vector<int> &nums) {
    int candidate = nums[0];
    int count = 0;

    for (size_t i = 0; i < nums.size(); ++i)
    {
        if (count == 0)
        {
            count = 1;
            candidate = nums[i];
        } else if (candidate == nums[i])
            ++count;
        else
            --count;
    }
    return candidate;
}

int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

