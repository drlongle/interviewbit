/*
NQueens

The n-queens puzzle is the problem of placing n queens on an nxn chessboard
such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens’ placement
where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]

 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
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
#include <unordered_set>
#include <unordered_map>
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

class Solution {
public:
    vector<vector<string> > my_solveNQueens(int n);

    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > solutions;
        vector<int> solution(n);
        solveNQueensImpl(0, solution, solutions);
        return solutions;
    }
    
    void solveNQueensImpl(int row, vector<int> &solution,
        vector<vector<string> > &solutions) {
        int n = solution.size();
        if (row == n) {
            solutions.push_back(solToStrings(solution));
            return;
        }
        // For each column...
        for (int j = 0; j < n; ++j) {
            // Skip if there is another queen in this column or diagonals
            if (isAvailable(solution, row, j)) {
                solution[row] = j;
                solveNQueensImpl(row + 1, solution, solutions);
            }
        }
    }

    bool isAvailable(const vector<int> &solution, int i, int j) {
        for (int k = 0; k < i; ++k) {
            if (j == solution[k] || i + j == k + solution[k] ||
                i - j == k - solution[k])
                return false;
        }
        return true;
    }

    vector<string> solToStrings(const vector<int>& sol) {
        int n = sol.size();
        vector<string> sol_strings(n);
        for (int i = 0; i < n; ++i) {
            sol_strings[i] = string(n, '.');
            sol_strings[i][sol[i]] = 'Q';
        }
        return sol_strings;
    }
};

void print_board(vector<int>& columns, vector<vector<string> >& result)
{
    vector<string> one_result;
    int nsize = columns.size();
    for (int i = 0; i < nsize; ++i)
    {
        stringstream ss;
        for (int j = 0; j < nsize; ++j)
            ss << ((j == columns[i]) ? 'Q' : '.');
        one_result.emplace_back(ss.str());
    }
    result.emplace_back(one_result);
}

bool has_conflict(vector<int>& columns, int index)
{
    for (int i = 0; i < index; ++i)
    {
        int diff = abs(columns[index]-columns[i]);
        if (diff == 0 || diff == index - i)
            return true;
    }
    return false;
}

void solve_n_queens(vector<int>& columns, int index,
    vector<vector<string> >& result)
{
    int nsize = columns.size();
    for (int i = 0; i < nsize; ++i)
    {
        columns[index] = i;
        if (has_conflict(columns, index))
            continue;
        if (index == nsize -1)
            print_board(columns, result);
        else
            solve_n_queens(columns, index+1, result);
    }
}

vector<vector<string> > Solution::my_solveNQueens(int n)
{
    vector<vector<string> > result;
    vector<int> columns(n);
    solve_n_queens(columns, 0, result);
    
    return result;
}

int main()
{
    Solution sol;
    vector<vector<string> > result;
    int n;
  
    n = 4;
    result = sol.solveNQueens(n);
    for (int i = 0; i < static_cast<int>(result.size()); ++i)
    {
        copy(result[i].begin(), result[i].end(),
            ostream_iterator<string>(cout, "\n"));
        cout << endl;
    }

    return 0;
}

