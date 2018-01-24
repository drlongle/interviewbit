/*
Bulbs

N light bulbs are connected by a wire. Each bulb has a switch associated with it, however due to faulty wiring, a switch also changes the state of all the bulbs to the right of current bulb. Given an initial state of all bulbs, find the minimum number of switches you have to press to turn on all the bulbs. You can press the same switch multiple times.

Note : 0 represents the bulb is off and 1 represents the bulb is on.

Example:
Input : [0 1 0 1]
Return : 4

Explanation :
	press switch 0 : [1 0 1 0]
	press switch 1 : [1 1 0 1]
	press switch 2 : [1 1 1 0]
	press switch 3 : [1 1 1 1]

Hint:
You will never need to press the same switch twice. Why? Because it is equivalent to not pressing the switch and you will end up with the same state as before. So we can always solve the problem in at most n switch flips.
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
    int my_bulbs(vector<int> &nums);

    int bulbs(vector<int> &A) {
        int state= 0, ans = 0;
	for (int i = 0;i < A.size();i++) {
	    if (A[i] == state) {
	        ans++;
	        state = 1 - state;
	    }
        }
        return ans;
    }
};

int Solution::my_bulbs(vector<int> &nums) {
    int res = 0;
    int N = nums.size();
    for (int i = 0; i < N; ++i) {
        if ((nums[i] == 0 && (res & 1) == 0) || (nums[i] && (res & 1) == 1)) {
            ++res;
        }
    }

    return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> nums;
    nums = {0, 1, 0, 1};
    int res = sol.bulbs(nums);
    cout << "Result: " << res << endl;

    return 0;
}

