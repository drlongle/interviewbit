/*
Word Break

Given a string s and a dictionary of words dict, determine if s can be segmented
into a space-separated sequence of one or more dictionary words.

For example, given

s = "myinterviewtrainer",
dict = ["trainer", "my", "interview"].

Return 1 ( corresponding to true ) because "myinterviewtrainer" can be segmented
as "my interview trainer".

Return 0 / 1 ( 0 for false, 1 for true ) for this problem

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
private:
    short memoize[100001];

public:
    bool wordBreak(int index, string &s, unordered_set<string> &dict) {
        if (index >= s.length()) return true;
        if (memoize[index] != -1) return memoize[index];
        bool result = false;
        // try to construct all substrings. 
        string substring = "";
        for (int i = index; i < s.length() && result == false; i++) {
            substring.push_back(s[i]);
            if (dict.find(substring) != dict.end()) {
                result |= wordBreak(i + 1, s, dict);
            }
        }
        return memoize[index] = result;
    }

    bool wordBreak(string s, vector<string> &dict) {
        memset(memoize, -1, sizeof(int) * s.length());
        unordered_set<string> dictSet(dict.begin(), dict.end());
        return wordBreak(0, s, dictSet);
    }
};

int main()
{
    Solution sol;

    return 0;
}

