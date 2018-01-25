/*
Word Ladder II

    Total Accepted: 51938
    Total Submissions: 379499
    Difficulty: Hard

Given two words (beginWord and endWord), and a dictionary's word list, find all
shortest transformation sequence(s) from beginWord to endWord, such that:
    Only one letter can be changed at a time
    Each intermediate word must exist in the word list

For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

Note:
    All words have the same length.
    All words contain only lowercase alphabetic characters.

Hint: Think in terms of a graph.

When can you do the transition from one word to another ? Does it mean it can indicate a graph edge between those 2 words ? How can this graph help you to achieve the purpose?

This is a classic shortest path problem.

Think in terms of a graph. You basically need to add an edge between two words which can be converted into one another. Resulting graph will be unweighted and undirected.
Which graph traversal algorithm can now help you in computing the shortest path in undirected, unweighted graph?

Once you know about the shortest path, how do we construct all shortest paths ? 
When will a node x be a parent of node Y ?
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
    vector<vector<string> > my_findLadders(string start, string end, vector<string> &dict);

    void constructPaths(string start, string &end, unordered_map<string, vector<string> > & parents, vector<string> &current, vector<vector<string> > &answer) {
        if (start == end) {
            answer.push_back(current);
            return;
        }
        for (int i = 0; i < parents[start].size(); i++) {
            current.push_back(parents[start][i]);
            constructPaths(parents[start][i], end, parents, current, answer);
            current.pop_back();
        }
        return;
    }

    vector<vector<string> > findLadders(string start, string end, vector<string> &dictV) {
        unordered_set<string> dict(dictV.begin(), dictV.end());
        vector<vector<string> > answer; 
        unordered_map<string, int> distance; // store the distance from start to the current word
        queue<string> q; // FIFO for bfs purpose
        unordered_map<string, vector<string> > parents;
        swap(start, end); // We do this because we construct the path later from end to start 
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
                    if (dict.find(newWord) != dict.end()) {
                        if (distance.find(newWord) == distance.end()) { // seen for the first time
                            distance[newWord] = distance[word] + 1;
                            q.push(newWord);
                            parents[newWord].push_back(word);
                        } else if (distance[newWord] == distance[word] + 1) {
                            parents[newWord].push_back(word);
                        }
                    }
                }
            }
        }
        if (distance.find(end) == distance.end()) return answer; // not found
        // backtrack and construct all possible paths now that we know possible optimal parents.  
        vector<string> current;
        current.push_back(end);
        constructPaths(end, start, parents, current, answer);
        return answer; 
    }
};

struct Entry;
map<string, Entry*> lookup;
int shortest_path;

struct Entry
{
    Entry(string& w, int h) : word(w), hops(h) { }

    vector<vector<string>> get_path()
    {
        vector<vector<string>> res;
        if (hops == 1) {
            vector<string> subres; 
            subres.emplace_back(word);
            res.emplace_back(subres);
        } else {
            for (string pre: prev) {
                vector<vector<string>> subres = lookup[pre]->get_path();
                for (vector<string> li: subres) {
                    li.emplace_back(word);
                    if (static_cast<int>(li.size()) <= shortest_path)
                        res.emplace_back(li);
                }
            }
        }

        return res;
    }
        
    string word;
    set<string> prev;
    int hops;
};


vector<vector<string> > Solution::my_findLadders(string start, string end, vector<string> &dict) {
    vector<vector<string>> res;
    if (start == end)
        return vector<vector<string>>(1, vector<string>(1, start));

    for (auto elem: lookup)
        delete elem.second;
    lookup.clear();
    shortest_path = numeric_limits<int>::max();

    unordered_set<string> words(dict.begin(), dict.end());
    queue<Entry*> queue;
    Entry* entry = new Entry(start, 1);
    lookup[start] = entry;
    queue.emplace(entry);

    while (queue.size())
    {
        Entry* e = queue.front();
        queue.pop();
        if (e->hops+1 > shortest_path)
            break;
        for (size_t i = 0; i < e->word.size(); ++i)
        {
            string word = e->word;
            for (char ch = 'a'; ch <= 'z'; ++ch)
            {
                if (ch == e->word[i])
                    continue;
                word[i] = ch;
                bool word_equal = (word == end);
                if (words.find(word) == words.end() && !word_equal)
                    continue;

                auto it = lookup.find(word);
                Entry* new_entry;
                if (it == lookup.end()) {
                    new_entry = new Entry(word, e->hops+1);
                    lookup[word] = new_entry;
                } else
                    new_entry = it->second;
                if (new_entry->hops <= e->hops||
                    new_entry->prev.find(e->word) != new_entry->prev.end())
                    continue;
                new_entry->prev.emplace(e->word);
                if (word_equal)
                    shortest_path = min(shortest_path, e->hops+1);
                else
                    queue.emplace(new_entry);
            }
        }
    }

    auto it = lookup.find(end);
    if (it != lookup.end())
        return it->second->get_path();

    return res;
}


int main(int argc, const char* argv[])
{
    Solution sol;
    vector<string> dict;
    string start, end;
    vector<vector<string>> res;

    //Expected: [ ["hit","hot","dot","dog","cog"], ["hit","hot","lot","log","cog"] ]
    start = "hit";
    end = "cog";
    dict = {"hot","dot","dog","lot","log"};

    // Expected: [bbaa baaa baba babb ] [bbaa bbba baba babb ] [bbaa bbba bbbb babb ]
    start = "bbaa";
    end = "babb";
    dict = {"baba", "abba", "aaba", "bbbb", "abaa", "abab", "aaab", "abba",
            "abba", "abba", "bbba", "aaab", "abaa", "baba", "baaa"};

    res = sol.findLadders(start, end, dict);
    for (auto& r: res) {
        copy(r.begin(), r.end(), ostream_iterator<string>(cout, ", "));
        cout << endl;
    }

    return 0;
}

