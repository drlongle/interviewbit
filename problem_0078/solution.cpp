/*
Longest Increasing Subsequence

Find the longest increasing subsequence of a given sequence / array.

In other words, find a subsequence of array in which the subsequence’s elements are in strictly increasing order, and in which the subsequence is as long as possible. 
This subsequence is not necessarily contiguous, or unique.
In this case, we only care about the length of the longest increasing subsequence.

Example :

Input : [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]
Output : 6
The sequence : [0, 2, 6, 9, 13, 15] or [0, 4, 6, 9, 11, 15] or [0, 4, 6, 9, 13, 15]
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
    int lis(const vector<int> &numbers);

};

int Solution::lis(const vector<int> &numbers)
{
    vector<int> tail_values;

    for (const auto& n: numbers)
    {
        if (binary_search(tail_values.begin(), tail_values.end(), n))
            continue;
        auto it = upper_bound(tail_values.begin(), tail_values.end(), n);
        if (it == tail_values.end())
            tail_values.emplace_back(n);
        else
            *it = n;
    }

    return tail_values.size();
}

int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

