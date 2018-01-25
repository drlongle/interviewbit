/*
Best Time to Buy and Sell Stocks I

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Example :

Input : [1 2]
Return :  1
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
    int my_maxProfit(const vector<int>& prices) {
        if (prices.empty()) return 0;
        int lowest = prices[0];
        int max_profit = 0;
        int nsize = prices.size();
        for (int i = 1; i < nsize; ++i)
        {
            if (prices[i] < lowest)
                lowest = prices[i];
            int temp = prices[i] - lowest;
            if (temp > max_profit)
                max_profit = temp;
        }
        return max_profit;
    }

    int maxProfit(vector<int> &prices) {
        int sz = prices.size();
        int maxTillNow = -1000000000, maxGain = 0;
        for (int i = sz - 1; i >= 0; i--) {
            maxGain = max(maxGain, maxTillNow - prices[i]);
            maxTillNow = max(maxTillNow, prices[i]);
        }
        return maxGain;
    }
};

int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

