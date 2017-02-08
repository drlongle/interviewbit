/*
Zigzag String

Write the code that will take a string and make this conversion given a
number of rows:
string convert(string text, int nRows);
convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR"
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
#include <vector>

#define ll long long int
#define ull unsigned long long int

using namespace std;

class Solution {
public:
    string my_convert(string A, int B);

    string convert(string s, int nRows) {
        if (nRows <= 1)
            return s;
    
        const int len = (int)s.length();
        string *str = new string[nRows];
    
        int row = 0, step = 1;
        for (int i = 0; i < len; ++i)
        {
            str[row].push_back(s[i]);
            if (row == 0)
                step = 1;
            else if (row == nRows - 1)
                step = -1;
            row += step;
        }
    
        s.clear();
        for (int j = 0; j < nRows; ++j)
        {
            s.append(str[j]);
        }
    
        return s;
    }
};

string Solution::my_convert(string A, int B) {
    if (B == 1) return A;

    vector<string> strs(B);
    int index = 0;
    bool go_down = true;
    for (size_t i = 0; i < A.size(); ++i) {
        strs[index].push_back(A[i]);
        if (index == B-1) {
            --index;
            go_down = false;
        } else if (!index) {
            ++index;
            go_down = true;
        } else if (go_down)
            ++index;
        else
            --index;
    }

    stringstream ss;
    for (int i = 0; i < B; ++i)
        ss << strs[i];
    return ss.str();
}

int main()
{
    Solution sol;
    string A;
    int B;
  
    A = "PAYPALISHIRING";
    B = 3;
    cout << "Result: " << sol.convert(A,B) << endl;
  
    return 0;
}
