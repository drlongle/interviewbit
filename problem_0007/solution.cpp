/*
First Missing Integer

Given an unsorted integer array, find the first missing positive integer.

Example:

Given [1,2,0] return 3,

[3,4,-1,1] return 2,

[-8, -7, -6] returns 1

Your algorithm should run in O(n) time and use constant space.
*/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <climits>
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
#include <vector>

#include <string.h>

using namespace std;


class Solution {
public:
    int firstMissingPositive(vector<int> &A) {
        int n = A.size();
        for (int i = 0; i < n; i++) {
            if (A[i] > 0 && A[i] <= n) {
                int pos = A[i] - 1;
                if (A[pos] != A[i]) {
                    swap(A[pos], A[i]);
                    i--;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (A[i] != i + 1) return (i + 1);
        }
        return n + 1;
    }

    int my_firstMissingPositive(vector<int> &A);
};


int Solution::my_firstMissingPositive(vector<int> &A) {
    int size = static_cast<int>(A.size());
    int begin = 0;
    int end = size-1;
    while (begin <= end) {
        while(A[begin] > 0 && begin < end) ++begin;
        if (begin == end) break;
        while(A[end] <= 0 && begin < end) --end;
        if (begin == end) break;
        swap(A[begin],A[end]);
        ++ begin, --end;
    }

    if (end < 0) return 1;
    if (end >= 0 && A[end] <= 0)
        --end;

    int index;
    for (int i = 0; i <= end; ++i) {
        index = abs(A[i])-1;

        if (index <= end && A[index] > 0)
            A[index] = -A[index];
    }

    for (int i = 0; i <= end; ++i)
        if (A[i] > 0) return i+1;

    return end+2;
}

int main()
{
    Solution sol;
    vector<int> input;
    input = {-9,3,4,-1,1,12,-8,7,5,-4,6,2,8,-4};
    input = {-8, -7, -6};

    cout << "Result: " << sol.firstMissingPositive(input) << endl;

    return 0;
}
