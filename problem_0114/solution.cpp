/*
Word Ladder

Given two words (start and end), and a dictionary, find the length of shortest transformation sequence from start to end, such that:

You must change exactly one character in every transformation
Each intermediate word must exist in the dictionary

Example :
Given:
start = "hit"
end = "cog"
dict = ["hot","dot","dog","lot","log"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note that we account for the length of the transformation path instead of the number of transformation itself.

Note:
  Return 0 if there is no such transformation sequence.
  All words have the same length.
  All words contain only lowercase alphabetic characters.
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
    int my_ladderLength(string start, string end, vector<string> &dictV);

    int ladderLength(string start, string end, vector<string> &dictV) {
        unordered_set<string> dict(dictV.begin(), dictV.end());
        unordered_map<string, int> distance; // store the distancetance from start to the current word
        queue<string> q; // FIFO for bfs purpose
        distance[start] = 1;
        q.push(start);
        while (!q.empty()) {
            string word = q.front(); 
            q.pop();
            if (word == end) break;
            for (int i = 0; i < word.size(); i++) {
                for (int j = 0; j < 26; j++) {
                    string newWord = word;
                    newWord[i] = 'a' + j;
                    if (dict.find(newWord) != dict.end() && distance.find(newWord) == distance.end()) {
                        distance[newWord] = distance[word] + 1;
                        q.push(newWord);
                    }
                }
            }
        }
        if (distance.find(end) == distance.end()) return 0; // not found
        return distance[end];
    }
};

int Solution::my_ladderLength(string start, string end, vector<string> &dictV) {
    unordered_set<string> words;
    for (auto w: dictV)
        words.emplace(w);
    queue<pair<string, int>> queue;
    queue.emplace(make_pair(start, 1));
    if (start == end)
        return 1;
    while (queue.size()) {
        auto node = queue.front();
        queue.pop();
        for (size_t i = 0; i < node.first.size(); ++i) {
            string word = node.first;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                word[i] = ch;
                if (word == node.first) continue;
                if (word == end) return node.second + 1;
                auto it = words.find(word);
                if (it != words.end()) {
                    words.erase(it);
                    queue.emplace(make_pair(word, node.second+1));
                }
            }
        }
    }

    return 0;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<string> dict;
    string start, end;
    int res;

    start = "hit";
    end = "cog";
    dict = {"hot","dot","dog","lot","log"};

    res = sol.ladderLength(start, end, dict);
    cout << "Result: " << res << endl;

    return 0;
}

