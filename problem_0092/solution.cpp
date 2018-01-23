/*
Tushar's Birthday Party

As it is Tushar’s Birthday on March 1st, he decided to throw a party to all his friends at TGI Fridays in Pune.
Given are the eating capacity of each friend, filling capacity of each dish and cost of each dish. A friend is satisfied if the sum of the filling capacity of dishes he ate is equal to his capacity. Find the minimum cost such that all of Tushar’s friends are satisfied (reached their eating capacity).

NOTE:

Each dish is supposed to be eaten by only one person. Sharing is not allowed.
Each friend can take any dish unlimited number of times.
There always exists a dish with filling capacity 1 so that a solution always exists.
Input Format

Friends : List of integers denoting eating capacity of friends separated by space.
Capacity: List of integers denoting filling capacity of each type of dish.
Cost :    List of integers denoting cost of each type of dish.
Constraints:
1 <= Capacity of friend <= 1000
1 <= No. of friends <= 1000
1 <= No. of dishes <= 1000

Example:

Input:
    2 4 6
    2 1 3
    2 5 3

Output:
    14

Explanation: 
    First friend will take 1st and 2nd dish, second friend will take 2nd dish.

Hint:
As friends cannot share dishes, can we independently calculate the cost for each friend and add them up?
If we calculate answer for each person independently, how different is this from the standard Knapsack problem?

Time for some dynamic thinking!

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
  int solve(const vector<int> &friends, const vector<int> &capacity, const vector<int> &prices);
  int my_solve(const vector<int> &friends, const vector<int> &capacity, const vector<int> &prices);
};

int Solution::my_solve(const vector<int> &friends, const vector<int> &capacity, const vector<int> &prices) {
    if (friends.empty()) return 0;
    int max = *max_element(friends.begin(), friends.end());
    vector<int> cost(max+1, numeric_limits<int>::max());
    cost[0] = 0;
    for (size_t j = 0; j < capacity.size(); ++j) {
        int ca = capacity[j];
        for (int i = ca; i <= max; ++i) {
            if (cost[i-ca] != numeric_limits<int>::max() && cost[i] > cost[i-ca] + prices[j])
                cost[i] = cost[i-ca] + prices[j];
        }
    }

    int sum = 0;
    for (const auto& f: friends)
        sum += cost[f];

    return sum;
}

#define INF 10000000

int dp[1005][1005];

int Solution::solve(const vector<int> &A,  const vector<int> &B, const vector<int> &C){
	// vector of pair {dish_items, dish_cost}
	vector<pair<int,int> > dish;
	int n = C.size();	
	for(int i=0; i<n; i++)	dish.push_back(make_pair(B[i],C[i]));
	
	//maximum capacity among friends
	int m = -1;
	for(int i=0; i<A.size(); i++){
		m = max(m, A[i]);
	}
	
	// dp[highest capacity][no. of dishes]
	for(int i=0; i<=m; i++){
		for(int j = 0; j<=n; j++){
			//if capacity of friend is 0
			if(i == 0) dp[i][j] = 0;
			//if no dish is remaining to choose from
			else if(j==0) dp[i][j] = INF;
			else{
				//if i-th person can eat jth dish
				if(i >= dish[j-1].first){
					//As one dish can be taken multiple times, we have used 
					//dp[ i-dish[j-1].first ][ j ] and not dp[ i-dish[j-1].first ][ j-1 ]. 
					
					dp[i][j] = min(dp[i][j-1], dp[i-dish[j-1].first][j] + dish[j-1].second);
				}
				else dp[i][j] = dp[i][j-1];
			} 
		}	
	}
	
	// Add for each friend independently
	int ans=0;
	for(int i=0; i<A.size(); i++){
		ans += dp[A[i]][n];
	}
	
	return ans;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    int res;
    vector<int> friends, capacity, prices;

    // Expected: 14
    friends = {4, 6};
    capacity = {1, 3};
    prices = {5, 3};

    // Expected: 20
    friends = { 2, 3, 1, 5, 4 };
    capacity = { 3, 2, 4, 1 };
    prices = { 1, 2, 5, 10 };

    res = sol.solve(friends, capacity, prices);
    cout << "Result: " << res << endl;

    return 0;
}

