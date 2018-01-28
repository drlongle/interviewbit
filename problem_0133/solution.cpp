/*
Distinct Subsequences

Given two sequences S, T, count number of unique ways in sequence S, to form a subsequence that is identical to the sequence T.

Subsequence : A subsequence of a string is a new string which is formed from the original string by deleting some (can be none ) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not). 

Example :

S = "rabbbit" 
T = "rabbit"
Return 3. And the formations as follows:

S1= "ra_bbit" 
S2= "rab_bit" 
S3="rabb_it"
"_" marks the removed character.

Hint: Can you solve the problem for some prefix of first string and some prefix of second string and use it to compute the final answer?

Try to think of DP on prefixes of both strings.

Solution approach:
As a typical way to implement a dynamic programming algorithm, we construct a matrix dp, where each cell dp[i][j] represents the number of solutions of aligning substring T[0..i] with S[0..j];

Rule 1). dp[0][j] = 1, since aligning T = “” with any substring of S would have only ONE solution which is to delete all characters in S.

Rule 2). when i > 0, dp[i][j] can be derived by two cases:

case 1). if T[i] != S[j], then the solution would be to ignore the character S[j] and align substring T[0..i] with S[0..(j-1)]. Therefore, dp[i][j] = dp[i][j-1].

case 2). if T[i] == S[j], then first we could adopt the solution in case 1), but also we could match the characters T[i] and S[j] and align the rest of them (i.e. T[0..(i-1)] and S[0..(j-1)]. As a result, dp[i][j] = dp[i][j-1] + d[i-1][j-1]

e.g. T = B, S = ABC

dp[1][2]=1: Align T’=B and S’=AB, only one solution, which is to remove character A in S’.
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
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define ll long long
#define ull unsigned long long

using namespace std;

int slen, tlen;
vector<vector<int>> cached;

class Solution {
public:
    int my_numDistinct(string s, string t);

    /**
     * Solution (DP):
     * We keep a m*n matrix and scanning through string S, while
     * m = T.length() + 1 and n = S.length() + 1
     * and each cell in matrix Path[i][j] means the number of distinct subsequences of 
     * T.substr(1...i) in S(1...j)
     * 
     * Path[i][j] = Path[i][j-1]            (discard S[j])
     *              +     Path[i-1][j-1]    (S[j] == T[i] and we are going to use S[j])
     *                 or 0                 (S[j] != T[i] so we could not use S[j])
     * while Path[0][j] = 1 and Path[i][0] = 0.
     */
    int numDistinct(string S, string T) {
        int m = T.length();
        int n = S.length();
        if (m > n) return 0;    // impossible for subsequence
        vector<vector<int>> path(m + 1, vector<int>(n + 1, 0));
        for (int k = 0; k <= n; k++) path[0][k] = 1;    // initialization

        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= m; i++) {
                path[i][j] = path[i][j - 1] + (T[i - 1] == S[j - 1] ? path[i - 1][j - 1] : 0);
            }
        }

        return path[m][n];
    }
};

int getNumDistinct(string& s, int sindex, string& t, int tindex)
{   
    if (sindex >= slen)
        return 0;
        
    if (cached[sindex][tindex] >= 0)
        return cached[sindex][tindex];
        
    int index = sindex, res = 0;
    char ch = t[tindex];
    while ((index = s.find(ch, index)) != string::npos)
    {   
        res += (tindex+1 == tlen) ? 1 :
            getNumDistinct(s, index+1, t, tindex+1);
        ++index;
    }
    cached[sindex][tindex] = res;

    return res;
}

int Solution::my_numDistinct(string s, string t)
{
    slen = s.size();
    tlen = t.size();
    if (slen == 0 || tlen == 0)
        return 0;
    cached.clear();
    cached.resize(slen, vector<int>(tlen, -1));

    return getNumDistinct(s, 0, t, 0);
}

int main(int argc, const char* argv[])
{
    Solution sol;
    string s, t;

    // Expected: 3
    s = "rabbbit";
    t = "rabbit";

    // Expected: 91439
    // s = "bbabbaabaaababbbaabbabababbbababbaaababbbbaabbbbb";
    // t = "abbbaa";

    cout << "Result: " << sol.numDistinct(s, t) << endl;

    return 0;
}

