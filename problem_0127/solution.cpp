/*
Regular Expression Matching

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") -> false
isMatch("aa","aa") -> true
isMatch("aaa","aa") -> false
isMatch("aa", "a*") -> true
isMatch("aa", ".*") -> true
isMatch("ab", ".*") -> true
isMatch("aab", "c*a*b") -> true
isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c") -> false
isMatch("abcd", "d*") -> false
isMatch("aaa", "ab*a") -> false
isMatch("a", "ab*") -> true
isMatch("a", ".*..a*") -> false

Hint:
Think DP.
Can you do something with DP to match prefix of first string with prefix of another string.

Think about the bruteforce solution. 
When you encounter ‘’, you would try to call the same isMatch function in the following manner: 
If p[0] == ‘’, then isMatch(s, p) is true if isMatch(s+1, p) is true OR isMatch(s, p+1) is true. 
else if p[0] is not ‘*’ and the characters s[0] and p[0] match ( or p[0] is ‘?’ ), then isMatch(s,p) is true only if isMatch(s+1, p+1) is true. 
If the characters don’t match isMatch(s, p) is false.

This appraoch is exponential. Think why. 
Lets see how we can make this better. Note that isMatch function can only be called with suffixes of s and p. As such, there could only be length(s) * length(p) unique calls to isMatch. Lets just memoize the result of the calls so we only do processing for unique calls. This makes the time and space complexity O(len(s) * len(p)).

There could be ways of optimizing the approach rejecting certain suffixes without processing them. For example, if len(non star characters in p) > len(s), then we can return false without checking anything.
*/

#include <algorithm>
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

int slen, plen;
bool match(vector<vector<bool>>& cache, const string& s, const string& p, int sindex, int pindex)
{
    if (plen == pindex && slen == sindex)
        return true;
    if (plen == pindex)
        return false;

    if (cache[sindex][pindex])
        return true;

    if (p[pindex] == '*')
        if (match(cache, s, p, sindex, pindex+1) ||
            (slen > sindex && match(cache, s, p, sindex+1, pindex))) {
            cache[sindex][pindex] = true;
            return true;
        }
    if (slen > sindex && (s[sindex] == p[pindex] || p[pindex] == '?') &&
        match(cache, s, p, sindex+1, pindex+1)) {
        cache[sindex][pindex] = true;
        return true;
    } else
        return false;
}

class Solution {
public:
    bool my_isMatch(const string& s, const string& p)
    {
        slen = static_cast<int>(s.size());
        plen = static_cast<int>(p.size());
        vector<vector<bool>> cache(slen+1, vector<bool>(plen+1, 0));

        if (slen > 0 && plen > 0) {
            const char& sback = s.back();
            const char& pback = p.back();
            if (pback != '?' && pback != '*' && pback != sback)
                return false;
        }
        int stars = count_if (p.begin(), p.end(), [](char c){return c == '*';});
        if (plen - stars > slen) return false;

        return match(cache, s, p, 0, 0);
    }

    map<pair<int, int>, int> M;
    int suffixLen[50001], len1, len2;
    bool helper(const char *s, const char *p, int index1, int index2) {
        // If we are at the end of both pattern and the string, then its obviously a match
        if (s[index1] == 0 && p[index2] == 0) return true;
        // If pattern ends, but the string hasn't, then its not a match
        if (p[index2] == 0) return false;
        // If string ends, then the only permissible character is '*' in the pattern array
        if (s[index1] == 0 && p[index2] != '*') return false;
        // If remaining non * characters in pattern are more than the total chars in s, there can't be match
        if (len1 - index1 < suffixLen[index2]) return false;
        // memoized result
        if (M.find(make_pair(index1, index2)) != M.end()) return M[make_pair(index1, index2)];
        // s has ended. We know next character in p is '*'. Lets check other following chars in p
        if (s[index1] == 0) return M[make_pair(index1, index2)] = helper(s, p, index1, index2 + 1);
        // characters match when pattern is not '*'
        if (s[index1] == p[index2] || p[index2] == '?') return M[make_pair(index1, index2)] = helper(s, p, index1 + 1, index2 + 1);
        // If pattern is '*', then explore both possibilities
        if (p[index2] == '*') return M[make_pair(index1, index2)] = (helper(s, p, index1 + 1, index2) || helper(s, p, index1, index2 + 1));
        return M[make_pair(index1, index2)] = false;
    }

    bool isMatch(const char *s, const char *p) {
        M.clear();
        len1 = strlen(s);
        len2 = strlen(p);
        int cnt = 0;
        for (int i = len2 - 1; i >= 0; i--){
            if (p[i] != '*') cnt++;
            suffixLen[i] = cnt;
        }
        return helper(s, p, 0, 0);
    }
};

int main()
{
    Solution solution;
    string s; 
    string p;

    // Expected: true
    s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    p = "a**************************************************************************************";

    // Expected: false
    s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    p = "*b";

    // Expected: true
    //s = "a";
    //p = "?";

    cout << boolalpha << solution.isMatch(s.c_str(), p.c_str()) << endl;
}

