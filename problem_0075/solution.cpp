/*
Max Sum Without Adjacent Elements
Given a 2 * N Grid of numbers, choose numbers such that the sum of the numbers
is maximum and no two chosen numbers are adjacent horizontally, vertically or diagonally, and return it.

Example:

Grid:
	1 2 3 4
	2 3 4 5
so we will choose
3 and 5 so sum will be 3 + 5 = 8
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
    int adjacent(vector<vector<int> > &matrix);
};

int Solution::adjacent(vector<vector<int> > &matrix) {
    int n = static_cast<int>(matrix[0].size());
    vector<int> cache(n);

    if (n == 0)
        return 0;
    for (int i = n-1; i >= 0; --i) {
        cache[i] = max(0, max(matrix[0][i], matrix[1][i]));
        if (i < n-2)
            cache[i] += cache[i+2];
        if (i < n-1 && cache[i+1] > cache[i])
            cache[i] = cache[i+1];
    }

    return cache[0];
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<int>> matrix = { {1, 2, 3, 4}, {2, 3, 4, 5}};
    cout << "Result: " << sol.adjacent(matrix) << endl;

    return 0;
}

