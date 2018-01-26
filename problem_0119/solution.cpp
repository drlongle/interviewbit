/*
Dungeon Princess

The demons had captured the princess (P) and imprisoned her in the bottom-right
corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid.
Our valiant knight (K) was initially positioned in the top-left room and must
fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at
any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers)
upon entering these rooms; other rooms are either empty (0's) or contain magic
orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move
only rightward or downward in each step.

Write a function to determine the knight's minimum initial health so that he is
able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at
least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)  -3      3
-5      -10     1
10       30     -5 (P)

Notes:
    The knight's health has no upper bound.
    Any room can contain threats or power-ups, even the first room the knight
    enters and the bottom-right room where the princess is imprisoned.
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
    int my_calculateMinimumHP(vector<vector<int> > &dungeon);
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int M = dungeon.size();
        int N = dungeon[0].size();
        // hp[i][j] represents the min hp needed at position (i, j)
        // Add dummy row and column at bottom and right side
        vector<vector<int> > hp(M + 1, vector<int>(N + 1, INT_MAX));
        hp[M][N - 1] = 1;
        hp[M - 1][N] = 1;
        for (int i = M - 1; i >= 0; i--) {
            for (int j = N - 1; j >= 0; j--) {
                int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0]; 
    }

};

vector<vector<int>> cache;

int calculate(vector<vector<int>>& dungeon, int i, int j) {
    if (cache[i][j] != -1)
        return cache[i][j];
    bool isStartCell = (i == 0 && j == 0);
    int cell = dungeon[i][j];
    int result;
    if (cell > 0)
        result = 0;
    else
        result = (isStartCell ? 1 : 0) - dungeon[i][j];
    if (i < static_cast<int>(dungeon.size()) - 1 || j < static_cast<int>(dungeon[0].size())-1)
    {   
        int x = numeric_limits<int>::max(), y = numeric_limits<int>::max();
        if (i < static_cast<int>(dungeon.size()) - 1)
            x = calculate(dungeon, i+1, j);
        if (j < static_cast<int>(dungeon[0].size())-1)
            y = calculate(dungeon, i, j+1);
        if (y < x)
            x = y;
        if (x > 0)
        {
            if (cell > 0)
                x -= cell - (isStartCell ? 1 : 0);
            if (x > 0)
                result += x;
        }
    }
    cache[i][j] = result;

    return result;
}

int Solution::my_calculateMinimumHP(vector<vector<int> > &dungeon) {
    int rows = dungeon.size();
    if (rows == 0 || dungeon[0].size() == 0)
        return 1;
    int columns = dungeon[0].size();
    cache.resize(rows);
    for (int i = 0; i < rows; ++i) {
        cache[i].resize(columns);
        for (int j = 0; j < columns; ++j)
            cache[i][j] = -1;
    }

    int result = calculate(dungeon, 0, 0);
    if (result == 0)
        return 1;
    else
        return result;
}

int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

