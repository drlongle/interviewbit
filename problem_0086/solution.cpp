/*
Sub Matrices with sum Zero

Given a 2D matrix, find the number non-empty sub matrices, such that the sum of the elements inside the sub matrix is equal to 0. (note: elements might be negative).

Example:

Input

-8 5  7
3  7 -8
5 -8  9
Output
2

Iterate over all pairs of rows. When fixing two rows r1 and r2, we can convert this to 1D version of the problem.

When we have a 1D array ARR we want to find number of subarrays such that the sum of the elements in the subarray is equal to 0. To do that lets iterate from left to right, say we are currently at i-th element. If we have i-th prefix sum equal to sum(ARR[0..i]), then we want to find number of such j’s that sum(ARR[0..i]) = sum(ARR[0..j]). That means that the subarray ARR[j + 1..i] will have zero sum. To efficiently count number of such j’s we can use a HashMap (unordered_map in C++).

In order to convert the problem to 1D, when we have a pair of fixed rows r1 and r2, we will keep a 2D prefix sums, let’s call it PRE (let’s also assume that initial matrix is A). PRE[i, j] will be the sum of elements in sub matrix whose upper left corner is [0, 0] and lower right corner is [i, j]. In other words it is a sum of all A[p, q] where 0 <= p <= i and 0 <= q <= j. 
The calculation of PRE is very easy: PRE[i, j] = A[i, j] + PRE[i - 1, j] + PRE[i, j - 1] - PRE[i - 1, j - 1] (if i - 1 or j - 1 are less than 0 then we just omit the terms where they appear). Notice, that we need to subtract PRE[i - 1, j - 1] since it is contained in both PRE[i - 1, j] and PRE[i, j - 1] and we want every element to appear in PRE[i, j] exactly once. This is called inclusion exclusion principle.

When we have two fixed rows r1, r2 and have calculated PRE, we can obtain ARR. Note that we don’t really need to calculate each element of ARR, since we only need prefix sums of ARR, that is sum(ARR[0..i]) for each i. The sum(ARR[0..i]) is equal to PRE[r2][i] - PRE[r1 - 1][i] (if r1 - 1 < 0 then omit second operand). Being able to efficiently calculate sum(ARR[0..i]), let’s apply the 1D solution.

The answer to the problem will be simply the sum of answers for all different pairs of rows.

Overall time complexity is O(N^3).
Space complexity is O(N^2)
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
    int solve(vector<vector<int> > &matrix);
    int my_solve(vector<vector<int> > &matrix);
};

int count_zero(const vector<int>& pre)
{
    int res = 0;
    unordered_map<int, int> cache;

    for (size_t i = 0; i < pre.size(); ++i)
    {
        if (!pre[i])
            ++res;
        auto it = cache.find(pre[i]);
        if (it != cache.end())
            res += it->second;
        ++cache[pre[i]];
    }

    return res;
}

int Solution::my_solve(vector<vector<int> > &matrix) {
    int height = matrix.size();
    if (!height) return 0;
    int width = matrix[0].size();
    int res = 0;

    vector<int> arr(width);
    vector<vector<int>> pre(height, vector<int>(width, 0));
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            pre[i][j] = matrix[i][j];
            if (i > 0)
                pre[i][j] += pre[i-1][j];
            if (j > 0)
                pre[i][j] += pre[i][j-1];
            if (i > 0 && j > 0)
                pre[i][j] -= pre[i-1][j-1];
        }
        // for the full blocks
        res += count_zero(pre[i]);
    }

    for (int r1 = 1; r1 < height; ++r1)
        for (int r2 = r1; r2 < height; ++r2)
        {
            for (int i = 0; i < width; ++i)
            {
                arr[i] = pre[r2][i];
                arr[i] -= pre[r1-1][i];
            }
            // for the blocks from line r1 to line r2
            res += count_zero(arr);
        }

    return res;
}

int Solution::solve(vector<vector<int>> &A) {
    int r = A.size(); 
    if(!r) return 0; 
    int c = A[0].size(); 
    if(!c) return 0;

    vector<vector<int> > pre;

    pre.resize(r, vector<int>(c, 0));

    for(int i = 0; i < r; ++i) {
	for(int j = 0; j < c; ++j) {
	    pre[i][j] = A[i][j];
	    if(i) pre[i][j] += pre[i - 1][j];
	    if(j) pre[i][j] += pre[i][j - 1];
	    if(i && j) pre[i][j] -= pre[i - 1][j - 1];
	}
    }

    int ans = 0;
    for(int r1 = 0; r1 < r; ++r1) {
	for(int r2 = r1; r2 < r; ++r2) {
	    unordered_map<int, int> count;
	    count[0] = 1;
	    for(int j = 0; j < c; ++j) {
		int val = pre[r2][j];
		if(r1) val -= pre[r1 - 1][j];
		    ans += count[-val];
		count[val]++;
	    }
	}
    }

    return ans; 
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<int>> matrix;

    // Expected: 2
    matrix = { {-8, 5, 7}, {3, 7, -8}, {5, -8, 9} };

    // Expected: 9
    matrix = { {0,0}, {0,0} };

    // Expected: 18
    matrix = { {0, 0, 0}, {0, 0, 0} };

    // Expected: 5
    matrix = { {1, -1}, {-1, 1} };

    cout << "Result: " << sol.solve(matrix) << endl;

    return 0;
}

