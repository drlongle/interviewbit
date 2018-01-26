/*
Black Shapes

Given N * M field of O's and X's, where O=white, X=black
Return the number of black shapes. A black shape consists of one or more adjacent X's (diagonals not included)

Example:
OOOXOOO
OOXXOXO
OXOOOXO

answer is 3 shapes are  :
(i)    X
     X X
(ii)
      X
 (iii)
      X
      X

Note that we are looking for connected shapes here.
For example,
XXX
XXX
XXX
is just one single connected black shape.
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
    int my_black(vector<string> &board);

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int N;
    int M;
    bool is_valid(int x, int y) {
        if(x < 0 || x >= N || y < 0 || y >= M)
            return false;
        return true;
    }

    void bfs(int i, int j, vector<string> &Vec) {
        queue<pair<int, int> > Que;
        Que.push(make_pair(i, j));

        while(!Que.empty()) {
            pair<int, int> P = Que.front();
            Que.pop();
            Vec[P.first][P.second] = 'O';
            for(int i = 0; i < 4; ++i) {
                int x = P.first + dx[i];
                int y = P.second + dy[i];
                if(is_valid(x, y) && Vec[x][y] == 'X') {
                    Que.push(make_pair(x, y));
                }
            }
        }
    }

    int black(vector<string> Vec) {
        N = Vec.size();
        M = Vec[0].size();
        int cnt = 0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < M; ++j) {
                if(Vec[i][j] == 'X') {
                    cnt++;
                    bfs(i, j, Vec);
                }
            }
        }
        return cnt;
    }
};

int Solution::my_black(vector<string> &board) {
    int row = board.size();
    if (!row) return 0;
    int column = board[0].size();
    if (!column) return 0;

    vector<vector<bool>> visited(row, vector<bool>(column, false));
    vector<pair<int, int>> offsets = {{0,1},{0,-1},{1,0},{-1,0}};
    queue<pair<int,int>> q;
    int count = 0;
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j) {
            if (board[i][j] == 'X' && !visited[i][j]) {
                q.emplace(make_pair(i,j));
                visited[i][j] = true;
                ++count;
                while (q.size()) {
                    auto p = q.front();
                    q.pop();
                    for (auto& offset: offsets) {
                        int x = p.first + offset.first;
                        int y = p.second + offset.second;
                        if (x >= 0 && x < row && y >= 0 && y < column &&
                            board[x][y] == 'X' && !visited[x][y]) {
                            q.emplace(make_pair(x,y));
                            visited[x][y] = true;
                        }
                    }
                }
            }
        }

    return count;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<string> board;

    board = {"OOOXOOO", "OOXXOXO", "OXOOOXO"};

    cout << "Result: " << sol.black(board) << endl;

    return 0;
}

