/*
Max Rectangle in Binary Matrix

Given a 2D binary matrix filled with 0’s and 1’s, find the largest rectangle containing all ones and return its area.

Bonus if you can solve it in O(n^2) or less.


A : [  1 1 1
       0 1 1
       1 0 0 
    ]

Output : 4 

As the max area rectangle is created by the 2x2 rectangle created by (0,1), (0,2), (1,1) and (1,2)
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
    int my_maximalRectangle(vector<vector<int> > &matrix);

    int maximalRectangle(vector<vector<char> > &matrix) {
            int rows = matrix.size();
            if (rows == 0) return 0;
            int cols = matrix[0].size();
            if (cols == 0) return 0;
            //number of consecutive 1s to the left of matrix[i][j], including itself
            vector<vector<int>> max_x(rows, vector<int>(cols, 0));

            int area = 0;
            for (int i = 0; i < rows; i++) { 
                for (int j = 0; j < cols; j++) {
                    if (matrix[i][j] == '1') { 
                        if (j == 0) max_x[i][j] = 1;
                        else max_x[i][j] = max_x[i][j - 1] + 1;
                        int y = 1;
                        int x = cols;
                        while((i - y + 1 >= 0) && (matrix[i - y + 1][j]=='1')) {
                            x = min(x, max_x[i - y + 1][j]);
                            area = max(area, x * y);
                            y++;
                        } 
                    }
                }
            }

            return area;
        }

};

int Solution::my_maximalRectangle(vector<vector<int> > &matrix) {
    int height = matrix.size();
    int width = matrix[0].size();
    vector<vector<int>> max_h(height, vector<int>(width, 0));
    vector<vector<int>> max_w(height, vector<int>(width, 0));

    for (int i = 0; i < width; ++i) {
        max_h[height-1][i] = (matrix[height-1][i] != 0) ? 1 : 0;
        for (int j = height - 2; j >= 0; --j) {
            max_h[j][i] = (matrix[j][i] != 0) ? 1 + max_h[j+1][i] : 0;
        }
    }

    for (int i = 0; i < height; ++i) {
        max_w[i][width-1] = (matrix[i][width-1] != 0) ? 1 : 0;
        for (int j = width - 2; j >= 0; --j) {
            max_w[i][j] = (matrix[i][j] != 0) ? 1 + max_w[i][j+1] : 0;
        }
    }

    int max_area = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int h = max_h[i][j];
            int w = max_w[i][j];
            int area = matrix[i][j] != 0 ? w : 0;
            for (int k = 1; k < h; ++k) {
                if (max_w[i+k][j] < w)
                    w = max_w[i+k][j];
                if (w*(k+1) > area)
                    area = w*(k+1);
            }
            if (area > max_area)
                max_area = area;
        }
    }

    return max_area;
}

int main(int argc, const char* argv[])
{
    Solution sol;

    // Expected: 20
    vector<vector<int>> matrix{ {1, 1, 1}, {0, 1, 1}, {1, 0, 0} };

    // Expected: 21
    /*
    matrix = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0}
    };
    */
    cout << "Result: " << sol.my_maximalRectangle(matrix) << endl;

    return 0;
}

