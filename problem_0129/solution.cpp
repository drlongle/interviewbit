/*
Queen Attack

On a N * M chessboard, where rows are numbered from 1 to N and columns from 1 to M, there are queens at some cells. Return a N * M array A, where A[i][j] is number of queens that can attack cell (i, j). While calculating answer for cell (i, j), assume there is no queen at that cell.

Notes:

Queen is able to move any number of squares vertically, horizontally or diagonally on a chessboard. A queen cannot jump over another queen to attack a position.
You are given an array of N strings, each of size M. Each character is either a 1 or 0 denoting if there is a queen at that position or not, respectively.
Expected time complexity is worst case O(N*M).

For example,

Let chessboard be,
[0 1 0]
[1 0 0]
[0 0 1]

where a 1 denotes a queen at that position.

Cell (1, 1) is attacked by queens at (2, 1), (1,2) and (3,3).
Cell (1, 2) is attacked by queen at (2, 1). Note that while calculating this, we assume that there is no queen at (1, 2).
Cell (1, 3) is attacked by queens at (3, 3) and (1, 2).
and so on...

Finally, we return matrix
[3, 1, 2]
[1, 3, 3]
[2, 3, 0]

Hint:
If you actually traverse in all 8 directions for each cell, total complexity in the worst case will be O(N*M*(N+M)).
Can you store some data for cells in such a way that for finding an answer to the cell (i, j) you just have to look at its neighbours only?

If you actually traverse in all 8 directions for each cell, total complexity in worst case will be O(N*M*(N+M)).
Can you store some data for cells in such a way that for finding answer to cell (i, j) you just have to look at its neighbours only.

We define f(i, j, k) as a number of queen attacks on the cell (i, j) from direction k. Eight directions can be given numbers 0 to 7.
Now, to see how many attacks are there on a cell (i, j), we go to its neighbour in direction k(say n_i, n_j). If the cell (n_i, n_j) has a queen, then there is just 1 attack. Else, number of attacks is f(n_i, n_j, k).

Can you formulate base cases?

We just have to take the sum of f(i, j, k) for all k=0 to 7 to find the answer for the position (i, j).
The total number of states is O(N*M*8) and the transition is O(1), so total complexity is O(N*M).
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

//dp array
vector<vector<int> > dp[8];

//checks if cell (i, j) is valid or not
bool valid(int i, int j, int n, int m){
    if(i < 0 or i >= n or j < 0 or j >= m)return false;
    return true;
}

//direction vectors
int dir1[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dir2[8] = {0, 1, 1, 1, 0, -1, -1, -1};

//returns dp(i, j, k) as defined in hint
int rec(int i, int j, int k, vector<string> & A, int n, int m){

    //memoisation
    int &ret = dp[k][i][j];
    if(ret != -1)return ret;
    
    ret=0;
    
    //new positions
    int ni = i + dir1[k];
    int nj = j + dir2[k];
    
    //if valid
    if(valid(ni, nj, n, m)){
        if(A[ni][nj] == '1') ret++;
        else ret += rec(ni, nj, k, A, n, m);
    }
    
    return ret;
}

class Solution {
public:
    vector<vector<int> > queenAttack(vector<string> &board);
    vector<vector<int> > my_queenAttack(vector<string> &board);
};

vector<vector<int> > Solution::queenAttack(vector<string> &A) {
    //init dp array
    int n = A.size(), m = A[0].size();
    for(int i = 0; i < 8; i++){
        dp[i].clear();
        dp[i].resize(n, vector<int>(m, -1));
    }

    vector< vector<int> > ret(n, vector<int>(m, 0));

    //calculate dp for all positions
    for(int k = 0; k < 8; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++){
                ret[i][j] += rec(i, j, k, A, n, m);
            }
    return ret;
}

vector<vector<int> > Solution::my_queenAttack(vector<string> &board) {
    int N = board.size();
    if (!N) return vector<vector<int>>(N, vector<int>(0));
    int M = board[0].size();
    vector<vector<int>> res(N, vector<int>(M, 0));
    int x, y;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == '1') {

                x = i-1;
                y = j;
                while (x >= 0) {
                    ++res[x][y];
                    if (board[x--][y] == '1') break;
                }

                x = i+1;
                y = j;
                while (x < N) {
                    ++res[x][y];
                    if (board[x++][y] == '1') break;
                }

                x = i;
                y = j-1;
                while (y >= 0) {
                    ++res[x][y];
                    if (board[x][y--] == '1') break;
                }

                x = i;
                y = j+1;
                while (y < M) {
                    ++res[x][y];
                    if (board[x][y++] == '1') break;
                }

                x = i-1;
                y = j-1;
                while (x >= 0 && y >= 0) {
                    ++res[x][y];
                    if (board[x--][y--] == '1') break;
                }

                x = i-1;
                y = j+1;
                while (x >= 0 && y < M) {
                    ++res[x][y];
                    if (board[x--][y++] == '1') break;
                }

                x = i+1;
                y = j-1;
                while (x < N && y >= 0) {
                    ++res[x][y];
                    if (board[x++][y--] == '1') break;
                }

                x = i+1;
                y = j+1;
                while (x < N && y < M) {
                    ++res[x][y];
                    if (board[x++][y++] == '1') break;
                }
            }
        }
    }

    return res;
}

int main(int argc, const char* argv[])
{
    Solution sol;
    vector<vector<int>> res;
    vector<string> board;

    // Expected: [3, 1, 2], [1, 3, 3], [2, 3, 0]
    board = {"010", "100", "001"};

    // Expected: [3 5 3 ] [5 8 5 ] [3 5 3 ]
    //board = {"111", "111", "111"};

    // Expected: [3 1 2 ] [1 3 3 ] [2 3 0 ]
    //board = {"010", "100", "001"};

    res = sol.queenAttack(board);
    for(auto& v: res) {
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, ", "));
        cout << endl;
    }

    return 0;
}

