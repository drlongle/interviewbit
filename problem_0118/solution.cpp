/*
Word Search Board

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The cell itself does not count as an adjacent cell. 
The same letter cell may be used more than once.

Example :
Given board =
[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]

word = "ABCCED", -> returns 1,
word = "SEE", -> returns 1,
word = "ABCB", -> returns 1,
word = "ABFSAB" -> returns 1
word = "ABCD" -> returns 0
Note that 1 corresponds to true, and 0 corresponds to false.

Hint: Think recursively.
Say the given word is [1…..N]. If you can match [2…..N] starting at every position of board how it can help you to compute the current answers for every position.

Lets look at the bruteforce approach. 
You iterate over every cell of the matrix to explore if it could be the starting point. Then for every neighboring character which has the same character as the next character in the string, we explore if rest of the string can be formed using that neighbor cell as the starting point.

To sum it up, 
exist(board, word, i , j) is true if for any neighbor (k,l) of (i,j) 
exist(board, word[1:], k, l) is true

Now note that we could memoize the answer for exist(board, word suffix length, i, j).
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
    int my_exist(vector<string> &board, string word);

    bool atleastOneNeighborTrue(vector<vector<int> > &doesExist, int r, int c) {
        if (r > 0 && doesExist[r - 1][c]) return true;
        if (c > 0 && doesExist[r][c - 1]) return true;
        if (r + 1 < doesExist.size() && doesExist[r + 1][c]) return true;
        if (c + 1 < doesExist[0].size() && doesExist[r][c + 1]) return true;
        return false;
    }

    int exist(vector<string> &board, string word) {
        if (0 == word.length())
            return 1;

        int row = board.size();
        if (row == 0) return 0;

        int col = board[0].size();
        if (col == 0) return 0;

        vector<vector<int> > doesExist[2];
        for (int j = 0; j < row; j++) {
            vector<int> temp(col, 0), temp2(col, 0);
            doesExist[0].push_back(temp);
            doesExist[1].push_back(temp2);
        }

        int cur = 0;

        for (int i = 0; i < word.length(); i++) {
            for (int j = 0; j < row; j++) {
                for (int k = 0; k < col; k++) {
                    if (i == 0) {
                        doesExist[cur][j][k] = (word[i] == board[j][k]);
                        continue;
                    }
                    doesExist[cur][j][k] = (word[i] == board[j][k] && atleastOneNeighborTrue(doesExist[1-cur], j, k));
                }
            }
            cur = 1 - cur;
        }
        cur = 1 - cur;
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {
                if (doesExist[cur][j][k]) return 1;
            }
        }
        return 0;
    }
};

struct Entry {
    Entry(int i, int j, int l) : x(i), y(j), len(l) { }
    int x, y, len;
};

int Solution::my_exist(vector<string> &board, string word) {
    int wlen = word.size();
    if (!wlen) return 1;
    int rows = board.size();
    if (!rows) return 0;
    int columns = board[0].size();
    if (!columns) return 0;

    map<pair<int,int>,set<int>> cache;
    queue<Entry> q;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == word[0])
                q.emplace(Entry(i, j, 1));
        }

    vector<pair<int, int>> offsets = {{0,1},{0,-1},{1,0},{-1,0}};
    while (q.size()) {
        Entry e = q.front();
        q.pop();
        if (e.len == wlen)
            return 1;
        for (auto& offset : offsets) {
            int new_x = e.x + offset.first;
            int new_y = e.y + offset.second;
            int new_len = e.len + 1;
            if (new_x >= 0 && new_x < rows && new_y >= 0 && new_y < columns
                && board[new_x][new_y] == word[e.len]) {
                if (cache[{new_x, new_y}].find(new_len) == cache[{new_x, new_y}].end()) {
                    q.emplace(Entry(new_x, new_y, e.len+1));
                    cache[{new_x, new_y}].emplace(new_len);
                }
            }
        }
    }

    return 0;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<string> board, words;

    board = {"ABCE", "SFCS", "ADEE"};
    words = {"ABCCED", "SEE", "ABCB", "ABFSAB", "ABCD"};
    for (auto& word: words)
        cout << word << " -> " << sol.exist(board, word) << endl;

    return 0;
}

