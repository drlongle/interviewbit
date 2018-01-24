/*
Assign Mice to Holes

There are N Mice and N holes are placed in a straight line.
Each hole can accomodate only 1 mouse.
A mouse can stay at his position, move one step right from x to x + 1, or move one step left from x to x − 1. Any of these moves consumes 1 minute.
Assign mice to holes so that the time when the last mouse gets inside a hole is minimized.

Example:

positions of mice are: 4 -4 2
positions of holes are: 4 0 5

Assign mouse at position x=4 to hole at position x=4 : Time taken is 0 minutes 
Assign mouse at position x=-4 to hole at position x=0 : Time taken is 4 minutes 
Assign mouse at position x=2 to hole at position x=5 : Time taken is 3 minutes 
After 4 minutes all of the mice are in the holes.

Since, there is no combination possible where the last mouse's time is less than 4, 
answer = 4.

Input:

A :  list of positions of mice
B :  list of positions of holes

Output: single integer value

NOTE: The final answer will fit in a 32 bit signed integer. 

Hint : Sorting. Can some greedy approach work here ?

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
    int my_mice(vector<int> &mice, vector<int> &holes);
    int mice(vector<int> &mice, vector<int> &Hole) {
        int N = mice.size();
        sort(mice.begin(), mice.end());
        sort(Hole.begin(), Hole.end());

        int ans = 0;
        for(int i = 0; i < N; ++i) {
            ans = max(ans, abs(mice[i] - Hole[i]));
        }
        return ans;
    }

};

int Solution::my_mice(vector<int> &mice, vector<int> &holes) {
    sort(mice.begin(), mice.end());
    sort(holes.begin(),holes.end());
    int res = 0;
    for(int i = 0; i< mice.size();i++){
        res = max(res, abs(mice[i]-holes[i]));
    }

    return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> mice, holes;
    int res;

    // Expected: 4
    mice = {4, -4, 2};
    holes = {4, 0, 5};

    // Expected: 28
    mice = { -49, 58, 72, -78, 9, 65, -42, -3 };
    holes = { 30, -13, -70, 58, -34, 79, -36, 27 };

    res = sol.mice(mice, holes);
    cout << "Result: " << res << endl;

    return 0;
}

