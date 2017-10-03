/*
Length of Longest Subsequence

Given an array of integers, find the length of longest subsequence which is first increasing then decreasing.

**Example: **

For the given array [1 11 2 10 4 5 2 1]

Longest subsequence is [1 2 10 4 2 1]

Return value 6
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

    int longestSubsequenceLength(const vector<int> &arr);
    int my_longestSubsequenceLength(const vector<int> &arr);
};

int Solution::my_longestSubsequenceLength(const vector<int> &arr)
{
    vector<int> temp;
    vector<int> inc, dec(arr.size());
    for (auto a: arr)
    {
        auto it = lower_bound(temp.begin(), temp.end(), a);
        if (it == temp.end()) {
            inc.emplace_back(temp.size());
            temp.emplace_back(a);
        } else {
            inc.emplace_back(it - temp.begin());
            *it = a;
        }
    }

    temp.clear();
    for (int i = arr.size()-1; i >= 0; --i)
    {
        auto a = arr[i];
        auto it = lower_bound(temp.begin(), temp.end(), a);
        if (it == temp.end()) {
            dec[i] = temp.size();
            temp.emplace_back(a);
        } else {
            dec[i] = it - temp.begin();
            *it = a;
        }
    }

    int res = 0;
    for (size_t i = 0; i < arr.size(); ++i)
    {
        int len = inc[i] + dec[i] + 1;
        if (len > res)
            res = len;
    }

    return res;
}

int Solution::longestSubsequenceLength(const vector<int> &A) {
    int n = A.size();
    int inc[n];
    int dec[n];

    inc[0] = 1;
    for(int i=1; i<n; i++)
    {
        inc[i] = 1;
        for(int j=i-1; j>=0; j--)
        {
            if(A[i] > A[j] && inc[i] < inc[j] + 1)
                inc[i] = inc[j] + 1;
        }
    }

    dec[n-1] = 1;
    for(int i=n-2; i>=0; i--)
    {
        dec[i] = 1;
        for(int j=i+1; j<n; j++)
        {
            if(A[i] > A[j] && dec[i] < dec[j] + 1)
                dec[i] = dec[j] + 1;
        }
    }

    int mx = 0;
    for(int i=0; i<n; i++)
        mx = max(mx, inc[i] + dec[i] - 1);

    return mx;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> arr;

    // Expected: 6
    arr = {1, 11, 2, 10, 4, 5, 2, 1};

    // Expected: 8
    arr = {7, 6, 8, 10, 2, 5, 12, 30, 31, 20, 22, 18};

    cout << "Result: " << sol.longestSubsequenceLength(arr) << endl;

    return 0;
}

