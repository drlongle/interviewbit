/*
Word Break II

    Total Accepted: 59700
    Total Submissions: 293118
    Difficulty: Hard

Given a string s and a dictionary of words dict, add spaces in s to construct
a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

Make sure the strings are sorted in your result.
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
    vector<string> wordBreak(string s, vector<string> &dictV) {
        unordered_set<string> dict(dictV.begin(), dictV.end());
        vector<vector<string> > words(s.length() + 1, vector<string>(0));

        // initialize the valid values
        words[s.length()].push_back("");

        // generate solutions from the end
        for(int i = s.length() - 1; i >= 0; i--) {
            vector<string> values;
            for(int j = i + 1; j <= s.length(); j++) {
                if (dict.find(s.substr(i, j - i)) != dict.end()) {
                    for (int k = 0; k < words[j].size(); k++) {
                        values.push_back(s.substr(i, j - i) +
                            (words[j][k].empty() ? "" : " ") + words[j][k]);
                    }
                }
            }
            words[i] = values;
        }
        return words[0];
    }
};

int main()
{
    return 0;
}

