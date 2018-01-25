/*
Stairs
Total Accepted: 113207 Total Submissions: 305325 Difficulty: Easy

You are climbing a stair case. It takes n ways to reach to the top.
Each time you can either climb 1 or 2 ways. In how many distinct ways can you climb to the top? 
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
    int climbStairs(int n) {
        vector<int> ways(n+1);
        ways[0] = 1;
        ways[1] = 1;
        for (int i = 2; i <= n; ++i)
            ways[i] = ways[i-1] + ways[i-2];
        return ways[n]; 
    }
};

int main()
{
    Solution sol;

    return 0;
}

