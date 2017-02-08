/*
Number of 1 Bits  
Total Accepted: 89529 Total Submissions: 238277 Difficulty: Easy

Write a function that takes an unsigned integer and returns the number of
1' bits it has (also known as the Hamming weight).

For example, the 32-bit integer 1' has binary representation
00000000000000000000000000001011, so the function should return 3.
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
    int numSetBits(uint32_t n);
};

int Solution::numSetBits(uint32_t n) {
    int res = 0;
    while (n) {
        ++res;
        n &= n-1;
    }
    return res;
}

int main()
{
    Solution sol;

    return 0;
}
