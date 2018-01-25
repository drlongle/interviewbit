/*
Stepping Numbers

Given N and M find all stepping numbers in range N to M

The stepping number:

A number is called as a stepping number if the adjacent digits have a difference of 1.
e.g 123 is stepping number, but 358 is not a stepping number.

Example:

N = 10, M = 20
all stepping numbers are 10 , 12 

Return the numbers in sorted order.

Hint:
Assume that we have a graph where the starting node is 0 and we need to traverse it from the start node to all the reachable nodes.

With the restrictions given in the graph about the stepping numbers, what do you think should be the restrictions defining the next transitions in the graph.

Solution:
Lets take a example:

N = 10 M = 20
start node = 0
From 0, we can move to 1 2 3 4 5 6 7 8 9 [ these are not in our range so we don't add it ]
now from 1, we can move to 12 and 10 
from 2, 23 and 21
from 3, 34 and 32
.
.
.
.
.
.
and so on

10 and 12 are in our range, so the answer = 2.
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
    vector<int> my_stepnum(int A, int B);

    vector<int> Ans;
    void dfs(int len, int N, int M, int num = 0) {
        if(num >= N && num <= M) {
            Ans.push_back(num);
        }
        if(len == 0)
            return;

        if(num == 0) {
            for(int i = 1; i <= 9; ++i) {
                dfs(len - 1, N, M, i);
            }
            return;
        }

        int last_dig = num%10;
        if(last_dig == 0) {
            dfs(len - 1, N, M, (num * 10) + (last_dig + 1));
        } else if(last_dig == 9) {
            dfs(len - 1, N, M, (num * 10) + (last_dig - 1));
        } else {
            dfs(len - 1, N, M, (num * 10) + (last_dig - 1));
            dfs(len - 1, N, M, (num * 10) + (last_dig + 1));
        }
    }

    vector<int> stepnum(int N, int M) {
        int len = 0;
        int temp = M;
        while(temp) {
            temp /= 10;
            len++;
        }

        Ans.clear();
        dfs(len, N, M);
        sort(Ans.begin(), Ans.end());
        return Ans;
    }
};

void step_numbers(set<int>& nums, string& s, int size, int index) {

    if (index == size) {
        nums.emplace(stoi(s));
        return;
    }

    char ch = s[index-1];
    if (ch > '0') {
        s[index] = ch - 1;
        step_numbers(nums, s, size, index+1);
    }
    if (ch < '9') {
        s[index] = ch + 1;
        step_numbers(nums, s, size, index+1);
    }
}

void step_numbers(set<int>& nums, int size)
{
    string s(size, '0');
    for (char ch = '0'; ch <= '9'; ++ch) {
        s[0] = ch;
        step_numbers(nums, s, size, 1);
    }
}

vector<int> Solution::my_stepnum(int A, int B) {
    vector<int> res;
    set<int> stepnums;
    for (size_t i = 1; i <= to_string(max(A, B)).size(); ++i)
        step_numbers(stepnums, i);
    for (auto it = stepnums.lower_bound(A); it != stepnums.end() && *it <= B; ++it)
        res.emplace_back(*it);

    return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<int> res;
    int A, B;

    // Expected: 10, 12
    A = 10;
    B = 20;

    // Expected: 0 1 2 3 4 5 6 7 8 9 10 12 21 23 32 34 43 45 54 56 65 67 76 78
    A = 0;
    B = 86;

    // Expected: 21 23 32 34 43 45 54 56 65 67 76 78 87 89 98
    A = 15;
    B = 99;

    res = sol.stepnum(A, B);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, ", "));

    return 0;
}

