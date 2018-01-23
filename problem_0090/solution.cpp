/*
Ways to color a 3xN Board

Given a 3Xn board, find the number of ways to color it using at most 4 colors such that no two adjacent boxes have same color. Diagonal neighbors are not treated as adjacent boxes. 
Output the ways % 1000000007 as the answer grows quickly.

1<= n < 100000

Example:
Input: n = 1
Output: 36

Hint: Suppose that you filled a given column in 3Xn board with a triplet of colors. Which
other triplets can you use to fill the next column?
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

const int MOD = 1000000007;

class Solution {
public:
    int solve(int num);
};

#define mod 1000000007
#define ll long long

struct triplet{
	int x, y, z;
};

vector<triplet> trip;  //vector of 36 triplets

void fillTriplets(){
	//trip vector contain the triplets of color that can be used to paint a certain column
       trip.clear();
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				if(i!=j && j!=k) trip.push_back({i,j,k});
			}
		}
	}
}

int dp[4][4][4][100005];


bool isCompatible(const triplet& t1,  const triplet& t2){
	//check if triplets t1 and t2 are compatible
	if(t1.x==t2.x || t1.y==t2.y || t1.z==t2.z ){
		return 0;
	}
	return 1;
}

int Solution::solve(int n){
        fillTriplets();
	if(n<=0) return -1;
	
       //Bottom-up dp
	for(int i=1; i<=n; i++){
		for(int j=0; j<36; j++){
			if(i==1) dp[trip[j].x][trip[j].y][trip[j].z][i] = 1;
			else{
				ll temp = 0;
				
				for(int k=0; k<36; k++){
					if(isCompatible(trip[j], trip[k])){
						temp += dp[trip[k].x][trip[k].y][trip[k].z][i-1];
						temp %= mod;
					}
				}
				dp[trip[j].x][trip[j].y][trip[j].z][i] = temp;
			}
		}
	}
	
	ll ans = 0;
	for(int i=0; i<trip.size(); i++){
		ans = (ans + dp[trip[i].x][trip[i].y][trip[i].z][n])%mod;
	}

	return ans;
}
int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

