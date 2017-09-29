/*
N digit numbers with digit sum S 
Find out the number of N digit numbers, whose digits on being added equals to a given number S. Note that a valid number starts from digits 1-9 except the number 0 itself. i.e. leading zeroes are not allowed.

Since the answer can be large, output answer modulo 1000000007

N = 2, S = 4 
Valid numbers are {22, 31, 13, 40} 
Hence output 4.
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

vector<vector<int>> dp;

const int MOD_CONST = 1000000007;

int count_ways(int N, int S, bool lead_digit)
{
    if (N == 1)
        return (S >= 0 && S <= 9) ? 1 : 0;
    if (dp[N][S] >= 0) {
        return dp[N][S];
    }
    int sum = 0;
    for (int i = lead_digit ? 1 : 0; i <= min(S, 9); ++i) {
        sum += count_ways(N-1, S-i, false);
        if (sum >= MOD_CONST)
            sum -= MOD_CONST;
    }
    return dp[N][S] = sum;
}

class Solution {
public:
    int solve(int N, int S);
};

int Solution::solve(int N, int S) {
    dp.resize(N+1);
    for (int i = 0; i <= N; ++i) {
        dp[i].resize(S+1);
        for (int j = 0; j <= S; ++j)
            dp[i][j] = -1;
    }
    return count_ways(N, S, true);
}

int main(int argc, const char* argv[])
{
    Solution sol;
    int n, s;
    cout << "N: ";
    cin >> n;
    cout << "S: ";
    cin >> s;
    cout << "Result: " << sol.solve(n, s) << endl;
    return 0;
}

