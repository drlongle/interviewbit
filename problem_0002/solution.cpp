/*
Min Steps in Infinite Grid

You are in an infinite 2D grid where you can move in any of the 8 directions:

 (x,y) to 
    (x+1, y), 
    (x - 1, y), 
    (x, y+1), 
    (x, y-1), 
    (x-1, y-1), 
    (x+1,y+1), 
    (x-1,y+1), 
    (x+1,y-1) 

You are given a sequence of points and the order in which you need to cover the
points. Give the minimum number of steps in which you can achieve it. You start
from the first point.

Example :

Input : [(0, 0), (1, 1), (1, 2)]
Output : 2

It takes 1 step to move from (0, 0) to (1, 1). It takes one more step to move
from (1, 1) to (1, 2).
*/

#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include <string.h>

using namespace std;

class Solution {
public:
    int my_coverPoints(vector<int>& x, vector<int>& y) ;

    int coverPoints(vector<int> x, vector<int> y) {
        if (x.size() <= 1) return 0;
        assert(x.size() == y.size());
        int ans = 0;
        for (int i = 1; i < x.size(); i++) {
            ans += max(abs(x[i] - x[i-1]), abs(y[i] - y[i-1]));
        }
        return ans;
    }
};

int Solution::my_coverPoints(vector<int> &X, vector<int> &Y) {
    int size = static_cast<int>(min(X.size(), Y.size()));
    int result = 0;
    int last_x = X[0];
    int last_y = Y[0];

    for (int i = 1; i < size; ++i)
    {
        int diff_x = abs(X[i] - last_x);
        int diff_y = abs(Y[i] - last_y);
        last_x = X[i];
        last_y = Y[i];
        result += max(diff_x, diff_y);
    }

    return result;
}

int main()
{
    Solution sol;
    vector<int> X, Y;
    X = {0, 1, 2, 3, 4, 6};
    Y = {10, 9, 8, 7, 6, 5};

    X = { 0, 1, 1};
    Y = { 0, 1, 2 };
    int result = sol.coverPoints(X, Y);
    cout << "Result: " << result << endl;

    return 0;
}
