/*
Capture Regions on Board

Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X
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
    void my_solve(vector<vector<char> > &board);

    void bfsBoundary(vector<vector<char> >& board, int w, int l) {
        int width = board.size();
        int length = board[0].size();
        deque<pair<int, int> > q;
        q.push_back(make_pair(w, l));
        board[w][l] = 'B';
        while (!q.empty()) {
            pair<int, int> cur = q.front();
            q.pop_front();
            pair<int, int> adjs[4] = {
                {cur.first - 1, cur.second}, 
                {cur.first + 1, cur.second}, 
                {cur.first, cur.second - 1},
                {cur.first, cur.second + 1}
            };
            for (int i = 0; i < 4; ++i) {
                int adjW = adjs[i].first;
                int adjL = adjs[i].second;
                if ((adjW >= 0) && (adjW < width) && (adjL >= 0)
                    && (adjL < length) 
                    && (board[adjW][adjL] == 'O')) {
                    q.push_back(make_pair(adjW, adjL));
                    board[adjW][adjL] = 'B';
                }
            }
        }
    }

    /*
     * Use BFS starting from 'O's on the boundary and mark them as 'B', 
     * then iterate over the whole board and mark 'O' as 'X' and 'B' as 'O'.
     */
    void solve(vector<vector<char> > &board) {
        int width = board.size();
        if (width == 0) 
            return;
        int length = board[0].size();
        if  (length == 0) 
            return;

        for (int i = 0; i < length; ++i) {
            if (board[0][i] == 'O')
                bfsBoundary(board, 0, i);

            if (board[width-1][i] == 'O')
                bfsBoundary(board, width - 1, i);
        }

        for (int i = 0; i < width; ++i) {
            if (board[i][0] == 'O')
                bfsBoundary(board, i, 0);
            if (board[i][length - 1] == 'O')
                bfsBoundary(board, i, length - 1);
        }

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < length; ++j) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'B')
                    board[i][j] = 'O';
            }
        }
    }
};

void Solution::my_solve(vector<vector<char> > &board) {
    int rows = board.size();
    if (rows == 0) return;
    int columns = board[0].size();
    if (columns == 0) return;

    queue<pair<int,int>> q;
    for (int i = 0; i < rows; ++i) {
        if (board[i][0] == 'O') {
            board[i][0] = 'o';
            q.emplace(i, 0);
        }
        if (board[i][columns-1] == 'O') {
            board[i][columns-1] = 'o';
            q.emplace(i,columns-1);
        }
    }

    for (int j = 0; j < columns; ++j) {
        if (board[0][j] == 'O') {
            board[0][j] = 'o';
            q.emplace(0,j);
        }
        if (board[rows-1][j] == 'O') {
            board[rows-1][j] = 'o';
            q.emplace(rows-1,j);
        }
    }

    vector<pair<int,int>> offset = { {0,-1}, {0,1}, {1,0}, {-1,0} };
    while (q.size()) {
        auto p = q.front();
        q.pop();
        for (auto off: offset) {
            int x = p.first + off.first;
            int y = p.second + off.second;
            if (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 'O') {
                board[x][y] = 'o';
                q.emplace(x, y);
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == 'O')
                board[i][j] = 'X';
            else if (board[i][j] == 'o')
                board[i][j] = 'O';
        }
    }
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<char>> board;

    board = {{'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}};

    sol.solve(board);
    for (auto& b: board) {
        copy(b.begin(), b.end(), ostream_iterator<char>(cout, ""));
        cout << endl;
    }

    return 0;
}

