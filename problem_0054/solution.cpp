/*
Substring with Concatenation of All Words
Total Accepted: 55712 Total Submissions: 265964 Difficulty: Hard

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter). 
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
    vector<int> my_findSubstring(string s, const vector<string>& words);
    vector<int> findSubstring(string s, const vector<string>& words);
};

unsigned int myhash(const string &s) {
    unsigned int ret = 0;
    for (int i = 0; i < s.length(); i++) {
        ret = (ret * 100 + s[i]) % 9999997;
    }
    return ret;
}

bool checkSubstring(const string &S, int j, unordered_multiset<string> L) {
    int lsize = L.size(), wsize = L.begin()->size();
    for (int i = 0; i < lsize; i++) {
        if (L.find(S.substr(j + i * wsize, wsize)) == L.end()) return false;
        L.erase(L.find(S.substr(j + i * wsize, wsize)));
    }
    return true;
}

vector<int> Solution::findSubstring(string S, const vector<string> &L) {
    vector<int> ret;
    if (L.empty()) return ret;
    unsigned int hashsum = 0;
    for (int i = 0; i < L.size(); i++) 
        hashsum += myhash(L[i]);

    int wsize = L[0].size(), lsize = L.size();
    for (int i = 0; i < wsize; i++) {
        // In this loop, we will consider all starting positions in S
        // where start % wsize = i.
        vector<unsigned int> hashes;
        int hashsum2 = 0;
        // Calculate the hash of wordsize for all start positions we are
        // considering ( start % wsize = i ) 
        for (int j = i; j < S.size(); j += wsize) {
            hashes.push_back(myhash(S.substr(j, wsize)));
        }
        if (hashes.size() < lsize) continue;
        // Calculare the hashsum of string size lsize * wsize from index i. 
        for (int j = 0; j < lsize; j++) hashsum2 += hashes[j];
        // If hashes are same, very high probability that this is part of
        // our solution. 
        if (hashsum == hashsum2) ret.push_back(i);

        for (int j = lsize; j < hashes.size(); j++) {
            // pop out [i, i + wsize] prefix  and include [j, j+wsize] suffix
            // in our string. In other words, adding new wsize chars. 
            hashsum2  = hashsum2 - hashes[j - lsize] + hashes[j];
            if (hashsum == hashsum2) ret.push_back(i + (j - lsize + 1) * wsize);
        }
    }

    // check the final result
    unordered_multiset<string> Lset(L.begin(), L.end());
    vector<int> ret2;
    for (int i = 0; i < ret.size(); i++) {
        if (checkSubstring(S, ret[i], Lset)) 
            ret2.push_back(ret[i]);
    }

    return ret2;
}


bool has_same_chars(const string& s)
{
    for (size_t i = 0; i < s.size()-1; ++i)
        if (s[i] != s[i+1])
            return false;
    return true;
}

vector<int> Solution::my_findSubstring(string s, const vector<string>& words)
{
    unordered_map<string, pair<int,int>> word_lookup;
    unordered_map<string, pair<int,int>>::iterator lookup_it;
    vector<int> res;

    int ssize = s.size();
    int word_set_size = words.size();
    int wsize = words[0].size();

    for (int i = 0; i < word_set_size; ++i)
        ++word_lookup[words[i]].first;

    int i = 0, word_count = 0;
    while (i <= ssize-wsize)
    {
        string subst = s.substr(i, wsize);
        lookup_it = word_lookup.find(subst);
        if (lookup_it == word_lookup.end())
        {
            i = i-(word_count)*wsize + 1;
            word_count = 0;
            for (auto& w: word_lookup)
                w.second.second = 0;
            continue;
        }

        ++word_count;
        ++lookup_it->second.second;

        if (lookup_it->second.second > lookup_it->second.first)
        {
            i = i-(word_count-1)*wsize + 1;
            word_count = 0;
            for (auto& w: word_lookup)
                w.second.second = 0;
            continue;
        }

        if (word_count == word_set_size)
        {
            res.emplace_back(i-(word_set_size-1)*wsize);
            string first_word = s.substr(i-(word_count-1)*wsize, wsize);
            if (!has_same_chars(first_word))
            {
                --word_lookup[first_word].second;
                --word_count;
                i += wsize;
            }
            else
            {
                i = i-(word_count-1)*wsize + 1;
                word_count = 0;
                for (auto& w: word_lookup)
                    w.second.second = 0;
            }
        }
        else
            i += wsize;
    }

    return res;
}

int main()
{
    Solution sol;
    string s;
    vector<string> words;
    vector<int> res;

    s = "barfoothefoobarman";
    words = {"foo", "bar"};

    // Expected: 6,9,12
    s = "barfoofoobarthefoobarman";
    words = {"bar","foo","the"};

    res = sol.findSubstring(s, words);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, ", "));
    cout << endl;

    return 0;
}

