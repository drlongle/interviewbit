
#include <algorithm>
#include <array>
#include <bitset>
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

class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
            int dir = 0;
            vector< vector<int> > matrix(n, vector<int> (n, 0));
            int i = 0, j = 0, k = 1;
            while (k <= n * n) {
                matrix[i][j] = k++;
                if (dir == 0){
                    j++;
                    if (j == n || matrix[i][j] != 0) dir = 1, j--, i++;
                } else
                if (dir == 1) {
                    i++;
                    if (i == n || matrix[i][j] != 0) dir = 2, i--, j--;
                } else
                if (dir == 2) {
                    j--;
                    if (j < 0 || matrix[i][j] != 0) dir = 3, j++, i--;
                } else
                if (dir == 3) {
                    i--;
                    if (i < 0 || matrix[i][j] != 0) dir = 0, i++, j++;
                }
            }
            return matrix;
        }
};

int main(int argc, const char* argv[])
{
    Solution sol;

    return 0;
}

