/*
Window String

Given a string S and a string T, find the minimum window in S which will
contain all the characters in T in linear time complexity.

Note that when the count of a character C in T is N, then the count of C in
minimum window in S should be at least N.

Example :

S = "ADOBECODEBANC"
T = "ABC"

Minimum window is "BANC"

Note:
  If there is no such window in S that covers all characters in T, return the empty string ''.
  If there are multiple such windows, return the first occurring minimum window ( with minimum start index ).

*/

#include <algorithm>
#include <cassert>
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
    string my_minWindow(string S, string T);
    string minWindow(string S, string T) {
        if (S.length() < T.length()) return "";
        unordered_map<char, int> counts;
        for (int i = 0; i < T.length(); i++) {
            if (counts.find(T[i]) == counts.end()) {
                counts[T[i]] = 1;
            } else {
                counts[T[i]]++;
            }
        }
        int start = 0;
        int length = 0;
        int total = 0;
        for (int head = 0, tail = 0; tail < S.length(); tail++) {
            auto itTail = counts.find(S[tail]);
            if (counts.find(S[tail]) == counts.end()) {
                // If this character is not present in T at all, 
                // we don't care about this character. 
                continue;
            }
            counts[S[tail]]--;
            // We check if the current character represented by tail caused
            // a character to be included which is relevant to T and is still
            // in deficit. 
            // For example, if T has 3 As, then the first 3 A are relevant to us
            // but the 4th one is not. 
            if (counts[S[tail]] >= 0) {
                total++;
            }
            // check if we have all characters in T covered. 
            if (total == T.size()) {
                // Now move the head pointer till popping out those characters 
                // still makes sure that all characters in T are covered. 
                while (counts.find(S[head]) == counts.end() ||
                    counts[S[head]] < 0) {
                    if (counts.find(S[head]) != counts.end()) counts[S[head]]++;
                    head++;
                }
                // Now [head - 1, tail] is a valid substring. Update the answer.
                if (length == 0 || tail - head + 1 < length) {
                    length = tail - head + 1;
                    start = head;
                }
            }
        }
        return S.substr(start, length);
    }
};

string Solution::my_minWindow(string S, string T)
{
    pair<int,int> result(-1,-1);
    unordered_map<char, int> Scount, Tcount;
    unordered_set<char> missing;
    int ssize = S.size();

    for (auto& t: T)
    {
        ++Tcount[t];
        missing.emplace(t);
    }

    int slow = 0;
    for (int fast = 0; fast < ssize; ++fast)
    {
        char ch = S[fast];
        if (Tcount.find(ch) == Tcount.end()) continue;
        if (++Scount[ch] == Tcount[ch])
            missing.erase(ch);
        if (missing.size()) continue;
        for ( ; slow < fast; ++slow)
        {
            ch = S[slow];
            if (Tcount.find(ch) == Tcount.end()) continue;
            if (--Scount[ch] < Tcount[ch]) break;
        }
        if (result.first < 0 || result.second - result.first > fast - slow)
            result = make_pair(slow, fast);

        missing.emplace(ch);
        ++slow;
    }
    if (result.first < 0)
        return "";
    else
        return S.substr(result.first, result.second - result.first+1);
}

int main()
{
    Solution sol;
    string S, T, result;
  
    S = "ADOBECODEBANC";
    T = "ABC";
    result = sol.minWindow(S, T);
    cout << "Result: " << result << endl;

    return 0;
}

