/*
Largest area of rectangle with permutations

Given a binary grid i.e. a 2D grid only consisting of 0’s and 1’s, find the area of the largest rectangle inside the grid such that all the cells inside the chosen rectangle should have 1 in them. You are allowed to permutate the columns matrix i.e. you can arrange each of the column in any order in the final grid. Please follow the below example for more clarity.

Lets say we are given a binary grid of 3 * 3 size.

1 0 1
0 1 0
1 0 0

At present we can see that max rectangle satisfying the criteria mentioned in the problem is of 1 * 1 = 1 area i.e either of the 4 cells which contain 1 in it. Now since we are allowed to permutate the columns of the given matrix, we can take column 1 and column 3 and make them neighbours. One of the possible configuration of the grid can be:

1 1 0
0 0 1
1 0 0

Now in this grid, first column is column 1, second column is column 3 and third column is column 2 from the original given grid. Now, we can see that if we calculate the max area rectangle, we get max area as 1 * 2 = 2 which is bigger than the earlier case. Hence 2 will be the answer in this case.

Hint:
Brute force approach would be to generate each possible permutations of the columns and then check which one generates the rectangle with the maximum area. 
Time Complexity of this approach would be 2^m * T where m denotes the number of columns and T denotes the time required to get the maximum area for a given grid. Now as this method takes exponential time, we can’t use it as a solution to our problem because of higher constraints on the values of n and m. 
 Now you have got the basic idea. Can you improve it by thinking any polynomial time solution? 

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
    int my_solve(vector<vector<int> > &matrix);
    int solve(vector<vector<int> > &matrix);
};

int Solution::my_solve(vector<vector<int> > &matrix) {
    int M = matrix.size();
    int N = matrix[0].size();
    vector<vector<int>> height(M, vector<int>(N));

    for (int i = M-1; i >= 0; --i) {
        for (int j = N-1; j >= 0; --j) {
            if (matrix[i][j])
                height[i][j] = 1 + ((i == M-1) ? 0 : height[i+1][j]);
        }
    }

    int area = 0;
    for (int i = 0; i < M; ++i) {
        map<int, int> count_heights;
        for (int j = 0; j < N; ++j) {
            ++count_heights[height[i][j]];
        }
        int res = 0;
        for (const auto& c: count_heights) {
            if (c.first * (N-res) > area)
                area = c.first * (N-res);
            res += c.second;
        }
    }

    return area;
}

int Solution::solve(vector<vector<int> > &A) {
	int n, m, res = 0;
	n = A.size();
	m = A[0].size();
	int dp[n+1][m+1];
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			if(A[j-1][i-1] == 0) {
				dp[j][i] = 0;
			}
			else {
				dp[j][i] += dp[j-1][i] + 1;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		int arr[n + 1], cnt = 0;
		memset(arr, 0, sizeof(arr));
		for (int j = 1; j <= m; ++j) {
			arr[dp[i][j]] ++;
		}
		for (int j = n; j >= 0; --j) {
			cnt += arr[j];
			res = max(res, cnt * j);
		}
	}
	return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<int>> matrix;

    matrix = {{1, 0, 1}, {0, 1, 0}, {1, 0, 0}};

    int res = sol.solve(matrix);
    cout << "Result: " << res << endl;

    return 0;
}

