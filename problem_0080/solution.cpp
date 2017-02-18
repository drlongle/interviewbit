/*
Coins in a Line

There are N coins (Assume N is even) in a line. Two players take turns to take a coin from one of the ends of the line until there are no more coins left. The player with the larger amount of money wins. Assume that you go first.

Write a program which computes the maximum amount of money you can win.

Example:
suppose that there are 4 coins which have value
1 2 3 4
now you are first so you pick 4
then in next term
next person picks 3 then
you pick 2 and
then next person picks 1
so total of your money is 4 + 2 = 6
next/opposite person will get 1 + 3 = 4
so maximum amount of value you can get is 6
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
    int maxcoin(vector<int> &coins);
};

int maxcoin_helper(vector<int> &coins, vector<vector<int>>& result, int begin, int end)
{
    if (begin == end)
        return coins[begin];
    else if (begin > end)
        return 0;
    if (result[begin][end] >= 0)
        return result[begin][end];
    result[begin][end] =
        max(coins[begin] + min(maxcoin_helper(coins, result, begin+2, end),
                               maxcoin_helper(coins, result, begin+1, end-1)),
            coins[end] + min(maxcoin_helper(coins, result, begin, end-2),
                             maxcoin_helper(coins, result, begin+1, end-1)));
    return result[begin][end];
}

int Solution::maxcoin(vector<int> &coins) {
    int n = static_cast<int>(coins.size());
    if (n == 0)
        return 0;
    vector<vector<int>> result(n, vector<int>(n, -1));

    maxcoin_helper(coins, result, 0, n-1);

    return result[0][n-1];
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> coins = {1, 2, 3, 4};
    cout << "Result: " << sol.maxcoin(coins) << endl;

    return 0;
}

