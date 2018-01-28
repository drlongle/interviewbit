/*
Regular Expression II

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
It might seem deceptively easy even you know the general idea, but programming it correctly with all the details require careful thought.

Think carefully how you would do matching of ‘’. Please note that ‘’ in regular expression is different from wildcard matching, as we match the previous character 0 or more times. But, how many times? If you are stuck, recursion is your friend.

This problem is a tricky one. Due to the huge number of edge cases, many people would write lengthy code and have numerous bugs on their first try. Try your best getting your code correct first, then refactor mercilessly to as clean and concise as possible!

This looks just like a straight forward string matching, isn’t it? Couldn’t we just match the pattern and the input string character by character? The question is, how to match a '*' ?

A natural way is to use a greedy approach; that is, we attempt to match the previous character as many as we can. Does this work? Let us look at some examples.

s = “abbbc”
p = “ab*c”
Assume we have matched the first ‘a’ on both s and p. When we see "b*" in p, we skip all b’s in s. Since the last ‘c’ matches on both side, they both match.

s = “ac”
p = “ab*c”
After the first ‘a’, we see that there is no b’s to skip for “b*”. We match the last ‘c’ on both side and conclude that they both match.

It seems that being greedy is good. But how about this case?

s = “abbc”
p = “ab*bbc”
When we see “b*” in p, we would have skip all b’s in s. They both should match, but we have no more b’s to match. Therefore, the greedy approach fails in the above case.

One might be tempted to think of a quick workaround. How about counting the number of consecutive b’s in s? If it is smaller or equal to the number of consecutive b’s after “b*” in p, we conclude they both match and continue from there. For the opposite, we conclude there is not a match.

This seem to solve the above problem, but how about this case:

s = “abcbcd” 
p = “a.*c.*d”
Here, “.*” in p means repeat ‘.’ 0 or more times. Since ‘.’ can match any character, it is not clear how many times ‘.’ should be repeated. Should the ‘c’ in p matches the first or second ‘c’ in s? Unfortunately, there is no way to tell without using some kind of exhaustive search.

We need some kind of backtracking mechanism such that when a matching fails, we return to the last successful matching state and attempt to match more characters in s with ‘*’. This approach leads naturally to recursion.

The recursion mainly breaks down elegantly to the following two cases:

If the next character of p is NOT ‘*’, then it must match the current character of s. Continue pattern matching with the next character of both s and p.
If the next character of p is ‘*’, then we do a brute force exhaustive matching of 0, 1, or more repeats of current character of p… Until we could not match any more characters.

You would need to consider the base case carefully too. That would be left as an exercise to the reader. :)
*/

#include <algorithm>
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

int slen, plen;
bool match(const string& s, const string& p, int sindex, int pindex, vector<vector<bool>>& cache)
{
    if (plen == pindex && slen == sindex)
        return true;
    if (plen == pindex)
        return false;
    if (cache[sindex][pindex]) return true;
    if (plen > pindex+1 && p[pindex+1] == '*') {
        if (match(s, p, sindex, pindex+2, cache)) {
            cache[sindex][pindex] = true;
            return true;
        }
        if (s[sindex] == p[pindex] || p[pindex] == '.')
            for (int i = sindex; i < slen; ++i) {
                if (s[i] != s[sindex] && p[pindex] != '.')
                    break;
                if (match(s, p, i+1, pindex+2, cache)) {
                    cache[sindex][pindex] = true;
                    return true;
                }
            }
    }

    if (slen > sindex && (s[sindex] == p[pindex] || p[pindex] == '.') &&
        match(s, p, sindex+1, pindex+1, cache)) {
        cache[sindex][pindex] = true;
        return true;
    } else
        return false;
}

// Editoral solution
bool isMatch(const char* s, const char *p) {
    assert(s && p);
    if (p == '\0') return *s == '\0';

    // next char is not '*': must match current character
    if (*(p+1) != '*') {
        assert(*p != '*');
        return ((*p == *s) || (*p == '.' && *s != '\0')) && isMatch(s+1, p+1);
    }

    // next char is '*'
    while ((*p == *s) || (*p == '.' && *s != '\0')) {
        if (isMatch(s, p+2)) return true;
        s++;
    }
    return isMatch(s, p+2);
}

class Solution {
public:
    int my_isMatch(const string s, const string p)
    {
        slen = static_cast<int>(s.size());
        plen = static_cast<int>(p.size());
        vector<vector<bool>> cache(slen+1, vector<bool>(plen+1, false));

        return match(s, p, 0, 0, cache);
    }

    int isMatch(const string &s, const string &p) {
    // Do not write main() function.
    // Do not read input, instead use the arguments to the function.
    // Do not print the output, instead return values as specified
    // Still have a doubt. Checkout www.interviewbit.com/pages/sample_codes/ for more details
    int m = s.size();
    int n = p.size();
    vector<bool>dp(n+1);
    dp[0] = true;
    for (int j = 1; j<n; j+=2) {
        if (p[j] == '*') {
            dp[j+1] = true;
        } else {
            break;
        }
    }
    bool next, pre;
    for (int i = 1; i<=m; ++i) {
        pre = dp[0];
        dp[0] = false;
        for (int j = 1; j<=n; ++j) {
            next = false;
            if (p[j-1] != '*') {
                if (pre && (s[i-1] == p[j-1] || '.' == p[j-1])) next = true;
            } else if (j>1) {
                if (dp[j-1] || dp[j-2] || (dp[j] && (s[i-1] == p[j-2] || '.' == p[j-2]))) next = true;
            }
            pre = dp[j];
            dp[j] = next;
        }
    }
    return dp[n];
}

};

int main()
{
    Solution solution;
    string s; 
    string p;

    s = "p";
    p = "p*";

    cout << "Result: " << boolalpha << solution.isMatch(s, p) << endl;
}

