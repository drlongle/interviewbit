/*
Manhattan Distance Neighbourhood

Given a matrix M of size nxm and an integer K, find the maximum element in the K manhattan distance neighbourhood for all elements in nxm matrix. 
In other words, for every element M[i][j] find the maximum element M[p][q] such that abs(i-p)+abs(j-q) <= K.

Note: Expected time complexity is O(N*N*K)

Constraints:

1 <= n <= 300
1 <= m <= 300
1 <= K <= 300
0 <= M[i][j] <= 1000

Example:

Input:
M  = [[1,2,4],[4,5,8]] , K = 2

Output:
ans = [[5,8,8],[8,8,8]]
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
    vector<vector<int> > solve(int distance, vector<vector<int> > &matrix);
    vector<vector<int> > my_solve(int distance, vector<vector<int> > &matrix);
};

bool check(int i, int j, int n, int m){
	//Check if (i,j) are with in matrix dimensions
	if(i >= 0 && j >=0 && i < n && j < m) return 1;
	return 0;
}

vector<vector<int> > Solution::solve(int A, vector<vector<int> > &B) {
	// DP can be optimized to be of N*N size as we need only dp[k-1][n][n] for dp[k][n][n]
	int n = B.size();
	int m = B[0].size();
	
	vector<vector<vector<int> > > dp(2);
	dp[0] = dp[1] = B;
	
	int rplus[4] = {1,0,0,-1};
	int cplus[4] = {0,-1,1,0};
	
	for(int k=0; k <= A; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				//base case
				if( k== 0) dp[k][i][j] = B[i][j];
				//dp[k][i][j] = max(dp[k-1][i-1][j],dp[k-1][i+1][j],dp[k-1][i][j-1],
				 //                                   dp[k-1][i][j+1],dp[k-1][i][j])
				else{
					int ans = dp[(k-1)%2][i][j];
					for(int p = 0; p < 4; p++){
						int temp_i = i+rplus[p];
						int temp_j = j+cplus[p];
						if(check(temp_i, temp_j, n, m)) ans = max(ans, dp[(k-1)%2][temp_i][temp_j]);
					}
					dp[k%2][i][j] = ans;
	
				}
			}
		}
	}
	
	return dp[A%2];
}

vector<vector<int> > Solution::my_solve(int distance, vector<vector<int> > &matrix) {
    vector<vector<vector<int>>> res(2, matrix);
    int M = matrix.size();
    int N = matrix[0].size();
    for (int k = 1; k <= distance; ++k) {
        vector<vector<int>>& curr = res[k % 2];
        vector<vector<int>>& prev = res[1 - k % 2];
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j) {
                int temp = numeric_limits<int>::min();
                if (i > 0 && prev[i-1][j] > temp)
                    temp = prev[i-1][j];
                if (i < M-1 && prev[i+1][j] > temp)
                    temp = prev[i+1][j];
                if (j > 0 && prev[i][j-1] > temp)
                    temp = prev[i][j-1];
                if (j < N-1 && prev[i][j+1] > temp)
                    temp = prev[i][j+1];

                curr[i][j] = max(temp, prev[i][j]);
            }
    }

    return res[distance % 2];
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<int>> matrix, res;
    int K;

    matrix = {{1,2,4},{4,5,8}};
    K = 2;

    res = sol.solve(K, matrix);
    for (const auto& v: res) {
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
        cout << endl;
    }

    return 0;
}

