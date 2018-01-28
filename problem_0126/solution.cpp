/*
Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring. For "(()", the longest valid parentheses substring is "()", which has length = 2. Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.

Hint:
If you know the longest parenthesis ending at index i, can you use that to compute answer?
Try to simulate using stack and DP.

Lets construct longest[i] where longest[i] denotes the longest set of parenthesis ending at index i.

If s[i] is ‘(‘, set longest[i] to 0, because any string end with ‘(‘ cannot be a valid one.
Else if s[i] is ‘)’ 
If s[i-1] is ‘(‘, longest[i] = longest[i-2] + 2 
Else if s[i-1] is ‘)’ and s[i-longest[i-1]-1] == ‘(‘, longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2]
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
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
#include <vector>

#include <string.h>

using namespace std;

class Solution {
public:
    int my_longestValidParentheses(string s)
    {
        int ssize = s.size();
        if (!ssize) return 0;
        int res = 0;
        vector<int> longest(ssize, 0);
        for (int i = 1; i < ssize; ++i) {
            if (s[i] == '(') continue;
            else if (s[i-1] == '(')
                longest[i] = 2 + (i >= 2 ? longest[i-2] : 0);
            else {
                int temp = longest[i-1];
                if (i - temp -1 >= 0 && s[i - temp -1] == '(')
                    longest[i] = longest[i-1] + 2 + longest[i-temp-2];
            }
            if (longest[i] > res) res = longest[i];
        }

        return res;
    }

    int longestValidParentheses(string s) {
        if (s.length() <= 1) return 0;
        int curMax = 0;
        vector<int> longest(s.size(), 0);
        for (int i = 1; i < s.length(); i++) {
            if (s[i] == ')' && i - longest[i - 1] - 1 >= 0 && s[i - longest[i - 1] - 1] == '(') {
                longest[i] = longest[i - 1] + 2 + ((i - longest[i - 1] - 2 >= 0) ? longest[i - longest[i - 1] - 2] : 0);
                curMax = max(longest[i], curMax);
            }
        }
        return curMax;
    }

};

int main()
{
    Solution sol;
    string s;

    // Expected: 22 
    s = ")(((((()())()()))()(()))(";
 
    // Expected: 22 
    s = "(())(())))())()())())())()))))((())()())))))))(()((()((()()())((()())))()(()(())((()(((((())())))))(";

    cout << "Result: " << sol.longestValidParentheses(s) << endl;

    return 0;
}
