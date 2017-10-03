/*
Longest Palindromic Substring

Given a string S, find the longest palindromic substring in S.

Substring of string S:
S[i...j] where 0 <= i <= j < len(S)

Palindrome string:
A string which reads the same backwards. More formally, S is palindrome
if reverse(S) = S.

In case of conflict, return the substring which occurs first ( with the least
starting index ).

Example :
Input : "aaaabaaa"
Output : "aaabaaa"
 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
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

#define ll long long int
#define ull unsigned long long int

using namespace std;

class Solution {
public:
    string my_longestPalindrome(string s);
    
    string expandAroundCenter(string s, int c1, int c2) {
        int l = c1, r = c2;
        int n = s.length();
        while (l >= 0 && r <= n-1 && s[l] == s[r]) {
            l--;
            r++;
        }
        return s.substr(l+1, r-l-1);
    }

    string longestPalindrome(string s) {
        int n = s.length();
        if (n == 0) return "";
        string longest = s.substr(0, 1);// a single char is a palindrome
        for (int i = 0; i < n-1; i++) {
            string p1 = expandAroundCenter(s, i, i);
            if (p1.length() > longest.length())
                longest = p1;

            string p2 = expandAroundCenter(s, i, i+1);
            if (p2.length() > longest.length())
                longest = p2;
        }
        return longest;
    }
};

string findLongestPalindrome(const string& s, int i, int j)
{
    while (i > 0 && j < static_cast<int>(s.size())-1) {
        if (s[i-1] == s[j+1]) {
            --i;
            ++j;
        } else
            break;
    }
    return s.substr(i, j-i+1);
}

string Solution::my_longestPalindrome(string s) {
    string res;
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        string temp = findLongestPalindrome(s, i,i);
        if (temp.size() > res.size())
            res = temp;
        if (i > 0 && s[i] == s[i-1]) {
            temp = findLongestPalindrome(s,i-1,i);
            if (temp.size()>res.size())
                res = temp;
        }
    }
    return res;
}

int main()
{
    Solution sol;
    string input;

    input = "aabbacde";
    cout << "Result: " << sol.longestPalindrome(input) << endl;

    return 0;
}
