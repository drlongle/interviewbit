/*
Grid Unique Paths

A robot is located at the top-left corner of an A x B grid.
The robot can only move either down or right at any point in time. The robot is
trying to reach the bottom-right corner of the grid.

How many possible unique paths are there?

Note: A and B will be such that the resulting answer fits in a 32 bit signed
integer.

Example :
Input : A = 2, B = 2
Output : 2

2 possible routes : (0, 0) -> (0, 1) -> (1, 1) 
              OR  : (0, 0) -> (1, 0) -> (1, 1)
*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <functional>
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

using namespace std;

int countPaths(int x, int y, int A, int B, vector<vector<int> >& cache)
{
    if (x == A && y == B) return 1;
    if (cache[x][y] > 0)
        return cache[x][y];

    int result = 0;
    if (x < A)
        result += countPaths(x+1,y,A,B, cache);
    if (y < B)
        result += countPaths(x,y+1,A,B, cache);
    cache[x][y] = result;
    return result;
}

class Solution {
public:
    int my_uniquePaths(int A, int B);

    int uniquePaths(int m, int n) {
        // m+n-2 C n-1 = (m+n-2)! / (n-1)! (m-1)!
        long long ans = 1;
        for (int i = n; i < (m + n - 1); i++) {
            ans *= i;
            ans /= (i - n + 1);
        }
        return (int)ans;
    }
};

int Solution::my_uniquePaths(int A, int B) {
    if (!A || !B || A == 1 || B == 1)
        return 1;
    vector<vector<int> > cache(A, vector<int>(B,-1));
    return countPaths(0, 0, A-1,B-1, cache);
}

int main()
{
    Solution sol;
    int result;
    int A, B;

    cout << "A: ";
    cin >> A;
    cout << "B: ";
    cin >> B;
    result = sol.uniquePaths(A,B);
    cout << "Result: " << result << endl;

    return 0;
}
