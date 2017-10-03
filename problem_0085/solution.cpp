/*
Longest Arithmetic Progression

Find longest Arithmetic Progression in an integer array and return its length. More formally, find longest sequence of indeces, 0 < i1 < i2 < … < ik < ArraySize(0-indexed) such that sequence A[i1], A[i2], …, A[ik] is an Arithmetic Progression. Arithmetic Progression is a sequence in which all the differences between consecutive pairs are the same, i.e sequence B[0], B[1], B[2], …, B[m - 1] of length m is an Arithmetic Progression if and only if B[1] - B[0] == B[2] - B[1] == B[3] - B[2] == … == B[m - 1] - B[m - 2].
Examples
1) 1, 2, 3(All differences are equal to 1)
2) 7, 7, 7(All differences are equal to 0)
3) 8, 5, 2(Yes, difference can be negative too)

Samples
1) Input: 3, 6, 9, 12
Output: 4

2) Input: 9, 4, 7, 2, 10
Output: 3(If we choose elements in positions 1, 2 and 4(0-indexed))
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
    int solve(const vector<int> &seq);
};

int Solution::solve(const vector<int> &seq) {
    int size = seq.size();
    if (size < 2) return size;
    unordered_map<int, int> cache;
    int res = 2;
    cache[seq[1]-seq[0]] = 2;
    for (int i = 2; i < size; ++i) {
        unordered_set<int> seen;
        for (int j = i-1; j >= 0; --j) {
            int diff = seq[i] - seq[j];
            if (seen.find(diff) != seen.end())
                continue;
            seen.insert(diff);
            if (cache.find(diff) != cache.end())
                cache[diff]++;
            else
                cache[diff] = 2;
            if (cache[diff] > res)
                res = cache[diff];
        }
    }

    return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> seq;

    seq = {3, 6, 9, 12};
    seq = {9, 4, 7, 2, 10};
    seq = {1,2,3};
    seq = {7,7,7,7};
    seq = {};
    seq = {100, 10, 8, 300, 6, 1, 4, 2};
    cout << "Result: " << sol.solve(seq) << endl;

    return 0;
}

