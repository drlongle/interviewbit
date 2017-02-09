/*
Coin Sum Infinite
You are given a set of coins S. In how many ways can you make sum N assuming you have infinite amount of each coin in the set.

Note : Coins in set S will be unique. Expected space complexity of this problem is O(N).

Example :
Input : 
	S = [1, 2, 3] 
	N = 4

Return : 4

Explanation : The 4 possible ways are
{1, 1, 1, 1}
{1, 1, 2}
{2, 2}
{1, 3}	
Note that the answer can overflow. So, give us the answer % 1000007
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
    int coinchange2(vector<int> &coins, int sum);
};

int Solution::coinchange2(vector<int> &coins, int sum) {
    vector<int> result(sum+1, 0);
    const int mod_value = 1000007;
    result[0] = 1;
    for (const auto& coin: coins) {
        for (int i = coin; i <= sum; ++i) {
            result[i] = (result[i-coin] + result[i]) % mod_value;
        }
    }

    return result[sum];
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> coins;
    int sum;

    coins = {1, 2, 3};
    sum = 4;
    cout << "Result: " << sol.coinchange2(coins, sum) << endl;

    return 0;
}

