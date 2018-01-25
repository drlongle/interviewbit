/*
Best Time to Buy and Sell Stock II
Total Accepted: 90951 Total Submissions: 211842 Difficulty: Medium

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

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
    int maxProfit(vector<int> &prices) {
        int total = 0, sz = prices.size();
        for (int i = 0; i < sz - 1; i++) {
            if (prices[i+1] > prices[i]) total += prices[i+1] - prices[i];
        }
        return total;
    }

    int my_maxProfit(const vector<int>& prices)
    {
        if (prices.empty()) return 0;
        int lowest = prices[0];
        int highest = prices[0];
        int profit = 0;
        int nsize = prices.size();
        for (int i = 1; i < nsize; ++i)
        {
            int p = prices[i];
            if (p < lowest || p < highest)
            {
                profit += highest - lowest;
                lowest = highest = p;
            }
            else if (p > highest)
                highest = p;
        }
        profit += highest - lowest;

        return profit;
    }
};

int main()
{
    Solution sol;
    vector<int> prices;
    // Expected: 2 
    prices = {2,1,2,0,1};

    cout << "Result: " << sol.maxProfit(prices) << endl;
    return 0;
}

