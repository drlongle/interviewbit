/*
Jump Game Array
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return 1 ( true ).

A = [3,2,1,0,4], return 0 ( false ).

Return 0/1 for this problem
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
    int canJump(vector<int> &input);

    bool canJump(int A[], int n) {
        int minIndexPossible = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            bool isPossibleFromThisIndex = false;
            if (i + A[i] >= minIndexPossible) {
                isPossibleFromThisIndex = true;
                minIndexPossible = i;
            }
            if (i == 0) return isPossibleFromThisIndex;
        }
        return true;
    }
};

int Solution::canJump(vector<int> &input)
{
    int size = input.size();
    vector<bool> canjump(size, false);
    canjump[size-1] = true;
    for (int i = size-2; i >= 0; --i) {
        int step = input[i];
        for (int j = i+1; j <= min(size-1, i+step); ++j) {
            if (canjump[j]) {
                canjump[i] = true;
                break;
            }
        }
    }

    return canjump[0] ? 1 : 0;    
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> input;

    input = {2,3,1,1,4};
    cout << "Result: " << sol.canJump(input) << endl;

    input = {3,2,1,0,4};
    cout << "Result: " << sol.canJump(input) << endl;

    return 0;
}

