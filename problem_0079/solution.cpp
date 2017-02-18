/*
Unique Paths in a Grid

Given a grid of size m * n, lets assume you are starting at (1,1) and your goal is to reach (m,n).
At any instance, if you are on (x,y), you can either go to (x, y + 1) or (x + 1, y).

Now consider if some obstacles are added to the grids. How many unique paths would there be?
An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Example :
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]

The total number of unique paths is 2.

Note: m and n will be at most 100. 
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
    int uniquePathsWithObstacles(vector<vector<int> > &matrix);
};

int Solution::uniquePathsWithObstacles(vector<vector<int> > &matrix)
{
    int m = matrix.size();
    if (m == 0)
        return 0;
    int n = matrix[0].size();

    vector<vector<int>> cache(m, vector<int>(n, 0));
    if (matrix[0][0] == 1 || matrix[m-1][n-1] == 1)
        return 0;
    cache[m-1][n-1] = 1;
    for (int i = m-1; i >= 0; --i)
        for (int j = n-1; j >= 0; --j)
        {
            if (matrix[i][j] == 1)
                continue;
            if (i < m-1)
                cache[i][j] += cache[i+1][j];
            if (j < n-1)
                cache[i][j] += cache[i][j+1];
        }

    return cache[0][0];
}


int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<int>> matrix;
    matrix = { {0,0,0}, {0,1,0}, {0,0,0}};

    cout << "Solution: " << sol.uniquePathsWithObstacles(matrix) << endl;

    return 0;
}

