/*
Flip Array

Given an array of positive elements, you have to flip the sign of some of its elements such that the resultant sum of the elements of array should be minimum non-negative(as close to zero as possible). Return the minimum no. of elements whose sign needs to be flipped such that the resultant sum is minimum non-negative.

Constraints:
1 <= n <= 100
Sum of all the elements will not exceed 10,000.

Example:

A = [15, 10, 6]
ans = 1 (Here, we will flip the sign of 15 and the resultant sum will be 1 )

A = [14, 10, 4]
ans = 1 (Here, we will flip the sign of 14 and the resultant sum will be 0)

Hint:
Let the sum of all the given elements be S. 
This problem can be reduced to a Knapsack problem where we have to fill a Knapsack of capacity (S/2) as fully as possible and using the minimum no. of elements. We will fill the Knapsack with the given elements. Sign of all the elements which come into the knapsack will be flipped.

As sum of all the elements in the Knapsack will be as close to S/2 as possible, we are indirectly calculating minimum non-negative sum of all the elements after flipping the sign. Give it a thought and code your way out!
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
    int solve(const vector<int> &arr);
    int my_solve(const vector<int> &arr);
};

// dp[i][j] = optimal solution for filling a knapsack of capacity j 
//using elements A[1,2,....,i]
//Optimal solution --> knapsack should be filled upto the capacity using least number of elements
struct node {
    int items;
    int weight;
} dp[105][10005];

int Solution::solve(const vector<int>& A){
    int n = A.size();
    int sum = 0;
	
    for(int i=0; i<n; i++) sum+=A[i];
	
    //knapsack algorithm for capacity sum/2
    int temp = sum/2;
	
    for(int i=0; i<=n; i++){
	for(int j=0; j<=temp; j++){
	    if(i==0 || j==0) dp[i][j] = {0, 0};
	    else{
		int prev_items = dp[i-1][j].items;
		int prev_weight = dp[i-1][j].weight;
		if(j-A[i-1] >= 0){
		    int curr_weight = dp[i-1][j-A[i-1]].weight + A[i-1];
		    int curr_items = dp[i-1][j-A[i-1]].items + 1;
					
		    if((curr_weight>prev_weight) ||
                        ((curr_weight==prev_weight) && (curr_items<prev_items))){
			dp[i][j] = {curr_items, curr_weight};
		    }
		    else{
			dp[i][j] = dp[i-1][j];
		    }
		}
		else{
		    dp[i][j] = dp[i-1][j];
		}
	    }
	}
    }

    return dp[n][temp].items;
}

int Solution::my_solve(const vector<int> &nums) {
    long max = 0;
    long sum = accumulate(nums.begin(), nums.end(), 0);
    long limit = (sum >> 1);
    unordered_map<int, int> subsums;
    subsums[0] = 0;
    for (const auto& num: nums) {
        unordered_set<int> skips;
        for (int j = 0; j <= limit; ++j) {
            if (skips.find(j) != skips.end()) continue;
            auto it1 = subsums.find(j);
            if (it1 == subsums.end()) continue;
            int temp = j + num;
            if (temp > limit) continue;
            auto it2 = subsums.find(temp);
            int count = it1->second + 1;
            if (it2 != subsums.end()) {
                if (it2->second > count) {
                    it2->second = count;
                    skips.emplace(temp);
                }
            } else {
                subsums[temp] = count;
                skips.emplace(temp);
            }
            if (temp > max)
                max = temp;
        }
    }

    //cout << "max: " << max << endl;
    return subsums[max];
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> arr;

    // Expected: 1
    arr = {15, 10, 6};

    // Expected: 1
    arr = {14, 10, 4};

    // Expected: 3
    arr = { 8, 4, 5, 7, 6, 2 };

    // Expected: 27
    arr = { 11, 10, 8, 6, 8, 11, 1, 10, 2, 3, 8, 3, 8, 12, 11, 1, 7, 5, 5, 12, 9, 4, 10, 3, 3, 3, 8, 8, 8, 6, 7, 7, 7, 6, 4, 2, 5, 8, 11, 10, 10, 10, 12, 9, 2, 3, 9, 12, 7, 6, 11, 8, 9, 9, 10, 3, 3, 5, 2, 10, 10, 9, 4, 9, 6, 11, 10, 2, 6, 1, 4, 7, 10, 3, 4, 3, 9, 4, 3, 8, 1, 1, 3 };

    cout << "Result: " << sol.solve(arr) << endl;

    return 0;
}

