/*
Best Time to Buy and Sell Stock III
Total Accepted: 59329 Total Submissions: 222129 Difficulty: Hard

Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).


Hint: Think DP.
What are the essential things you need to keep in your DP states?
You will need to store maximum number of transactions you can do in any suffix/prefix of array.

What if you construct your DP space as :
f[k, ii] represents the max profit up until prices[ii]
(Note: NOT ending with prices[ii]) using at most k transactions
How would you fill in values in f[k, ii] and how would the DP relations look like.

Hint:
https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-share-at-most-k-times/
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

    int maxProfit(const vector<int>& price, int k)
    {
        int n = price.size();

        // table to store results of subproblems
        // profit[t][i] stores maximum profit using
        // atmost t transactions up to day i (including
        // day i)
        int profit[k+1][n+1];
 
        // For day 0, you can't earn money
        // irrespective of how many times you trade
        for (int i = 0; i <= k; i++)
            profit[i][0] = 0;
 
        // profit is 0 if we don't do any transation
        // (i.e. k =0)
        for (int j = 0; j <= n; j++)
            profit[0][j] = 0;

        // fill the table in bottom-up fashion
        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j < n; j++)
            {
                int max_so_far = INT_MIN;
                for (int m = 0; m < j; m++)
                    max_so_far = max(max_so_far,
                                     price[j] - price[m] + profit[i-1][m]);
                profit[i][j] = max(profit[i][j-1], max_so_far);
            }
        }

        return profit[k][n-1];
    }

    int maxProfit2(const vector<int>& prices)
    {
        return maxProfit(prices, 2);
    }

    int maxProfit(const vector<int> &prices) {
        // f[k, ii] represents the max profit up until prices[ii]
        // (Note: NOT ending with prices[ii]) using at most k transactions. 
        // f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
        //          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
        // f[0, ii] = 0; 0 times transation makes 0 profit
        // f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade

        if (prices.size() <= 1) return 0;
        int K = 2; // number of max transation allowed
        int maxProf = 0;
        vector<vector<int> > f(K+1, vector<int>(prices.size(), 0));
        for (int kk = 1; kk <= K; kk++) {
            int tmpMax = f[kk-1][0] - prices[0];
            for (int ii = 1; ii < prices.size(); ii++) {
                f[kk][ii] = max(f[kk][ii-1], prices[ii] + tmpMax);
                tmpMax = max(tmpMax, f[kk-1][ii] - prices[ii]);
                maxProf = max(f[kk][ii], maxProf);
            }
        }

        return maxProf;
    }

};

int main()
{
    Solution sol;
    vector<int> prices;
    prices = {2,1,2,0,1};

    cout << "Result: " << sol.maxProfit(prices) << endl;

    return 0;
}

