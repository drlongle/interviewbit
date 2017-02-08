/*
Single Number II

Given an array of integers, every element appears thrice except for one
which occurs once. Find that element which does not appear thrice.

Note: Your algorithm should have a linear runtime complexity.
Could you implement it without using extra memory?

Example :

Input : [1, 2, 4, 3, 3, 2, 2, 3, 1, 1]
Output : 4

 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
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

#define ll long long int
#define ull unsigned long long int

using namespace std;

class Solution {
public:
    int my_singleNumber(const vector<int> &A);
    int singleNumber(const vector<int> &A) {
        int n = A.size();
        int count[32] = {0};
        int result = 0;
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < n; j++) {
                if ((A[j] >> i) & 1) {
                    count[i]++;
                }
            }
            result |= ((count[i] % 3) << i);
        }
        return result;
    }
};

int Solution::my_singleNumber(const vector<int> &A) {
    int ones = 0, twos = 0;
    int next_ones, next_twos;
    for (const auto& a: A) {
        next_ones = (ones & ~a) | (~ones & ~twos & a);
        next_twos = (twos & ~a) | (~twos & ones & a);
        ones = next_ones;
        twos = next_twos;
    }
    return ones;    
}

int main()
{
    Solution sol;

    return 0;
}
