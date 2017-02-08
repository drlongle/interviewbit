/*
Matrix Search

Write an efficient algorithm that searches for a value in an m x n matrix.

This matrix has the following properties:
- Integers in each row are sorted from left to right.
- The first integer of each row is greater than or equal to the last integer
of the previous row.

Example:

Consider the following matrix:
[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return 1 ( 1 corresponds to true )

Return 0 / 1 ( 0 if the element is not present, 1 if the element is present )
for this problem
*/

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cstring>
#include <functional>
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

using namespace std;

class Solution {
public:
    int my_searchMatrix(vector<vector<int> > &matrix, int target);

    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        int l = 0, r = m * n - 1;
        while (l != r){
            int mid = (l + r - 1) >> 1;
            if (matrix[mid / m][mid % m] < target)
                l = mid + 1;
            else
                r = mid;
        }
        return matrix[r / m][r % m] == target;
    }
};

int row_size, column_size;
int rowColumnToIndex(int row, int column)
{
    return row*column_size + column;
}

pair<int,int> indexToRowColumn(int index)
{
    int row = index / column_size;
    int column = index - row*column_size;
    return make_pair(row,column);
}

int Solution::my_searchMatrix(vector<vector<int> > &matrix, int target) {
    row_size = matrix.size();
    if (!row_size) return false;
    column_size = matrix[0].size();
    int begin = 0, end = rowColumnToIndex(row_size-1, column_size-1);

    while (begin <= end)
    {
        int mid = begin + ((end-begin) >> 1);
        pair<int,int> index = indexToRowColumn(mid);

        if (matrix[index.first][index.second] == target)
            return true;
        else if (matrix[index.first][index.second] > target)
            end = mid-1;
        else
            begin = mid+1;
    }

    return false;
}

int main()
{
    Solution sol;

    return 0;
}
